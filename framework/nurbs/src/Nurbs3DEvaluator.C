/*
 * Nurbs3DEvaluator.C 
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
 *  $Id: Nurbs3DEvaluator.C,v 1.4 1996/02/16 13:37:49 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/nurbs/Nurbs3DTypes.h"
#include "booga/nurbs/BinomialCoeffs.h"
#include "booga/nurbs/Nurbs3DEvaluator.h"
#include "booga/nurbs/Nurbs3DBasisFuns.h"

#include "booga/nurbs/Nurbs3D.h"             // Class Nurbs3D and related

/***********************************************************
  Constants
***********************************************************/

/***********************************************************
  Static data
***********************************************************/

/***********************************************************
  Type definitions
***********************************************************/

//_____________________________________________________________ Nurbs3DEvaluator

implementRTTI(Nurbs3DEvaluator, Nurbs3DHandler);

/*
 * derivatives : Evaluate derivatives at parameter
 *
 * This function evaluates the derivatives up to order "d" of the given NURBS
 * curve
 */

void Nurbs3DEvaluator::derivatives (Real u, int d, PtArray1D *CK) const
{
  register int k, i;
  int      du, p, span;
  Vector3D vec;

  p = myNurbs->myKnotsU->getDegree ();
  du = min (d, p);
  myNurbs->myKnotsU->findSpan (u, span);

  Nurbs3DBasisFuns N (myNurbs->myKnotsU->copy());
  N.calculateAll (u, span, p);

  span++;
  Vec4DArr2D *PK = new Vec4DArr2D;
  derivativePoints (du, span-p, span, PK);

  Vec4DArr1D *CKw = new Vec4DArr1D (d+1);
  for (k = 0; k <= du; k++)                 // Calculate 4D-B-Spline derivatives
  {
    for (i = 0; i <= p-k; i++)
      (*CKw)[k] += N.get (i, p-k) * (*PK)[k][i];
  }

  PtArray1D *Aders = new PtArray1D (d+1);
  WtArray1D *wders = new WtArray1D (d+1);
  for (i = 0; i <= d; i++)                  // Split CKw into "Aders" and "wders"
  {
    Aders->set (i, Vector3D((*CKw)[i].x(), (*CKw)[i].y(), (*CKw)[i].z()));
    wders->set (i, (*CKw)[i].w());
  }

  BinomialCoeffs Bin (d);              // Generate binomial coefficients
  CK->initSize (d+1);
  for (k = 0; k <= d; k++)             // Calculate rational derivatives
  {
    vec = Aders->get (k);
    for (i = 1; i <= k; i++)
      vec -= Bin.get (k, i) * wders->get (i) * CK->get (k-i);
    CK->set (k, vec / wders->get(0));
  }

  delete PK;                           // Clean up
  delete CKw;
  delete Aders;
  delete wders;
}

/*
 * derivatives : Evaluate derivatives at parameter
 *
 * This function evaluates the derivatives up to order "d" of the given NURBS
 * curve
 */

void Nurbs3DEvaluator::derivatives (Real u, Real v, int d, PtArray2D *SKL) const
{
  register int k, l, i, j;
  int      du, dv, dd, p, q, uspan, vspan;
  Vector4D tmp;
  Vector3D vec1, vec2;

  p = myNurbs->myKnotsU->getDegree ();
  q = myNurbs->myKnotsV->getDegree ();
  du = min (d, p);
  dv = min (d, q);
  myNurbs->myKnotsU->findSpan (u, uspan);
  myNurbs->myKnotsV->findSpan (v, vspan);

  Nurbs3DBasisFuns Nu (myNurbs->myKnotsU->copy());
  Nurbs3DBasisFuns Nv (myNurbs->myKnotsV->copy());
  Nu.calculateAll (u, uspan, p);
  Nv.calculateAll (v, vspan, q);

  uspan++;
  vspan++;

  Vec4DArr4D *PKL = new Vec4DArr4D;
  derivativePoints (d, uspan-p, uspan, vspan-q, vspan, PKL);

  Vec4DArr2D *SKLw = new Vec4DArr2D (d+1, d+1);
  for (k = 0; k <= du; k++)                       // Calculate 4D-B-Spline derivatives
  {
    dd = min (d-k, dv);
    for (l = 0; l <= dd; l++)
    {
      for (i = 0; i <= q-l; i++)
      {
	tmp = Vector4D (0, 0, 0, 0);;
	for (j = 0; j <= p-k; j++)
	  tmp += Nu.get (j, p-k) * (*PKL)[k][l][j][i];
	(*SKLw)[k][l] += Nv.get (i, q-l) * tmp;
      }
    }
  }

  PtArray2D *Aders = new PtArray2D (d+1, d+1);
  WtArray2D *wders = new WtArray2D (d+1, d+1);
  for (i = 0; i <= d; i++)                  // Split SKLw into "Aders" and "wders"
    for (j = 0; j <= d; j++)
    {
      Aders->set (i, j, Vector3D((*SKLw)[i][j].x(), (*SKLw)[i][j].y(), (*SKLw)[i][j].z()));
      wders->set (i, j, (*SKLw)[i][j].w());
    }

  BinomialCoeffs Bin (d);              // Generate binomial coefficients
  SKL->initSize (d+1, d+1);
  for (k = 0; k <= d; k++)             // Calculate rational derivatives
  {
    for (l = 0; l <= d-k; l++)
    {
      vec1 = Aders->get (k, l);
      for (j = 1; j <= l; j++)
	vec1 -= Bin.get (l, j) * wders->get (0, j) * SKL->get (k, l-j);
      for (i = 1; i <= k; i++)
      {
	vec1 -= Bin.get (k, i) * wders->get (i, 0) * SKL->get (k-i, l);
	vec2 = Vector3D (0, 0, 0);
	for (j = 1; j <= l; j++)
	  vec2 += Bin.get (l, j) * wders->get (i, j) * SKL->get (k-i, l-j);
	vec1 -= Bin.get (k, i) * vec2;
      }
      SKL->set (k, l, vec1 / wders->get(0, 0));
    }
  }

  delete PKL;
  delete SKLw;
  delete Aders;
  delete wders;
}

