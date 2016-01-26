/*
 * $RCSfile: Object2D.h,v $
 *
 * Base class of Object2D hierarchy. 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Object2D.h,v 1.25 1996/10/04 09:47:33 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Object2D_H
#define _Object2D_H

#include "booga/base/BoundingRect.h"
#include "booga/object/BOOGAObject.h"
#include "booga/object/Transform2D.h"
#include "booga/object/Ray2D.h"

class Path2D;
class Texture2D;

//_____________________________________________________________________ Object2D

class Object2D : public BOOGAObject<Object2D, Transform2D, Vector2D, BoundingRect, Ray2D> {
declareRTTI(Object2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Object2D();
  Object2D(Exemplar);
protected:
  Object2D(const Object2D& object);      // Internal use only.
  
public:
  virtual ~Object2D();
  
private:
  Object2D& operator=(const Object2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Object2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object2D* copy() const = 0;
  // Virtual copy constructor.

  static void recomputeBounds(const Path2D& path);
  // An object on the path given as a parameter has changed its appearance. The
  // bounding boxes of the objects on this path have to be recomputed.

  virtual Object2D* makeUnique(Path2D* path = NULL, bool shared = false) = 0;
  // Make an object a unique instance. 
  // If makeUnique() is called without a path, every object in the object 
  // tree ('this' is the root) is copied if it is shared with others (see class 
  // Shared2D).
  // If the path is provided as a parameter, unique instances are created only 
  // on the path. 'shared' is a flag that indicates if a predecessor beeing 
  // shared, so copying of objects has to be performed.

  void appendTexture(Texture2D* adoptTexture);
  const Texture2D* getTexture() const;
  Texture2D* orphanTexture();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Texture2D*  myTexture;     // Local textures.
};

//______________________________________________________________________ INLINES

inline const Texture2D* Object2D::getTexture() const
{
  return myTexture;
}

#endif // _Object2D_H

