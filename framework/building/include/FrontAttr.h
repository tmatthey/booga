/*
 * FrontAttr.h
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

#ifndef _FrontAttr_H
#define _FrontAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Front;
class RCString;

//____________________________________________________________________ FrontAttr

class FrontAttr : public ObjectAttr {
declareRTTI(FrontAttr);
// enable RTTI support

public:
  virtual void setAttribute(Front* front) const = 0;
  // Interface to class Front. Whenever setSpecifier(specifier)
  // is called for an instance of class Front,
  // specifier->setAttribute(frontObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Front
  // object by executing the right method. The corresponding call graph:
  //
  //   frontObject->setSpecifier(specifier)
  //       specifier->setAttribute(frontObject)
  //           frontObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ FrontAttrWallOff

class FrontAttrWallOff : public FrontAttr {
declareRTTI(FrontAttrWallOff);
// enable RTTI support

public:
  FrontAttrWallOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Front* front) const;
};

//______________________________________________________________ FrontAttrWallOn

class FrontAttrWallOn : public FrontAttr {
declareRTTI(FrontAttrWallOn);
// enable RTTI support

public:
  FrontAttrWallOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Front* front) const;
};

#endif // _FrontAttr_H
