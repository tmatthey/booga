/*
 * $RCSfile: PreorderTraversal2D.C,v $
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
 *  $Id: PreorderTraversal2D.C,v 1.1 1996/09/13 08:05:47 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Object2D.h"
#include "booga/object/Primitive2D.h"
#include "booga/object/Path2D.h"
#include "booga/component/PreorderTraversal2D.h"

//__________________________________________________________ PreorderTraversal2D

implementRTTI(PreorderTraversal2D, AbstractTraversal2D);

bool PreorderTraversal2D::traverse(Object2D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}

bool PreorderTraversal2D::doTraverse(Object2D* obj)
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
       Report::recoverable("[PreorderTraversal2D::doTraverse] unknown tag");
       return false;
   }

  bool retval;
  Primitive2D* primitive = dynamic_cast<Primitive2D*>(obj);

  if (primitive != NULL && state != Traversal::CONTINUE) {
    Object2D* decomposition = primitive->createDecomposition();

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

void PreorderTraversal2D::beforeVisitObject(Object2D *object)
{
  getPath()->append(object);
}

void PreorderTraversal2D::afterVisitObject(Object2D*)
{
  getPath()->removeLast();
}
