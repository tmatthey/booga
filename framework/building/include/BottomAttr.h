/*
 * BottomAttr.h
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

#ifndef _BottomAttr_H
#define _BottomAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Bottom;
class RCString;

//___________________________________________________________________ BottomAttr

class BottomAttr : public ObjectAttr {
declareRTTI(BottomAttr);
// enable RTTI support

public:
  virtual void setAttribute(Bottom* bottom) const = 0;
  // Interface to class Bottom. Whenever setSpecifier(specifier)
  // is called for an instance of class Bottom,
  // specifier->setAttribute(bottomObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Bottom
  // object by executing the right method. The corresponding call graph:
  //
  //   bottomObject->setSpecifier(specifier)
  //       specifier->setAttribute(bottomObject)
  //           bottomObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ BottomAttrHeight

class BottomAttrHeight : public BottomAttr {
declareRTTI(BottomAttrHeight);
// enable RTTI support

public:
  BottomAttrHeight(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Bottom* bottom) const;
  BottomAttrHeight(const Real& height);

private:
  Real myHeight;
};

#endif // _BottomAttr_H
