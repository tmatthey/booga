/*
 * GouraudTriangleInterpolator.h
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
 *  $Id: GouraudTriangleInterpolator.h,v 1.1 1996/09/13 08:04:40 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GouraudTriangleInterpolator_H
#define _GouraudTriangleInterpolator_H

#include "booga/component/TriangleInterpolator.h"

//__________________________________________________ GouraudTriangleInterpolator

class GouraudTriangleInterpolator : public TriangleInterpolator {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Use default versions.
  // GouraudTriangleInterpolator();
  // GouraudTriangleInterpolator(const GouraudTriangleInterpolator&);

public:
  // Use default version.
  // virtual ~GouraudTriangleInterpolator();

private:
  // No assignments.
  GouraudTriangleInterpolator& operator=(const GouraudTriangleInterpolator&);

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
  Color myColor[3];
  Color myStartColor, myEndColor;
};

#endif
