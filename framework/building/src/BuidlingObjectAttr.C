/*
 * BuildingObjectAttr.C
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
#include "booga/building/BuildingObjectAttr.h"
#include "booga/building/BuildingObject.h"

//___________________________________________________________ BuildingObjectAttr

implementRTTI(BuildingObjectAttr, ObjectAttr);

//_________________________________________________________ BuildingObjectAttrOn

implementRTTI(BuildingObjectAttrOn, BuildingObjectAttr);

Makeable* BuildingObjectAttrOn::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BuildingObjectAttrOn(anExemplar);
}

void BuildingObjectAttrOn::setAttribute(BuildingObject* buildingobject) const
{
  buildingobject->turnOn();
}

//________________________________________________________ BuildingObjectAttrOff

implementRTTI(BuildingObjectAttrOff, BuildingObjectAttr);

Makeable* BuildingObjectAttrOff::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BuildingObjectAttrOff(anExemplar);
}

void BuildingObjectAttrOff::setAttribute(BuildingObject* buildingobject) const
{
  buildingobject->turnOff();
}

