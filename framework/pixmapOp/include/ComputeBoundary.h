/*
 * $RCSfile: ComputeBoundary.h,v $
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
 *  $Id: ComputeBoundary.h,v 1.1 1996/12/06 14:25:29 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ComputeBoundary_H
#define _ComputeBoundary_H

#include "booga/base/List.h"
#include "booga/base/Vector2D.h"
#include "booga/pixmapOp/PixmapGenerator.h"

//__________________________________________________________ ComputeBoundary

class ComputeBoundary : public PixmapGenerator {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ComputeBoundary();
private:
  ComputeBoundary(const ComputeBoundary&);	         // No copies.

public:
  // virtual ~ComputeBoundary();   // Use default version.

private:
  ComputeBoundary& operator=(const ComputeBoundary&);  // No assignments.

public:
  const List<Vector2D>& getBoundaryPoints() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class PixmapGenerator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual AbstractPixmap* generate(const AbstractPixmap* pm);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private: 
  List<Vector2D> myBoundaryPoints; // store the boundary points
  static int ourDeltaX[]; // offset array needed to compute positions of neighbour points
  static int ourDeltaY[];
};

#endif // _ComputeBoundary_H

