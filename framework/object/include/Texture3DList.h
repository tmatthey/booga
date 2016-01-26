/*
 * Texture3DList.h
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Texture3DList.h,v 1.10 1996/10/04 09:48:42 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Texture3DList_H
# define _Texture3DList_H

#include "booga/base/List.h"
#include "booga/base/MIterator.h"
#include "booga/object/Texture3D.h"

//________________________________________________________________ Texture3DList

class Texture3DList : public Texture3D, 
		      public MIterator<Texture3D*,List<Texture3D*> > {
declareRTTI(Texture3DList);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Texture3DList();
  Texture3DList(Exemplar);
  Texture3DList(const Texture3DList& textureList);

public:
  virtual ~Texture3DList();

private:
  Texture3DList& operator=(const Texture3DList&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Texture3DList
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void appendTexture(Texture3D* adoptTexture);
  
// Iterator interface
public:
  const Texture3D* getTexture() const;
private:
  virtual List<Texture3D*>* getContainer();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture3D* copy() const;
  virtual void doTexturing(Texture3DContext& context) const;
  virtual void computeCumulatedTransform(const Transform3D& additionalTransform);
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual void iterateAttributes(MakeableHandler *handler);
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Texture3D*> myTextures;
};

#endif // _Texture3DList_H

