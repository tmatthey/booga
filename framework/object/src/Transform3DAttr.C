/*
 * Transform3DAttr.C
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
#include "booga/object/Transform3DAttr.h"
#include "booga/object/Transform3D.h"

//______________________________________________________________ Transform3DAttr

implementRTTI(Transform3DAttr, Transform3D);

//_________________________________________________________ Transform3DAttrScale

implementRTTI(Transform3DAttrScale, Transform3DAttr);

Makeable* Transform3DAttrScale::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, scaleFactor);

  return new Transform3D(TransMatrix3D::makeScale(scaleFactor));
}

void Transform3DAttrScale::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//_____________________________________________________ Transform3DAttrTranslate

implementRTTI(Transform3DAttrTranslate, Transform3DAttr);

Makeable* Transform3DAttrTranslate::make(RCString& errMsg,
                                         const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector3D, value);

  return new Transform3D(TransMatrix3D::makeTranslate(value));
}

void Transform3DAttrTranslate::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//________________________________________________________ Transform3DAttrRotate

implementRTTI(Transform3DAttrRotate, Transform3DAttr);

Makeable* Transform3DAttrRotate::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, angle);

  getParameter(2, Vector3D, axis);

  return new Transform3D(TransMatrix3D::makeRotate(axis, dtor(angle)));
}

void Transform3DAttrRotate::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//_______________________________________________________ Transform3DAttrRotateX

implementRTTI(Transform3DAttrRotateX, Transform3DAttr);

Makeable* Transform3DAttrRotateX::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, angle);

  return new Transform3D(TransMatrix3D::makeRotateX(dtor(angle)));
}

void Transform3DAttrRotateX::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//_______________________________________________________ Transform3DAttrRotateY

implementRTTI(Transform3DAttrRotateY, Transform3DAttr);

Makeable* Transform3DAttrRotateY::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, angle);

  return new Transform3D(TransMatrix3D::makeRotateY(dtor(angle)));
}

void Transform3DAttrRotateY::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//_______________________________________________________ Transform3DAttrRotateZ

implementRTTI(Transform3DAttrRotateZ, Transform3DAttr);

Makeable* Transform3DAttrRotateZ::make(RCString& errMsg,
                                       const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, angle);

  return new Transform3D(TransMatrix3D::makeRotateZ(dtor(angle)));
}

void Transform3DAttrRotateZ::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

//________________________________________________________ Transform3DAttrMatrix

implementRTTI(Transform3DAttrMatrix, Transform3DAttr);

Makeable* Transform3DAttrMatrix::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, TransMatrix3D, value);

  TransMatrix3D inverse = value;
  if (!inverse.invert()) {
    errMsg = "singular transformation matrix";
    return NULL;
  }

  return new Transform3D(value);
}

void Transform3DAttrMatrix::setAttribute(Transform3D* transform3d) const
{
  transform3d->addTransform(*this);
}

