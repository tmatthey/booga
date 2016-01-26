/*
 * Animation3DAttr.h
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

#ifndef _Animation3DAttr_H
#define _Animation3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Animation3D;
class RCString;

//______________________________________________________________ Animation3DAttr

class Animation3DAttr : public ObjectAttr {
declareRTTI(Animation3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Animation3D* animation3d) const = 0;
  // Interface to class Animation3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Animation3D,
  // specifier->setAttribute(animation3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Animation3D
  // object by executing the right method. The corresponding call graph:
  //
  //   animation3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(animation3dObject)
  //           animation3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//____________________________________________________________ Animation3DAttrOn

class Animation3DAttrOn : public Animation3DAttr {
declareRTTI(Animation3DAttrOn);
// enable RTTI support

public:
  Animation3DAttrOn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Animation3D* animation3d) const;
};

//___________________________________________________________ Animation3DAttrOff

class Animation3DAttrOff : public Animation3DAttr {
declareRTTI(Animation3DAttrOff);
// enable RTTI support

public:
  Animation3DAttrOff(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Animation3D* animation3d) const;
};

#endif // _Animation3DAttr_H
