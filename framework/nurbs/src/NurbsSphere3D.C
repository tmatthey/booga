/*
 * $RCSfile: NurbsSphere3D.C,v $
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
 *  $Id: NurbsSphere3D.C,v 1.7 1996/09/12 13:51:37 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/nurbs/NurbsSphere3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

//________________________________________________________________ NurbsSphere3D

implementRTTI (NurbsSphere3D, Nurbs3D);

NurbsSphere3D::NurbsSphere3D (void)
  : Nurbs3D ()
{
  myRadius = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myCalculatedFlag = false;
}

NurbsSphere3D::NurbsSphere3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myRadius = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myCalculatedFlag = false;
}

NurbsSphere3D::NurbsSphere3D (Real radius, const Vector3D &center)
  : Nurbs3D (), myRadius (radius), myCenter (center)
{
  myCalculatedFlag = false;
}

NurbsSphere3D::NurbsSphere3D (const NurbsSphere3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsSphere3D& NurbsSphere3D::operator= (const NurbsSphere3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  myRadius = nrb.myRadius;
  myCenter = nrb.myCenter;
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsSphere3D::setRadius (Real radius)
{
  if (radius != myRadius)
  {
    myRadius = radius;
    myCalculatedFlag = false;
  }
}

void NurbsSphere3D::setCenter (const Vector3D &center)
{
  if (center != myCenter)
  {
    myCenter = center;
    myCalculatedFlag = false;
  }
}

void NurbsSphere3D::rebuild (void)
{
  if (myCalculatedFlag == false)               // Test if anything has to be done
  {
    KnotArray *kts = new KnotArray (6);
    PtArray1D *pts = new PtArray1D (5);
    WtArray1D *wts = new WtArray1D (5);

    kts->set (0, 0.0); kts->set (1, 0.0);        // Setup semi-circle with radius "myRadius"
    kts->set (2, 0.5); kts->set (3, 0.5);
    kts->set (4, 1.0); kts->set (5, 1.0);
    pts->set (0, Vector3D(0, 0, -myRadius));
    pts->set (1, Vector3D(myRadius, 0, -myRadius));
    pts->set (2, Vector3D(myRadius, 0, 0));
    pts->set (3, Vector3D(myRadius, 0, myRadius));
    pts->set (4, Vector3D(0, 0, myRadius));
    wts->set (0, 1.0);
    wts->set (1, 0.707106781);
    wts->set (2, 1.0);
    wts->set (3, 0.707106781);
    wts->set (4, 1.0);

    Nurbs3D *sphere = new Nurbs3D;  // Create sphere
    sphere->setType (Nurbs3DTypes::Curve);
    sphere->adoptKnotsU (new Nurbs3DKnots(2, kts));
    sphere->adoptPoints (new Nurbs3DPoints(pts));
    sphere->adoptWeights (new Nurbs3DWeights(wts));

    Nurbs3DCreator create (sphere); // Initialize creator
    create.surfaceOfRevolution ();  // Create surface of revolution
    sphere = create.orphanNurbs ();

    Nurbs3DPoints *spherePoints = sphere->orphanPoints ();    // Set control points around center
    for (register int x = 0; x < 5; x++)
      for (register int y = 0; y < 9; y++)
	spherePoints->set (x, y, myCenter + spherePoints->get(x, y));

    setType (Nurbs3DTypes::Surface);
    adoptKnotsU (sphere->orphanKnotsU());
    adoptKnotsV (sphere->orphanKnotsV());
    adoptPoints (spherePoints);
    adoptWeights (sphere->orphanWeights());
    delete sphere;            // Clean up

    myCalculatedFlag = true;             // Signal that I'm done
  }
}

Object3D* NurbsSphere3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsSphere3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsSphere3D::doComputeBounds (void)
{
  myBounds.expand (myCenter[0]-myRadius, myCenter[1]-myRadius, myCenter[2]-myRadius);
  myBounds.expand (myCenter[0]+myRadius, myCenter[1]+myRadius, myCenter[2]+myRadius);
}

Makeable* NurbsSphere3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  checkParameterNumber (2);
  getParameter (1, Real, radius);
  getParameter (2, Vector3D, center);

  if (radius < EPSILON) {
    errMsg = "degenerate sphere";
    return NULL;
  }

  NurbsSphere3D *newSphere = new NurbsSphere3D (*this);
  newSphere->setRadius (radius);
  newSphere->setCenter (center);
  
  return newSphere;
}

Object3D* NurbsSphere3D::copy (void) const
{
  return new NurbsSphere3D (*this);
}

