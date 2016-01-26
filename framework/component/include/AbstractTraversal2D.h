/*
 * $RCSfile: AbstractTraversal2D.h,v $
 *
 * Base class for traversal operation on World2D objects.
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
 *  $Id: AbstractTraversal2D.h,v 1.1 1996/09/13 08:03:09 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AbstractTraversal2D_H
#define _AbstractTraversal2D_H

#include "booga/object/Object2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/World2D.h"

#include "booga/component/Traversal.h"
#include "booga/component/MTraversal.h"  // Traversal protocol mixin

//__________________________________________________________ AbstractTraversal2D

class AbstractTraversal2D : public Traversal,
                              public MTraversal<World2D,Object2D,Path2D> {
declareRTTI(AbstractTraversal2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // AbstractTraversal2D();                           // Use default version.
  // AbstractTraversal2D(const AbstractTraversal2D&); // Use default version.

public:
  // virtual ~AbstractTraversal2D();                  // Use default version.

private:
  // AbstractTraversal2D& operator=(const AbstractTraversal2D&);  
  // Use default version.
};

#endif // _AbstractTraversal2D_H

