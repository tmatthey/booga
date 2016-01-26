/*
 * $RCSfile: Ray3DUtilities.h,v $
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
 *  $Id: Ray3DUtilities.h,v 1.8 1996/08/09 14:53:23 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Ray3DUtilities_H
#define _Ray3DUtilities_H

#include "booga/base/PrimitiveTypes.h"  // bool

class Ray3D;
class Color;
class Texture3DContext;

//_______________________________________________________________ Ray3DUtilities

class Ray3DUtilities {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Ray3DUtilities();                               // No construction.
  Ray3DUtilities(const Ray3DUtilities&);          // No copies.

private:
  ~Ray3DUtilities();                              // No destruction.

private:
  Ray3DUtilities& operator=(const Ray3DUtilities&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Ray3DUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static bool shadeSecondary(Ray3D* ray, Color& color, const Texture3DContext& context);
  // Returns true if secondary ray has hit an object, false otherwise.
  
  friend class _dummy;
  // Avoid warning about private ctor/dtor and no friends.
};

//______________________________________________________________________ INLINES

#endif // _Ray3DUtilities_H

