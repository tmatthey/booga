/*
 * Text3DAttr.h
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

#ifndef _Text3DAttr_H
#define _Text3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Text3D;
class RCString;

//___________________________________________________________________ Text3DAttr

class Text3DAttr : public ObjectAttr {
declareRTTI(Text3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Text3D* text3d) const = 0;
  // Interface to class Text3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Text3D,
  // specifier->setAttribute(text3dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Text3D
  // object by executing the right method. The corresponding call graph:
  //
  //   text3dObject->setSpecifier(specifier)
  //       specifier->setAttribute(text3dObject)
  //           text3dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________________ Text3DAttrFont

class Text3DAttrFont : public Text3DAttr {
declareRTTI(Text3DAttrFont);
// enable RTTI support

public:
  Text3DAttrFont(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Text3D* text3d) const;
  Text3DAttrFont(const RCString& font);

private:
  RCString myFont;
};

#endif // _Text3DAttr_H
