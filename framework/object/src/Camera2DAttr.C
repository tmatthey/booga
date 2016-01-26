/*
 * Camera2DAttr.C
 *
 * Copyright (C) 1994-96, University of Berne, Switzerland
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
 */

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/object/Camera2DAttr.h"
#include "booga/object/Camera2D.h"

//_________________________________________________________________ Camera2DAttr

implementRTTI(Camera2DAttr, ObjectAttr);

//_______________________________________________________ Camera2DAttrResolution

implementRTTI(Camera2DAttrResolution, Camera2DAttr);

Camera2DAttrResolution::Camera2DAttrResolution(const Real& resX, const Real& resY)
: myResX(resX), myResY(resY)
{}

Makeable* Camera2DAttrResolution::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, resX);
  if (!((frac(resX) < EPSILON) && resX >= 1)) {
    Report::warning("expecting integer number (real passed -> converting to int)");
  }

  getParameter(2, Real, resY);
  if (!((frac(resX) < EPSILON) && resX >= 1)) {
    Report::warning("expecting integer number (real passed -> converting to int)");
  }

  return new Camera2DAttrResolution(resX, resY);
}

void Camera2DAttrResolution::setAttribute(Camera2D* camera2d) const
{
  camera2d->getViewing()->setResolution(int(rint(myResX)), int(rint(myResY)));
}

//___________________________________________________________ Camera2DAttrWindow

implementRTTI(Camera2DAttrWindow, Camera2DAttr);

Camera2DAttrWindow::Camera2DAttrWindow(const Vector2D& origin, const Vector2D& resolution)
: myOrigin(origin), myResolution(resolution)
{}

Makeable* Camera2DAttrWindow::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Vector2D, origin);

  getParameter(2, Vector2D, resolution);

  return new Camera2DAttrWindow(origin, resolution);
}

void Camera2DAttrWindow::setAttribute(Camera2D* camera2d) const
{
  camera2d->getViewing()->setWindow(myOrigin, myResolution);
}

//_______________________________________________________________ Camera2DAttrOn

implementRTTI(Camera2DAttrOn, Camera2DAttr);

Makeable* Camera2DAttrOn::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Camera2DAttrOn(anExemplar);
}

void Camera2DAttrOn::setAttribute(Camera2D* camera2d) const
{
  camera2d->turnOn();
}

//______________________________________________________________ Camera2DAttrOff

implementRTTI(Camera2DAttrOff, Camera2DAttr);

Makeable* Camera2DAttrOff::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Camera2DAttrOff(anExemplar);
}

void Camera2DAttrOff::setAttribute(Camera2D* camera2d) const
{
  camera2d->turnOff();
}

//_______________________________________________________ Camera2DAttrBackground

implementRTTI(Camera2DAttrBackground, Camera2DAttr);

Camera2DAttrBackground::Camera2DAttrBackground(const Color& background)
: myBackground(background)
{}

Makeable* Camera2DAttrBackground::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new Camera2DAttrBackground(Color(value.x(), value.y(), value.z()));
}

void Camera2DAttrBackground::setAttribute(Camera2D* camera2d) const
{
  camera2d->setBackground(myBackground);
}

