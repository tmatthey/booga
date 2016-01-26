/*
 * $RCSfile: BistableObject2D.C,v $ 
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
 *  $Id: BistableObject2D.C,v 1.2 1996/09/13 08:03:20 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/BistableObject2D.h"

//________________________________________________________________ BistableObject2D

implementRTTI(BistableObject2D, InteractionObject2D);

BistableObject2D::BistableObject2D(Exemplar exemplar)
: MBistableObject<InteractionObject2D, BistableObject2D, Object2D, Object2DAttr, Shared2D, World2D, Path2D>(exemplar) {}

BistableObject2D::BistableObject2D(Object2D* on, Object2D* off, Switch state)
: MBistableObject<InteractionObject2D, BistableObject2D, Object2D, Object2DAttr, Shared2D, World2D, Path2D>(on, off, state) {}

