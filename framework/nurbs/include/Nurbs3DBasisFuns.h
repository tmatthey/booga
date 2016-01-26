/*
 * Nurbs3DBasisFuns.h
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
 *  $Id: Nurbs3DBasisFuns.h,v 1.3 1996/01/12 16:09:42 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DBasisFuns_H
# define _Nurbs3DBasisFuns_H

#include "booga/nurbs/Nurbs3DTypes.h"

class Nurbs3DKnots;      // Forward declaration

//_____________________________________________________________ Nurbs3DBasisFuns

class Nurbs3DBasisFuns {
public:
  Nurbs3DBasisFuns (void);
  Nurbs3DBasisFuns (Nurbs3DKnots *adoptKnots);
  ~Nurbs3DBasisFuns (void);

public:
  void         adoptKnots (Nurbs3DKnots *knots);
  Nurbs3DKnots *copyKnots (void);
  Nurbs3DKnots *orphanKnots (void);

public:
  void calculate (Real u);
  void calculate (Real u, int span);
  void calculateAll (Real u, int deg);
  void calculateAll (Real u, int span, int deg);
  Real get (int i);
  Real get (int i, int j);

private:
  Nurbs3DKnots *myKnots;
  RealArr2D    *myBasisFuns;
};

//______________________________________________________________________ INLINES

inline Real Nurbs3DBasisFuns::get (int i)
{
  return myBasisFuns->get (i, 0);
}

inline Real Nurbs3DBasisFuns::get (int i, int j)
{
  return myBasisFuns->get (i, j);
}

#endif // _Nurbs3DBasisFuns_H

