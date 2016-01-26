/*
 * PointLightAttr.h
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

#ifndef _PointLightAttr_H
#define _PointLightAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class PointLight;
class RCString;

//_______________________________________________________________ PointLightAttr

class PointLightAttr : public ObjectAttr {
declareRTTI(PointLightAttr);
// enable RTTI support

public:
  virtual void setAttribute(PointLight* pointlight) const = 0;
  // Interface to class PointLight. Whenever setSpecifier(specifier)
  // is called for an instance of class PointLight,
  // specifier->setAttribute(pointlightObject) will be called. Method
  // setAttribute has to alter the appropriate member of the PointLight
  // object by executing the right method. The corresponding call graph:
  //
  //   pointlightObject->setSpecifier(specifier)
  //       specifier->setAttribute(pointlightObject)
  //           pointlightObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________________ PointLightAttrRadius

class PointLightAttrRadius : public PointLightAttr {
declareRTTI(PointLightAttrRadius);
// enable RTTI support

public:
  PointLightAttrRadius(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PointLight* pointlight) const;
  PointLightAttrRadius(const Real& radius);

private:
  Real myRadius;
};

//_______________________________________________________ PointLightAttrPosition

class PointLightAttrPosition : public PointLightAttr {
declareRTTI(PointLightAttrPosition);
// enable RTTI support

public:
  PointLightAttrPosition(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PointLight* pointlight) const;
  PointLightAttrPosition(const Vector3D& position);

private:
  Vector3D myPosition;
};

#endif // _PointLightAttr_H
