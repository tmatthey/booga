/*
 * $RCSfile: TriangleRemover.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: TriangleRemover.C,v 1.7 1996/11/01 13:35:14 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/RCString.h"
#include "booga/base/Report.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/building/Front.h"
#include "booga/building/Snatch.h"
#include "booga/building/BottomUser.h"
#include "booga/building/RoofUser.h"
#include "booga/building/FaceItem.h"

#include "TriangleRemover.h"

//_____________________________________________________________________ TriangleRemover

implementRTTI(TriangleRemover, Operation3D);

TriangleRemover::TriangleRemover() 
{}

TriangleRemover::~TriangleRemover() 
{
  if (myTriangleVertices.count() > 0){
    for (long i = 0; i < myTriangleVertices.count(); i++)
      delete myTriangleVertices.item(i);
    myTriangleVertices.removeAll();
  }

  if (myPath3D.count() > 0){
    for (long i = 0; i < myPath3D.count(); i++)
      if (myPath3D.item(i))
	delete myPath3D.item(i);
    myPath3D.removeAll();
  }

  myDeletedTriangles.removeAll();
}

Traversal::Result TriangleRemover::visit(Triangle3D* obj)
{
  //
  // Add modeling transformation to the vertices.
  //
  Vector3D* w;
  Vector3D* v = new Vector3D[3];
  int flag;
  long i, count;

  for (i=0; i<3; i++)
    v[i] = getTraversal()->getPath()->getLastTransform().transformAsPoint(
  	         obj->getVertex(i));

  getTraversal()->getPath()->last();

  myTriangleVertices.append(v);
  myDeletedTriangles.append(false);

  myPath3D.append(new Path3D(*(getTraversal()->getPath())));


  for (i = 0; i < myTriangleVertices.count()-1; i++){
    w = myTriangleVertices.item(i);
    flag = 0;
    count = 0;

    if (v[0] == w[0]) {flag |= 1; count++;}
    if (v[0] == w[1]) {flag |= 8; count++;}
    if (v[0] == w[2]) {flag |= 64;count++;}
    if (count < 1) continue;

    if(v[1] == w[0]) {flag |= 128;count++;}
    if(v[1] == w[1]) {flag |= 2;  count++;}
    if(v[1] == w[2]) {flag |= 16; count++;}
    if (count < 2) continue;


    if(v[2] == w[0]) {flag |= 32; count++;}
    if(v[2] == w[1]) {flag |= 256;count++;}
    if(v[2] == w[2]) {flag |= 4;  count++;}
    if (count < 3) continue;


    if (((flag & 7) == 7) ||((flag & 7) == 7*8) || ((flag & 7) == 7*64)){
      // same orientation, delete only the last triangle
      myDeletedTriangles.item(myTriangleVertices.count()-1) = true;
      break;
    }
    else{
      // conter orientation, delete both triangles
      myDeletedTriangles.item(i)= true;
      myDeletedTriangles.item(myTriangleVertices.count()-1) = true;      
      break;
    }

  }


  return Traversal::CONTINUE;
}


Traversal::Result TriangleRemover::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D, obj);

  //
  // do not do a decomosition of the primitives
  //
  if (dynamic_cast<Primitive3D*>(obj))
    return Traversal::PRUNE;

  //
  // test only the BuilingObjects wihch may have triangles
  // otherwise PRUNE
  //
  if (dynamic_cast<BuildingObject*>(obj)){
    if (dynamic_cast<BottomUser*>(obj))
      return Traversal::UNKNOWN;
    if (dynamic_cast<RoofUser*>(obj))
      return Traversal::UNKNOWN;
    if (dynamic_cast<Front*>(obj))
      return Traversal::UNKNOWN;
    if (dynamic_cast<Snatch*>(obj))
      return Traversal::UNKNOWN;
    if (dynamic_cast<FaceItem*>(obj))

    return Traversal::PRUNE;
  }

  //
  // Create decomposition for all other objects
  //
  return Traversal::UNKNOWN;
}

bool TriangleRemover::postprocessing()
{
  long count = 0;
  Aggregate3D* agg;
  Shared3D* shared;

  for (long i = 0; i < myDeletedTriangles.count(); i++)
    if(myDeletedTriangles.item(i)){
      myPath3D.item(i)->last();
      if (dynamic_cast<Triangle3D*>(myPath3D.item(i)->getObject())){
	myPath3D.item(i)->prev();
	if ((agg = dynamic_cast<Aggregate3D*>(myPath3D.item(i)->getObject())) != NULL){
	  myPath3D.item(i)->last();
	  if (agg->orphanObject(myPath3D.item(i)->getObject()) == 1)
	    count++;
        }
	else if ((shared = dynamic_cast<Shared3D*>(myPath3D.item(i)->getObject())) != NULL){
	  myPath3D.item(i)->last();
	  shared->adoptObject(new NullObject3D());
	  count++;
        } 
      }
    }

  std::stringstream os;
  os << "Removed " << count << " ("<< (count*100)/myDeletedTriangles.count()
     << "%) triangles of " << myDeletedTriangles.count();
  Report::debug(os);

  return Operation3D::postprocessing();  
}
