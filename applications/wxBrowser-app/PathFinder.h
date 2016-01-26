/*
 * $RCSfile: PathFinder.h,v $ 
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
 *  $Id: PathFinder.h,v 1.3 1996/12/20 15:45:24 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PathFinder_H
#define _PathFinder_H

#include "booga/object/Path3D.h"
#include "booga/component/Operation3D.h"

//_____________________________________________________________________ PathFinder

class PathFinder : public Operation3D {
declareRTTI(PathFinder);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PathFinder() : myPath(NULL), myFindObject(NULL) {};
  // PathFinder();                         // Use default version.
private:
  PathFinder(const PathFinder&);             // No copies.

public:
  // virtual ~PathFinder();                // Use default version.

private:
  PathFinder& operator=(const PathFinder&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PathFinder
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void findObject(Object3D* obj, World3D* world);
  Path3D* getPath();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Operation3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  bool doExecute() { return true; };
  virtual Traversal::Result visit(Object3D* obj);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Path3D* myPath;
  Object3D* myFindObject;
};

//______________________________________________________________________ INLINES

#endif // _PathFinder_H