/*
 * derivativeCurve : Evaluate the derivative curve
 *
 * This function evaluates the derivative curve of order "d" of the given NURBS
 * curve
 */

Nurbs3D* Nurbs3DEvaluator::derivativeCurve (int d) const
{
  if (myNurbs->myType != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3DEvaluator::derivativeCurve] needs a curve");
    return NULL;
  }

  int p = myNurbs->myKnotsU->getDegree ();

  if (d > p-1)
    d = p - 1;
  if (d < 1)
  {
    Report::warning ("[Nurbs3DEvaluator::derivativeCurve] cannot calculate derivatives");
    return NULL;
  }

  int last = myNurbs->myKnotsU->getCount()- 1 - p;
  
  Vec4DArr2D *CK = new Vec4DArr2D;
  derivativePoints (d, 0, last, CK);

  register int x;
  int n = CK->getCountU ();
  PtArray1D *pts = new PtArray1D (n-d);
  WtArray1D *wts = new WtArray1D (n-d);

  for (x = 0; x < n-d; x++)
  {
    pts->set (x, (CK->get(d, x)).make3D());
    wts->set (x, (CK->get(d, x)).w());
  }

  Nurbs3DKnots *uknots = myNurbs->myKnotsU->copy ();
  Nurbs3DPoints *points = new Nurbs3DPoints (pts);
  Nurbs3DWeights *weights = new Nurbs3DWeights (wts);

  uknots->setDegree (p-d);
  uknots->scanKnots ();

  return new Nurbs3D (uknots, points, weights);
}

/*
 * derivativeSurface : Evaluate the derivative surface
 *
 * This function evaluates the derivative surface of order "du" and "dv"  of the
 * given NURBS surface
 */

Nurbs3D* Nurbs3DEvaluator::derivativeSurface (int /* du */, int /* dv */) const
{
//   if (myNurbs->myType != Nurbs3DTypes::Surface)
//   {
//     Report::warning ("[Nurbs3DEvaluator::derivativeSurface] needs a surface");
    return NULL;
//   }

//   int d = max (du, dv);

}

/*
 * evaluate : Evaluate point on curve at given parameter
 *
 * This function calls the evaluator function according to the specified
 * evaluation method of the NURBS
 */

Vector3D Nurbs3DEvaluator::evaluate (Real u) const
{
  switch (myNurbs->myEvaluation)
    {
    case Nurbs3DTypes::BasisFuns:
      return evaluateBasisFuns (u);

    case Nurbs3DTypes::CornerCut:
      return evaluateCornerCut (u);

    case Nurbs3DTypes::DeBoor:
      return evaluateDeBoor (u);

    default:
      Report::error ("[Nurbs3DEvaluator::evaluate] unknown evaluation type specified!");
      return Vector3D ();
    }
}

/*
 * evaluate : Evaluate point on surface at given parameters
 *
 * This function calls the evaluator function according to the specified
 * evaluation method of the NURBS
 */

Vector3D Nurbs3DEvaluator::evaluate (Real u, Real v) const
{
  switch (myNurbs->myEvaluation)
    {
    case Nurbs3DTypes::BasisFuns:
      return evaluateBasisFuns (u, v);

    case Nurbs3DTypes::CornerCut:
      return evaluateCornerCut (u, v);

    case Nurbs3DTypes::DeBoor:
      return evaluateDeBoor (u, v);

    default:
      Report::error ("[Nurbs3DEvaluator::evaluate] unknown evaluation type specified!");
      return Vector3D ();
    }
}

/*
 * isoParametricU : Extract iso-parametric curve from surface
 *
 * This function calls the appropriate function for extracting an iso-parametric
 * curve which is given by the NURBS
 */

