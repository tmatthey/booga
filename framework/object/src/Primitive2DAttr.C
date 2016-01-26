/*
 * Primitive2DAttr.C
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
#include "booga/object/Primitive2DAttr.h"
#include "booga/object/Primitive2D.h"

//______________________________________________________________ Primitive2DAttr

implementRTTI(Primitive2DAttr, ObjectAttr);

//_____________________________________________________ Primitive2DAttrPrecision

implementRTTI(Primitive2DAttrPrecision, Primitive2DAttr);

Primitive2DAttrPrecision::Primitive2DAttrPrecision(const float& precision)
: myPrecision(precision)
{}

Makeable* Primitive2DAttrPrecision::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);
  if (!((value > -EPSILON))) {
    errMsg = "no negative value allowed";
    return NULL;
  }

  return new Primitive2DAttrPrecision(((value < 0) ? 0 : (float)value));
}

void Primitive2DAttrPrecision::setAttribute(Primitive2D* primitive2d) const
{
  primitive2d->setPrecision(myPrecision);
}

