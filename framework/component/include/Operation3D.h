/*
 * $RCSfile: Operation3D.h,v $
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
 *  $Id: Operation3D.h,v 1.6 1996/09/13 08:05:25 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Operation3D_H
#define _Operation3D_H

#include "booga/object/World3D.h"
#include "booga/component/Component.h"
#include "booga/component/AbstractTraversal3D.h"

//__________________________________________________________________ Operation3D

class Operation3D : public Component<World3D,                // Input world
                                      World3D,                //  Result world
                                      AbstractTraversal3D> {  //  Traverse world3D
declareRTTI(Operation3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Operation3D();
  // Operation3D(const Operation3D&);          // Use default version.

public:
  // virtual ~Operation3D();                   // Use default version.

private:
  Operation3D& operator=(const Operation3D&);  // No assignments.  
};

#endif // _Operation3D_H
