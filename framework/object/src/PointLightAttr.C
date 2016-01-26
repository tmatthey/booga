/*
 * PointLightAttr.C
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
#include "booga/object/PointLightAttr.h"
#include "booga/object/PointLight.h"

//_______________________________________________________________ PointLightAttr

implementRTTI(PointLightAttr, ObjectAttr);

//_________________________________________________________ PointLightAttrRadius

implementRTTI(PointLightAttrRadius, PointLightAttr);

PointLightAttrRadius::PointLightAttrRadius(const Real& radius)
: myRadius(radius)
{}

Makeable* PointLightAttrRadius::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new PointLightAttrRadius(value);
}

void PointLightAttrRadius::setAttribute(PointLight* pointlight) const
{
  pointlight->setRadius(myRadius);
}

//_______________________________________________________ PointLightAttrPosition

implementRTTI(PointLightAttrPosition, PointLightAttr);

PointLightAttrPosition::PointLightAttrPosition(const Vector3D& position)
: myPosition(position)
{}

Makeable* PointLightAttrPosition::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);

  return new PointLightAttrPosition(value);
}

void PointLightAttrPosition::setAttribute(PointLight* pointlight) const
{
  pointlight->setPosition(myPosition);
}

