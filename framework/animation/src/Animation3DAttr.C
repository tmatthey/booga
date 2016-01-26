/*
 * Animation3DAttr.C
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
#include "booga/animation/Animation3DAttr.h"
#include "booga/animation/Animation3D.h"

//______________________________________________________________ Animation3DAttr

implementRTTI(Animation3DAttr, ObjectAttr);

//____________________________________________________________ Animation3DAttrOn

implementRTTI(Animation3DAttrOn, Animation3DAttr);

Makeable* Animation3DAttrOn::make(RCString& errMsg,
                                  const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Animation3DAttrOn(anExemplar);
}

void Animation3DAttrOn::setAttribute(Animation3D* animation3d) const
{
  animation3d->turnOn();
}

//___________________________________________________________ Animation3DAttrOff

implementRTTI(Animation3DAttrOff, Animation3DAttr);

Makeable* Animation3DAttrOff::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Animation3DAttrOff(anExemplar);
}

void Animation3DAttrOff::setAttribute(Animation3D* animation3d) const
{
  animation3d->turnOff();
}

