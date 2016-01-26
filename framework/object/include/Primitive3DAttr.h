/*
 * Primitive3DAttr.h
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

#ifndef _Primitive3DAttr_H
#define _Primitive3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Primitive3D;
class RCString;

//______________________________________________________________ Primitive3DAttr

class Primitive3DAttr : public ObjectAttr {
declareRTTI(Primitive3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Primitive3D* primitive3d) const = 0;
  // Interface to class Primitive3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Primitive3D,
  // specifier->setAttribute(primitive3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Primitive3D
  // object by executing the right method. The corresponding call graph:
  //
  //   primitive3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(primitive3dObject)
  //           primitive3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________ Primitive3DAttrPrecision

class Primitive3DAttrPrecision : public Primitive3DAttr {
declareRTTI(Primitive3DAttrPrecision);
// enable RTTI support

public:
  Primitive3DAttrPrecision(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Primitive3D* primitive3d) const;
  Primitive3DAttrPrecision(const float& precision);

private:
  float myPrecision;
};

#endif // _Primitive3DAttr_H
