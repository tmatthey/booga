/*
 * FaceAttr.h
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

#ifndef _FaceAttr_H
#define _FaceAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Face;
class RCString;

//_____________________________________________________________________ FaceAttr

class FaceAttr : public ObjectAttr {
declareRTTI(FaceAttr);
// enable RTTI support

public:
  virtual void setAttribute(Face* face) const = 0;
  // Interface to class Face. Whenever setSpecifier(specifier)
  // is called for an instance of class Face,
  // specifier->setAttribute(faceObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Face
  // object by executing the right method. The corresponding call graph:
  //
  //   faceObject->setSpecifier(specifier)
  //       specifier->setAttribute(faceObject)
  //           faceObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//________________________________________________________________ FaceAttrDepth

class FaceAttrDepth : public FaceAttr {
declareRTTI(FaceAttrDepth);
// enable RTTI support

public:
  FaceAttrDepth(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Face* face) const;
  FaceAttrDepth(const Real& depth);

private:
  Real myDepth;
};

#endif // _FaceAttr_H
