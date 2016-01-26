/*
 * Camera2DAttr.h
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

#ifndef _Camera2DAttr_H
#define _Camera2DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"
#include <math.h>
#include "booga/base/Color.h"

class Camera2D;
class RCString;

//_________________________________________________________________ Camera2DAttr

class Camera2DAttr : public ObjectAttr {
declareRTTI(Camera2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Camera2D* camera2d) const = 0;
  // Interface to class Camera2D. Whenever setSpecifier(specifier)
  // is called for an instance of class Camera2D,
  // specifier->setAttribute(camera2dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Camera2D
  // object by executing the right method. The corresponding call graph:
  //
  //   camera2dObject->setSpecifier(specifier)
  //       specifier->setAttribute(camera2dObject)
  //           camera2dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________ Camera2DAttrResolution

class Camera2DAttrResolution : public Camera2DAttr {
declareRTTI(Camera2DAttrResolution);
// enable RTTI support

public:
  Camera2DAttrResolution(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera2D* camera2d) const;
  Camera2DAttrResolution(const Real& resX, const Real& resY);

private:
  Real myResX;
  Real myResY;
};

//___________________________________________________________ Camera2DAttrWindow

class Camera2DAttrWindow : public Camera2DAttr {
declareRTTI(Camera2DAttrWindow);
// enable RTTI support

public:
  Camera2DAttrWindow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera2D* camera2d) const;
  Camera2DAttrWindow(const Vector2D& origin, const Vector2D& resolution);

private:
  Vector2D myOrigin;
  Vector2D myResolution;
};

//_______________________________________________________________ Camera2DAttrOn

class Camera2DAttrOn : public Camera2DAttr {
declareRTTI(Camera2DAttrOn);
// enable RTTI support

public:
  Camera2DAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera2D* camera2d) const;
};

//______________________________________________________________ Camera2DAttrOff

class Camera2DAttrOff : public Camera2DAttr {
declareRTTI(Camera2DAttrOff);
// enable RTTI support

public:
  Camera2DAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera2D* camera2d) const;
};

//_______________________________________________________ Camera2DAttrBackground

class Camera2DAttrBackground : public Camera2DAttr {
declareRTTI(Camera2DAttrBackground);
// enable RTTI support

public:
  Camera2DAttrBackground(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera2D* camera2d) const;
  Camera2DAttrBackground(const Color& background);

private:
  Color myBackground;
};

#endif // _Camera2DAttr_H
