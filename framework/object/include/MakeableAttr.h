/*
 * MakeableAttr.h
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

#ifndef _MakeableAttr_H
#define _MakeableAttr_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"

class Makeable;
class RCString;

//_________________________________________________________________ MakeableAttr

class MakeableAttr : public Makeable {
declareRTTI(MakeableAttr);
// enable RTTI support

public:
  virtual void setAttribute(Makeable* makeable) const = 0;
  // Interface to class Makeable. Whenever setSpecifier(specifier)
  // is called for an instance of class Makeable,
  // specifier->setAttribute(makeableObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Makeable
  // object by executing the right method. The corresponding call graph:
  //
  //   makeableObject->setSpecifier(specifier)
  //       specifier->setAttribute(makeableObject)
  //           makeableObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ MakeableAttrName

class MakeableAttrName : public MakeableAttr {
declareRTTI(MakeableAttrName);
// enable RTTI support

public:
  MakeableAttrName(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Makeable* makeable) const;
  MakeableAttrName(const RCString& name);

private:
  RCString myName;
};

#endif // _MakeableAttr_H
