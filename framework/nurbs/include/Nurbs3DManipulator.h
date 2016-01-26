/*
 * Nurbs3DManipulator.h
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
 *  $Id: Nurbs3DManipulator.h,v 1.3 1996/01/12 16:09:47 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DManipulator_H
# define _Nurbs3DManipulator_H

#include "booga/nurbs/Nurbs3DHandler.h"

class Nurbs3DKnots;       // Forward declaration

//___________________________________________________________ Nurbs3DManipulator

class Nurbs3DManipulator : public Nurbs3DHandler {
declareRTTI(Nurbs3DManipulator);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DManipulator (void) : Nurbs3DHandler () {};
  Nurbs3DManipulator (Nurbs3D *adoptNurbs) : Nurbs3DHandler (adoptNurbs) {};
//   virtual ~Nurbs3DManipulator (void);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DManipulator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void elevateU (void);
  virtual void elevateV (void);
  virtual void insertKnotU (Real u, int r = 1);
  virtual void insertKnotV (Real v, int r = 1);
  virtual void joinPatchesInU (int cn, Nurbs3D *nrb1, Nurbs3D *nrb2, bool force = false);
  virtual void joinPatchesInV (int cn, Nurbs3D *nrb1, Nurbs3D *nrb2, bool force = false);
  virtual void refineU (Nurbs3DKnots *refineKnots);
  virtual void refineV (Nurbs3DKnots *refineKnots);
  virtual int  removeKnotU (Real u, int num = 1, Real tol = 0.0, bool force = false);
  virtual int  removeKnotV (Real v, int num = 1, Real tol = 0.0, bool force = false);
  virtual void splitAtU (Real u, Nurbs3D *nrb1, Nurbs3D *nrb2);
  virtual void splitAtV (Real v, Nurbs3D *nrb1, Nurbs3D *nrb2);
  virtual Nurbs3DKnots *createRefinedKnotsU (Real prec) const;
  virtual Nurbs3DKnots *createRefinedKnotsV (Real prec) const;

protected:
  virtual void insertKnotCurve (Real u, int r);
  virtual void insertKnotSurface (Real u, int r);
  virtual void refineCurve (Nurbs3DKnots *refineKnots);
  virtual void refineSurface (Nurbs3DKnots *refineKnots);
  virtual int  removeKnotCurve (Real u, int num, Real tol, bool force);
  virtual int  removeKnotSurface (Real u, int num, Real tol, bool force);

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

#endif // _Nurbs3DManipulator_H
