/*
 * FaceAttr.C
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
#include "booga/building/FaceAttr.h"
#include "booga/building/Face.h"

//_____________________________________________________________________ FaceAttr

implementRTTI(FaceAttr, ObjectAttr);

//________________________________________________________________ FaceAttrDepth

implementRTTI(FaceAttrDepth, FaceAttr);

FaceAttrDepth::FaceAttrDepth(const Real& depth)
: myDepth(depth)
{}

Makeable* FaceAttrDepth::make(RCString& errMsg,
                              const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceAttrDepth(value);
}

void FaceAttrDepth::setAttribute(Face* face) const
{
  face->setDepth(myDepth);
}

