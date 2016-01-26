/*
 * Transform3DAttr.h
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

#ifndef _Transform3DAttr_H
#define _Transform3DAttr_H

#include "booga/base/Value.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/object/Transform3D.h"

class Transform3D;
class RCString;

//______________________________________________________________ Transform3DAttr

class Transform3DAttr : public Transform3D {
declareRTTI(Transform3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Transform3D* transform3d) const = 0;
  // Interface to class Transform3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Transform3D,
  // specifier->setAttribute(transform3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Transform3D
  // object by executing the right method. The corresponding call graph:
  //
  //   transform3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(transform3dObject)
  //           transform3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________________ Transform3DAttrScale

class Transform3DAttrScale : public Transform3DAttr {
declareRTTI(Transform3DAttrScale);
// enable RTTI support

public:
  Transform3DAttrScale(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//_____________________________________________________ Transform3DAttrTranslate

class Transform3DAttrTranslate : public Transform3DAttr {
declareRTTI(Transform3DAttrTranslate);
// enable RTTI support

public:
  Transform3DAttrTranslate(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//________________________________________________________ Transform3DAttrRotate

class Transform3DAttrRotate : public Transform3DAttr {
declareRTTI(Transform3DAttrRotate);
// enable RTTI support

public:
  Transform3DAttrRotate(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//_______________________________________________________ Transform3DAttrRotateX

class Transform3DAttrRotateX : public Transform3DAttr {
declareRTTI(Transform3DAttrRotateX);
// enable RTTI support

public:
  Transform3DAttrRotateX(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//_______________________________________________________ Transform3DAttrRotateY

class Transform3DAttrRotateY : public Transform3DAttr {
declareRTTI(Transform3DAttrRotateY);
// enable RTTI support

public:
  Transform3DAttrRotateY(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//_______________________________________________________ Transform3DAttrRotateZ

class Transform3DAttrRotateZ : public Transform3DAttr {
declareRTTI(Transform3DAttrRotateZ);
// enable RTTI support

public:
  Transform3DAttrRotateZ(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

//________________________________________________________ Transform3DAttrMatrix

class Transform3DAttrMatrix : public Transform3DAttr {
declareRTTI(Transform3DAttrMatrix);
// enable RTTI support

public:
  Transform3DAttrMatrix(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Transform3D* transform3d) const;
};

#endif // _Transform3DAttr_H
