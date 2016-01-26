/*
 * Viewing3DAttr.h
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

#ifndef _Viewing3DAttr_H
#define _Viewing3DAttr_H

#include "booga/base/Value.h"
#include <math.h>
#include "booga/object/ObjectAttr.h"

class Viewing3D;
class RCString;

//________________________________________________________________ Viewing3DAttr

class Viewing3DAttr : public ObjectAttr {
declareRTTI(Viewing3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Viewing3D* viewing3d) const = 0;
  // Interface to class Viewing3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Viewing3D,
  // specifier->setAttribute(viewing3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Viewing3D
  // object by executing the right method. The corresponding call graph:
  //
  //   viewing3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(viewing3dObject)
  //           viewing3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ Viewing3DAttrEye

class Viewing3DAttrEye : public Viewing3DAttr {
declareRTTI(Viewing3DAttrEye);
// enable RTTI support

public:
  Viewing3DAttrEye(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrEye(const Vector3D& eye);

private:
  Vector3D myEye;
};

//__________________________________________________________ Viewing3DAttrLookat

class Viewing3DAttrLookat : public Viewing3DAttr {
declareRTTI(Viewing3DAttrLookat);
// enable RTTI support

public:
  Viewing3DAttrLookat(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrLookat(const Vector3D& lookat);

private:
  Vector3D myLookat;
};

//______________________________________________________________ Viewing3DAttrUp

class Viewing3DAttrUp : public Viewing3DAttr {
declareRTTI(Viewing3DAttrUp);
// enable RTTI support

public:
  Viewing3DAttrUp(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrUp(const Vector3D& up);

private:
  Vector3D myUp;
};

//_____________________________________________________________ Viewing3DAttrFov

class Viewing3DAttrFov : public Viewing3DAttr {
declareRTTI(Viewing3DAttrFov);
// enable RTTI support

public:
  Viewing3DAttrFov(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrFov(const Real& hFov, const Real& vFov);

private:
  Real myHFov;
  Real myVFov;
};

//___________________________________________________ Viewing3DAttrEyeSeparation

class Viewing3DAttrEyeSeparation : public Viewing3DAttr {
declareRTTI(Viewing3DAttrEyeSeparation);
// enable RTTI support

public:
  Viewing3DAttrEyeSeparation(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrEyeSeparation(const Real& eyeSep);

private:
  Real myEyeSep;
};

//______________________________________________________ Viewing3DAttrResolution

class Viewing3DAttrResolution : public Viewing3DAttr {
declareRTTI(Viewing3DAttrResolution);
// enable RTTI support

public:
  Viewing3DAttrResolution(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Viewing3D* viewing3d) const;
  Viewing3DAttrResolution(const Real& resX, const Real& resY);

private:
  Real myResX;
  Real myResY;
};

#endif // _Viewing3DAttr_H