Nurbs3D* Nurbs3DEvaluator::isoParametricU (Real u) const
{
  switch (myNurbs->myEvaluation)
    {
    case Nurbs3DTypes::BasisFuns:
      return isoParametricBasisFuns (u);

    case Nurbs3DTypes::CornerCut:
      return isoParametricCornerCut (u);

    case Nurbs3DTypes::DeBoor:
      return isoParametricDeBoor (u);

    default:
      Report::error ("[Nurbs3DEvaluator::isoParametricU] unknown evaluation type specified!");
      return new Nurbs3D;
    }
}

/***   isoParametricV : Extract isoparametric v-curve   ***/
//                                                        //
//  This function extracts an isoparametric curve in      //
//  v-direction by transposing the element, extracting    //
//  the u-curve and retransposing the element.            //
//                                                        //
/**********************************************************/

Nurbs3D* Nurbs3DEvaluator::isoParametricV (Real v) const
{
  myNurbs->transpose ();                    // Setup for curve extraction
  Nurbs3D *retCurve = isoParametricU (v);   // Extract curve in u-direction
  myNurbs->transpose ();                    // Retranspose
  return retCurve;
}

/***   tangents : Get tangent direction   *****************/
//                                                        //
//  This function calculates a point on a curve by        //
//  corner-cutting and derives thus also the tangent      //
//  in u-direction.                                       //
//                                                        //
/**********************************************************/

void Nurbs3DEvaluator::tangents (Real u, Vector3D &pt, Vector3D &tu) const
{
  if (myNurbs->myType != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3DEvaluator::tangents] needs a curve");
    return;
  }

  PtArray1D *ptAndDer = new PtArray1D;
  derivatives (u, 1, ptAndDer);             // Calculate point and derivative

  pt = ptAndDer->get (0);                   // Get point
  tu = ptAndDer->get (1);                   // Get tangent
  tu.normalize ();                          // We indicate only directions
  delete ptAndDer;                          // Clean up
}

/***   tangents : Get tangent directions   ****************/
//                                                        //
//  This function calculates a point on a curve by        //
//  corner-cutting and derives thus also the tangents     //
//  in u- and v-directions and from them the surface      //
//  normal in the given point.                            //
//                                                        //
/**********************************************************/

void Nurbs3DEvaluator::tangents (Real u, Real v, Vector3D &pt, Vector3D &tu, Vector3D &tv, Vector3D &nl) const
{
  if (myNurbs->myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3DEvaluator::tangents] needs a surface");
    return;
  }

  pt = evaluate (u, v);                // Calculate point

  if (myNurbs->isDegenerated())
  {
    if (myNurbs->isDegeneratedFirstRowU() &&  equal(u, myNurbs->myKnotsU->getFirstKnot()))
      u += EPSILON;
    else if (myNurbs->isDegeneratedLastRowU() && equal(u, myNurbs->myKnotsU->getLastKnot()))
      u -= EPSILON;
    if (myNurbs->isDegeneratedFirstRowV() && equal(v, myNurbs->myKnotsV->getFirstKnot()))
      v += EPSILON;
    else if (myNurbs->isDegeneratedLastRowV() && equal(v, myNurbs->myKnotsV->getLastKnot()))
      v -= EPSILON;
  }

  PtArray2D *ptAndDers = new PtArray2D;
  derivatives (u, v, 1, ptAndDers);

  tu = ptAndDers->get (1, 0);
  tv = ptAndDers->get (0, 1);

  nl = tu * tv;                        // Surface normal
  tu.normalize ();                     // Only tangent and normal directions are given
  tv.normalize ();
  nl.normalize ();
  delete ptAndDers;                         // Clean up
}


/*
 * derivativePoints : Evaluate control points for derivatives at parameter
 *
 * This function evaluates the derivatives up to order "d" of the given NURBS
 * curve
 */

void Nurbs3DEvaluator::derivativePoints (int d, int r1, int r2, Vec4DArr2D *PK) const
{
  register int i;
  int r = r2 - r1, uc, p;

  uc = myNurbs->myKnotsU->getCount ();
  p = myNurbs->myKnotsU->getDegree ();

  KnotArray  *U = new KnotArray (r+p);
  Vec4DArr1D *Pw = new Vec4DArr1D (r+1);

  for (i = 0; i < r+p; i++)               // Initialize knots <<<=== to do !!!
    U->set (i, myNurbs->myKnotsU->get(r1+i));
  for (i = 0; i <= r; i++)                // Initialize only points that are used!
    Pw->set (i, Vector4D(myNurbs->myPoints->get (r1+i), myNurbs->myWeights->get(r1+i)));

  derivativePoints (p, U, d, r, Pw, PK);  // Calculate derivative points
  delete U;                               // Clean up
  delete Pw;
}

/*
 * derivativePoints : Evaluate control points for derivatives at parameter
 *
 * This function evaluates the derivatives up to order "d" of the given NURBS
 * curve
 */

