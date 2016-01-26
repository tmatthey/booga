/*
 * RoofAttr.h
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

#ifndef _RoofAttr_H
#define _RoofAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Roof;
class RCString;

//_____________________________________________________________________ RoofAttr

class RoofAttr : public ObjectAttr {
declareRTTI(RoofAttr);
// enable RTTI support

public:
  virtual void setAttribute(Roof* roof) const = 0;
  // Interface to class Roof. Whenever setSpecifier(specifier)
  // is called for an instance of class Roof,
  // specifier->setAttribute(roofObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Roof
  // object by executing the right method. The corresponding call graph:
  //
  //   roofObject->setSpecifier(specifier)
  //       specifier->setAttribute(roofObject)
  //           roofObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________________ RoofAttrHeight

class RoofAttrHeight : public RoofAttr {
declareRTTI(RoofAttrHeight);
// enable RTTI support

public:
  RoofAttrHeight(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Roof* roof) const;
  RoofAttrHeight(const Real& height);

private:
  Real myHeight;
};

//_____________________________________________________________ RoofAttrLedgeOff

class RoofAttrLedgeOff : public RoofAttr {
declareRTTI(RoofAttrLedgeOff);
// enable RTTI support

public:
  RoofAttrLedgeOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Roof* roof) const;
};

//______________________________________________________________ RoofAttrLedgeOn

class RoofAttrLedgeOn : public RoofAttr {
declareRTTI(RoofAttrLedgeOn);
// enable RTTI support

public:
  RoofAttrLedgeOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Roof* roof) const;
};

#endif // _RoofAttr_H
