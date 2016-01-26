/*
 * Text2DAttr.h
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

#ifndef _Text2DAttr_H
#define _Text2DAttr_H

#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class Text2D;
class RCString;

//___________________________________________________________________ Text2DAttr

class Text2DAttr : public ObjectAttr {
declareRTTI(Text2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Text2D* text2d) const = 0;
  // Interface to class Text2D. Whenever setSpecifier(specifier)
  // is called for an instance of class Text2D,
  // specifier->setAttribute(text2dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Text2D
  // object by executing the right method. The corresponding call graph:
  //
  //   text2dObject->setSpecifier(specifier)
  //       specifier->setAttribute(text2dObject)
  //           text2dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________________________ Text2DAttrFont

class Text2DAttrFont : public Text2DAttr {
declareRTTI(Text2DAttrFont);
// enable RTTI support

public:
  Text2DAttrFont(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Text2D* text2d) const;
  Text2DAttrFont(const RCString& font);

private:
  RCString myFont;
};

#endif // _Text2DAttr_H
