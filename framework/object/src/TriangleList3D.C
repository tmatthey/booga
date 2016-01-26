/*
 * $RCSfile: TriangleList3D.C,v $
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: TriangleList3D.C,v 1.1 1998/05/22 11:00:25 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>

#include "booga/object/TriangleList3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_______________________________________________________________________ TriangleList3D

implementRTTI(TriangleList3D, Grid3D);

TriangleList3D::TriangleList3D(int sizeX, int sizeY, int sizeZ) : Grid3D(sizeX,sizeY,sizeZ)
{
}

TriangleList3D::TriangleList3D(Exemplar exemplar)
: Grid3D(exemplar)
{
}

TriangleList3D::~TriangleList3D()
{
}

TriangleList3D::TriangleList3D(const TriangleList3D& list) : Grid3D(list)
{
}

Object3D* TriangleList3D::copy() const
{
  return new TriangleList3D(*this);
}
/*
long TriangleList3D::countSubobject() const
{
  return 0; // myElements.countSubobject();
}
*/
long TriangleList3D::countTriangles() const
{
  return myElements.count();
}
/*
Object3D* TriangleList3D::getSubobject(long index)
{
  return myElements.item(index);
}
*/ 
Object3D* TriangleList3D::makeUnique(Path3D* path, bool shared)
{
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;

  //
  // If a predecessor is shared more than once, we have to provide a copy
  // of ourself.
  //
  if (shared == true) {
    Object3D* newTriangleList3D = copy();
    path->replace(newTriangleList3D);
    return newTriangleList3D;
  }
  else
    return this;
}

/*
void TriangleList3D::doComputeBounds()
{
  myElements.computeBounds();
  myBounds.expand(myElements.getBounds());
}
*/
/* 
bool TriangleList3D::doIntersect(Ray3D& ray)
{
  return myElements.intersect(ray);
}
*/
int TriangleList3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  Triangle3D* object = dynamic_cast(Triangle3D, specifier);
  if (object != NULL){
    myElements.append(object);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

Triangle3D* TriangleList3D::getTriangle(long i) const
{
  return (dynamic_cast(Triangle3D, myElements.item(i)));
}

Makeable* TriangleList3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  if (parameters != NULL && parameters->count() > 0) {
    checkParameterNumber(1);
    getParameter(1, Vector3D, dimension);
    
    if (dimension.x() < 1 || dimension.y() < 1 || dimension.z() < 1) {
      ostrstream os;
      os << "Illegal dimension settings " << dimension 
        << ", no component less than 1";
      errMsg = os;  
      return new TriangleList3D;
    } else
      return new TriangleList3D((int)rint(dimension.x()),
      (int)rint(dimension.y()),
      (int)rint(dimension.z()));
  } else
    return new TriangleList3D(1,1,1);
}

static const RCString TriangleList3DKeyword("triangleList");

RCString TriangleList3D::getKeyword() const {
  return TriangleList3DKeyword;
}

void TriangleList3D::adoptObject(Object3D* object)
{
  if (dynamic_cast(Triangle3D,object)) {
    myElements.append(object);
    myBounds.expand(object->getBounds());
  } else {
    Report::warning("[TriangleList::adoptObject]: only accept triangles.");
  }
}

void TriangleList3D::iterateAttributes(MakeableHandler *handler)
{
  Object3D::iterateAttributes(handler);
  
  for(long i=0; i<myElements.count();i++)
    handler->handle(myElements.item(i));
}

