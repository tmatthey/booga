/*
 * $RCSfile: Operation2DTo3D.h,v $
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
 *  $Id: Operation2DTo3D.h,v 1.6 1996/09/13 08:05:23 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Operation2DTo3D_H
#define _Operation2DTo3D_H

#include "booga/object/World2D.h"
#include "booga/object/World3D.h"
#include "booga/component/AbstractTraversal2D.h"
#include "booga/component/Component.h"

//______________________________________________________________ Operation2DTo3D

class Operation2DTo3D : public Component<World2D,                // Input world
                                           World3D,                //  Result world
                                           AbstractTraversal2D> {  //  Traverse world2D
declareRTTI(Operation2DTo3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Operation2DTo3D();
  // Operation2DTo3D(const Operation2DTo3D&);          // Use default version.

public:
  // virtual ~Operation2DTo3D();                       // Use default version.

private:
  Operation2DTo3D& operator=(const Operation2DTo3D&);  // No assignments.  
};

#endif // _Operation2DTo3D_H
