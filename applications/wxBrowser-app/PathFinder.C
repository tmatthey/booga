/*
 * $RCSfile: PathFinder.C,v $ 
 *
 * Copyright (C) 1996, Bernhard Buhlmann <buhlmann@iam.unibe,ch>
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
 *  $Id: PathFinder.C,v 1.3 1996/09/13 08:05:29 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "PathFinder.h"
#include "booga/object/Object3D.h"

//_____________________________________________________________________ PathFinder

implementRTTI(PathFinder, Transformer3D);

void PathFinder::findObject(Object3D* obj, World3D* world)
{
  myFindObject = obj;
  traverse(world);
}


Traversal::Result PathFinder::visit(Object3D* obj)
{
  if (obj == myFindObject) {
    delete myPath;
    myPath = new Path3D(*((Path3D*) myTraversal->getPath()));
    return Traversal::EXIT;
  }
  return Traversal::CONTINUE;
}


Path3D* PathFinder::getPath()
{
  if (myPath)
    return myPath;
}
