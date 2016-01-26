/*
 * $RCSfile: Aggregate2D.h,v $
 *
 * Base class for aggregate objects of Object2D hierarchy.
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Aggregate2D.h,v 1.14 1996/10/04 09:45:38 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Aggregate2D_H
#define _Aggregate2D_H

#include "booga/object/Object2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/MAggregate.h"

//__________________________________________________________________ Aggregate2D

class Aggregate2D : public MAggregate<Object2D, Aggregate2D, Path2D> {
declareRTTI(Aggregate2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Aggregate2D();
  Aggregate2D(Exemplar);
protected:
  Aggregate2D(const Aggregate2D& aggregate);

public:
  // virtual ~Aggregate2D();                   // Use default version.

private:
  Aggregate2D& operator=(const Aggregate2D&);  // No assignments.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void iterateAttributes(MakeableHandler *handler);
};

#endif // _Aggregate2D_H
