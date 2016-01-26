/*
 * $RCSfile: Aggregate3D.C,v $ 
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
 *  $Id: Aggregate3D.C,v 1.16 1996/10/04 09:45:41 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Aggregate3D.h"
#include "booga/object/MakeableHandler.h"

//__________________________________________________________________ Aggregate3D

implementRTTI(Aggregate3D, Object3D);

Aggregate3D::Aggregate3D() {}

Aggregate3D::Aggregate3D(Exemplar exemplar)
: MAggregate<Object3D, Aggregate3D, Path3D>(exemplar) {}

Aggregate3D::Aggregate3D(const Aggregate3D& aggregate)
: MAggregate<Object3D, Aggregate3D, Path3D>(aggregate) {}

void Aggregate3D::iterateAttributes(MakeableHandler *handler) {
  Object3D::iterateAttributes(handler);
  for(long i=0; i<countSubobject(); i++) {
    handler->handle(getSubobject(i));
  }
}
