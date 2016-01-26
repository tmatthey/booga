/*
 * $RCSfile: Shared2D.C,v $
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
 *  $Id: Shared2D.C,v 1.11 1996/09/13 08:06:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Shared2D.h"

//_____________________________________________________________________ Shared2D

implementRTTI(Shared2D, Object2D);

Shared2D::Shared2D(Object2D* adoptObject)
: MShared<Object2D, Shared2D, Path2D, Ray2D>(adoptObject) {}

Shared2D::Shared2D(Object2D* adoptObject, const Name defName)
: MShared<Object2D, Shared2D, Path2D, Ray2D>(adoptObject, defName) {}

