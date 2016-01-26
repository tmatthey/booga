/*
 * Object3D.h 
 *
 * Base class of Object3D hierarchy. 
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
 *  $Id: Object3D.h,v 1.23 1996/10/04 09:47:35 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Object3D_H
#define _Object3D_H

#include "booga/base/BoundingBox.h"
#include "booga/object/BOOGAObject.h"
#include "booga/object/Transform3D.h"
#include "booga/object/Ray3D.h"

class Path3D;
class Texture3D;

//_____________________________________________________________________ Object3D

class Object3D : public BOOGAObject<Object3D, Transform3D, Vector3D, BoundingBox, Ray3D> {
declareRTTI(Object3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Object3D();
  Object3D(Exemplar);
protected:
  Object3D(const Object3D& object);      // Internal use only.
  
public:
  virtual ~Object3D();
  
private:
  Object3D& operator=(const Object3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const = 0;
  // Virtual copy constructor.

  static void recomputeBounds(const Path3D& path);
  // An object on the path given as a parameter has changed its appearance. The
  // bounding boxes of the objects on this path have to be recomputed.
  
  static void resetBounds(const Path3D& path);
  // An object on the path given as a parameter has changed its appearance. The
  // bounding boxes of the objects on this path have to be reset.
  
  virtual Object3D* makeUnique(Path3D* path = NULL, bool shared = false) = 0;
  // Make an object a unique instance. 
  // If makeUnique() is called without a path, every object in the object 
  // tree ('this' is the root) is copied if it is shared with others (see class 
  // Shared3D).
  // If the path is provided as a parameter, unique instances are created only 
  // on the path. 'shared' is a flag that indicates if a predecessor beeing 
  // shared, so copying of objects has to be performed.

  void appendTexture(Texture3D* adoptTexture);
  const Texture3D* getTexture() const;
  Texture3D* orphanTexture();

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
  Texture3D*  myTexture;     // Local textures.
};

//______________________________________________________________________ INLINES

inline const Texture3D* Object3D::getTexture() const
{
  return myTexture;
}

#endif // _Object3D_H