void Nurbs3DEvaluator::derivativePoints (int d, int r1, int r2, int s1, int s2, Vec4DArr4D *PKL) const
{
  register int i, j, k, l;
  int p, q, uc, vc, du, dv, dd, r = r2 - r1, s = s2 - s1;

  uc = myNurbs->myKnotsU->getCount ();
  vc = myNurbs->myKnotsV->getCount ();
  p = myNurbs->myKnotsU->getDegree ();
  q = myNurbs->myKnotsV->getDegree ();
  du = min (d, p);
  dv = min (d, q);

  KnotArray  *UV = new KnotArray;
  Vec4DArr1D *Pw = new Vec4DArr1D;
  Vec4DArr2D *temp = new Vec4DArr2D (p+1, q+1);           // Stay on the safe side

  UV->initSize (r+p);
  for (i = 0; i < r+p; i++)
    UV->set (i, myNurbs->myKnotsU->get(r1+i));

  Pw->initSize (r+1);
  PKL->initSize (p+1, q+1, p+1, q+1);
  for (j = s1; j <= s2; j++)
  {
    for (i = 0; i <= r; i++)
      Pw->set (i, Vector4D(myNurbs->myPoints->get(r1+i, j), myNurbs->myWeights->get(r1+i, j)));

    derivativePoints (p, UV, du, r, Pw, temp);
    for (k = 0; k <= du; k++)
      for (i = 0; i <= r-k; i++)
	(*PKL)[k][0][i][j-s1] = temp->get (k, i);
  }

  UV->initSize (s+q);
  for (i = 0; i < s+q; i++)
    UV->set (i, myNurbs->myKnotsV->get(s1+i));

  Pw->initSize (s+1);
  for (k = 0; k <= du; k++)
  {
    for (i = 0; i <= r-k; i++)
    {
      dd = min (d-k, dv);
      for (j = 0; j <= s; j++)
	Pw->set (j, PKL->get(k, 0, i, j));

      derivativePoints (q, UV, dd, s, Pw, temp);
      for (l = 1; l <= dd; l++)
	for (j = 0; j <= s-l; j++)
	  (*PKL)[k][l][i][j] = temp->get (l, j);
    }
  }

  delete UV;                          // Clean up
  delete Pw;
  delete temp;
}

/***   evaluate : Evalute point on curve   ****************/
//                                                        //
//  A point on the curve is computed using the            //
//  non-rational basis functions N_i^k(u).                //
//                                                        //
/**********************************************************/

Vector3D Nurbs3DEvaluator::evaluateBasisFuns (Real u) const
{
  int p = myNurbs->myKnotsU->getDegree ();           // Get degree of curve
  int span;

  if (myNurbs->myKnotsU->findSpan(u, span) == false)
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateBasisFuns] value out of bounds!");
    return Vector3D ();
  }

  register   int i;
  Vec4DArr1D Pw (p+1);                 // Array for 4D control points
  Vector4D   Cw;                       // Resulting point

  for (i = 0; i <= p; i++)
    Pw.set (i, Vector4D(myNurbs->myPoints->get(span-p+i+1),
			myNurbs->myWeights->get(span-p+i+1)));

  Nurbs3DBasisFuns N (myNurbs->myKnotsU->copy());
  N.calculate (u, span);

  for (i = 0; i <= p; i++)
    Cw += N.get (i) * Pw.get (i);

  return Cw.make3D ();                 // Return evaluated point
}

/***   evaluate : Evaluate point on surface   *************/
//                                                        //
//  A point on the surface is computed using the          //
//  non-rational basis functions N_i^k(u).                //
//                                                        //
/**********************************************************/

Vector3D Nurbs3DEvaluator::evaluateBasisFuns (Real u, Real v) const
{
  int p, q, n, m, uspan, vspan;

  p = myNurbs->myKnotsU->getDegree ();           // Get u- and v-degrees
  q = myNurbs->myKnotsV->getDegree ();
  n = myNurbs->myPoints->getCountU ();           // Get control point counts
  m = myNurbs->myPoints->getCountV ();

  if (myNurbs->myKnotsU->findSpan(u, uspan) == false)
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateBasisFuns] u-value out of bounds!");
    return Vector3D ();
  }
  if (myNurbs->myKnotsV->findSpan(v, vspan) == false)
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateBasisFuns] v-value out of bounds!");
    return Vector3D ();
  }

  register   int i, j;
  Vec4DArr2D Pw (p+1, q+1);            // Array for 4D control points
  Vec4DArr1D temp (q+1);               // Temporary array
  Vector4D   Sw;                       // Resulting point

  for (i = 0; i <= p; i++)
    for (j = 0; j <= q; j++)
      Pw.set (i, j, Vector4D(myNurbs->myPoints->get(uspan-p+i+1, vspan-q+j+1),
			     myNurbs->myWeights->get(uspan-p+i+1, vspan-q+j+1)));

  Nurbs3DBasisFuns Nu (myNurbs->myKnotsU->copy());
  Nurbs3DBasisFuns Nv (myNurbs->myKnotsV->copy());
  Nu.calculate (u, uspan);
  Nv.calculate (v, vspan);

  for (j = 0; j <= q; j++)
  {
    temp[j] = Vector4D ();
    for (i = 0; i <= p; i++)
      temp[j] += Nu.get (i) * Pw.get (i, j);
  }
  for (j = 0; j <= q; j++)
    Sw += Nv.get (j) * temp.get (j);

  return Sw.make3D ();                 // Return evaluated point
}

