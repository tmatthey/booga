/*
 * $RCSfile: GSBFastTraversal3D.C,v $
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
 *  $Id: GSBFastTraversal3D.C,v 1.6 1997/04/08 11:04:41 habegger Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Object3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Path3D.h"
#include "GSBFastTraversal3D.h"
#include "GSBNodeTools.h"

//__________________________________________________________ GSBFastTraversal3D

implementRTTI(GSBFastTraversal3D, AbstractTraversal3D);

bool GSBFastTraversal3D::traverse(Object3D* obj)
{
  bool retval = true;

  if (obj != NULL) {
    beforeVisitObject(obj);
    retval = doTraverse(obj);
    afterVisitObject(obj);
  }

  return retval;
}


bool GSBFastTraversal3D::doTraverse(Object3D* obj)
{
  if (obj == NULL)
    return true;

  int retval;

  Shared3D* shared = dynamic_cast(Shared3D, obj);
  Primitive3D* primitive = dynamic_cast(Primitive3D, obj);

  if (!primitive && !GSBNodeTools::getNodeManager(obj)->isPruned()) {
    // 
    // Visit the subobjects... (only if object isn't shared or not pruned)
    //
    for (long i=0; i < obj->countSubobject(); i++) {
      getVisitor()->incLevel();
      retval = traverse(obj->getSubobject(i));
      getVisitor()->decLevel();
      if (!retval)
	return false;
    }
  }

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
      Report::warning("[GSBFastTraversal3D::doTraverse] unknown tag");
      return false;
  }
  
  if (primitive != NULL && state != Traversal::CONTINUE) {
    Object3D* decomposition = primitive->createDecomposition();

    retval = traverse(decomposition);
    if (decomposition != NULL)
      delete decomposition;

    return retval;
  }
  
  return true;
}

void GSBFastTraversal3D::beforeVisitObject(Object3D *object)
{
  getPath()->append(object);
}

void GSBFastTraversal3D::afterVisitObject(Object3D*)
{
  getPath()->removeLast();
}
