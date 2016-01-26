/*
 * $RCSfile: Operation3DTo2D.h,v $
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
 *  $Id: Operation3DTo2D.h,v 1.6 1996/09/13 08:05:27 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Operation3DTo2D_H
#define _Operation3DTo2D_H

#include "booga/object/World2D.h"
#include "booga/object/World3D.h"
#include "booga/component/AbstractTraversal3D.h"
#include "booga/component/Component.h"

//______________________________________________________________ Operation3DTo2D

class Operation3DTo2D : public Component<World3D,                // Input world
                                           World2D,                //  Result world
                                           AbstractTraversal3D> {  //  Traverse world3D
declareRTTI(Operation3DTo2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Operation3DTo2D();
  // Operation3DTo2D(const Operation3DTo2D&);          // Use default version.

public:
  // virtual ~Operation3DTo2D();                       // Use default version.

private:
  Operation3DTo2D& operator=(const Operation3DTo2D&);  // No assignments.  
};

#endif // _Operation3DTo2D_H
