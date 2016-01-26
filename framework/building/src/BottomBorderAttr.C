/*
 * BottomBorderAttr.C
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
#include "booga/building/BottomBorderAttr.h"
#include "booga/building/BottomBorder.h"

//_______________________________________________________________ BottomBorderAttr

implementRTTI(BottomBorderAttr, ObjectAttr);

//___________________________________________________________ BottomBorderAttrOpen

implementRTTI(BottomBorderAttrOpen, BottomBorderAttr);

Makeable* BottomBorderAttrOpen::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BottomBorderAttrOpen(anExemplar);
}

void BottomBorderAttrOpen::setAttribute(BottomBorder* BottomBorder) const
{
  BottomBorder->open();
}

//__________________________________________________________ BottomBorderAttrClose

implementRTTI(BottomBorderAttrClose, BottomBorderAttr);

Makeable* BottomBorderAttrClose::make(RCString& errMsg,
                                    const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new BottomBorderAttrClose(anExemplar);
}

void BottomBorderAttrClose::setAttribute(BottomBorder* BottomBorder) const
{
  BottomBorder->close();
}

