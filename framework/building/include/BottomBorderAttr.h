/*
 * BottomBorderAttr.h
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

#ifndef _BottomBorderAttr_H
#define _BottomBorderAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class BottomBorder;
class RCString;

//_______________________________________________________________ BottomBorderAttr

class BottomBorderAttr : public ObjectAttr {
declareRTTI(BottomBorderAttr);
// enable RTTI support

public:
  virtual void setAttribute(BottomBorder* BottomBorder) const = 0;
  // Interface to class BottomBorder. Whenever setSpecifier(specifier)
  // is called for an instance of class BottomBorder,
  // specifier->setAttribute(BottomBorderObject) will be called. Method
  // setAttribute has to alter the appropriate member of the BottomBorder
  // object by executing the right method. The corresponding call graph:
  //
  //   BottomBorderObject->setSpecifier(specifier)
  //       specifier->setAttribute(BottomBorderObject)
  //           BottomBorderObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________________ BottomBorderAttrOpen

class BottomBorderAttrOpen : public BottomBorderAttr {
declareRTTI(BottomBorderAttrOpen);
// enable RTTI support

public:
  BottomBorderAttrOpen(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(BottomBorder* BottomBorder) const;
};

//__________________________________________________________ BottomBorderAttrClose

class BottomBorderAttrClose : public BottomBorderAttr {
declareRTTI(BottomBorderAttrClose);
// enable RTTI support

public:
  BottomBorderAttrClose(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(BottomBorder* BottomBorder) const;
};

#endif // _BottomBorderAttr_H
