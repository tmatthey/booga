/*
 * $RCSfile: Texture2D.h,v $
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
 *  $Id: Texture2D.h,v 1.8 1996/10/04 09:48:31 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Texture2D_H
#define _Texture2D_H

#include <stdlib.h> // for the definition of NULL
#include "booga/object/Transform2D.h"
#include "booga/object/ObjectSpecifier.h"

class Texture2DContext;
class Path2D;

//____________________________________________________________________ Texture2D

class Texture2D : public ObjectSpecifier {
declareRTTI(Texture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Texture2D();                          // Use default version.
  // Texture2D(const Texture2D&);          // Use default version.
  
public:
  // virtual ~Texture2D();                 // Use default version.

private:
  Texture2D& operator=(const Texture2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const = 0;
  // Virtual copy ctor.

  static void texturing(Texture2DContext& context, const Path2D* path);
  // Do texturing by visiting all objects on the path with textures 
  // attached and call texturing(context) for each.

  virtual void texturing(Texture2DContext& context) const;
  // Apply the transformation of the texture and call 
  // doTexturing() to perform texturing calculations.

  virtual void doTexturing(Texture2DContext& context) const = 0;
  // doTexturing is internally called by the template method texturing().
  // It would be better style to put doTexturing() in the protected section 
  // of the class. But a Texture2DList aggregate has to call doTexturing() 
  // for all its members, and this is not allowed! (see ARM p. 253ff). 
  // So doTexturing() resides in the public section...

  void addTransform(const Transform2D& transform);
  // Concat 'transform' with the current transformation. 
  const Transform2D& getTransform() const;
  // Returns transformation to be applied to the object 

  virtual void computeCumulatedTransform(const Transform2D& additionalTransform);
  // Compute the cumulated transformation according to the position in the texture
  // hierachie.
  const Transform2D& getCumulatedTransform() const;

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
  Transform2D myTransform;
  Transform2D myCumulatedTransform;
};

//______________________________________________________________________ INLINES

inline const Transform2D& Texture2D::getTransform() const
{
  return myTransform;
}

inline const Transform2D& Texture2D::getCumulatedTransform() const
{
  return myCumulatedTransform;
}

#endif // _Texture2D_H

