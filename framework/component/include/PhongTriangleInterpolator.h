/*
 * PhongTriangleInterpolator.h
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: PhongTriangleInterpolator.h,v 1.1 1996/09/13 08:05:31 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PhongTriangleInterpolator_H
#define _PhongTriangleInterpolator_H

#include "booga/component/TriangleInterpolator.h"

//____________________________________________________ PhongTriangleInterpolator

class PhongTriangleInterpolator : public TriangleInterpolator {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Use default versions.
  // PhongTriangleInterpolator();
  // PhongTriangleInterpolator(const PhongTriangleInterpolator&);

public:
  // Use default version. 
  // virtual ~PhongTriangleInterpolator();

private:
  // No assignments.
  PhongTriangleInterpolator& operator=(const PhongTriangleInterpolator&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TriangleInterpolator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TriangleInterpolator* copy() const;
  virtual void getColor(Color& color);

protected:
  virtual void doInit(int firstPoint);
  virtual void doComputeScanLine(Real startFactor, Real endFactor);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Vector3D myStartNormal, myEndNormal;
};

#endif
