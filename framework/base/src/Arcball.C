/*
 * $RCSfile: Arcball.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: Arcball.C,v 1.3 1996/08/04 14:29:24 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Arcball.h"

//____________________________________________________________ Arcball Utilities

/*
 * Convert window coordinates to sphere coordinates. 
 */
static Vector3D mouseOnSphere(Vector3D mouse, Vector3D ballCenter, Real ballRadius)
{
  Vector3D ballMouse((mouse.x() - ballCenter.x()) / ballRadius,
                     (mouse.y() - ballCenter.y()) / ballRadius,
                      0);
  double mag = sqr(ballMouse.x()) + sqr(ballMouse.y());
  if (mag > 1.0) {
    double scale = 1.0/sqrt(mag);
    ballMouse.x() *= scale; 
    ballMouse.y() *= scale;
    ballMouse.z() = 0.0;
  } 
  else {
    ballMouse.z() = sqrt(1 - mag);
  }

  return ballMouse;
}

/*
 * Construct a unit quaternion from two points on unit sphere.
 */
static Quaternion QuaternionFromBallPoints(const Vector3D& from, 
                                           const Vector3D& to)
{
  return Quaternion(from.y()*to.z() - from.z()*to.y(),
                    from.z()*to.x() - from.x()*to.z(),
                    from.x()*to.y() - from.y()*to.x(),
                    from.x()*to.x() + from.y()*to.y() + from.z()*to.z());
}

/* 
 * Convert a unit quaternion to two points on unit sphere.
 */
static void QuaternionToBallPoints(const Quaternion& q, 
                                   Vector3D& arcFrom, Vector3D& arcTo)
{
  double s = sqrt(sqr(q.x()) + sqr(q.y()));

  if (equal(s, 0.0))
    arcFrom = Vector3D(0.0, 1.0, 0.0);
  else
    arcFrom = Vector3D(-q.y()/s, q.x()/s, 0.0);

  arcTo.x() = q.w()*arcFrom.x() - q.z()*arcFrom.y();
  arcTo.y() = q.w()*arcFrom.y() + q.z()*arcFrom.x();
  arcTo.z() = q.x()*arcFrom.y() - q.y()*arcFrom.x();
  if (q.w() < 0.0) 
    arcFrom = Vector3D(-arcFrom.x(), -arcFrom.y(), 0.0);
}

//______________________________________________________________________ Arcball

/*
 * Establish reasonable initial values for controller.
 */
Arcball::Arcball()
{
  myRadius = 1.0;
  myDragging   = false;

  // myAxisSet = Arcball::NoAxes;
  //  mySets[Arcball::CameraAxes] = mId[X]; ball->setSizes[CameraAxes] = 3;
  //  mySets[Arcball::BodyAxes] = ball->mDown[X]; ball->setSizes[BodyAxes] = 3;
  //  mySets[Arcball::OtherAxes] = otherAxis[X]; ball->setSizes[OtherAxes] = 1;
}

void Arcball::place(const Vector3D& center, Real radius)
{
  myCenter = center;
  myRadius = radius;
}

void Arcball::mouse(Real x, Real y)
{
  myVNow.x() = x;
  myVNow.y() = y;
}

void Arcball::useSet(Arcball::AxisSet /* axisSet */)
{
  // if (!myDragging) 
  //  myAxisSet = axisSet;
}

void Arcball::update()
{
  //  int setSize = ball->setSizes[ball->axisSet];
  //  HVect *set = (HVect *)(ball->sets[ball->axisSet]);
  myVFrom = mouseOnSphere(myVDown, myCenter, myRadius);
  myVTo   = mouseOnSphere(myVNow,  myCenter, myRadius);
  if (myDragging) {
  //      if (ball->axisSet!=NoAxes) {
  //          ball->vFrom = ConstrainToAxis(ball->vFrom, set[ball->axisIndex]);
  //          ball->vTo = ConstrainToAxis(ball->vTo, set[ball->axisIndex]);
  //      }
    myQDrag = QuaternionFromBallPoints(myVFrom, myVTo);
    myQNow  = myQDrag * myQDown;
  } else {
  //      if (ball->axisSet!=NoAxes) {
  //          ball->axisIndex = NearestConstraintAxis(ball->vTo, set, setSize);
  //      }
  }

  QuaternionToBallPoints(myQDown, myVrFrom, myVrTo);
  myMNow = myQNow.conjugate();
}

TransMatrix3D Arcball::value() const
{
  return myMNow;
}

void Arcball::beginDrag()
{
  myDragging = true;
  myVDown = myVNow;
}
 
void Arcball::endDrag()
{
  myDragging = false;
  myQDown = myQNow;
  myMDown = myMNow;
}
 






