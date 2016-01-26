/*
 * PerspectiveViewing3D.h
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: PerspectiveViewing3D.C,v 1.7 1996/10/04 09:47:50 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <strstream.h>  // ostrstream

#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_________________________________________________________ PerspectiveViewing3D

implementRTTI(PerspectiveViewing3D, Viewing3D);

PerspectiveViewing3D::PerspectiveViewing3D()
 : Viewing3D()
{}
 
PerspectiveViewing3D::PerspectiveViewing3D(Exemplar)
 : Viewing3D()
{}

Vector3D PerspectiveViewing3D::transformWorld2Screen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  Vector3D vp = p*myViewMat;

  if (equal(vp.z(), 0)) 
    return Vector3D(0,0,0);

  vp.x() = myResolutionX*(0.5+vp.x()*myHWVP/vp.z());
  vp.y() = myResolutionY*(0.5+vp.y()*myHHVP/vp.z());

  return vp;
}

Vector3D PerspectiveViewing3D::transformView2Screen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  if (equal(p.z(), 0)) 
    return Vector3D(0,0,0);

  return Vector3D(myResolutionX*(0.5+p.x()*myHWVP/p.z()),
		  myResolutionY*(0.5+p.y()*myHHVP/p.z()),
		  p.z());
}

Vector3D PerspectiveViewing3D::transformView2NormalScreen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  if (equal(p.z(), 0)) 
    return Vector3D(0,0,0);

  return Vector3D(p.x()/p.z(), p.y()/p.z(), p.z());
}

void PerspectiveViewing3D::computeRayThrough(int x, int y, Ray3D& ray) const
{
  if (myNeedInit)
    buildView();

  if (x < 0 || x >= myResolutionX  || 
      y < 0 || y >= myResolutionY) {
    ostrstream os;
    os << "[PerspectiveViewing3D::computeRayThrough] illegal screen coordinates (" 
       << x << " " << y << ") ignored."
       << " Range is x: [0, " << myResolutionX 
       <<        "], y: [0, " << myResolutionY << "]";
    Report::recoverable(os);
    return;
  }

  ray.setOrigin(myEye);
  ray.setDirection(myScreenOrigin + y*myScreenDeltaV + x*myScreenDeltaU);
}

Viewing3D* PerspectiveViewing3D::copy() const
{
  return new PerspectiveViewing3D(*this);
}

static const RCString perspectiveViewing3DKeyword("perspective");

RCString PerspectiveViewing3D::getKeyword() const {
  return perspectiveViewing3DKeyword;
}

void PerspectiveViewing3D::iterateAttributes(MakeableHandler *handler) {
  Viewing3D::iterateAttributes(handler);
  DummyMakeable m("fov", Value(rtod(getHFov())));
  handler->handle(&m);
}
