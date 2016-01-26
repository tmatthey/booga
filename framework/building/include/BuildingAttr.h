/*
 * $RCSfile: BuildingAttr.h,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 * -----------------------------------------------------------------------------
 *  $Id: BuildingAttr.h,v 1.2 1997/02/20 09:39:57 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BuildingAttr_H
#define _BuildingAttr_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"
#include "booga/building/Building.h"

//_____________________________________________________________ BuildingAttr

class BuildingAttr : public Makeable {
declareRTTI(BuildingAttr);
// enable RTTI support

public:
  virtual void setAttribute(Building* building) const = 0;
  // Interface to class Building. Whenever setSpecifier(specifier)
  // is called for an instance of class Building,
  // specifier->setAttribute(Building) will be called. Method
  // setAttribute has to alter the appropriate member of the Building
  // object by executing the right method. The corresponding call graph:
  //
  //   Building->setSpecifier(specifier)
  //       specifier->setAttribute(Building)
  //           Building->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________ BuildingAttrHole

class BuildingAttrHole : public BuildingAttr {
declareRTTI(BuildingAttrHole);
// enable RTTI support

public:
  BuildingAttrHole(Exemplar){};
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Building* building) const;

private:
  BuildingAttrHole(const List<Vector3D>& vertices);
  BuildingAttrHole(){};

  List <Vector3D> myVertices;
};

//_________________________________________________________ BuildingAttrOn

class BuildingAttrOn : public BuildingAttr {
declareRTTI(BuildingAttrOn);
// enable RTTI support

public:
  BuildingAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Building* building) const;
};

//________________________________________________________ BuildingAttrOff

class BuildingAttrOff : public BuildingAttr {
declareRTTI(BuildingAttrOff);
// enable RTTI support

public:
  BuildingAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Building* building) const;
};

#endif // _BuildingAttr_H
