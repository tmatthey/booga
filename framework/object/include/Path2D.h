/*
 * Path2D.h
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
 *  $Id: Path2D.h,v 1.2 1995/08/11 15:02:06 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Path2D_H
# define _Path2D_H

#include "booga/object/Object2D.h"
#include "booga/object/PathOf.h"
#include "booga/object/Transform2D.h"

//_______________________________________________________________________ Path2D

// typedef  Path2D PathOf<Object2D, Transform2D>;

class Path2D : public PathOf<Object2D, Transform2D> {};

#endif // _Path2D_H

