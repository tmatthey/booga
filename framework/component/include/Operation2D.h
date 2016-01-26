/*
 * $RCSfile: Operation2D.h,v $
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
 *  $Id: Operation2D.h,v 1.6 1996/09/13 08:05:19 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Operation2D_H
#define _Operation2D_H

#include "booga/object/World2D.h"
#include "booga/component/AbstractTraversal2D.h"
#include "booga/component/Component.h"

//__________________________________________________________________ Operation2D
 
class Operation2D : public Component<World2D,                // Input world
                                      World2D,                //  Result world
                                      AbstractTraversal2D> {  //  Traverse world2D
declareRTTI(Operation2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Operation2D();
  // Operation2D(const Operation2D&);          // Use default version.

public:
  // virtual ~Operation2D();                   // Use default version.

private:
  Operation2D& operator=(const Operation2D&);  // No assignments.  
};

#endif // _Operation2D_H
