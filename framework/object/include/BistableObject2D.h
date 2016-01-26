/*
 * $RCSfile: BistableObject2D.h,v $
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
 *  $Id: BistableObject2D.h,v 1.2 1996/09/13 08:03:21 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _BistableObject2D_H
#define _BistableObject2D_H

#include "booga/object/InteractionObject2D.h"
#include "booga/object/Object2DAttr.h"
#include "booga/object/Shared2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/MBistableObject.h"

//____________________________________________________________ BistableObject2D

class BistableObject2D : public MBistableObject<InteractionObject2D, BistableObject2D, Object2D, Object2DAttr, Shared2D, World2D, Path2D> {
declareRTTI(BistableObject2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  BistableObject2D(Exemplar);
  BistableObject2D(Object2D* on, Object2D* off, Switch state);
  // BistableObject2D(const BistableObject2D&); // Use default version.

public:
  // virtual ~BistableObject2D();               // Use default version.

private:
  BistableObject2D& operator=(const BistableObject2D&);  // No assignments.
};

#endif // _BistableObject2D_H

