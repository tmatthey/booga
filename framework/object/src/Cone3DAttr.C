/*
 * Cone3DAttr.C
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
#include "booga/object/Cone3DAttr.h"
#include "booga/object/Cone3D.h"

//___________________________________________________________________ Cone3DAttr

implementRTTI(Cone3DAttr, ObjectAttr);

//_______________________________________________________________ Cone3DAttrOpen

implementRTTI(Cone3DAttrOpen, Cone3DAttr);

Makeable* Cone3DAttrOpen::make(RCString& errMsg,
                               const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Cone3DAttrOpen(anExemplar);
}

void Cone3DAttrOpen::setAttribute(Cone3D* cone3d) const
{
  cone3d->open();
}

//______________________________________________________________ Cone3DAttrClose

implementRTTI(Cone3DAttrClose, Cone3DAttr);

Makeable* Cone3DAttrClose::make(RCString& errMsg,
                                const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Cone3DAttrClose(anExemplar);
}

void Cone3DAttrClose::setAttribute(Cone3D* cone3d) const
{
  cone3d->close();
}

