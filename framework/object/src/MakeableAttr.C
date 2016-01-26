/*
 * MakeableAttr.C
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
#include "booga/object/MakeableAttr.h"
#include "booga/object/Makeable.h"

//_________________________________________________________________ MakeableAttr

implementRTTI(MakeableAttr, Makeable);

//_____________________________________________________________ MakeableAttrName

implementRTTI(MakeableAttrName, MakeableAttr);

MakeableAttrName::MakeableAttrName(const RCString& name)
: myName(name)
{}

Makeable* MakeableAttrName::make(RCString& errMsg,
                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, value);

  return new MakeableAttrName(value);
}

void MakeableAttrName::setAttribute(Makeable* makeable) const
{
  makeable->setName(myName);
}

