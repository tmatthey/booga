/*
 * Polygon2D.C
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
 *                     Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: Polygon2D.C,v 1.8 1996/12/19 16:14:46 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <sstream>

#include "booga/base/Value.h"
#include "booga/object/Shared2D.h"
#include "booga/object/List2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Polygon2D.h"
#include "booga/object/MakeableHandler.h"

// ____________________________________________________________________ Polygon2D

implementRTTI(Polygon2D, Primitive2D);

Polygon2D::Polygon2D(Exemplar exemplar)
: Primitive2D(exemplar)
{
  myDecomposition = NULL;
}

Polygon2D::Polygon2D(const List<Vector2D>& vertices)
: myVertices(vertices)
{
  myDecomposition = NULL;
}

Polygon2D::Polygon2D(const Polygon2D& poly)
: myVertices(poly.myVertices)
{
  myDecomposition = NULL;
}

Polygon2D::~Polygon2D()
{
  delete myDecomposition;
}

void Polygon2D::addVertex(const Vector2D& vertex)
{
  long count = myVertices.count();

  //
  // Check for valid vertex.
  //
  if (count > 0) {
    if (myVertices.item(count-1) == vertex) {
      std::stringstream os;
      os << "[Polygon2D::addVertex] two consecutive vertices ("
         << vertex << ") must not have the same value";
      Report::recoverable(os);
      return;
    }
  }

  if (myDecomposition != NULL) {
    delete myDecomposition;
    myDecomposition = NULL;
  }
  
  myVertices.append(vertex);
}

Object2D* Polygon2D::createDecomposition() const
{
  //
  // We already have a valid decomposition of the polygon object -> just make a copy.
  //
  if (myDecomposition != NULL)
    return myDecomposition->copy();
    
  long count = myVertices.count();
  if (count < 3) {
    Report::warning("[Polygon2D::createDecomposition] degenerate polygon");
    return NULL;
  }

  List2D* lines = new List2D;
 
  //
  // The vertices have to be passed in anti-clockwise order to the tessalation
  // algorithmn in order to produce a correct result.
  //

  for (long i=0; i< count; i++)
    lines->adoptObject(new Line2D(myVertices.item(i),myVertices.item((i+1) % count)));

  ((Polygon2D*)this)->myDecomposition = new Shared2D(lines);
  ((Polygon2D*)this)->myDecomposition->computeBounds();
  return myDecomposition->copy();
}

Object2D* Polygon2D::copy() const
{
  return new Polygon2D(*this);
}

bool Polygon2D::doIntersect(Ray2D& ray)
{
  if (myDecomposition == NULL)
    delete Polygon2D::createDecomposition();

  return myDecomposition->intersect(ray);
}

void Polygon2D::doComputeBounds()
{
  for (register long i=0; i<myVertices.count(); i++)
    myBounds.expand(myVertices.item(i));
}
  
Makeable* Polygon2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  Polygon2D* newPolygon = new Polygon2D(*this);
  newPolygon->removeVertices();
  for (int i=1; i<=parameters->count(); i++) {
    getParameter(i, Vector2D, vertex);
    newPolygon->addVertex(vertex);
  }
    
  return newPolygon;
}

static const RCString polygon2DKeyword("polygon");

RCString Polygon2D::getKeyword() const {
  return polygon2DKeyword;
}

List<Value*>* Polygon2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  for (long i=0; i<getVertices().count(); i++) {
    parameters->append(new Value(getVertices().item(i)));
  }
  return parameters;
}
