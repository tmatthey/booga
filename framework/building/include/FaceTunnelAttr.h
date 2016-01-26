/*
 * FaceTunnelAttr.h
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

#ifndef _FaceTunnelAttr_H
#define _FaceTunnelAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class FaceTunnel;
class RCString;

//_______________________________________________________________ FaceTunnelAttr

class FaceTunnelAttr : public ObjectAttr {
declareRTTI(FaceTunnelAttr);
// enable RTTI support

public:
  virtual void setAttribute(FaceTunnel* facetunnel) const = 0;
  // Interface to class FaceTunnel. Whenever setSpecifier(specifier)
  // is called for an instance of class FaceTunnel,
  // specifier->setAttribute(facetunnelObject) will be called. Method
  // setAttribute has to alter the appropriate member of the FaceTunnel
  // object by executing the right method. The corresponding call graph:
  //
  //   facetunnelObject->setSpecifier(specifier)
  //       specifier->setAttribute(facetunnelObject)
  //           facetunnelObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________ FaceTunnelAttrNumberOfPoints

class FaceTunnelAttrNumberOfPoints : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrNumberOfPoints);
// enable RTTI support

public:
  FaceTunnelAttrNumberOfPoints(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
  FaceTunnelAttrNumberOfPoints(const Real& numberOfPoints);

private:
  Real myNumberOfPoints;
};

//_______________________________________________ FaceTunnelAttrBezierParameter1

class FaceTunnelAttrBezierParameter1 : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrBezierParameter1);
// enable RTTI support

public:
  FaceTunnelAttrBezierParameter1(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
  FaceTunnelAttrBezierParameter1(const Real& bezierParameter1);

private:
  Real myBezierParameter1;
};

//_______________________________________________ FaceTunnelAttrBezierParameter2

class FaceTunnelAttrBezierParameter2 : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrBezierParameter2);
// enable RTTI support

public:
  FaceTunnelAttrBezierParameter2(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
  FaceTunnelAttrBezierParameter2(const Real& bezierParameter2);

private:
  Real myBezierParameter2;
};

//____________________________________________________ FaceTunnelAttrColumnWidth

class FaceTunnelAttrColumnWidth : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrColumnWidth);
// enable RTTI support

public:
  FaceTunnelAttrColumnWidth(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
  FaceTunnelAttrColumnWidth(const Real& columnWidth);

private:
  Real myColumnWidth;
};

//________________________________________________________ FaceTunnelAttrWallOff

class FaceTunnelAttrWallOff : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrWallOff);
// enable RTTI support

public:
  FaceTunnelAttrWallOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
};

//_________________________________________________________ FaceTunnelAttrWallOn

class FaceTunnelAttrWallOn : public FaceTunnelAttr {
declareRTTI(FaceTunnelAttrWallOn);
// enable RTTI support

public:
  FaceTunnelAttrWallOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceTunnel* facetunnel) const;
};

#endif // _FaceTunnelAttr_H
