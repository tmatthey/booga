/*
 * Cylinder3DAttr.C
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
#include "booga/object/Cylinder3DAttr.h"
#include "booga/object/Cylinder3D.h"

//_______________________________________________________________ Cylinder3DAttr

implementRTTI(Cylinder3DAttr, ObjectAttr);

//___________________________________________________________ Cylinder3DAttrOpen

implementRTTI(Cylinder3DAttrOpen, Cylinder3DAttr);

Makeable* Cylinder3DAttrOpen::make(RCString& errMsg,
                                   const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Cylinder3DAttrOpen(anExemplar);
}

void Cylinder3DAttrOpen::setAttribute(Cylinder3D* cylinder3d) const
{
  cylinder3d->open();
}

//__________________________________________________________ Cylinder3DAttrClose

implementRTTI(Cylinder3DAttrClose, Cylinder3DAttr);

Makeable* Cylinder3DAttrClose::make(RCString& errMsg,
                                    const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new Cylinder3DAttrClose(anExemplar);
}

void Cylinder3DAttrClose::setAttribute(Cylinder3D* cylinder3d) const
{
  cylinder3d->close();
}

