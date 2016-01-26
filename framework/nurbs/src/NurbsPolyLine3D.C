/*
 * $RCSfile: NurbsPolyLine3D.C,v $
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
 *                     University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: NurbsPolyLine3D.C,v 1.5 1996/09/12 13:51:33 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/object/Cylinder3D.h"
#include "booga/object/List3D.h"
#include "booga/nurbs/NurbsPolyLine3D.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//______________________________________________________________ NurbsPolyLine3D

implementRTTI (NurbsPolyLine3D, Nurbs3D);

NurbsPolyLine3D::NurbsPolyLine3D (void)
  : Nurbs3D ()
{
  myPointCount = 0;
  myPoints = NULL;
  myCalculatedFlag = false;
}

NurbsPolyLine3D::NurbsPolyLine3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myPointCount = 0;
  myPoints = NULL;
  myCalculatedFlag = false;
}

NurbsPolyLine3D::NurbsPolyLine3D (PtArray1D *adoptPoints)
  : Nurbs3D (), myPointCount (0), myPoints (NULL)
{
  if (adoptPoints != NULL)
  {
   myPointCount = adoptPoints->getCount ();
   myPoints = adoptPoints;
  }
  myCalculatedFlag = false;
}

NurbsPolyLine3D::NurbsPolyLine3D (const NurbsPolyLine3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsPolyLine3D::~NurbsPolyLine3D (void)
{
  if (myPoints != NULL)
    delete myPoints;
}

NurbsPolyLine3D& NurbsPolyLine3D::operator= (const NurbsPolyLine3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  myPointCount = nrb.myPointCount;
  if (nrb.myPoints != NULL)
    myPoints = new PtArray1D (*nrb.myPoints);
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsPolyLine3D::adoptLinePoints (PtArray1D *points)
{
  if (myPoints != NULL)
    delete myPoints;
  if (points != NULL)
  {
    myPointCount = points->getCount ();
    myPoints = points;
  }
  else
  {
    myPointCount = 0;
    myPoints = NULL;
  }
  myCalculatedFlag = false;
}

void NurbsPolyLine3D::setLinePoint (int pos, const Vector3D &point)
{
  if (pos >= 0 && pos < myPointCount)
  {
    myPoints->set (pos, point);
    myCalculatedFlag = false;
  }
}

void NurbsPolyLine3D::rebuild (void)
{
  if (myCalculatedFlag == false && myPointCount > 0)  // Test if anything has to be done
  {
    register int x;
    Real     step;

    KnotArray *kts = new KnotArray (myPointCount);
    PtArray1D *pts = new PtArray1D (myPointCount);
    WtArray1D *wts = new WtArray1D (myPointCount);

    step = 1 / (myPointCount - 1);
    for (x = 0; x < myPointCount; x++)
    {
      kts->set (x, x*step);                // Setup knot vector {0,...,1} for polyline
      pts->set (x, myPoints->get(x));      // Setup control points
      wts->set (x, 1);                     // Setup weights
    }

    setType (Nurbs3DTypes::Curve);
    adoptKnotsU (new Nurbs3DKnots(1, kts));
    adoptPoints (new Nurbs3DPoints(pts));
    adoptWeights (new Nurbs3DWeights(wts));
    
    myCalculatedFlag = true;             // Signal that I'm done
  }
}

Object3D* NurbsPolyLine3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsPolyLine3D*)this)->rebuild ();

  List3D *cylinders = new List3D;
  Cylinder3D *newCylinder;
  for (int x = 0; x < myPointCount - 1; x++)
  {
    newCylinder = new Cylinder3D(getDiameter(), myPoints->get(x), myPoints->get(x+1));
    newCylinder->setPrecision(getPrecision());
    cylinders->adoptObject(newCylinder);
  }

  cylinders->computeBounds();
  return cylinders;
}

void NurbsPolyLine3D::doComputeBounds (void)
{
  for (int x = 0; x < myPointCount; x++)
    myBounds.expand (myPoints->get(x));
}

Makeable* NurbsPolyLine3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  NurbsPolyLine3D *newPolyLine = new NurbsPolyLine3D (*this);

  PtArray1D *newPoints = new PtArray1D (parameters->count());
  for (int x = 0; x < parameters->count(); x++)
  {
    getParameter (x+1, Vector3D, vector);
    newPoints->set (x, vector);
  }
  newPolyLine->adoptLinePoints (newPoints);       // Adopt points of polyline

  return newPolyLine;
}

/*
 * setAttribute : Set an attribute
 *
 * Used to set an attribute of a Nurbs3DPathAttr object.
 */

void NurbsPolyLine3D::setAttribute (Nurbs3DPathAttr *attr)
{
  rebuild ();
  if (attr != NULL)
    attr->adoptCurve (new Nurbs3D(*this));
}

Object3D* NurbsPolyLine3D::copy (void) const
{
  return new NurbsPolyLine3D (*this);
}

