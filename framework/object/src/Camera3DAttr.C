/*
 * Camera3DAttr.C
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
#include "booga/object/Camera3DAttr.h"
#include "booga/object/Camera3D.h"

//_________________________________________________________________ Camera3DAttr

implementRTTI(Camera3DAttr, ObjectAttr);

//_______________________________________________________________ Camera3DAttrOn

implementRTTI(Camera3DAttrOn, Camera3DAttr);

Makeable* Camera3DAttrOn::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Camera3DAttrOn(anExemplar);
}

void Camera3DAttrOn::setAttribute(Camera3D* camera3d) const
{
  camera3d->turnOn();
}

//______________________________________________________________ Camera3DAttrOff

implementRTTI(Camera3DAttrOff, Camera3DAttr);

Makeable* Camera3DAttrOff::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Camera3DAttrOff(anExemplar);
}

void Camera3DAttrOff::setAttribute(Camera3D* camera3d) const
{
  camera3d->turnOff();
}

//_______________________________________________________ Camera3DAttrBackground

implementRTTI(Camera3DAttrBackground, Camera3DAttr);

Camera3DAttrBackground::Camera3DAttrBackground(const Color& background)
: myBackground(background)
{}

Makeable* Camera3DAttrBackground::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new Camera3DAttrBackground(Color(value.x(), value.y(), value.z()));
}

void Camera3DAttrBackground::setAttribute(Camera3D* camera3d) const
{
  camera3d->setBackground(myBackground);
}

