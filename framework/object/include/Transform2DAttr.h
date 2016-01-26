/*
 * Transform2DAttr.h
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

#ifndef _Transform2DAttr_H
#define _Transform2DAttr_H

#include "booga/base/Value.h"
#include "booga/base/TransMatrix2D.h"
#include "booga/object/Transform2D.h"

class Transform2D;
class RCString;

//______________________________________________________________ Transform2DAttr

class Transform2DAttr : public Transform2D {
declareRTTI(Transform2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Transform2D* transform2d) const = 0;
  // Interface to class Transform2D. Whenever setSpecifier(specifier)
  // is called for an instance of class Transform2D,
  // specifier->setAttribute(transform2dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Transform2D
  // object by executing the right method. The corresponding call graph:
  //
  //   transform2dObject->setSpecifier(specifier)
  //       specifier->setAttribute(transform2dObject)
  //           transform2dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________________ Transform2DAttrScale

class Transform2DAttrScale : public Transform2DAttr {
declareRTTI(Transform2DAttrScale);
// enable RTTI support

public:
  Transform2DAttrScale(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform2D* transform2d) const;
};

//_____________________________________________________ Transform2DAttrTranslate

class Transform2DAttrTranslate : public Transform2DAttr {
declareRTTI(Transform2DAttrTranslate);
// enable RTTI support

public:
  Transform2DAttrTranslate(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform2D* transform2d) const;
};

//________________________________________________________ Transform2DAttrRotate

class Transform2DAttrRotate : public Transform2DAttr {
declareRTTI(Transform2DAttrRotate);
// enable RTTI support

public:
  Transform2DAttrRotate(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform2D* transform2d) const;
};

//__________________________________________________ Transform2DAttrRotateOrigin

class Transform2DAttrRotateOrigin : public Transform2DAttr {
declareRTTI(Transform2DAttrRotateOrigin);
// enable RTTI support

public:
  Transform2DAttrRotateOrigin(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform2D* transform2d) const;
};

//________________________________________________________ Transform2DAttrMatrix

class Transform2DAttrMatrix : public Transform2DAttr {
declareRTTI(Transform2DAttrMatrix);
// enable RTTI support

public:
  Transform2DAttrMatrix(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform2D* transform2d) const;
};

#endif // _Transform2DAttr_H
