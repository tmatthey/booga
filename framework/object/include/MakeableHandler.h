/*
 * $RCSfile: MakeableHandler.h,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: MakeableHandler.h,v 1.3 1996/10/04 09:47:10 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MakeableHandler_H
#define _MakeableHandler_H

#include "booga/base/RTTI.h"

class Makeable;

//_____________________________________________________________________ MakeableHandler

class MakeableHandler {
declareRTTI(MakeableHandler);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MakeableHandler(); // use default
  virtual ~MakeableHandler();

private:
  MakeableHandler(const MakeableHandler&);             // No copies.

public:
  // virtual ~MakeableHandler();                // Use default version.

private:
  MakeableHandler& operator=(const MakeableHandler&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MakeableHandler
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void handle(Makeable* makeable)=0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  
};

//______________________________________________________________________ INLINES

#endif // _MakeableHandler_H

