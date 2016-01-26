/*
 * BinomialCoeffs.h
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
 *  $Id: BinomialCoeffs.h,v 1.3 1996/01/12 16:09:38 streit Exp $ 
 * -----------------------------------------------------------------------------
 */

#ifndef _BinomialCoeffs_H
# define _BinomialCoeffs_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/nurbs/BaseArray.h"

//_______________________________________________________________ BinomialCoeffs

class BinomialCoeffs {
public:
  BinomialCoeffs (int n = 0);
  ~BinomialCoeffs (void);

public:
  void reCalculate (int n = 0);
  Real get (int n, int k);

private:
  Array2DOf<Real> *myCoefficients;
};

//______________________________________________________________________ INLINES

inline BinomialCoeffs::BinomialCoeffs (int n)
{
  myCoefficients = new Array2DOf<Real>;
  reCalculate (n);
}

inline BinomialCoeffs::~BinomialCoeffs (void)
{
  delete myCoefficients;
}

inline Real BinomialCoeffs::get (int n, int k)
{
  return myCoefficients->get (n, k);
}

#endif // _BinomialCoeffs_H

