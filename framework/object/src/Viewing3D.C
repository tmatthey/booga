/*
 * Viewing3D.C
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
 *  $Id: Viewing3D.C,v 1.8 1997/09/19 07:15:15 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <stream.h>
#endif
#include <strstream.h>  // ostrstream

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/Viewing3DAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"
//____________________________________________________________________ Viewing3D

implementRTTI(Viewing3D, Makeable);

Viewing3D::Viewing3D()
: myNeedInit(true), myEye(0,-8,0), myLookat(0,0,0), myUp(0,0,1)
{
  myHFov = dtor(45); 
  myVFov = 0;
  myComputeVFov = true;
  myEyeSeparation = 1;
  myResolutionX = myResolutionY = 512;
}

void Viewing3D::setEye(const Vector3D& eye)
{
  myEye = eye;
  myNeedInit = true;
}

void Viewing3D::setLookat(const Vector3D& lookat)
{
  myLookat = lookat;
  myNeedInit = true;
}

void Viewing3D::setUp(const Vector3D& up)
{
  myUp = up;
  myNeedInit = true;
}

void Viewing3D::setHFov(Real hFov)
{
  myHFov = hFov;
  myNeedInit = true;
}

void Viewing3D::setVFov(Real vFov)
{
  myVFov = vFov;
  myComputeVFov = false;
  myNeedInit = true;
}

void Viewing3D::setFov(Real hFov, Real vFov)
{
  myHFov = hFov;
  if (vFov < 0) {
    myComputeVFov = true;
  }
  else {
    myVFov = vFov;
    myComputeVFov = false;
  }
  myNeedInit = true;
}

Real Viewing3D::getVFov() const
{
  if (myComputeVFov && myNeedInit)
    buildView();
    
  return myVFov;
}

void Viewing3D::setResolution(int resX, int resY)
{
  myResolutionX = resX;
  myResolutionY = resY;
  myNeedInit = true;
}
 
void Viewing3D::setView(const Vector3D& bbMin, const Vector3D& bbMax, 
                        Real zoomFactor, ViewPlane viewPlane)
{
  Real halfWidthX = fabs(0.5*(bbMax.x()-bbMin.x()));
  Real halfWidthY = fabs(0.5*(bbMax.y()-bbMin.y()));
  Real halfHeight = fabs(0.5*(bbMax.z()-bbMin.z()));
  Real distance = 0;
 
  if (myComputeVFov) {
    myVFov = 2*atan(myResolutionY*tan(myHFov/2)/myResolutionX);
  }

  if (viewPlane == AUTOSELECT) {
    if (halfWidthX > halfWidthY) {
      viewPlane = XZ_PLANE;
    } 
    else {
      viewPlane = YZ_PLANE;
    }
  }
  
  switch (viewPlane) {
  case XZ_PLANE :
    // let's look to the xz-plane
    distance = max(zoomFactor*halfWidthX/tan(myHFov/2.), 
		   zoomFactor*halfHeight/tan(myVFov/2.));
    myEye.x() = bbMin.x() + halfWidthX;
    myEye.y() = bbMax.y() + distance;
    myEye.z() = bbMin.z() + halfHeight; 
    setUp(Vector3D(0.,0.,1.));
    break;

  case YZ_PLANE :
    // let's look to the yz-plane
    distance = max(zoomFactor*halfWidthY/tan(myHFov/2.),
		   zoomFactor*halfHeight/tan(myVFov/2.));
    myEye.x() = bbMax.x() + distance;
    myEye.y() = bbMin.y() + halfWidthY;
    myEye.z() = bbMin.z() + halfHeight;
    setUp(Vector3D(0.,0.,1.));
    break;

  case XY_PLANE:
    // let's look to the xy-plane
    distance = max(zoomFactor*halfWidthX/tan(myHFov/2.),
		   zoomFactor*halfWidthY/tan(myVFov/2.));
    myEye.x() = bbMin.x() + halfWidthX;
    myEye.y() = bbMin.y() + halfWidthY;
    myEye.z() = bbMax.z() + distance;
    setUp(Vector3D(0.,1.,0.));
    break;

  default:
    Report::warning("[Viewing3D::setView] illegal view plane, setView failed");
    break;
  }
  myLookat.x() = bbMin.x() + halfWidthX;
  myLookat.y() = bbMin.y() + halfWidthY;
  myLookat.z() = bbMin.z() + halfHeight;

  myNeedInit = true;
}

Vector3D Viewing3D::transformWorld2View(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  return p*myViewMat;
}

Vector3D Viewing3D::transformNormalScreen2Screen(const Vector3D& p) const
{
  if (myNeedInit)
    buildView();

  return Vector3D(myXScreenOffset+myXScreenFactor*p.x(), 
                  myYScreenOffset+myYScreenFactor*p.y(), 
                  p.z());
}

Real Viewing3D::transformNormalScreen2ScreenX(Real x) const
{
  if (myNeedInit)
    buildView();

  return myXScreenOffset+myXScreenFactor*x;
}

Real Viewing3D::transformNormalScreen2ScreenY(Real y) const
{
  if (myNeedInit)
    buildView();

  return myYScreenOffset+myYScreenFactor*y;
}

Vector3D Viewing3D::getScreenDeltaU() const
{
  if (myNeedInit)
    buildView();
  return myScreenDeltaU;
}

Vector3D Viewing3D::getScreenDeltaV() const
{
  if (myNeedInit)
    buildView();
  return myScreenDeltaV;
}

Vector3D Viewing3D::getScreenOrigin() const
{
  if (myNeedInit)
    buildView();
  return myScreenOrigin;
}

bool Viewing3D::buildView() const
{
  //
  // This method alters the *internal* state of the object only ->
  // logical const-ness of 'this' is casted away.
  //
  Viewing3D* This = (Viewing3D*) this;

  Vector3D n, v, u;

  n = myLookat - myEye; 
  if (equal(n.normalize(), 0)) {
    Report::warning("[Viewing3D::buildView] view point and look point are identical");
    return false;
  }

  v = myUp - (n^myUp)*n;

  if (equal(v.normalize(), 0)) {
    Report::warning(RCString("[Viewing3D::buildView] ")
		    + "view and up directions identical?\n" + 
		    form(" eye(%g, %g, %g)\n lookat(%g, %g, %g)\n up(%g, %g, %g)",
			 myEye.x(),    myEye.y(),    myEye.z(),
			 myLookat.x(), myLookat.y(), myLookat.z(),
			 myUp.x(),     myUp.y(),     myUp.z()));
    return false;
  }

  u = n * v; 

  //
  // myComputeVFov indicates, that vFov has to be computed in a way, that
  // the resulting image will not be distorted.
  //
  if (myComputeVFov)
    This->myVFov = 2*atan(myResolutionY*tan(myHFov/2)/myResolutionX);

  This->myHWVP  = 0.5/tan(0.5*myHFov);
  This->myHHVP  = 0.5/tan(0.5*myVFov);
  
  This->myXScreenOffset = 0.5*myResolutionX;
  This->myXScreenFactor = myHWVP*myResolutionX;
  This->myYScreenOffset = 0.5*myResolutionY;
  This->myYScreenFactor = myHHVP*myResolutionY;

  This->myScreenDeltaU = (2*tan(0.5*myHFov)/(Real)myResolutionX)*u;
  This->myScreenDeltaV = (2*tan(0.5*myVFov)/(Real)myResolutionY)*v;
  This->myScreenOrigin = n - (0.5*myResolutionX + 0.5)*myScreenDeltaU 
                           - (0.5*myResolutionY + 0.5)*myScreenDeltaV;

  This->myViewMat = 
    TransMatrix3D( u.x(), v.x(), n.x(),
                   u.y(), v.y(), n.y(),
                   u.z(), v.z(), n.z(),
		-myEye.x()*u.x() - myEye.y()*u.y() - myEye.z()*u.z(),
		-myEye.x()*v.x() - myEye.y()*v.y() - myEye.z()*v.z(),
		-myEye.x()*n.x() - myEye.y()*n.y() - myEye.z()*n.z());

  This->myNeedInit = false;
  return true;
}

int Viewing3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Viewing3D attributes
  Viewing3DAttr* attr = dynamic_cast(Viewing3DAttr, specifier);
  if (attr != NULL) {
    // The Viewing3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Makeable::setSpecifier(errMsg, specifier);
}

Makeable* Viewing3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

void Viewing3D::iterateAttributes(MakeableHandler* handler) {
  DummyMakeable eye("eye", Value(getEye()));
  handler->handle(&eye);
  DummyMakeable lookat("lookat", Value(getLookat()));
  handler->handle(&lookat);
  DummyMakeable up("up", Value(getUp()));
  handler->handle(&up);
  DummyMakeable eyesep("eyesep", Value(getEyeSeparation()));
  handler->handle(&eyesep);
  DummyMakeable resolution("resolution", Value(getResolutionX()));
  resolution.addParameter(Value(getResolutionY()));
  handler->handle(&resolution);
}

ostream& operator<<(ostream& os, const Viewing3D& view)
{
  os << "Eye    : " << view.myEye    << endl
     << "Lookat : " << view.myLookat << endl
     << "Up     : " << view.myUp     << endl
     << "HFov   : " << view.myHFov   << endl
     << "VFov   : " << view.myVFov   << endl
     << "Res    : " << view.myResolutionX << " " << view.myResolutionY << endl;

  return os;
}
