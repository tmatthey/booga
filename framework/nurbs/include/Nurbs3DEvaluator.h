/*
 * Nurbs3DEvaluator.h
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
 *  $Id: Nurbs3DEvaluator.h,v 1.3 1996/01/12 16:09:44 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DEvaluator_H
# define _Nurbs3DEvaluator_H

#include "booga/nurbs/Nurbs3DHandler.h"

//_____________________________________________________________ Nurbs3DEvaluator

class Nurbs3DEvaluator : public Nurbs3DHandler {
declareRTTI(Nurbs3DEvaluator);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DEvaluator (void) : Nurbs3DHandler () {};
  Nurbs3DEvaluator (Nurbs3D *adoptNurbs) : Nurbs3DHandler (adoptNurbs) {};
//   virtual ~Nurbs3DEvaluator (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DEvaluator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void     derivatives (Real u, int d, PtArray1D *CK) const;
  virtual void     derivatives (Real u, Real v, int d, PtArray2D *SKL) const;
  virtual Nurbs3D* derivativeCurve (int d) const;
  virtual Nurbs3D* derivativeSurface (int du, int dv) const;
  virtual Vector3D evaluate (Real u) const;
  virtual Vector3D evaluate (Real u, Real v) const;
  virtual Nurbs3D* isoParametricU (Real u) const;
  virtual Nurbs3D* isoParametricV (Real v) const;
  virtual void     tangents (Real u, Vector3D &pt, Vector3D &tu) const;
  virtual void     tangents (Real u, Real v, Vector3D &pt, Vector3D &tu, Vector3D &tv, Vector3D &nl) const;

protected:
  virtual void     derivativePoints (int d, int r1, int r2, Vec4DArr2D *PK) const;
  virtual void     derivativePoints (int d, int r1, int r2, int s1, int s2, Vec4DArr4D *PKL) const;
  virtual Vector3D evaluateBasisFuns (Real u) const;
  virtual Vector3D evaluateBasisFuns (Real u, Real v) const;
  virtual Vector3D evaluateCornerCut (Real u) const;
  virtual Vector3D evaluateCornerCut (Real u, Real v) const;
  virtual Vector3D evaluateDeBoor (Real u) const;
  virtual Vector3D evaluateDeBoor (Real u, Real v) const;
  virtual Real     evaluateDeBoorW (Real u) const;
  virtual Nurbs3D* isoParametricBasisFuns (Real u) const;
  virtual Nurbs3D* isoParametricCornerCut (Real u) const;
  virtual Nurbs3D* isoParametricDeBoor (Real u) const;

private:
  virtual void     derivativePoints (int p, KnotArray *U, int d, int r, Vec4DArr1D *Pw, Vec4DArr2D *PK) const;
  virtual Vector3D du (int i, int k, Real u) const;
  virtual Real     wu (int i, int k, Real u) const;
  virtual Real     au (int i, int k, Real u) const;

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

#endif // _Nurbs3DEvaluator_H

