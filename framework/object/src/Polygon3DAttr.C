/*
 * $RCSfile: Polygon3DAttr.C,v $
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
#include "booga/object/Polygon3DAttr.h"

//_____________________________________________________________ Polygon3DAttr

implementRTTI(Polygon3DAttr, Makeable);

//_________________________________________________ Polygon3DAttrHole

implementRTTI(Polygon3DAttrHole, Polygon3DAttr);

Polygon3DAttrHole::Polygon3DAttrHole(const List<Vector3D>& vertices)
: myVertices(vertices)
{
}

Polygon3DAttrHole::Polygon3DAttrHole()
{
}

Polygon3DAttrHole::Polygon3DAttrHole(Exemplar)
{
}


Makeable* Polygon3DAttrHole::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  List<Vector3D> vertices;
  if (parameters != NULL) {
    for (int i=1; i<=parameters->count(); i++){
      getParameter(i, Vector3D, vertex);
      if (i > 1) {
        if (vertices.item(i-2) == vertex) {
          std::stringstream os;
          os << "[Polygon3DAttrHole::make] two consecutive vertices ("
             << vertex << ") must not have the same value";
          Report::recoverable(os);
          return NULL;
        }
     }
     vertices.append(vertex);
    }
  }
  return new Polygon3DAttrHole(vertices);
}

void Polygon3DAttrHole::setAttribute(Polygon3D* polygon) const
{
  polygon->addHole(myVertices);
}

