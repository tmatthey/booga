/*
 * OrthographicViewing3D.h
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
 *  $Id: OrthographicViewing3D.h,v 1.7 1996/10/04 09:47:49 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _OrthographicViewing3D_H
#define _OrthographicViewing3D_H

#include "booga/object/Viewing3D.h"

//________________________________________________________ OrthographicViewing3D

class OrthographicViewing3D : public Viewing3D {
declareRTTI(OrthographicViewing3D); 
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  OrthographicViewing3D();   
  OrthographicViewing3D(Exemplar);
  // OrthographicViewing3D(const OrthographicViewing3D&);  // Use default version.

public:
  // virtual ~OrthographicViewing3D();                    // Use default version.

private:
  OrthographicViewing3D& operator=(const OrthographicViewing3D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class OrthographicViewing3D
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
  virtual RCString getKeyword() const;

protected:
  virtual bool buildView() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector3D myDirection;
  Vector3D myEyePlaneOrigin;
};

//______________________________________________________________________ INLINES

#endif // _OrthographicViewing3D_H

