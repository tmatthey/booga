/*
 * WhittedAttr.C
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
#include "booga/texture/WhittedAttr.h"
#include "booga/texture/Whitted.h"

//__________________________________________________________________ WhittedAttr

implementRTTI(WhittedAttr, Texture3DAttr);

//___________________________________________________________ WhittedAttrAmbient

implementRTTI(WhittedAttrAmbient, WhittedAttr);

WhittedAttrAmbient::WhittedAttrAmbient(const Color& ambient)
: myAmbient(ambient)
{}

Makeable* WhittedAttrAmbient::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new WhittedAttrAmbient(Color(fabs(value.x()), fabs(value.y()), fabs(value.z())));
}

void WhittedAttrAmbient::setAttribute(Whitted* whitted) const
{
  whitted->setAmbient(myAmbient);
}

//___________________________________________________________ WhittedAttrDiffuse

implementRTTI(WhittedAttrDiffuse, WhittedAttr);

WhittedAttrDiffuse::WhittedAttrDiffuse(const Color& diffuse)
: myDiffuse(diffuse)
{}

Makeable* WhittedAttrDiffuse::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new WhittedAttrDiffuse(Color(fabs(value.x()), fabs(value.y()), fabs(value.z())));
}

void WhittedAttrDiffuse::setAttribute(Whitted* whitted) const
{
  whitted->setDiffuse(myDiffuse);
}

//______________________________________________________ WhittedAttrTransparency

implementRTTI(WhittedAttrTransparency, WhittedAttr);

WhittedAttrTransparency::WhittedAttrTransparency(const Real& transparency)
: myTransparency(transparency)
{}

Makeable* WhittedAttrTransparency::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!(value >= 0 && value <= 1)) {
    errMsg = "set transparency within [0..1]";
    return NULL;
  }

  return new WhittedAttrTransparency(value);
}

void WhittedAttrTransparency::setAttribute(Whitted* whitted) const
{
  whitted->setTransparency(myTransparency);
}

//______________________________________________________ WhittedAttrReflectivity

implementRTTI(WhittedAttrReflectivity, WhittedAttr);

WhittedAttrReflectivity::WhittedAttrReflectivity(const Real& reflectivity)
: myReflectivity(reflectivity)
{}

Makeable* WhittedAttrReflectivity::make(RCString& errMsg,
                                        const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!(value >= 0 && value <= 1)) {
    errMsg = "set reflectivity within [0..1]";
    return NULL;
  }

  return new WhittedAttrReflectivity(value);
}

void WhittedAttrReflectivity::setAttribute(Whitted* whitted) const
{
  whitted->setReflectivity(myReflectivity);
}

//___________________________________________________ WhittedAttrRefractionIndex

implementRTTI(WhittedAttrRefractionIndex, WhittedAttr);

WhittedAttrRefractionIndex::WhittedAttrRefractionIndex(const Real& refractionIndex)
: myRefractionIndex(refractionIndex)
{}

Makeable* WhittedAttrRefractionIndex::make(RCString& errMsg,
                                           const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new WhittedAttrRefractionIndex(value);
}

void WhittedAttrRefractionIndex::setAttribute(Whitted* whitted) const
{
  whitted->setRefractionIndex(myRefractionIndex);
}

