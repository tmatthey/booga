/*
 * $RCSfile: NurbsLine3D.C,v $
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
 *  $Id: NurbsLine3D.C,v 1.7 1996/09/12 13:51:31 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/object/Cylinder3D.h"
#include "booga/nurbs/NurbsLine3D.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//__________________________________________________________________ NurbsLine3D

implementRTTI (NurbsLine3D, Nurbs3D);

NurbsLine3D::NurbsLine3D (void)
  : Nurbs3D ()
{
  myStart = Vector3D (0, 0, 0);
  myEnd = Vector3D (1, 1, 1);
  myCalculatedFlag = false;
}

NurbsLine3D::NurbsLine3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myStart = Vector3D (0, 0, 0);
  myEnd = Vector3D (1, 1, 1);
  myCalculatedFlag = false;
}

NurbsLine3D::NurbsLine3D (const Vector3D &start, const Vector3D &end)
  : Nurbs3D (), myStart (start), myEnd (end)
{
  myCalculatedFlag = false;
}

NurbsLine3D::NurbsLine3D (const NurbsLine3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsLine3D& NurbsLine3D::operator= (const NurbsLine3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  myStart = nrb.myStart;
  myEnd = nrb.myEnd;
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsLine3D::setStart (const Vector3D &start)
{
  if (start != myStart)
  {
    myStart = start;
    myCalculatedFlag = false;
  }
}

void NurbsLine3D::setEnd (const Vector3D &end)
{
  if (end != myEnd)
  {
    myEnd = end;
    myCalculatedFlag = false;
  }
}

void NurbsLine3D::rebuild (void)
{
  if (myCalculatedFlag == false)               // Test if anything has to be done
  {
    KnotArray *kts = new KnotArray (2);
    PtArray1D *pts = new PtArray1D (2);
    WtArray1D *wts = new WtArray1D (2);

    kts->set (0, 0.00); kts->set (1, 1.00);    // Setup line from "myStart" to "myEnd"
    pts->set (0, myStart);
    pts->set (1, myEnd);
    wts->set (0, 1.0);
    wts->set (1, 1.0);

    setType (Nurbs3DTypes::Curve);
    adoptKnotsU (new Nurbs3DKnots(1, kts));
    adoptPoints (new Nurbs3DPoints(pts));
    adoptWeights (new Nurbs3DWeights(wts));
    
    myCalculatedFlag = true;             // Signal that I'm done
  }
}

Object3D* NurbsLine3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsLine3D*)this)->rebuild ();

  Cylinder3D *newCylinder = new Cylinder3D (getDiameter(), myStart, myEnd);
  newCylinder->setPrecision (getPrecision());
  newCylinder->computeBounds();
  
  return newCylinder;
}

void NurbsLine3D::doComputeBounds (void)
{
  myBounds.expand (myStart);
  myBounds.expand (myEnd);
}

Makeable* NurbsLine3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  checkParameterNumber (2);
  getParameter (1, Vector3D, start);
  getParameter (2, Vector3D, end);

  NurbsLine3D *newLine = new NurbsLine3D (*this);
  newLine->setStart (start);
  newLine->setEnd (end);
  
  return newLine;
}

/*
 * setAttribute : Set an attribute
 *
 * Used to set an attribute of a Nurbs3DPathAttr object.
 */

void NurbsLine3D::setAttribute (Nurbs3DPathAttr *attr)
{
  rebuild ();
  if (attr != NULL)
    attr->adoptCurve (new Nurbs3D(*this));
}

Object3D* NurbsLine3D::copy () const
{
  return new NurbsLine3D (*this);
}

