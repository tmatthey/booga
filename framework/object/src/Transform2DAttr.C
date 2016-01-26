/*
 * Transform2DAttr.C
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
#include "booga/object/Transform2DAttr.h"
#include "booga/object/Transform2D.h"

//______________________________________________________________ Transform2DAttr

implementRTTI(Transform2DAttr, Transform2D);

//_________________________________________________________ Transform2DAttrScale

implementRTTI(Transform2DAttrScale, Transform2DAttr);

Makeable* Transform2DAttrScale::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector2D, scaleFactor);

  return new Transform2D(TransMatrix2D::makeScale(scaleFactor));
}

void Transform2DAttrScale::setAttribute(Transform2D* transform2d) const
{
  transform2d->addTransform(*this);
}

//_____________________________________________________ Transform2DAttrTranslate

implementRTTI(Transform2DAttrTranslate, Transform2DAttr);

Makeable* Transform2DAttrTranslate::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector2D, value);

  return new Transform2D(TransMatrix2D::makeTranslate(value));
}

void Transform2DAttrTranslate::setAttribute(Transform2D* transform2d) const
{
  transform2d->addTransform(*this);
}

//________________________________________________________ Transform2DAttrRotate

implementRTTI(Transform2DAttrRotate, Transform2DAttr);

Makeable* Transform2DAttrRotate::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, angle);

  getParameter(2, Vector2D, axis);

  return new Transform2D(TransMatrix2D::makeRotate(axis, dtor(angle)));
}

void Transform2DAttrRotate::setAttribute(Transform2D* transform2d) const
{
  transform2d->addTransform(*this);
}

//__________________________________________________ Transform2DAttrRotateOrigin

implementRTTI(Transform2DAttrRotateOrigin, Transform2DAttr);

Makeable* Transform2DAttrRotateOrigin::make(RCString& errMsg,
                                            const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, angle);

  return new Transform2D(TransMatrix2D::makeRotateOrigin(dtor(angle)));
}

void Transform2DAttrRotateOrigin::setAttribute(Transform2D* transform2d) const
{
  transform2d->addTransform(*this);
}

//________________________________________________________ Transform2DAttrMatrix

implementRTTI(Transform2DAttrMatrix, Transform2DAttr);

Makeable* Transform2DAttrMatrix::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, TransMatrix2D, value);

  TransMatrix2D inverse = value;
  if (!inverse.invert()) {
    errMsg = "singular transformation matrix";
    return NULL;
  }

  return new Transform2D(value);
}

void Transform2DAttrMatrix::setAttribute(Transform2D* transform2d) const
{
  transform2d->addTransform(*this);
}

