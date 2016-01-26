/*
 * $RCSfile: PolygonExtrudeAttr.C,v $
 *
 * Copyright (C) 1996, University of Berne, Switzerland
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

#include <sstream>

#include "booga/base/Value.h"
#include "booga/object/PolygonExtrudeAttr.h"

//_____________________________________________________________ PolygonExtrudeAttr

implementRTTI(PolygonExtrudeAttr, Makeable);

//_________________________________________________ PolygonExtrudeAttrHole

implementRTTI(PolygonExtrudeAttrHole, PolygonExtrudeAttr);

PolygonExtrudeAttrHole::PolygonExtrudeAttrHole(const List<Vector3D>& vertices)
: myVertices(vertices)
{
}

PolygonExtrudeAttrHole::PolygonExtrudeAttrHole()
{
}

PolygonExtrudeAttrHole::PolygonExtrudeAttrHole(Exemplar)
{
}


Makeable* PolygonExtrudeAttrHole::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  List<Vector3D> vertices;
  if (parameters != NULL) {
    for (int i=1; i<=parameters->count(); i++){
      getParameter(i, Vector3D, vertex);
      if (i > 1) {
        if (vertices.item(i-2) == vertex) {
          std::stringstream os;
          os << "[PolygonExtrudeAttrHole::make] two consecutive vertices ("
             << vertex << ") must not have the same value";
          Report::recoverable(os);
          return NULL;
        }
     }
     vertices.append(vertex);
    }
  }
  return new PolygonExtrudeAttrHole(vertices);
}

void PolygonExtrudeAttrHole::setAttribute(PolygonExtrude* polygon) const
{
  polygon->addHole(myVertices);
}


