/*
 * $RCSfile: PreorderTraversal3D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PreorderTraversal3D.C,v 1.1 1996/09/13 08:05:53 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Object3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/PreorderTraversal3D.h"

//__________________________________________________________ PreorderTraversal3D

implementRTTI(PreorderTraversal3D, AbstractTraversal3D);

bool PreorderTraversal3D::traverse(Object3D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}

bool PreorderTraversal3D::doTraverse(Object3D* obj)
{
  if (obj == NULL)
    return true;

  Traversal::Result state = getVisitor()->dispatch(obj);

   switch (state) {
     case Traversal::EXIT:
       return false;

     case Traversal::PRUNE:
       return true;

     case Traversal::CONTINUE:
     case Traversal::UNKNOWN:
       break;

     default:
       Report::recoverable("[PreorderTraversal3D::doTraverse] unknown tag");
       return false;
   }

  bool retval;
  Primitive3D* primitive = dynamic_cast(Primitive3D, obj);

  if (primitive != NULL && state != Traversal::CONTINUE) {
    Object3D* decomposition = primitive->createDecomposition();

    retval = traverse(decomposition);
    if (decomposition != NULL)
      delete decomposition;

    return retval;
  }
  else {
    // 
    // Visit the subobjects...
    //
    for (long i=0; i<obj->countSubobject(); i++) {
      if (state == Traversal::CONTINUE)
	getVisitor()->incLevel();
	
      // Recursively traverse the structure.
      retval = traverse(obj->getSubobject(i));

      if (state == Traversal::CONTINUE)
	getVisitor()->decLevel();
      
      if (retval == false)
	return false;
    }
  }

  return true;
}

void PreorderTraversal3D::beforeVisitObject(Object3D *object)
{
  getPath()->append(object);
}

void PreorderTraversal3D::afterVisitObject(Object3D*)
{
  getPath()->removeLast();
}
