/*
 * BuildingObjectAttr.h
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

#ifndef _BuildingObjectAttr_H
#define _BuildingObjectAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class BuildingObject;
class RCString;

//___________________________________________________________ BuildingObjectAttr

class BuildingObjectAttr : public ObjectAttr {
declareRTTI(BuildingObjectAttr);
// enable RTTI support

public:
  virtual void setAttribute(BuildingObject* buildingobject) const = 0;
  // Interface to class BuildingObject. Whenever setSpecifier(specifier)
  // is called for an instance of class BuildingObject,
  // specifier->setAttribute(buildingobjectObject) will be called. Method
  // setAttribute has to alter the appropriate member of the BuildingObject
  // object by executing the right method. The corresponding call graph:
  //
  //   buildingobjectObject->setSpecifier(specifier)
  //       specifier->setAttribute(buildingobjectObject)
  //           buildingobjectObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________________ BuildingObjectAttrOn

class BuildingObjectAttrOn : public BuildingObjectAttr {
declareRTTI(BuildingObjectAttrOn);
// enable RTTI support

public:
  BuildingObjectAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(BuildingObject* buildingobject) const;
};

//________________________________________________________ BuildingObjectAttrOff

class BuildingObjectAttrOff : public BuildingObjectAttr {
declareRTTI(BuildingObjectAttrOff);
// enable RTTI support

public:
  BuildingObjectAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(BuildingObject* buildingobject) const;
};

#endif // _BuildingObjectAttr_H
