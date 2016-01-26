/*
 * Cylinder3DAttr.h
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

#ifndef _Cylinder3DAttr_H
#define _Cylinder3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Cylinder3D;
class RCString;

//_______________________________________________________________ Cylinder3DAttr

class Cylinder3DAttr : public ObjectAttr {
declareRTTI(Cylinder3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Cylinder3D* cylinder3d) const = 0;
  // Interface to class Cylinder3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Cylinder3D,
  // specifier->setAttribute(cylinder3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Cylinder3D
  // object by executing the right method. The corresponding call graph:
  //
  //   cylinder3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(cylinder3dObject)
  //           cylinder3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________________ Cylinder3DAttrOpen

class Cylinder3DAttrOpen : public Cylinder3DAttr {
declareRTTI(Cylinder3DAttrOpen);
// enable RTTI support

public:
  Cylinder3DAttrOpen(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Cylinder3D* cylinder3d) const;
};

//__________________________________________________________ Cylinder3DAttrClose

class Cylinder3DAttrClose : public Cylinder3DAttr {
declareRTTI(Cylinder3DAttrClose);
// enable RTTI support

public:
  Cylinder3DAttrClose(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Cylinder3D* cylinder3d) const;
};

#endif // _Cylinder3DAttr_H
