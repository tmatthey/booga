/*
 * WhittedAttr.h
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

#ifndef _WhittedAttr_H
#define _WhittedAttr_H

#include "booga/base/Value.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3DAttr.h"

class Whitted;
class RCString;

//__________________________________________________________________ WhittedAttr

class WhittedAttr : public Texture3DAttr {
declareRTTI(WhittedAttr);
// enable RTTI support

public:
  virtual void setAttribute(Whitted* whitted) const = 0;
  // Interface to class Whitted. Whenever setSpecifier(specifier)
  // is called for an instance of class Whitted,
  // specifier->setAttribute(whittedObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Whitted
  // object by executing the right method. The corresponding call graph:
  //
  //   whittedObject->setSpecifier(specifier)
  //       specifier->setAttribute(whittedObject)
  //           whittedObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________________ WhittedAttrAmbient

class WhittedAttrAmbient : public WhittedAttr {
declareRTTI(WhittedAttrAmbient);
// enable RTTI support

public:
  WhittedAttrAmbient(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Whitted* whitted) const;
  WhittedAttrAmbient(const Color& ambient);

private:
  Color myAmbient;
};

//___________________________________________________________ WhittedAttrDiffuse

class WhittedAttrDiffuse : public WhittedAttr {
declareRTTI(WhittedAttrDiffuse);
// enable RTTI support

public:
  WhittedAttrDiffuse(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Whitted* whitted) const;
  WhittedAttrDiffuse(const Color& diffuse);

private:
  Color myDiffuse;
};

//______________________________________________________ WhittedAttrTransparency

class WhittedAttrTransparency : public WhittedAttr {
declareRTTI(WhittedAttrTransparency);
// enable RTTI support

public:
  WhittedAttrTransparency(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Whitted* whitted) const;
  WhittedAttrTransparency(const Real& transparency);

private:
  Real myTransparency;
};

//______________________________________________________ WhittedAttrReflectivity

class WhittedAttrReflectivity : public WhittedAttr {
declareRTTI(WhittedAttrReflectivity);
// enable RTTI support

public:
  WhittedAttrReflectivity(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Whitted* whitted) const;
  WhittedAttrReflectivity(const Real& reflectivity);

private:
  Real myReflectivity;
};

//___________________________________________________ WhittedAttrRefractionIndex

class WhittedAttrRefractionIndex : public WhittedAttr {
declareRTTI(WhittedAttrRefractionIndex);
// enable RTTI support

public:
  WhittedAttrRefractionIndex(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Whitted* whitted) const;
  WhittedAttrRefractionIndex(const Real& refractionIndex);

private:
  Real myRefractionIndex;
};

#endif // _WhittedAttr_H