/*
 * evaluateCornerCut : Evaluate point on curve
 *
 * This function evaluates a point on a curve by applying the corner
 * cutting algorithm.
 */

Vector3D Nurbs3DEvaluator::evaluateCornerCut (Real u) const
{
  int n = myNurbs->myPoints->getCountU (), p = myNurbs->myKnotsU->getDegree ();

  if (equal(u, myNurbs->myKnotsU->getFirstKnot()))    // Handle starting point
    return myNurbs->myPoints->get (0);
  if (equal(u, myNurbs->myKnotsU->getLastKnot()))     // Handle end point
    return myNurbs->myPoints->get (n-1);

  register int i, j;
  int  r, s = 0, k, L;
  Real al;

  if (myNurbs->myKnotsU->findSpanMult(u, k, s) == false) // Get knot span and multiplicity
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateCornerCut] value out of bounds");
    return Vector3D ();
  }
  k++;                                 // My k is Piegl's k - 1

  r = p - s;                           // Number of times to insert "u"
  if (r == 0)                               // Knot has full multiplicity
    return myNurbs->myPoints->get (k-p);   // Get corresponding control point
  
  Vec4DArr1D Rw (r+1);                 // Array to hold temporary control points

  for (i = 0; i <= r; i++)             // Initialize temporary points "Rw"
    Rw.set (i, Vector4D(myNurbs->myPoints->get(k-p+i), myNurbs->myWeights->get(k-p+i)));

  for (j = 1; j <= r; j++)             // Corner-cutting
  {
    L = k - p + j;
    for (i = 0; i <= r-j; i++)
    {
      al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+k) - myNurbs->myKnotsU->get(L+i-1));
      Rw[i] = al * Rw[i+1] + (1.0-al) * Rw[i];
    }
  }
  return Rw[0].make3D ();              // Assign point on curve
}

/*
 * evaluateCornerCut : Evaluate point on curve
 *
 * This function evaluates a point on a curve by applying the corner
 * cutting algorithm.
 */

