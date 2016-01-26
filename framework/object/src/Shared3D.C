/*
 * $RCSfile: Shared3D.C,v $
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Shared3D.C,v 1.12 1996/09/13 08:06:19 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Shared3D.h"

//_____________________________________________________________________ Shared3D

implementRTTI(Shared3D, Object3D);

Shared3D::Shared3D(Object3D* adoptObject)
: MShared<Object3D, Shared3D, Path3D, Ray3D>(adoptObject) {}

Shared3D::Shared3D(Object3D* adoptObject, const Name defName)
: MShared<Object3D, Shared3D, Path3D, Ray3D>(adoptObject, defName) {}

