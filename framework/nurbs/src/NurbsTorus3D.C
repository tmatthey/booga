/*
 * $RCSfile: NurbsTorus3D.C,v $
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
 *  $Id: NurbsTorus3D.C,v 1.7 1996/09/12 13:51:47 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/base/TransMatrix3D.h"
#include "booga/nurbs/NurbsTorus3D.h"
#include "booga/nurbs/NurbsCircle3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

//________________________________________________________________ NurbsTorus3D

implementRTTI (NurbsTorus3D, Nurbs3D);

NurbsTorus3D::NurbsTorus3D (void)
  : Nurbs3D ()
{
  mySweptRadius = 1.0;
  myTubeRadius = 0.1;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsTorus3D::NurbsTorus3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  mySweptRadius = 1.0;
  myTubeRadius = 0.1;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsTorus3D::NurbsTorus3D (Real sweptRadius, Real tubeRadius, const Vector3D &center, const Vector3D &normal)
  : Nurbs3D (), mySweptRadius (sweptRadius), myTubeRadius (tubeRadius), myCenter (center), myNormal (normal)
{
  myCalculatedFlag = false;
}

NurbsTorus3D::NurbsTorus3D (const NurbsTorus3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsTorus3D& NurbsTorus3D::operator= (const NurbsTorus3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  mySweptRadius = nrb.mySweptRadius;
  myTubeRadius = nrb.myTubeRadius;
  myCenter = nrb.myCenter;
  myNormal = nrb.myNormal;
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsTorus3D::setSweptRadius (Real sweptRadius)
{
  if (sweptRadius != mySweptRadius)
  {
    mySweptRadius = sweptRadius;
    myCalculatedFlag = false;
  }
}

void NurbsTorus3D::setTubeRadius (Real tubeRadius)
{
  if (tubeRadius != myTubeRadius)
  {
    myTubeRadius = tubeRadius;
    myCalculatedFlag = false;
  }
}

void NurbsTorus3D::setCenter (const Vector3D &center)
{
  if (center != myCenter)
  {
    myCenter = center;
    myCalculatedFlag = false;
  }
}

void NurbsTorus3D::setNormal (const Vector3D &normal)
{
  if (normal != myNormal)
  {
    myNormal = normal.normalized ();
    myCalculatedFlag = false;
  }
}

void NurbsTorus3D::rebuild (void)
{
  if (myCalculatedFlag == false)               // Test if anything has to be done
  {
    register int x, y;
    NurbsCircle3D *circle = new NurbsCircle3D (myTubeRadius, mySweptRadius*Vector3D(1,0,0), Vector3D(0,1,0));

    circle->rebuild ();                    // Create circle
    Nurbs3DCreator create (circle);
    create.surfaceOfRevolution ();             // Create torus
    Nurbs3D *torus = create.orphanNurbs ();

    Nurbs3DPoints *torusPoints = torus->orphanPoints ();    // Set control points around center
    if (myNormal != Vector3D(0, 0, 1))       // Torus lies outside xy-plane
    {
      Vector3D axis = myNormal * Vector3D (0, 0, 1);   // Rotation axis
      Real     angle = myNormal ^ Vector3D (0, 0, 1);  // Rotation angle (cos)

      angle = acos (angle);
      TransMatrix3D rotation;

      rotation.rotate (axis, angle);
      for (x = 0; x < 9; x++)
	for (y = 0; y < 9; y++)
	  torusPoints->set (x, y, myCenter + torusPoints->get(x, y) * rotation);
    }
    else
      for (x = 0; x < 9; x++)     // Place at center
	for (y = 0; y < 9; y++)
	  torusPoints->set (x, y, myCenter + torusPoints->get(x, y));

    setType (Nurbs3DTypes::Surface);
    adoptKnotsU (torus->orphanKnotsU());
    adoptKnotsV (torus->orphanKnotsV());
    adoptPoints (torusPoints);
    adoptWeights (torus->orphanWeights());
    delete torus;            // Clean up

    myCalculatedFlag = true;
  }
}

Object3D* NurbsTorus3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsTorus3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsTorus3D::doComputeBounds (void)
{
  Vector3D e1 = Vector3D (-mySweptRadius-myTubeRadius, -mySweptRadius-myTubeRadius, -myTubeRadius);
  Vector3D e2 = Vector3D (-mySweptRadius-myTubeRadius, -mySweptRadius-myTubeRadius, +myTubeRadius);
  Vector3D e3 = Vector3D (-mySweptRadius-myTubeRadius, +mySweptRadius+myTubeRadius, -myTubeRadius);
  Vector3D e4 = Vector3D (-mySweptRadius-myTubeRadius, +mySweptRadius+myTubeRadius, +myTubeRadius);
  Vector3D e5 = Vector3D (+mySweptRadius+myTubeRadius, -mySweptRadius-myTubeRadius, -myTubeRadius);
  Vector3D e6 = Vector3D (+mySweptRadius+myTubeRadius, -mySweptRadius-myTubeRadius, +myTubeRadius);
  Vector3D e7 = Vector3D (+mySweptRadius+myTubeRadius, +mySweptRadius+myTubeRadius, -myTubeRadius);
  Vector3D e8 = Vector3D (+mySweptRadius+myTubeRadius, +mySweptRadius+myTubeRadius, +myTubeRadius);

  if (myNormal != Vector3D(0, 0, 1))       // Circle lies outside xy-plane
  {
    Vector3D axis = myNormal * Vector3D (0, 0, 1);   // Rotation axis
    Real     angle = myNormal ^ Vector3D (0, 0, 1);  // Rotation angle (cos)

    angle = acos (angle);
    TransMatrix3D rotation;

    rotation.rotate (axis, angle);
    e1 = e1 * rotation;
    e2 = e2 * rotation;
    e3 = e3 * rotation;
    e4 = e4 * rotation;
    e5 = e5 * rotation;
    e6 = e6 * rotation;
    e7 = e7 * rotation;
    e8 = e8 * rotation;
  }
  myBounds.expand (myCenter+e1);
  myBounds.expand (myCenter+e2);
  myBounds.expand (myCenter+e3);
  myBounds.expand (myCenter+e4);
  myBounds.expand (myCenter+e5);
  myBounds.expand (myCenter+e6);
  myBounds.expand (myCenter+e7);
  myBounds.expand (myCenter+e8);
}

Makeable* NurbsTorus3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  checkParameterNumber(4);
  getParameter (1, Real, sweptRadius);
  getParameter (2, Real, tubeRadius);
  getParameter (3, Vector3D, center);
  getParameter (4, Vector3D, normal);

  if (sweptRadius < EPSILON) {
    errMsg = "degenerate torus";
    return NULL;
  }

  NurbsTorus3D *newTorus = new NurbsTorus3D (*this);
  newTorus->setSweptRadius (sweptRadius);
  newTorus->setTubeRadius (tubeRadius);
  newTorus->setCenter (center);
  newTorus->setNormal (normal);
  
  return newTorus;
}

Object3D* NurbsTorus3D::copy () const
{
  return new NurbsTorus3D (*this);
}