Vector3D Nurbs3DEvaluator::evaluateCornerCut (Real u, Real v) const
{
  int  n = myNurbs->myPoints->getCountU (), m = myNurbs->myPoints->getCountV ();
  int  p = myNurbs->myKnotsU->getDegree (), q = myNurbs->myKnotsV->getDegree ();
  bool firstU, lastU, firstV, lastV;

  firstU = lastU = firstV = lastV = false;  // Flags for first and last knots

  if (equal(u, myNurbs->myKnotsU->getFirstKnot()))    // Got first u-knot
    firstU = true;
  else if (equal(u, myNurbs->myKnotsU->getLastKnot()))     // Got last u-knot
    lastU = true;
  if (equal(v, myNurbs->myKnotsV->getFirstKnot()))    // Got first v-knot
    firstV = true;
  else if (equal(v, myNurbs->myKnotsV->getLastKnot()))     // Got last v-knot
    lastV = true;

  if (firstU && firstV)                     // Handle corner points
    return myNurbs->myPoints->get (0, 0);
  if (firstU && lastV)
    return myNurbs->myPoints->get (0, m-1);
  if (lastU && firstV)
    return myNurbs->myPoints->get (n-1, 0);
  if (lastU && lastV)
    return myNurbs->myPoints->get (n-1, m-1);

  register int i, j, k;
  int  ru, rv, su = 0, sv = 0, ku, kv, L;
  Real al;

  if (myNurbs->myKnotsU->findSpanMult(u, ku, su) == false)     // Get knot span and multiplicity
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateCornerCut] u-value out of bounds");
    return Vector3D ();
  }
  if (myNurbs->myKnotsV->findSpanMult(v, kv, sv) == false)     // Get knot span and multiplicity
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateCornerCut] v-value out of bounds");
    return Vector3D ();
  }
  ku++;                                // Adjust k-values
  kv++;

  if (lastU)                           // Ensure correct spans for end knots
    ku += p;
  if (lastV)
    kv += p;

  ru = p - su;                         // Get number of knot insertions
  rv = q - sv;

  if (ru == 0 && rv == 0)              // Nothing to do at all
      return myNurbs->myPoints->get (ku-p, kv-q);

  if (ru == 0)                         // Nothing to do in u-direction
  {
    Vec4DArr1D Rw (rv+1);              // Array to hold temporary control points

    for (i = 0; i <= rv; i++)          // Initialize temporary points "Rw"
      Rw.set (i, Vector4D(myNurbs->myPoints->get(ku-p, kv-q+i), myNurbs->myWeights->get(ku-p, kv-q+i)));

    for (j = 1; j <= rv; j++)          // Corner-cutting
    {
      L = kv - q + j;
      for (i = 0; i <= rv-j; i++)
      {
	al = (v - myNurbs->myKnotsV->get(L+i-1)) / (myNurbs->myKnotsV->get(i+kv) - myNurbs->myKnotsV->get(L+i-1));
	Rw[i] = al * Rw[i+1] + (1.0-al) * Rw[i];
      }
    }
    return Rw[0].make3D ();            // Assign point on surface
  } 
  if (rv == 0)                         // Nothing to do in v-direction
  {
    Vec4DArr1D Rw (ru+1);              // Array to hold temporary control points

    for (i = 0; i <= ru; i++)          // Initialize temporary points "Rw"
      Rw.set (i, Vector4D(myNurbs->myPoints->get(ku-p+i, kv-q), myNurbs->myWeights->get(ku-p+i, kv-q)));

    for (j = 1; j <= ru; j++)          // Corner-cutting
    {
      L = ku - p + j;
      for (i = 0; i <= ru-j; i++)
      {
	al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+ku) - myNurbs->myKnotsU->get(L+i-1));
	Rw[i] = al * Rw[i+1] + (1.0-al) * Rw[i];
      }
    }
    return Rw[0].make3D ();            // Assign point on surface
  } 

  Vec4DArr2D Rw (ru+1, rv+1);          // Array to hold temporary control points

  for (i = 0; i <= ru; i++)            // Initialize temporary points "Rw"
    for (j = 0; j <= rv; j++)
      Rw.set (i, j, Vector4D(myNurbs->myPoints->get(ku-p+i, kv-q+j), myNurbs->myWeights->get(ku-p+i, kv-q+j)));

  for (j = 1; j <= ru; j++)            // Corner-cutting in u-direction
  {
    L = ku - p + j;
    for (i = 0; i <= ru-j; i++)
    {
      al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+ku) - myNurbs->myKnotsU->get(L+i-1));
      for (k = 0; k <= rv; k++)
	Rw[i][k] = al * Rw[i+1][k] + (1.0-al) * Rw[i][k];
    }
  }
  for (j = 1; j <= rv; j++)            // Corner-cutting in v-direction
  {
    L = kv - q + j;
    for (i = 0; i <= rv-j; i++)
    {
      al = (v - myNurbs->myKnotsV->get(L+i-1)) / (myNurbs->myKnotsV->get(i+kv) - myNurbs->myKnotsV->get(L+i-1));
      Rw[0][i] = al * Rw[0][i+1] + (1.0-al) * Rw[0][i];
      Rw[1][i] = al * Rw[1][i+1] + (1.0-al) * Rw[1][i];
    }
  }
  return Rw[0][0].make3D ();           // Assign point on surface
}

/***   deBoor : de Boor evaluation   **********************/
//                                                        //
//  A point on the curve is evaluated using a rational    //
//  implementation of de Boor's algorithm. This method    //
//  is numerically stable, as it uses only convex         //
//  combinations.                                         //
//                                                        //
/**********************************************************/

Vector3D Nurbs3DEvaluator::evaluateDeBoor (Real u) const
{
  int I;

  if (equal(u, myNurbs->myKnotsU->getFirstKnot()))    // First knot gets first control point
    return myNurbs->myPoints->get (0);
  if (equal(u, myNurbs->myKnotsU->getLastKnot()))     // Last knot gets last control point
    return myNurbs->myPoints->get (myNurbs->myPoints->getCountU()-1);

  if (myNurbs->myKnotsU->findSpan(u, I) == true) // Find interval containing value
  {
    int p = myNurbs->myKnotsU->getDegree ();     // Get degree of curve

    return du (I+1, p, u);             // Start recursive calculation of point on curve
  }
  return Vector3D ();                  // Return default
}

/***   deBoorW : de Boor weight evaluation   **************/
//                                                        //
//  The weight corresponding to the point on the curve    //
//  is evaluated using the rational de Boor algorithm.    //
//  Used for evaluating a surface point.                  //
//                                                        //
/**********************************************************/

Real Nurbs3DEvaluator::evaluateDeBoorW (Real u) const
{
  int  I;

  if (equal(u, myNurbs->myKnotsU->getFirstKnot()))     // First knot gets first weight
    return myNurbs->myWeights->get (0);
  if (equal(u, myNurbs->myKnotsU->getLastKnot()))      // Last knot gets last weight
    return myNurbs->myWeights->get (myNurbs->myWeights->getCountU()-1);

  if (myNurbs->myKnotsU->findSpan(u, I) == true)  // Find interval containing value
  {
    int p = myNurbs->myKnotsU->getDegree ();      // Get degree of curve

    return wu (I+1, p, u);              // Start recursive calculation of weight
  }
  else
    return 0.0;                         // Return default
}

