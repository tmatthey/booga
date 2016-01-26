/*
 * Primitive3DAttr.C
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
#include "booga/object/Primitive3DAttr.h"
#include "booga/object/Primitive3D.h"

//______________________________________________________________ Primitive3DAttr

implementRTTI(Primitive3DAttr, ObjectAttr);

//_____________________________________________________ Primitive3DAttrPrecision

implementRTTI(Primitive3DAttrPrecision, Primitive3DAttr);

Primitive3DAttrPrecision::Primitive3DAttrPrecision(const float& precision)
: myPrecision(precision)
{}

Makeable* Primitive3DAttrPrecision::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!((value > -EPSILON))) {
    errMsg = "no negative value allowed";
    return NULL;
  }

  return new Primitive3DAttrPrecision(((value < 0) ? 0 : (float)value));
}

void Primitive3DAttrPrecision::setAttribute(Primitive3D* primitive3d) const
{
  primitive3d->setPrecision(myPrecision);
}

