/*
 * $RCSfile: Boundary2D.h,v $
 *
 * Compute the convex hull of a 2D point set. The convex hull is 
 * displayed by adding line segments to the world.
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: Boundary2D.h,v 1.1 1996/12/06 14:55:03 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Boundary2D_H
#define _Boundary2D_H

#include "booga/component/Operation2D.h"

class Texture2D;

//_________________________________________________________________ Boundary2D

class Boundary2D : public Operation2D {
declareRTTI(Boundary2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Boundary2D(long maxVertex = 128, double precision = 0.1);
private:
  // Boundary2D(const Boundary2D&);          // se default version.

public:
  virtual ~Boundary2D();

private:
  Boundary2D& operator=(const Boundary2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Boundary2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptTexture(Texture2D* boundaryTexture);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  long myMaxVertex;
  double myPrecision;
  Texture2D* myBoundaryTexture;
};

//______________________________________________________________________ INLINES

#endif // _Boundary2D_H

