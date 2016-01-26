 /*
 * PerspectiveViewing3D.h
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
 *  $Id: PerspectiveViewing3D.h,v 1.6 1996/10/04 09:47:51 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PerspectiveViewing3D_H
#define _PerspectiveViewing3D_H

#include "booga/object/Viewing3D.h"

//_________________________________________________________ PerspectiveViewing3D

class PerspectiveViewing3D : public Viewing3D {
declareRTTI(PerspectiveViewing3D); 
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PerspectiveViewing3D();
  PerspectiveViewing3D(Exemplar);
  // PerspectiveViewing3D(const PerspectiveViewing3D&);  // Use default version

public:
  // virtual ~PerspectiveViewing3D();                    // Use deafult version.

private:
  PerspectiveViewing3D& operator=(const PerspectiveViewing3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PerspectiveViewing3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Viewing3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Vector3D transformWorld2Screen(const Vector3D& p) const;
  virtual Vector3D transformView2Screen(const Vector3D& p) const;
  virtual Vector3D transformView2NormalScreen(const Vector3D& p) const;

  virtual void computeRayThrough(int x, int y, Ray3D& ray) const;

  virtual Viewing3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual RCString getKeyword() const;
  virtual void iterateAttributes(MakeableHandler *handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

};

//______________________________________________________________________ INLINES

#endif // _PerspectiveViewing3D_H

