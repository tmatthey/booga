/*
 * $RCSfile: Object3DAttr.h,v $
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
 *  $Id: Object3DAttr.h,v 1.2 1996/08/07 09:21:08 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Object3DAttr_H
#define _Object3DAttr_H

#include "booga/object/ObjectAttr.h"

class Object3D;

//_________________________________________________________ Object3DAttr

class Object3DAttr : public ObjectAttr {
declareRTTI(Object3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Object3D* object) const = 0;
  // Interface to class Object3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Object3D,
  // specifier->setAttribute(object) will be called. Method
  // setAttribute has to alter the appropriate member of the Object3D
  // object by executing the right method. The corresponding call graph:
  //
  //   object3D->setSpecifier(specifier)
  //       specifier->setAttribute(object3D)
  //           object3D->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//___________________________________________________ Object3DAttrObject

class Object3DAttrObject : public Object3DAttr {
declareRTTI(Object3DAttrObject);
// enable RTTI support

public:
  Object3DAttrObject();
  Object3DAttrObject(Exemplar);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

protected:
  Object3D* myObject;
};

#endif // _Object3DAttr_H
