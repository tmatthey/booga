/*
 * $RCSfile: AbstractTraversal3D.h,v $
 *
 * Base class for traversal operation on World3D objects.
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
 *  $Id: AbstractTraversal3D.h,v 1.1 1996/09/13 08:03:13 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AbstractTraversal3D_H
#define _AbstractTraversal3D_H

#include "booga/object/Object3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/World3D.h"

#include "booga/component/Traversal.h"
#include "booga/component/MTraversal.h"  // Traversal protocol mixin

//__________________________________________________________ AbstractTraversal3D

class AbstractTraversal3D : public Traversal,
                               public MTraversal<World3D,Object3D,Path3D> {
declareRTTI(AbstractTraversal3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // AbstractTraversal3D();                           // Use default version.
  // AbstractTraversal3D(const AbstractTraversal3D&); // Use default version.

public:
  // virtual ~AbstractTraversal3D();                  // Use default version.

private:
  // AbstractTraversal3D& operator=(const AbstractTraversal3D&);  
  // Use default version.
};

#endif // _AbstractTraversal3D_H

