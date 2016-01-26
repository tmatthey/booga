/*
 * RoofAttr.C
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
#include "booga/building/RoofAttr.h"
#include "booga/building/Roof.h"

//_____________________________________________________________________ RoofAttr

implementRTTI(RoofAttr, ObjectAttr);

//_______________________________________________________________ RoofAttrHeight

implementRTTI(RoofAttrHeight, RoofAttr);

RoofAttrHeight::RoofAttrHeight(const Real& height)
: myHeight(height)
{}

Makeable* RoofAttrHeight::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new RoofAttrHeight(value);
}

void RoofAttrHeight::setAttribute(Roof* roof) const
{
  roof->setHeight(myHeight);
}

//_____________________________________________________________ RoofAttrLedgeOff

implementRTTI(RoofAttrLedgeOff, RoofAttr);

Makeable* RoofAttrLedgeOff::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new RoofAttrLedgeOff(anExemplar);
}

void RoofAttrLedgeOff::setAttribute(Roof* roof) const
{
  roof->ledgeOff();
}

//______________________________________________________________ RoofAttrLedgeOn

implementRTTI(RoofAttrLedgeOn, RoofAttr);

Makeable* RoofAttrLedgeOn::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new RoofAttrLedgeOn(anExemplar);
}

void RoofAttrLedgeOn::setAttribute(Roof* roof) const
{
  roof->ledgeOn();
}

