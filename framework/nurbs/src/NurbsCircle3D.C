/*
 * $RCSfile: NurbsCircle3D.C,v $
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
 *  $Id: NurbsCircle3D.C,v 1.7 1996/09/12 13:51:25 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/base/TransMatrix3D.h"
#include "booga/nurbs/NurbsCircle3D.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//________________________________________________________________ NurbsCircle3D

implementRTTI (NurbsCircle3D, Nurbs3D);

NurbsCircle3D::NurbsCircle3D (void)
  : Nurbs3D ()
{
  myRadius = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsCircle3D::NurbsCircle3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myRadius = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsCircle3D::NurbsCircle3D (Real radius, const Vector3D &center, const Vector3D &normal)
  : Nurbs3D (), myRadius (radius), myCenter (center), myNormal (normal)
{
  myCalculatedFlag = false;
}

NurbsCircle3D::NurbsCircle3D (const NurbsCircle3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsCircle3D& NurbsCircle3D::operator= (const NurbsCircle3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  myRadius = nrb.myRadius;
  myCenter = nrb.myCenter;
  myNormal = nrb.myNormal;
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsCircle3D::setRadius (Real radius)
{
  if (radius != myRadius)
  {
    myRadius = radius;
    myCalculatedFlag = false;
  }
}

void NurbsCircle3D::setCenter (const Vector3D &center)
{
  if (center != myCenter)
  {
    myCenter = center;
    myCalculatedFlag = false;
  }
}

void NurbsCircle3D::setNormal (const Vector3D &normal)
{
  if (normal != myNormal)
  {
    myNormal = normal.normalized ();
    myCalculatedFlag = false;
  }
}

void NurbsCircle3D::rebuild (void)
{
  if (myCalculatedFlag == false)               // Test if anything has to be done
  {
    register int x;
    KnotArray *kts = new KnotArray (10);
    PtArray1D *pts = new PtArray1D (9);
    WtArray1D *wts = new WtArray1D (9);

    kts->set (0, 0.00); kts->set (1, 0.00);    // Setup circle with radius "myRadius"
    kts->set (2, 0.25); kts->set (3, 0.25);    // in xy-plane
    kts->set (4, 0.50); kts->set (5, 0.50);
    kts->set (6, 0.75); kts->set (7, 0.75);
    kts->set (8, 1.00); kts->set (9, 1.00);
    pts->set (0, Vector3D(myRadius, 0, 0));
    pts->set (1, Vector3D(myRadius, myRadius, 0));
    pts->set (2, Vector3D(0, myRadius, 0));
    pts->set (3, Vector3D(-myRadius, myRadius, 0));
    pts->set (4, Vector3D(-myRadius, 0, 0));
    pts->set (5, Vector3D(-myRadius, -myRadius, 0));
    pts->set (6, Vector3D(0, -myRadius, 0));
    pts->set (7, Vector3D(myRadius, -myRadius, 0));
    pts->set (8, Vector3D(myRadius, 0, 0));
    wts->set (0, 1.0);
    wts->set (1, 0.707106781);
    wts->set (2, 1.0);
    wts->set (3, 0.707106781);
    wts->set (4, 1.0);
    wts->set (5, 0.707106781);
    wts->set (6, 1.0);
    wts->set (7, 0.707106781);
    wts->set (8, 1.0);

    if (myNormal != Vector3D(0, 0, 1))       // Circle lies outside xy-plane
    {
      Vector3D axis = myNormal * Vector3D (0, 0, 1);   // Rotation axis
      Real     angle = myNormal ^ Vector3D (0, 0, 1);  // Rotation angle (cos)

      angle = acos (angle);
      TransMatrix3D rotation;

      rotation.rotate (axis, angle);
      for (x = 0; x < 9; x++)
	pts->set (x, myCenter + pts->get(x) * rotation);
    }
    else
      for (x = 0; x < 9; x++)     // Place at center
	pts->set (x, myCenter + pts->get(x));

    setType (Nurbs3DTypes::Curve);
    adoptKnotsU (new Nurbs3DKnots(2, kts));
    adoptPoints (new Nurbs3DPoints(pts));
    adoptWeights (new Nurbs3DWeights(wts));
    
    myCalculatedFlag = true;             // Signal that I'm done
  }
}

Object3D* NurbsCircle3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsCircle3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsCircle3D::doComputeBounds (void)
{
  Vector3D e1 = Vector3D (-myRadius, -myRadius, 0);  // Edges of circle's bb in xy-plane
  Vector3D e2 = Vector3D (-myRadius, myRadius, 0);
  Vector3D e3 = Vector3D (myRadius, -myRadius, 0);
  Vector3D e4 = Vector3D (myRadius, myRadius, 0);

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
  }
  myBounds.expand (myCenter+e1);
  myBounds.expand (myCenter+e2);
  myBounds.expand (myCenter+e3);
  myBounds.expand (myCenter+e4);
}

Makeable* NurbsCircle3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  checkParameterNumber (3);
  getParameter (1, Real, radius);
  getParameter (2, Vector3D, center);
  getParameter (3, Vector3D, normal);

  if (radius < EPSILON) {
    errMsg = "degenerate circle";
    return NULL;
  }

  NurbsCircle3D *newCircle = new NurbsCircle3D (*this);
  newCircle->setRadius (radius);
  newCircle->setCenter (center);
  newCircle->setNormal (normal);
  
  return newCircle;
}

/*
 * setAttribute : Set an attribute
 *
 * Used to set an attribute of a Nurbs3DPathAttr object.
 */
void NurbsCircle3D::setAttribute (Nurbs3DPathAttr *attr)
{
  rebuild ();
  if (attr != NULL)
    attr->adoptCurve (new Nurbs3D(*this));
}

Object3D* NurbsCircle3D::copy () const
{
  return new NurbsCircle3D (*this);
}

