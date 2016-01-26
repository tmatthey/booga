/*
 * Nurbs3DBasisFuns.C 
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
 *  $Id: Nurbs3DBasisFuns.C,v 1.3 1996/01/12 16:06:18 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/Nurbs3DBasisFuns.h"

#include "booga/nurbs/Nurbs3DKnots.h"       // Class Nurbs3DKnots

//_____________________________________________________________ Nurbs3DBasisFuns

Nurbs3DBasisFuns::Nurbs3DBasisFuns (void)
{
  myKnots = NULL;
  myBasisFuns = NULL;
}

Nurbs3DBasisFuns::Nurbs3DBasisFuns (Nurbs3DKnots *adoptKnots)
{
  myKnots = adoptKnots;
  myBasisFuns = new RealArr2D (myKnots->getDegree()+1, 1);
}

Nurbs3DBasisFuns::~Nurbs3DBasisFuns (void)
{
  if (myKnots != NULL)
    delete myKnots;
  if (myBasisFuns != NULL)
    delete myBasisFuns;
}

void Nurbs3DBasisFuns::adoptKnots (Nurbs3DKnots *knots)
{
  if (myKnots != NULL)
    delete myKnots;
  myKnots = knots;
  if (myBasisFuns == NULL)
    myBasisFuns = new RealArr2D (myKnots->getDegree()+1, 1);
  else
    myBasisFuns->initSize (myKnots->getDegree()+1, 1);
}

Nurbs3DKnots* Nurbs3DBasisFuns::copyKnots (void)
{
  return new Nurbs3DKnots (*myKnots);
}

Nurbs3DKnots* Nurbs3DBasisFuns::orphanKnots (void)
{
  Nurbs3DKnots *retKnots = myKnots;

  myKnots = NULL;
  if (myBasisFuns != NULL)
  {
    delete myBasisFuns;
    myBasisFuns = NULL;
  }
  return retKnots;
}

void Nurbs3DBasisFuns::calculate (Real u)
{
  if (myKnots == NULL)
    Report::error ("[Nurbs3DBasisFuns::calculate] called on object without knots!");

  int span;

  if (myKnots->findSpan(u, span) == false)
  {
    Report::warning ("[Nurbs3DBasisFuns::calculate] value out of bounds!");
    return;
  }
  calculate (u, span);
}

void Nurbs3DBasisFuns::calculate (Real u, int span)
{
  if (myKnots == NULL)
    Report::error ("[Nurbs3DBasisFuns::calculate] called on object without knots!");

  register int i, r;
  int  p;
  Real temp, saved;

  p = myKnots->getDegree ();
  
  if (myBasisFuns == NULL)
    myBasisFuns = new RealArr2D (p+1, 1);
  else
    myBasisFuns->initSize (p+1, 1);
  RealArr1D left (p+1), right (p+1);

  myBasisFuns->set (0, 0, 1.0);          // Initial value
  for (i = 1; i <= p; i++)
  {
    left[i] = u - myKnots->get (span+1-i);
    right[i] = myKnots->get (span+i) - u;
    saved = 0.0;
    for (r = 0; r < i; r++)
    {
      temp = myBasisFuns->get (r, 0) / (right[r+1]+left[i-r]);
      myBasisFuns->set (r, 0, saved + right[r+1] * temp);
      saved = left[i-r] * temp;
    }
    myBasisFuns->set (i, 0, saved);
  }
}

void Nurbs3DBasisFuns::calculateAll (Real u, int deg)
{
  if (myKnots == NULL)
    Report::error ("[Nurbs3DBasisFuns::calculateAll] called on object without knots!");

  int span;

  if (myKnots->findSpan(u, span) == false)
  {
    Report::warning ("[Nurbs3DBasisFuns::calculateAll] value out of bounds!");
    return;
  }
  calculateAll (u, span, deg);
}

void Nurbs3DBasisFuns::calculateAll (Real u, int span, int deg)
{
  if (myKnots == NULL)
    Report::error ("[Nurbs3DBasisFuns::calculateAll] called on object without knots!");

  register int i, j, r;
  Real temp, saved;


  if (myBasisFuns == NULL)
    myBasisFuns = new RealArr2D (deg+1, deg+1);
  else
    myBasisFuns->initSize (deg+1, deg+1);
  RealArr1D left (deg+1), right (deg+1);

  for (j = 0; j <= deg; j++)
  {
    myBasisFuns->set (0, j, 1.0);          // Initial value
    for (i = 1; i <= j; i++)
    {
      left[i] = u - myKnots->get (span+1-i);
      right[i] = myKnots->get (span+i) - u;
      saved = 0.0;
      for (r = 0; r < i; r++)
      {
	temp = myBasisFuns->get (r, j) / (right[r+1]+left[i-r]);
	myBasisFuns->set (r, j, saved + right[r+1] * temp);
	saved = left[i-r] * temp;
      }
      myBasisFuns->set (i, j, saved);
    }
  }
}

