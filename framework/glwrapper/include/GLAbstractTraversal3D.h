/*
 * $RCSfile: GLAbstractTraversal3D.h,v $
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
 *  $Id: GLAbstractTraversal3D.h,v 1.2 1996/09/13 08:04:18 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLAbstractTraversal3D_H
#define _GLAbstractTraversal3D_H

#include "booga/component/AbstractTraversal3D.h"
#include "booga/glwrapper/GLTraversal.h"

//________________________________________________________ GLAbstractTraversal3D

class GLAbstractTraversal3D : public AbstractTraversal3D,
                                 public GLTraversal {
declareRTTI(GLAbstractTraversal3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLAbstractTraversal3D();            // Use default version.

  // GLAbstractTraversal3D(const GLAbstractTraversal3D&); 
  // Use default version.

public:
  // virtual ~GLAbstractTraversal3D();   // Use default version.

private:
  // GLAbstractTraversal3D& operator=(const GLAbstractTraversal3D&);  
  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class MTraversal<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void reset();
};

#endif // _GLAbstractTraversal3D_H

