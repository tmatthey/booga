/*
 * Path3D.h
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
 *  $Id: Path3D.h,v 1.2 1995/08/11 15:02:07 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Path3D_H
# define _Path3D_H

#include "booga/object/PathOf.h"
#include "booga/object/Transform3D.h"

class Object3D;

//_______________________________________________________________________ Path3D

// typedef PathOf<Object3D, Transform3D> Path3D;

class Path3D : public PathOf<Object3D, Transform3D> {};

#endif // _Path3D_H

