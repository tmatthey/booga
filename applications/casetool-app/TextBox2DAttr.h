/*
 * $RCSfile: TextBox2DAttr.h,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 * -----------------------------------------------------------------------------
 *  $Id: TextBox2DAttr.h,v 1.1 1996/10/30 15:31:47 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TextBox2DAttr_H
#define _TextBox2DAttr_H

#include <math.h>
#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class TextBox2DAttr;
class RCString;

//_____________________________________________________ TextBox2DAttr

class TextBox2DAttr : public ObjectAttr {
declareRTTI(TextBox2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(TextBox2D* textbox) const = 0;
  // Interface to class TextBox2D. Whenever setSpecifier(specifier)
  // is called for an instance of class TextBox2D,
  // specifier->setAttribute(textbox) will be called. Method
  // setAttribute has to alter the appropriate member of the TextBox2D
  // object by executing the right method. The corresponding call graph:
  //
  //   textbox->setSpecifier(specifier)
  //       specifier->setAttribute(textbox)
  //           textbox->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________ TextBox2DAttrText

class TextBox2DAttrText : public TextBox2DAttr {
declareRTTI(TextBox2DAttrText);
// enable RTTI support

public:
  TextBox2DAttrText(Exemplar) {}
  TextBox2DAttrText(RCString text);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(TextBox2D* textbox) const;
  
private:
  RCString myText;
};

#endif // _TextBox2DAttr_H
