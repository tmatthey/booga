/*
 * $RCSfile: GDB3CanonicalViews.h,v $
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
 *  $Id: GDB3CanonicalViews.h,v 1.2 1997/02/20 09:30:24 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDB3CanonicalViews_H
#define _GDB3CanonicalViews_H

#include "booga/graphicsdb/GDBOperation.h"

//_____________________________________________________________________ GDB3CanonicalViews

class GDB3CanonicalViews : public GDBOperation {
declareRTTI(GDB3CanonicalViews);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDB3CanonicalViews(DataBase& aDB,
                   GDBDataType* sourceType, GDBRepType* sourceRep,
                   GDBDataType* targetType, GDBRepType* targetRep,
                   int xsize=100, int ysize=100);
  GDB3CanonicalViews(Prototype aPrototype);

private:
  GDB3CanonicalViews(const GDB3CanonicalViews&);             // No copies.

public:
  virtual ~GDB3CanonicalViews();

private:
  GDB3CanonicalViews& operator=(const GDB3CanonicalViews&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDB3CanonicalViews
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GDBOperation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myIconSizeX;
  int myIconSizeY;
  long myMaxBoundaryPoints;
  double myBoundaryPrecision;
};

//______________________________________________________________________ INLINES

#endif // _GDB3CanonicalViews_H


