/*
 * PhongAttr.C
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
#include "booga/texture/PhongAttr.h"
#include "booga/texture/Phong.h"

//____________________________________________________________________ PhongAttr

implementRTTI(PhongAttr, Texture3DAttr);

//_____________________________________________________________ PhongAttrAmbient

implementRTTI(PhongAttrAmbient, PhongAttr);

PhongAttrAmbient::PhongAttrAmbient(const Color& ambient)
: myAmbient(ambient)
{}

Makeable* PhongAttrAmbient::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new PhongAttrAmbient(Color(value.x(), value.y(), value.z()));
}

void PhongAttrAmbient::setAttribute(Phong* phong) const
{
  phong->setAmbient(myAmbient);
}

//_____________________________________________________________ PhongAttrDiffuse

implementRTTI(PhongAttrDiffuse, PhongAttr);

PhongAttrDiffuse::PhongAttrDiffuse(const Color& diffuse)
: myDiffuse(diffuse)
{}

Makeable* PhongAttrDiffuse::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new PhongAttrDiffuse(Color(value.x(), value.y(), value.z()));
}

void PhongAttrDiffuse::setAttribute(Phong* phong) const
{
  phong->setDiffuse(myDiffuse);
}

//____________________________________________________________ PhongAttrSpecular

implementRTTI(PhongAttrSpecular, PhongAttr);

PhongAttrSpecular::PhongAttrSpecular(const Color& specular)
: mySpecular(specular)
{}

Makeable* PhongAttrSpecular::make(RCString& errMsg,
                                  const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new PhongAttrSpecular(Color(value.x(), value.y(), value.z()));
}

void PhongAttrSpecular::setAttribute(Phong* phong) const
{
  phong->setSpecular(mySpecular);
}

//_____________________________________________________________ PhongAttrSpecPow

implementRTTI(PhongAttrSpecPow, PhongAttr);

PhongAttrSpecPow::PhongAttrSpecPow(const int& specPow)
: mySpecPow(specPow)
{}

Makeable* PhongAttrSpecPow::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!((value >= 1) && (frac(value) == 0))) {
    errMsg = "failed constraint \"(value >= 1) && (frac(value) == 0)\" for 1. argument";
    return NULL;
  }

  return new PhongAttrSpecPow(int(value));
}

void PhongAttrSpecPow::setAttribute(Phong* phong) const
{
  phong->setSpecPow(mySpecPow);
}

