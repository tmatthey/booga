/*
 * FaceArbourAttr.h
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

#ifndef _FaceArbourAttr_H
#define _FaceArbourAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class FaceArbour;
class RCString;

//_______________________________________________________________ FaceArbourAttr

class FaceArbourAttr : public ObjectAttr {
declareRTTI(FaceArbourAttr);
// enable RTTI support

public:
  virtual void setAttribute(FaceArbour* facearbour) const = 0;
  // Interface to class FaceArbour. Whenever setSpecifier(specifier)
  // is called for an instance of class FaceArbour,
  // specifier->setAttribute(facearbourObject) will be called. Method
  // setAttribute has to alter the appropriate member of the FaceArbour
  // object by executing the right method. The corresponding call graph:
  //
  //   facearbourObject->setSpecifier(specifier)
  //       specifier->setAttribute(facearbourObject)
  //           facearbourObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________ FaceArbourAttrNumberOfPoints

class FaceArbourAttrNumberOfPoints : public FaceArbourAttr {
declareRTTI(FaceArbourAttrNumberOfPoints);
// enable RTTI support

public:
  FaceArbourAttrNumberOfPoints(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrNumberOfPoints(const Real& numberOfPoints);

private:
  Real myNumberOfPoints;
};

//_______________________________________________ FaceArbourAttrBezierParameter1

class FaceArbourAttrBezierParameter1 : public FaceArbourAttr {
declareRTTI(FaceArbourAttrBezierParameter1);
// enable RTTI support

public:
  FaceArbourAttrBezierParameter1(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrBezierParameter1(const Real& bezierParameter1);

private:
  Real myBezierParameter1;
};

//_______________________________________________ FaceArbourAttrBezierParameter2

class FaceArbourAttrBezierParameter2 : public FaceArbourAttr {
declareRTTI(FaceArbourAttrBezierParameter2);
// enable RTTI support

public:
  FaceArbourAttrBezierParameter2(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrBezierParameter2(const Real& bezierParameter2);

private:
  Real myBezierParameter2;
};

//____________________________________________________ FaceArbourAttrColumnDepth

class FaceArbourAttrColumnDepth : public FaceArbourAttr {
declareRTTI(FaceArbourAttrColumnDepth);
// enable RTTI support

public:
  FaceArbourAttrColumnDepth(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrColumnDepth(const Real& columnDepth);

private:
  Real myColumnDepth;
};

//____________________________________________________ FaceArbourAttrColumnWidth

class FaceArbourAttrColumnWidth : public FaceArbourAttr {
declareRTTI(FaceArbourAttrColumnWidth);
// enable RTTI support

public:
  FaceArbourAttrColumnWidth(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrColumnWidth(const Real& columnWidth);

private:
  Real myColumnWidth;
};

//____________________________________________________ FaceArbourAttrArbourDepth

class FaceArbourAttrArbourDepth : public FaceArbourAttr {
declareRTTI(FaceArbourAttrArbourDepth);
// enable RTTI support

public:
  FaceArbourAttrArbourDepth(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
  FaceArbourAttrArbourDepth(const Real& arbourDepth);

private:
  Real myArbourDepth;
};

//________________________________________________________ FaceArbourAttrWallOff

class FaceArbourAttrWallOff : public FaceArbourAttr {
declareRTTI(FaceArbourAttrWallOff);
// enable RTTI support

public:
  FaceArbourAttrWallOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
};

//_________________________________________________________ FaceArbourAttrWallOn

class FaceArbourAttrWallOn : public FaceArbourAttr {
declareRTTI(FaceArbourAttrWallOn);
// enable RTTI support

public:
  FaceArbourAttrWallOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(FaceArbour* facearbour) const;
};

#endif // _FaceArbourAttr_H
