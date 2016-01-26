/*
 * $RCSfile: ConvexHull2D.h,v $
 *
 * Compute the convex hull of a 2D point set. The convex hull is 
 * displayed by adding line segments to the world.
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
 *  $Id: ConvexHull2D.h,v 1.3 1996/08/01 11:59:35 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ConvexHull2D_H
#define _ConvexHull2D_H

#include "booga/component/Operation2D.h"

class Texture2D;

//_________________________________________________________________ ConvexHull2D

class ConvexHull2D : public Operation2D {
declareRTTI(ConvexHull2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ConvexHull2D();
private:
  // ConvexHull2D(const ConvexHull2D&);          // se default version.

public:
  virtual ~ConvexHull2D();

private:
  ConvexHull2D& operator=(const ConvexHull2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ConvexHull2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptTexture(Texture2D* hullTexture);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Texture2D* myHullTexture;
};

//______________________________________________________________________ INLINES

#endif // _ConvexHull2D_H

