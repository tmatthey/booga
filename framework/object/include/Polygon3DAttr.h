/*
 * $RCSfile: Polygon3DAttr.h,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 */

#ifndef _Polygon3DAttr_H
#define _Polygon3DAttr_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"
#include "booga/object/Polygon3D.h"

//_____________________________________________________________ Polygon3DAttr

class Polygon3DAttr : public Makeable {
declareRTTI(Polygon3DAttr);
// enable RTTI support

public:
  virtual void setAttribute(Polygon3D* polygon) const = 0;
  // Interface to class Polygon3D. Whenever setSpecifier(specifier)
  // is called for an instance of class Polygon3D,
  // specifier->setAttribute(Polygon3DObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Polygon3D
  // object by executing the right method. The corresponding call graph:
  //
  //   Polygon3DObject->setSpecifier(specifier)
  //       specifier->setAttribute(Polygon3DObject)
  //           Polygon3DObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________ Polygon3DAttrHole

class Polygon3DAttrHole : public Polygon3DAttr {
declareRTTI(Polygon3DAttrHole);
// enable RTTI support

public:
  Polygon3DAttrHole(Exemplar);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Polygon3D* polygon) const;

private:
  Polygon3DAttrHole(const List<Vector3D>& vertices);
  Polygon3DAttrHole();

  List <Vector3D> myVertices;
};

#endif // _Polygon3DAttr_H
