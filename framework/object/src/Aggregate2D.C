/*
 * $RCSfile: Aggregate2D.C,v $
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
 *  $Id: Aggregate2D.C,v 1.19 1996/10/04 09:45:20 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Aggregate2D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

//__________________________________________________________________ Aggregate2D

implementRTTI(Aggregate2D, Object2D);

Aggregate2D::Aggregate2D() {}

Aggregate2D::Aggregate2D(Exemplar exemplar)
: MAggregate<Object2D, Aggregate2D, Path2D>(exemplar) {}

Aggregate2D::Aggregate2D(const Aggregate2D& aggregate)
: MAggregate<Object2D, Aggregate2D, Path2D>(aggregate) {}

void Aggregate2D::iterateAttributes(MakeableHandler *handler) {
  Object2D::iterateAttributes(handler);
  for(long i=0; i<countSubobject(); i++) {
    handler->handle(getSubobject(i));
  }
}
