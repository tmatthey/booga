/*
 * MatteAttr.C
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
#include "booga/texture/MatteAttr.h"
#include "booga/texture/Matte.h"

//____________________________________________________________________ MatteAttr

implementRTTI(MatteAttr, Texture3DAttr);

//_____________________________________________________________ MatteAttrAmbient

implementRTTI(MatteAttrAmbient, MatteAttr);

MatteAttrAmbient::MatteAttrAmbient(const Color& ambient)
: myAmbient(ambient)
{}

Makeable* MatteAttrAmbient::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new MatteAttrAmbient(Color(value.x(), value.y(), value.z()));
}

void MatteAttrAmbient::setAttribute(Matte* matte) const
{
  matte->setAmbient(myAmbient);
}

//_____________________________________________________________ MatteAttrDiffuse

implementRTTI(MatteAttrDiffuse, MatteAttr);

MatteAttrDiffuse::MatteAttrDiffuse(const Color& diffuse)
: myDiffuse(diffuse)
{}

Makeable* MatteAttrDiffuse::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new MatteAttrDiffuse(Color(value.x(), value.y(), value.z()));
}

void MatteAttrDiffuse::setAttribute(Matte* matte) const
{
  matte->setDiffuse(myDiffuse);
}

