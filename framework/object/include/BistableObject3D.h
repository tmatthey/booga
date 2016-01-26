/*
 * $RCSfile: BistableObject3D.h,v $
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: BistableObject3D.h,v 1.5 1996/09/13 08:03:24 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BistableObject3D_H
#define _BistableObject3D_H

#include "booga/object/InteractionObject3D.h"
#include "booga/object/Object3DAttr.h"
#include "booga/object/Shared3D.h"
#include "booga/object/World3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/MBistableObject.h"

//____________________________________________________________ BistableObject3D

class BistableObject3D : public MBistableObject<InteractionObject3D, BistableObject3D, Object3D, Object3DAttr, Shared3D, World3D, Path3D> {
declareRTTI(BistableObject3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BistableObject3D(Exemplar);
  BistableObject3D(Object3D* on, Object3D* off, Switch state);
  // BistableObject3D(const BistableObject3D&); // Use default version.

public:
  // virtual ~BistableObject3D();               // Use default version.

private:
  BistableObject3D& operator=(const BistableObject3D&);  // No assignments.
};

#endif // _BistableObject3D_H

