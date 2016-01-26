/*
 * Primitive2DAttr.h
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

#ifndef _Primitive2DAttr_H
#define _Primitive2DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Primitive2D;
class RCString;

//______________________________________________________________ Primitive2DAttr

class Primitive2DAttr : public ObjectAttr {
declareRTTI(Primitive2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Primitive2D* primitive2d) const = 0;
  // Interface to class Primitive2D. Whenever setSpecifier(specifier)
  // is called for an instance of class Primitive2D,
  // specifier->setAttribute(primitive2dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Primitive2D
  // object by executing the right method. The corresponding call graph:
  //
  //   primitive2dObject->setSpecifier(specifier)
  //       specifier->setAttribute(primitive2dObject)
  //           primitive2dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________ Primitive2DAttrPrecision

class Primitive2DAttrPrecision : public Primitive2DAttr {
declareRTTI(Primitive2DAttrPrecision);
// enable RTTI support

public:
  Primitive2DAttrPrecision(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Primitive2D* primitive2d) const;
  Primitive2DAttrPrecision(const float& precision);

private:
  float myPrecision;
};

#endif // _Primitive2DAttr_H
