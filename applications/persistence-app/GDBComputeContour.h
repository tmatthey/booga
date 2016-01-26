/*
 * $RCSfile: GDBComputeContour.h,v $
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
 *  $Id: GDBComputeContour.h,v 1.1 1996/10/09 14:12:04 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBComputeContour_H
#define _GDBComputeContour_H

#include "GDBOperation.h"

//_____________________________________________________________________ GDBComputeContour

class GDBComputeContour : public GDBOperation {
declareRTTI(GDBComputeContour);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBComputeContour();
  virtual ~GDBComputeContour();

private:
  GDBComputeContour(const GDBComputeContour&);             // No copies.

public:
  // virtual ~GDBComputeContour();                // Use default version.

private:
  GDBComputeContour& operator=(const GDBComputeContour&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBComputeContour
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

#endif // _GDBComputeContour_H

