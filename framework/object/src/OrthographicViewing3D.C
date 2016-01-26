/*
 * OrthographicViewing3D.C
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
 *  $Id: OrthographicViewing3D.C,v 1.8 1998/03/26 09:19:27 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>  // std::stringstream

#include "booga/object/OrthographicViewing3D.h"

//________________________________________________________ OrthographicViewing3D

implementRTTI(OrthographicViewing3D, Viewing3D);

OrthographicViewing3D::OrthographicViewing3D()
 : Viewing3D()
{}

OrthographicViewing3D::OrthographicViewing3D(Exemplar)
 : Viewing3D()
{}

Vector3D OrthographicViewing3D::transformWorld2Screen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  Vector3D vp = p*myViewMat;

  vp.x() = myResolutionX*(0.5+vp.x()*myHWVP);
  vp.y() = myResolutionY*(0.5+vp.y()*myHHVP);

  return vp;
}

Vector3D OrthographicViewing3D::transformView2Screen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  return Vector3D(myResolutionX*(0.5+p.x()*myHWVP),
		myResolutionY*(0.5+p.y()*myHHVP),
		p.z());
}

Vector3D OrthographicViewing3D::transformView2NormalScreen(const Vector3D& p) const
{
  return p;
}

void OrthographicViewing3D::computeRayThrough(int x, int y, Ray3D& ray) const
{
  if (myNeedInit)
    buildView();

  if (x < 0 || x >= myResolutionX  || 
      y < 0 || y >= myResolutionY) {
    std::stringstream os;
    os << "[OrthographicViewing3D::computeRayThrough] illegal screen coordinates (" 
       << x << " " << y << ") ignored."
       << " Range is x: [0, " << myResolutionX 
       <<        "], y: [0, " << myResolutionY << "]";
    Report::recoverable(os);
    return;
  }
  ray.setOrigin(myEye + (y-.5*myResolutionY)*myScreenDeltaV + (x-.5*myResolutionX)*myScreenDeltaU);
  ray.setDirection(myDirection);
}

Viewing3D* OrthographicViewing3D::copy() const
{
  return new OrthographicViewing3D(*this);
}

bool OrthographicViewing3D::buildView() const
{
  bool success = Viewing3D::buildView(); // papa's first
  
  if (success) {
    OrthographicViewing3D* This = (OrthographicViewing3D*)this;
    This->myDirection      = (myLookat-myEye).normalized();
    This->myEyePlaneOrigin = myEye;
//		myScreenOrigin -
//            fabs(myDirection^(myEye-myScreenOrigin))*myDirection;
  }
  
  return success;
}

static const RCString orthographicViewing3DKeyword("orthographic");

RCString OrthographicViewing3D::getKeyword() const {
  return orthographicViewing3DKeyword;
}
