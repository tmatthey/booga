/*
 * $RCSfile: RaytraceBSDL3.h,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: RaytraceBSDL3.h,v 1.4 1996/10/09 14:13:38 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _RaytraceBSDL3_H
#define _RaytraceBSDL3_H

#include "GDBOperation.h"

//_____________________________________________________________________ RaytraceBSDL3

class RaytraceBSDL3 : public GDBOperation {
declareRTTI(RaytraceBSDL3);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RaytraceBSDL3(RCString inputType);                     // Use default version.
private:
  RaytraceBSDL3(const RaytraceBSDL3&);             // No copies.

public:
  // virtual ~RaytraceBSDL3();                // Use default version.

private:
  RaytraceBSDL3& operator=(const RaytraceBSDL3&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class RaytraceBSDL3
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

};

//______________________________________________________________________ INLINES

#endif // _RaytraceBSDL3_H

