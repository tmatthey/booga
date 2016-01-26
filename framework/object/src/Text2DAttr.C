/*
 * Text2DAttr.C
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
#include "booga/object/Text2DAttr.h"
#include "booga/object/Text2D.h"

//___________________________________________________________________ Text2DAttr

implementRTTI(Text2DAttr, ObjectAttr);

//_______________________________________________________________ Text2DAttrFont

implementRTTI(Text2DAttrFont, Text2DAttr);

Text2DAttrFont::Text2DAttrFont(const RCString& font)
: myFont(font)
{}

Makeable* Text2DAttrFont::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, value);

  return new Text2DAttrFont(value);
}

void Text2DAttrFont::setAttribute(Text2D* text2d) const
{
  text2d->setFont(myFont);
}

