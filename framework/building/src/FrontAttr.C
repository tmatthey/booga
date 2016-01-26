/*
 * FrontAttr.C
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
#include "booga/building/FrontAttr.h"
#include "booga/building/Front.h"

//____________________________________________________________________ FrontAttr

implementRTTI(FrontAttr, ObjectAttr);

//_____________________________________________________________ FrontAttrWallOff

implementRTTI(FrontAttrWallOff, FrontAttr);

Makeable* FrontAttrWallOff::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FrontAttrWallOff(anExemplar);
}

void FrontAttrWallOff::setAttribute(Front* front) const
{
  front->wallOff();
}

//______________________________________________________________ FrontAttrWallOn

implementRTTI(FrontAttrWallOn, FrontAttr);

Makeable* FrontAttrWallOn::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FrontAttrWallOn(anExemplar);
}

void FrontAttrWallOn::setAttribute(Front* front) const
{
  front->wallOn();
}

