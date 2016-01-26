/*
 * CheckerAttr.h
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: CheckerAttr.h,v 1.2 1995/04/21 12:31:28 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CheckerAttr_H
# define _CheckerAttr_H

#include "booga/object/Checker.h"
#include "booga/object/Texture3DAttr.h"

class Texture3D;

//__________________________________________________________________ CheckerAttr

class CheckerAttr : public Texture3DAttr {
declareRTTI(CheckerAttr);
// enable RTTI support

public:
  virtual void setAttribute(Checker* checker) const = 0;
  // Interface to class Checker. Whenever setSpecifier(specifier)
  // is called for an instance of class Checker,
  // specifier->setAttribute(checkerObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Checker
  // object by executing the right method. The corresponding call graph:
  //
  //   checkerObject->setSpecifier(specifier)
  //       specifier->setAttribute(checkerObject)
  //           checkerObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________________ CheckerAttrTexture

class CheckerAttrTexture : public CheckerAttr {
declareRTTI(CheckerAttrTexture);
// enable RTTI support

public:
  CheckerAttrTexture();
  CheckerAttrTexture(Exemplar);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

protected:
  Texture3D* myTexture;
};

//______________________________________________________________ CheckerAttrEven

class CheckerAttrEven : public CheckerAttrTexture {
declareRTTI(CheckerAttrEven);
// enable RTTI support

public:
  CheckerAttrEven(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Checker* checker) const;
};

//_______________________________________________________________ CheckerAttrOdd

class CheckerAttrOdd : public CheckerAttrTexture {
declareRTTI(CheckerAttrOdd);
// enable RTTI support

public:
  CheckerAttrOdd(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Checker* checker) const;
};

#endif // _CheckerAttr_H
