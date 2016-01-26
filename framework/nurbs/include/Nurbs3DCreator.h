/*
 * Nurbs3DCreator.h
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Nurbs3DCreator.h,v 1.3 1996/01/12 16:09:43 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DCreator_H
# define _Nurbs3DCreator_H

#include "booga/nurbs/Nurbs3DHandler.h"

//_______________________________________________________________ Nurbs3DCreator

class Nurbs3DCreator : public Nurbs3DHandler {
  declareRTTI(Nurbs3DCreator);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DCreator (void) : Nurbs3DHandler () {};
  Nurbs3DCreator (Nurbs3D *adoptNurbs) : Nurbs3DHandler (adoptNurbs) {};
//   virtual ~Nurbs3DCreator (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DCreator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void extrude (Vector3D d, Real len);
  virtual void fitData (int numCtl, PtArray1D *pts, int deg = 2);
  virtual void fitData (int numUCt, int numVCt, PtArray2D *pts, int uDeg = 2, int vDeg = 2);
  virtual void interpolate (PtArray1D *dataPts, int deg = 2);
  virtual void interpolate (PtArray2D *dataPts, int udeg = 2, int vdeg = 2);
  virtual void ruledSurface (Nurbs3D *nrb1, Nurbs3D *nrb2);
  virtual void surfaceOfRevolution (void);
  virtual void sweep (Nurbs3D *traj);
  virtual void swing (Nurbs3D *traj);

private:
  virtual void interpolateC (PtArray1D *dataPts, PtArray1D *ctrlPts, Real *param, int deg, int vd = 0);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Nurbs3DHandler
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protected:
  void dummy (void) {};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

};

//______________________________________________________________________ INLINES



#endif // _Nurbs3DCreator_H
