/*
 * $RCSfile: Traversal.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Traversal.h,v 1.1 1996/09/13 08:06:35 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Traversal_H
#define _Traversal_H

#include "booga/base/RTTI.h"

//____________________________________________________________________ Traversal

class Traversal {
declareRTTI(Traversal);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local types/enums
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum Result { 
    CONTINUE,  // Continue with traversal process, everything is OK.
    UNKNOWN,   // Unknown object visited -> call decomposition, ...
    PRUNE,     // Stop traversal of current branch of the object hierarchie.
    EXIT       // Cleanup on exit the traversal process.
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Traversal();                            // Use default version.
  // Traversal(const Traversal&);            // Use default version.

public:
  virtual ~Traversal();

public:  
  // Traversal& operator=(const Traversal&); // Use default version.
};

#endif // _Traversal_H
