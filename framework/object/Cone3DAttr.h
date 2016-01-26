/*
 * Cone3DAttr.h
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

#ifndef _Cone3DAttr_H
#define _Cone3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Cone3D;
class RCString;

//___________________________________________________________________ Cone3DAttr

class Cone3DAttr : public ObjectAttr {
declareRTTI(Cone3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Cone3D* cone3d) const = 0;
  // Interface to class Cone3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Cone3D,
  // specifier->setAttribute(cone3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Cone3D
  // object by executing the right method. The corresponding call graph:
  //
  //   cone3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(cone3dObject)
  //           cone3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________________ Cone3DAttrOpen

class Cone3DAttrOpen : public Cone3DAttr {
declareRTTI(Cone3DAttrOpen);
// enable RTTI support

public:
  Cone3DAttrOpen(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Cone3D* cone3d) const;
};

//______________________________________________________________ Cone3DAttrClose

class Cone3DAttrClose : public Cone3DAttr {
declareRTTI(Cone3DAttrClose);
// enable RTTI support

public:
  Cone3DAttrClose(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Cone3D* cone3d) const;
};

#endif // _Cone3DAttr_H
