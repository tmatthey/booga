/*
 * $RCSfile: Texture3D.h,v $
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
 *  $Id: Texture3D.h,v 1.9 1996/10/04 09:48:36 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Texture3D_H
#define _Texture3D_H

#include <stdlib.h> // for the definition of NULL
#include "booga/object/Transform3D.h"
#include "booga/object/ObjectSpecifier.h"

class Texture3DContext;
class Path3D;

//____________________________________________________________________ Texture3D

class Texture3D : public ObjectSpecifier {
  declareRTTI(Texture3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Texture3D();                          // Use default version.
  // Texture3D(const Texture3D&);          // Use default version.
  
public:
  // virtual ~Texture3D();                 // Use default version.

private:
  Texture3D& operator=(const Texture3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const = 0;
  // Virtual copy ctor.

  static void texturing(Texture3DContext& context, const Path3D* path);
  // Do texturing by visiting all objects on the path with textures 
  // attached and call texturing(context) for each.

  virtual void texturing(Texture3DContext& context) const;
  // Apply the transformation of the texture and call 
  // doTexturing() to perform texturing calculations.

  virtual void doTexturing(Texture3DContext& context) const = 0;
  // doTexturing is internally called by the template method texturing().
  // It would be better style to put doTexturing() in the protected section 
  // of the class. But a Texture3DList aggregate has to call doTexturing() 
  // for all its members, and this is not allowed! (see ARM p. 253ff). 
  // So doTexturing() resides in the public section...

  void addTransform(const Transform3D& transform);
  // Concat 'transform' with the current transformation. 
  const Transform3D& getTransform() const;
  // Returns transformation to be applied to the object 

  virtual void computeCumulatedTransform(const Transform3D& additionalTransform);
  // Compute the cumulated transformation according to the position in the texture
  // hierachie.
  const Transform3D& getCumulatedTransform() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Transform3D myTransform;
  Transform3D myCumulatedTransform;
};

//______________________________________________________________________ INLINES

inline const Transform3D& Texture3D::getTransform() const
{
  return myTransform;
}

inline const Transform3D& Texture3D::getCumulatedTransform() const
{
  return myCumulatedTransform;
}


 
#endif // _Texture3D_H

