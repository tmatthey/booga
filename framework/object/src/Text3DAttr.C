/*
 * Text3DAttr.C
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
#include "booga/object/Text3DAttr.h"
#include "booga/object/Text3D.h"

//___________________________________________________________________ Text3DAttr

implementRTTI(Text3DAttr, ObjectAttr);

//_______________________________________________________________ Text3DAttrFont

implementRTTI(Text3DAttrFont, Text3DAttr);

Text3DAttrFont::Text3DAttrFont(const RCString& font)
: myFont(font)
{}

Makeable* Text3DAttrFont::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, value);

  return new Text3DAttrFont(value);
}

void Text3DAttrFont::setAttribute(Text3D* text3d) const
{
  text3d->setFont(myFont);
}

