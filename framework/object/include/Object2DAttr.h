/*
 * $RCSfile: Object2DAttr.h,v $
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Object2DAttr.h,v 1.1 1996/08/07 09:21:06 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Object2DAttr_H
#define _Object2DAttr_H

#include "booga/object/ObjectAttr.h"

class Object2D;

//_________________________________________________________ Object2DAttr

class Object2DAttr : public ObjectAttr {
declareRTTI(Object2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Object2D* object) const = 0;
  // Interface to class Object2D. Whenever setSpecifier(specifier)
  // is called for an instance of class Object2D,
  // specifier->setAttribute(object) will be called. Method
  // setAttribute has to alter the appropriate member of the Object2D
  // object by executing the right method. The corresponding call graph:
  //
  //   object2D->setSpecifier(specifier)
  //       specifier->setAttribute(object2D)
  //           object2D->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________ Object2DAttrObject

class Object2DAttrObject : public Object2DAttr {
declareRTTI(Object2DAttrObject);
// enable RTTI support

public:
  Object2DAttrObject();
  Object2DAttrObject(Exemplar);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

protected:
  Object2D* myObject;
};

#endif // _Object2DAttr_H
