/*
 * LightSourceAttr.C
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
#include "booga/object/LightSourceAttr.h"
#include "booga/object/LightSource.h"

//______________________________________________________________ LightSourceAttr

implementRTTI(LightSourceAttr, ObjectAttr);

//____________________________________________________________ LightSourceAttrOn

implementRTTI(LightSourceAttrOn, LightSourceAttr);

Makeable* LightSourceAttrOn::make(RCString& errMsg,
                                  const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new LightSourceAttrOn(anExemplar);
}

void LightSourceAttrOn::setAttribute(LightSource* lightsource) const
{
  lightsource->turnOn();
}

//___________________________________________________________ LightSourceAttrOff

implementRTTI(LightSourceAttrOff, LightSourceAttr);

Makeable* LightSourceAttrOff::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new LightSourceAttrOff(anExemplar);
}

void LightSourceAttrOff::setAttribute(LightSource* lightsource) const
{
  lightsource->turnOff();
}