/***   deBoor : de Boor algorithm for surfaces   **********/
//                                                        //
//  This is an adapted algorithm for evaluating a point   //
//  on a surface using the rational version of de Boor's  //
//  algorithm. First an isoparametric curve in            //
//  v-direction is extracted at parameter values "u",     //
//  then the point at parameter value "v" on the          //
//  isoparametric curve is evaluated. For efficiency      //
//  reasons it is easier to get the isoparametric curve   //
//  first and to evaluate points on it if lots of         //
//  points are to be determined.                          //
//                                                        //
/**********************************************************/

Vector3D Nurbs3DEvaluator::evaluateDeBoor (Real u, Real v) const
{
  Nurbs3DEvaluator eval (isoParametricDeBoor(u));

  return eval.evaluateDeBoor (v);
}

/*
 * isoParametricBasisFuns : Extract iso-parametric curve with basis functions
 *
 * An iso-parametric curve is extracted by using basis functions
 */

Nurbs3D* Nurbs3DEvaluator::isoParametricBasisFuns (Real u) const
{
  if (myNurbs->myType != Nurbs3DTypes::Surface)
  {
    Report::error ("[Nurbs3DEvaluator::isoParametricBasisFuns] may only evaluate on surface!");
    return new Nurbs3D;
  }

  int p = myNurbs->myKnotsU->getDegree ();       // Get degree of curve
  int m = myNurbs->myPoints->getCountV ();
  int span;

  if (myNurbs->myKnotsU->findSpan(u, span) == false)
  {
    Report::warning ("[Nurbs3DEvaluator::isoParametricBasisFuns] value out of bounds!");
    return new Nurbs3D;
  }

  register   int i, j;
  Vec4DArr2D Pw (p+1, m);              // Array for 4D control points
  Vec4DArr1D Cw (m);                   // Resulting point

  for (i = 0; i <= p; i++)
    for (j = 0; j < m; j++)
      Pw.set (i, j, Vector4D(myNurbs->myPoints->get(span-p+i+1, j),
			     myNurbs->myWeights->get(span-p+i+1, j)));

  Nurbs3DBasisFuns N (myNurbs->myKnotsU->copy());
  N.calculate (u, span);

  for (i = 0; i <= p; i++)
    for (j = 0; j < m; j++)
    Cw[j] += N.get (i) * Pw.get (i, j);

  PtArray1D *pts = new PtArray1D (m);       // New control points
  WtArray1D *wts = new WtArray1D (m);

  for (j = 0; j < m; j++)               // Extract points and weights
  {
    pts->set (j, Cw[j].make3D());
    wts->set (j, Cw[j].w());
  }

  return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
}

/*
 * isoParametricCornerCut : Extract iso-parametric curve by corner cutting
 *
 * An iso-parametric curve is extracted by applying the corner cutting algorithm
 */

Nurbs3D* Nurbs3DEvaluator::isoParametricCornerCut (Real u) const
{
  if (myNurbs->myType != Nurbs3DTypes::Surface)
  {
    Report::error ("[Nurbs3DEvaluator::isoParametricBasisFuns] may only evaluate on surface!");
    return new Nurbs3D;
  }

  int p = myNurbs->myKnotsU->getDegree ();
  int n = myNurbs->myPoints->getCountU ();
  int m = myNurbs->myPoints->getCountV ();

  register int i, j, l;
  int  r, s = 0, k, L;
  Real al;

  if (myNurbs->myKnotsU->findSpanMult(u, k, s) == false) // Get knot span and multiplicity
  {
    Report::warning ("[Nurbs3DEvaluator::evaluateCornerCut] value out of bounds");
    return new Nurbs3D;
  }
  k++;                                 // My k is Piegl's k - 1

  PtArray1D *pts = new PtArray1D (m);       // New control points
  WtArray1D *wts = new WtArray1D (m);

  if (equal(u, myNurbs->myKnotsU->getFirstKnot()))    // Handle starting points
  {
    for (j = 0; j < m; j++)
    { 
      pts->set (j, myNurbs->myPoints->get(0, j));
      wts->set (j, myNurbs->myWeights->get (0, j));
    }
    return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
  }
  if (equal(u, myNurbs->myKnotsU->getLastKnot()))     // Handle end points
  {
    for (j = 0; j < m; j++)
    { 
      pts->set (j, myNurbs->myPoints->get(n-1, j));
      wts->set (j, myNurbs->myWeights->get (n-1, j));
    }
    return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
  }

  r = p - s;                           // Number of times to insert "u"
  if (r == 0)                               // Knot has full multiplicity
  {
    for (j = 0; j < m; j++)
    { 
      pts->set (j, myNurbs->myPoints->get(k-p, j));
      wts->set (j, myNurbs->myWeights->get (k-p, j));
    }
    return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
  }
  
  Vec4DArr2D Rw (r+1, m);              // Array to hold temporary control points

  for (i = 0; i <= r; i++)             // Initialize temporary points "Rw"
    for (j = 0; j < m; j++)
      Rw.set (i, j, Vector4D(myNurbs->myPoints->get(k-p+i, j), myNurbs->myWeights->get(k-p+i, j)));

  for (j = 1; j <= r; j++)             // Corner-cutting
  {
    L = k - p + j;
    for (i = 0; i <= r-j; i++)
    {
      al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+k) - myNurbs->myKnotsU->get(L+i-1));
      for (l = 0; l < m; l++)
	Rw[i][l] = al * Rw[i+1][l] + (1.0-al) * Rw[i][l];
    }
  }

  for (j = 0; j < m; j++)            // Extract points and weights
  {
    pts->set (j, Rw[0][j].make3D());
    wts->set (j, Rw[0][j].w());
  }
  return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
}

