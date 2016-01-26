/*
 * $RCSfile: MTraversal.h,v $
 *
 * Protocol mixin for traversal classes. 
 *
 * A traversal is activate by calling apply(world, visitor) with a world and 
 * a visitor object as its arguments. The world object is traversed and the 
 * visitor is called for each object found during the traversal process.
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: MTraversal.h,v 1.1 1996/09/13 08:05:01 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MTraversal_H
#define _MTraversal_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Visitor.h"

//_________________________________________________________________ MTraversal<>

template <class TWorld,   // World2D or World3D
          class TObject,  // Object2D or Object3D
          class TPath>    // Path2D or Path3D
class MTraversal {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MTraversal();
  // MTraversal(const MTraversal<TWorld,TObject,TPath>&);
  // Use default version.

public:
  virtual ~MTraversal();

private:
  // MTraversal<TWorld,TObject,TPath>& 
  //    operator=(const MTraversal<TWorld,TObject,TPath>&);  
  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  bool apply(TWorld* world, Visitor* visitor);
  // Start traversal process by calling the following methods:
  // 
  //     apply(w, v)
  //       check for valid w, v
  //       reset();
  //       traverse(w->getObjects());
  //
  //  Returns true on success, false otherwise.

public:  // Accessors
  TWorld*  getWorld()   const;
  Visitor* getVisitor() const;
  TPath*   getPath()    const;
  
protected:
  virtual void reset();
  // Reset the state of the traversal object.
  
  virtual bool traverse(TObject* object) = 0;
  // Recursively traverses the object structure.
  // Returns true : continue
  //         false: abort the traversal

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TWorld*   myWorld;
  Visitor*  myVisitor;
  TPath*    myPath;
};

//______________________________________________________________________ INLINES

template <class TWorld, class TObject, class TPath>
inline TWorld* MTraversal<TWorld,TObject,TPath>::getWorld() const
{
  return myWorld;
}

template <class TWorld, class TObject, class TPath>
inline Visitor* MTraversal<TWorld,TObject,TPath>::getVisitor() const
{
  return myVisitor;
}

template <class TWorld, class TObject, class TPath>
inline TPath* MTraversal<TWorld,TObject,TPath>::getPath() const
{
  return myPath;
}

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../component/src/MTraversal.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MTraversal_H

