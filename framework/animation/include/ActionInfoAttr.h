/*
 * ActionInfoAttr.h
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

#ifndef _ActionInfoAttr_H
#define _ActionInfoAttr_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"

class ActionInfo;
class RCString;

//_______________________________________________________________ ActionInfoAttr

class ActionInfoAttr : public Makeable {
declareRTTI(ActionInfoAttr);
// enable RTTI support

public:
  virtual void setAttribute(ActionInfo* actioninfo) const = 0;
  // Interface to class ActionInfo. Whenever setSpecifier(specifier)
  // is called for an instance of class ActionInfo,
  // specifier->setAttribute(actioninfoObject) will be called. Method
  // setAttribute has to alter the appropriate member of the ActionInfo
  // object by executing the right method. The corresponding call graph:
  //
  //   actioninfoObject->setSpecifier(specifier)
  //       specifier->setAttribute(actioninfoObject)
  //           actioninfoObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//____________________________________________________ ActionInfoAttrScaleFactor

class ActionInfoAttrScaleFactor : public ActionInfoAttr {
declareRTTI(ActionInfoAttrScaleFactor);
// enable RTTI support

public:
  ActionInfoAttrScaleFactor(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrScaleFactor(const Vector3D& scaleFactor, const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  Vector3D myScaleFactor;
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

//________________________________________________________ ActionInfoAttrCycling

class ActionInfoAttrCycling : public ActionInfoAttr {
declareRTTI(ActionInfoAttrCycling);
// enable RTTI support

public:
  ActionInfoAttrCycling(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrCycling(const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

//_________________________________________________________ ActionInfoAttrCenter

class ActionInfoAttrCenter : public ActionInfoAttr {
declareRTTI(ActionInfoAttrCenter);
// enable RTTI support

public:
  ActionInfoAttrCenter(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrCenter(const Vector3D& center);

private:
  Vector3D myCenter;
};

//______________________________________________________ ActionInfoAttrDirection

class ActionInfoAttrDirection : public ActionInfoAttr {
declareRTTI(ActionInfoAttrDirection);
// enable RTTI support

public:
  ActionInfoAttrDirection(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrDirection(const Vector3D& direction, const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  Vector3D myDirection;
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

//___________________________________________________________ ActionInfoAttrAxis

class ActionInfoAttrAxis : public ActionInfoAttr {
declareRTTI(ActionInfoAttrAxis);
// enable RTTI support

public:
  ActionInfoAttrAxis(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrAxis(const Vector3D& axis);

private:
  Vector3D myAxis;
};

//__________________________________________________________ ActionInfoAttrAlpha

class ActionInfoAttrAlpha : public ActionInfoAttr {
declareRTTI(ActionInfoAttrAlpha);
// enable RTTI support

public:
  ActionInfoAttrAlpha(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrAlpha(const Real& alpha, const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  Real myAlpha;
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

//__________________________________________________________ ActionInfoAttrMorphing

class ActionInfoAttrMorphing : public ActionInfoAttr {
declareRTTI(ActionInfoAttrMorphing);
// enable RTTI support

public:
  ActionInfoAttrMorphing(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrMorphing(const Real& alpha, const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  Real myAlpha;
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

//____________________________________________________ ActionInfoAttrShearFactor

class ActionInfoAttrShearFactor : public ActionInfoAttr {
declareRTTI(ActionInfoAttrShearFactor);
// enable RTTI support

public:
  ActionInfoAttrShearFactor(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(ActionInfo* actioninfo) const;
  ActionInfoAttrShearFactor(const Vector2D& shearFactor, const RCString& functionName, const Real& start, const Real& end, const Real& step);

private:
  Vector2D myShearFactor;
  RCString myFunctionName;
  Real myStart;
  Real myEnd;
  Real myStep;
};

#endif // _ActionInfoAttr_H