/***   isoparametricU : Extract isoparametric u-curve   ***/
//                                                        //
//  This function extracts an isoparametric curve at      //
//  a given u-value. This is done by evaluating the       //
//  control points by de Boor evaluation.                 //
//                                                        //
/**********************************************************/

Nurbs3D* Nurbs3DEvaluator::isoParametricDeBoor (Real u) const
{
  register int j;
  int m = myNurbs->myPoints->getCountV ();          // Get number of controlpoints

  Nurbs3D        *curve;
  Nurbs3DPoints    *points;
  Nurbs3DWeights   *weights;
  Nurbs3DEvaluator eval;
  PtArray1D *pts = new PtArray1D (m);
  WtArray1D *wts = new WtArray1D (m);

  for (j = 0; j < m; j++)          // Evaluate control points
  {
    points = myNurbs->myPoints->extractAtV (j);
    weights = myNurbs->myWeights->extractAtV (j);
    curve = new Nurbs3D (myNurbs->myKnotsU->copy(), points, weights);
    eval.adoptNurbs (curve);
    pts->set (j, eval.evaluateDeBoor(u));
    wts->set (j, eval.evaluateDeBoorW(u));
  }
  return new Nurbs3D (myNurbs->myKnotsV->copy(), new Nurbs3DPoints(pts), new Nurbs3DWeights(wts));
}

/*
 * derivativePoints : Evaluate control points for derivatives at parameter
 *
 * This function evaluates the derivatives up to order "d" of the given NURBS
 * curve
 */

void Nurbs3DEvaluator::derivativePoints (int p, KnotArray *U, int d, int r, Vec4DArr1D *Pw, Vec4DArr2D *PK) const
{
  register int i, k;
  int tmp;

  PK->initSize (p+1, p+1);
  for (i = 0; i <= r; i++)
    PK->set (0, i, Pw->get(i));

  for (k = 1; k <= d; k++)
  {
    tmp = p - k + 1;
    for (i = 0; i <= r-k; i++)
      PK->set (k, i, tmp * (PK->get(k-1, i+1) - PK->get(k-1, i)) / 
	       (U->get(i+p) - U->get(i+k-1)));
  }
}

/***   du : Calculate rational de Boor point   ************/
//                                                        //
//  This function calculates an intermediate point        //
//  d_i^k(u) by de Boor's method (rational version).      //
//                                                        //
/**********************************************************/

Vector3D Nurbs3DEvaluator::du (int i, int k, Real u) const
{
  if (k == 0)                          // End of recursion
    return myNurbs->myPoints->get (i);
  else                                 // Start rational recursion
  {
    Real alpha = au (i, k, u);
    return ((1 - alpha) * wu(i-1, k-1, u) * du(i-1, k-1, u) + alpha * wu(i, k-1, u) * du(i, k-1, u)) / wu(i, k, u);
  }
}

/***   wu : Calculate rational de Boor weight   ***********/
//                                                        //
//  This function calculates an intermediate weight       //
//  d_i^k(u) by de Boor's method (rational version).      //
//                                                        //
/**********************************************************/

Real Nurbs3DEvaluator::wu (int i, int k, Real u) const
{
  if (k == 0)                          // End of recursion
    return myNurbs->myWeights->get (i);
  else                                 // Start rational recursion
  {
    Real alpha = au (i, k, u);
    return (1 - alpha) * wu(i-1, k-1, u) + alpha * wu(i, k-1, u);
  }
}

/***   au : Calculate rational alpha   ********************/
//                                                        //
//  This function calculates the rational factor alpha    //
//  used for de Boor points and weights.                  //
//                                                        //
/**********************************************************/

Real Nurbs3DEvaluator::au (int i, int k, Real u) const
{
  Real gamma, ui_1 = myNurbs->myKnotsU->get (i-1);
  int  n = myNurbs->myKnotsU->getDegree ();

  gamma = myNurbs->myKnotsU->get (i+n-k) - ui_1;     // Denominator
  if (gamma != 0.0)                    // Calculate alpha if possible
    return (u - ui_1) / gamma;
  else
    return 0.0;
}
