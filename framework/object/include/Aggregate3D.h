/*
 * $RCSfile: Aggregate3D.h,v $ 
 *
 * Base class for aggregate objects of Object3D hierarchy.
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
 *  $Id: Aggregate3D.h,v 1.12 1996/10/04 09:45:44 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Aggregate3D_H
#define _Aggregate3D_H

#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/MAggregate.h"

//__________________________________________________________________ Aggregate3D

class Aggregate3D : public MAggregate<Object3D, Aggregate3D, Path3D> {
declareRTTI(Aggregate3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Aggregate3D();
  Aggregate3D(Exemplar);
protected:
  Aggregate3D(const Aggregate3D& aggregate);

public:
  // virtual ~Aggregate3D();                   // Use default version.

private:
  Aggregate3D& operator=(const Aggregate3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void iterateAttributes(MakeableHandler *handler);
};

#endif // _Aggregate3D_H
