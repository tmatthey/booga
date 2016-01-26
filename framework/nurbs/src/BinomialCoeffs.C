/*
 * BinomialCoeffs.C 
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
 *  $Id: BinomialCoeffs.C,v 1.3 1996/01/12 16:06:10 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/BinomialCoeffs.h"

//_______________________________________________________________ BinomialCoeffs

void BinomialCoeffs::reCalculate (int n)
{
  if (n < 0)
    Report::error ("[BinomialCoeffs::reCalculate] called with negative size!");

  register int i, j;

  myCoefficients->initSize (n+1, n+1);
  for (i = 0; i <= n; i++)              // Calculate binomial coefficients
  {
    myCoefficients->set (i, 0, 1.0);    // Initialize binom (n, 0)
    for (j = 1; j < i; j++)             // Calculate binom (n+1, k+1) = binom (n, k) + binom (n, k+1)
      myCoefficients->set (i, j, myCoefficients->get (i-1, j-1) + myCoefficients->get (i-1, j));
    myCoefficients->set (i, i, 1.0);    // Initialize binom (n, n)
    for (j = i+1; j <= n; j++)
      myCoefficients->set (i, j, 0.0);  // Initialize binom (n, k) with k > n
  }
}
