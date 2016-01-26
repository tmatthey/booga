/*
 * Camera3DAttr.h
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

#ifndef _Camera3DAttr_H
#define _Camera3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"
#include <math.h>
#include "booga/base/Color.h"

class Camera3D;
class RCString;

//_________________________________________________________________ Camera3DAttr

class Camera3DAttr : public ObjectAttr {
declareRTTI(Camera3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Camera3D* camera3d) const = 0;
  // Interface to class Camera3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Camera3D,
  // specifier->setAttribute(camera3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Camera3D
  // object by executing the right method. The corresponding call graph:
  //
  //   camera3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(camera3dObject)
  //           camera3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________________ Camera3DAttrOn

class Camera3DAttrOn : public Camera3DAttr {
declareRTTI(Camera3DAttrOn);
// enable RTTI support

public:
  Camera3DAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera3D* camera3d) const;
};

//______________________________________________________________ Camera3DAttrOff

class Camera3DAttrOff : public Camera3DAttr {
declareRTTI(Camera3DAttrOff);
// enable RTTI support

public:
  Camera3DAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera3D* camera3d) const;
};

//_______________________________________________________ Camera3DAttrBackground

class Camera3DAttrBackground : public Camera3DAttr {
declareRTTI(Camera3DAttrBackground);
// enable RTTI support

public:
  Camera3DAttrBackground(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Camera3D* camera3d) const;
  Camera3DAttrBackground(const Color& background);

private:
  Color myBackground;
};

#endif // _Camera3DAttr_H
