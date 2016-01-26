/*
 * $RCSfile: NurbsSquare3D.C,v $
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
 *  $Id: NurbsSquare3D.C,v 1.7 1996/09/12 13:51:39 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h" 
#include "booga/base/TransMatrix3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/List3D.h"
#include "booga/nurbs/NurbsSquare3D.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//________________________________________________________________ NurbsSquare3D

implementRTTI (NurbsSquare3D, Nurbs3D);

NurbsSquare3D::NurbsSquare3D (void)
  : Nurbs3D ()
{
  myLength = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsSquare3D::NurbsSquare3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myLength = 1.0;
  myCenter = Vector3D (0, 0, 0);
  myNormal = Vector3D (0, 0, 1);
  myCalculatedFlag = false;
}

NurbsSquare3D::NurbsSquare3D (Real length, const Vector3D &center, const Vector3D &normal)
  : Nurbs3D (), myLength (length), myCenter (center), myNormal (normal)
{
  myCalculatedFlag = false;
}

NurbsSquare3D::NurbsSquare3D (const NurbsSquare3D &nrb)
  : Nurbs3D ()
{
  *this = nrb;
}

NurbsSquare3D& NurbsSquare3D::operator= (const NurbsSquare3D &nrb)
{
  Nurbs3D::reset ();

  setType (nrb.getType());
  setEvaluation (nrb.getEvaluation());
  myLength = nrb.myLength;
  myCenter = nrb.myCenter;
  myNormal = nrb.myNormal;
  myCalculatedFlag = false;
  if (nrb.myCalculatedFlag == true)
    rebuild ();

  return *this;
}

void NurbsSquare3D::setLength (Real length)
{
  if (length != myLength)
  {
    myLength = length;
    myCalculatedFlag = false;
  }
}

void NurbsSquare3D::setCenter (const Vector3D &center)
{
  if (center != myCenter)
  {
    myCenter = center;
    myCalculatedFlag = false;
  }
}

void NurbsSquare3D::setNormal (const Vector3D &normal)
{
  if (normal != myNormal)
  {
    myNormal = normal.normalized ();
    myCalculatedFlag = false;
  }
}

void NurbsSquare3D::rebuild (void)
{
  if (myCalculatedFlag == false)               // Test if anything has to be done
  {
    register int x;
    Real offset = myLength / 2;

    KnotArray *kts = new KnotArray (5);
    PtArray1D *pts = new PtArray1D (5);
    WtArray1D *wts = new WtArray1D (5);

    kts->set (0, 0.00); kts->set (1, 0.25);    // Setup Square with length "myLength"
    kts->set (2, 0.50); kts->set (3, 0.75);    // in xy-plane
    kts->set (4, 1.00);
    pts->set (0, Vector3D(offset, -offset, 0));
    pts->set (1, Vector3D(offset, offset, 0));
    pts->set (2, Vector3D(-offset, offset, 0));
    pts->set (3, Vector3D(-offset, -offset, 0));
    pts->set (4, Vector3D(offset, -offset, 0));
    wts->set (0, 1.0);
    wts->set (1, 1.0);
    wts->set (2, 1.0);
    wts->set (3, 1.0);
    wts->set (4, 1.0);

    if (myNormal != Vector3D(0, 0, 1))       // Circle lies outside xy-plane
    {
      Vector3D axis = myNormal * Vector3D (0, 0, 1);   // Rotation axis
      Real     angle = myNormal ^ Vector3D (0, 0, 1);  // Rotation angle (cos)

      angle = acos (angle);
      TransMatrix3D rotation;

      rotation.rotate (axis, angle);
      for (x = 0; x < 5; x++)
	pts->set (x, myCenter + pts->get(x) * rotation);
    }
    else
      for (x = 0; x < 5; x++)     // Place at center
	pts->set (x, myCenter + pts->get(x));

    setType (Nurbs3DTypes::Curve);
    adoptKnotsU (new Nurbs3DKnots(1, kts));
    adoptPoints (new Nurbs3DPoints(pts));
    adoptWeights (new Nurbs3DWeights(wts));
    
    myCalculatedFlag = true;             // Signal that I'm done
  }
}

Object3D* NurbsSquare3D::createDecomposition (void) const
{
  if (!myCalculatedFlag)
    ((NurbsSquare3D*)this)->rebuild ();

  List3D* newList = new List3D;
  Cylinder3D* newCylinder;

  for (int x = 0; x < 4; x++) {
    newCylinder = new Cylinder3D(getDiameter(), getPoint(x), getPoint(x+1));
    newCylinder->setPrecision(getPrecision());
    newList->adoptObject(newCylinder);
  }
  
  newList->computeBounds();
  
  return newList;
}

void NurbsSquare3D::doComputeBounds (void)
{
  Vector3D e1 = Vector3D (-myLength/2, -myLength/2, 0);  // Edges of square's bb in xy-plane
  Vector3D e2 = Vector3D (-myLength/2, myLength/2, 0);
  Vector3D e3 = Vector3D (myLength/2, -myLength/2, 0);
  Vector3D e4 = Vector3D (myLength/2, myLength/2, 0);

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

Makeable* NurbsSquare3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  checkParameterNumber (3);
  getParameter (1, Real, length);
  getParameter (2, Vector3D, center);
  getParameter (3, Vector3D, normal);

  if (length < EPSILON) {
    errMsg = "degenerate square";
    return NULL;
  }

  NurbsSquare3D *newSquare = new NurbsSquare3D (*this);
  newSquare->setLength (length);
  newSquare->setCenter (center);
  newSquare->setNormal (normal);
  
  return newSquare;
}

/*
 * setAttribute : Set an attribute
 *
 * Used to set an attribute of a Nurbs3DPathAttr object.
 */

void NurbsSquare3D::setAttribute (Nurbs3DPathAttr *attr)
{
  rebuild ();
  if (attr != NULL)
    attr->adoptCurve (new Nurbs3D(*this));
}

Object3D* NurbsSquare3D::copy (void) const
{
  return new NurbsSquare3D (*this);
}

