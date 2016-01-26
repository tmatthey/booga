/*
 * $RCSfile: PolygonExtrudeAttr.h,v $
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

#ifndef _PolygonExtrudeAttr_H
#define _PolygonExtrudeAttr_H

#include "booga/base/Value.h"
#include "booga/object/Makeable.h"
#include "booga/object/PolygonExtrude.h"

//_____________________________________________________________ PolygonExtrudeAttr

class PolygonExtrudeAttr : public Makeable {
declareRTTI(PolygonExtrudeAttr);
// enable RTTI support

public:
  virtual void setAttribute(PolygonExtrude* polygon) const = 0;
  // Interface to class PolygonExtrude. Whenever setSpecifier(specifier)
  // is called for an instance of class PolygonExtrude,
  // specifier->setAttribute(PolygonExtrudeObject) will be called. Method
  // setAttribute has to alter the appropriate member of the PolygonExtrude
  // object by executing the right method. The corresponding call graph:
  //
  //   PolygonExtrudeObject->setSpecifier(specifier)
  //       specifier->setAttribute(PolygonExtrudeObject)
  //           PolygonExtrudeObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_________________________________________________ PolygonExtrudeAttrHole

class PolygonExtrudeAttrHole : public PolygonExtrudeAttr {
declareRTTI(PolygonExtrudeAttrHole);
// enable RTTI support

public:
  PolygonExtrudeAttrHole(Exemplar);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PolygonExtrude* polygon) const;

private:
  PolygonExtrudeAttrHole(const List<Vector3D>& vertices);
  PolygonExtrudeAttrHole();

  List <Vector3D> myVertices;
};

#endif // _PolygonExtrudeAttr_H

