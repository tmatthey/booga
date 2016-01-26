/*
 * PolygonMapperAttr.C
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
#include "booga/texture/PolygonMapperAttr.h"
#include "booga/texture/PolygonMapper.h"

//____________________________________________________________ PolygonMapperAttr

implementRTTI(PolygonMapperAttr, Texture3DAttr);

//____________________________________________________ PolygonMapperAttrSpecular

implementRTTI(PolygonMapperAttrSpecular, PolygonMapperAttr);

PolygonMapperAttrSpecular::PolygonMapperAttrSpecular(const Color& specular)
: mySpecular(specular)
{}

Makeable* PolygonMapperAttrSpecular::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new PolygonMapperAttrSpecular(Color(value.x(), value.y(), value.z()));
}

void PolygonMapperAttrSpecular::setAttribute(PolygonMapper* polygonmapper) const
{
  polygonmapper->setSpecular(mySpecular);
}

//_____________________________________________________ PolygonMapperAttrSpecPow

implementRTTI(PolygonMapperAttrSpecPow, PolygonMapperAttr);

PolygonMapperAttrSpecPow::PolygonMapperAttrSpecPow(const int& specPow)
: mySpecPow(specPow)
{}

Makeable* PolygonMapperAttrSpecPow::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!((value >= 1) && (frac(value) == 0))) {
    errMsg = "failed constraint \"(value >= 1) && (frac(value) == 0)\" for 1. argument";
    return NULL;
  }

  return new PolygonMapperAttrSpecPow(int(value));
}

void PolygonMapperAttrSpecPow::setAttribute(PolygonMapper* polygonmapper) const
{
  polygonmapper->setSpecPow(mySpecPow);
}

//________________________________________________ PolygonMapperAttrReflectivity

implementRTTI(PolygonMapperAttrReflectivity, PolygonMapperAttr);

PolygonMapperAttrReflectivity::PolygonMapperAttrReflectivity(const Real& reflectivity)
: myReflectivity(reflectivity)
{}

Makeable* PolygonMapperAttrReflectivity::make(RCString& errMsg,
                                              const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!((value < 1+EPSILON) && (value  > -EPSILON))) {
    errMsg = "failed constraint \"(value < 1+EPSILON) && (value  > -EPSILON)\" for 1. argument";
    return NULL;
  }

  return new PolygonMapperAttrReflectivity(Real(value));
}

void PolygonMapperAttrReflectivity::setAttribute(PolygonMapper* polygonmapper) const
{
  polygonmapper->setReflectivity(myReflectivity);
}

//_____________________________________________________ PolygonMapperAttrAmbient

implementRTTI(PolygonMapperAttrAmbient, PolygonMapperAttr);

PolygonMapperAttrAmbient::PolygonMapperAttrAmbient(const Color& ambient)
: myAmbient(ambient)
{}

Makeable* PolygonMapperAttrAmbient::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);
  if (!(value.x()>-EPSILON && value.y()>-EPSILON && value.z()>-EPSILON)) {
    errMsg = "negative component for color value";
    return NULL;
  }

  return new PolygonMapperAttrAmbient(Color(value.x(), value.y(), value.z()));
}

void PolygonMapperAttrAmbient::setAttribute(PolygonMapper* polygonmapper) const
{
  polygonmapper->setAmbient(myAmbient);
}

