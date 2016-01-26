/*
 * LightSourceAttr.h
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

#ifndef _LightSourceAttr_H
#define _LightSourceAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class LightSource;
class RCString;

//______________________________________________________________ LightSourceAttr

class LightSourceAttr : public ObjectAttr {
declareRTTI(LightSourceAttr);
// enable RTTI support

public:
  virtual void setAttribute(LightSource* lightsource) const = 0;
  // Interface to class LightSource. Whenever setSpecifier(specifier)
  // is called for an instance of class LightSource,
  // specifier->setAttribute(lightsourceObject) will be called. Method
  // setAttribute has to alter the appropriate member of the LightSource
  // object by executing the right method. The corresponding call graph:
  //
  //   lightsourceObject->setSpecifier(specifier)
  //       specifier->setAttribute(lightsourceObject)
  //           lightsourceObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//____________________________________________________________ LightSourceAttrOn

class LightSourceAttrOn : public LightSourceAttr {
declareRTTI(LightSourceAttrOn);
// enable RTTI support

public:
  LightSourceAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(LightSource* lightsource) const;
};

//___________________________________________________________ LightSourceAttrOff

class LightSourceAttrOff : public LightSourceAttr {
declareRTTI(LightSourceAttrOff);
// enable RTTI support

public:
  LightSourceAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(LightSource* lightsource) const;
};

#endif // _LightSourceAttr_H
