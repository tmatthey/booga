/*
 * Nurbs3DManipulator.C 
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
 *  $Id: Nurbs3DManipulator.C,v 1.5 1996/02/16 13:37:50 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/nurbs/Nurbs3DTypes.h"
#include "booga/nurbs/Nurbs3DManipulator.h"

#include "booga/nurbs/Nurbs3D.h"             // Class Nurbs3D and related

/***********************************************************
  Constants
***********************************************************/

const Real TOLERANCE = 0.0025;

/***********************************************************
  Static data
***********************************************************/

/***********************************************************
  Type definitions
***********************************************************/

//___________________________________________________________ Nurbs3DManipulator

implementRTTI(Nurbs3DManipulator, Nurbs3DHandler);

/***   elevate : Degree elevation   ***********************/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::elevateU (void)
{
}

/***   elevate : Degree elevation   ***********************/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::elevateV (void)
{
}

/*
 * insertKnotU : Insert knot into u-knot vector
 *
 * Inserts the given knot into the vector according to the object type
 */

void Nurbs3DManipulator::insertKnotU (Real u, int r)
{
  if (myNurbs->myType == Nurbs3DTypes::Curve)
    insertKnotCurve (u, r);
  else if (myNurbs->myType == Nurbs3DTypes::Surface)
    insertKnotSurface (u, r);
}

/***   insertKnotV : Insert knot into v-vector   **********/
//                                                        //
//  The element is transposed and the knot is inserted    //
//  into the u-knot vector. Finally the element is        //
//  transposed back to the original form.                 //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::insertKnotV (Real v, int ct)
{
  myNurbs->transpose ();               // Prepare insertion
  insertKnotU (v, ct);                 // Now insert into u-knot vector
  myNurbs->transpose ();               // Retranspose to original
}

/***   joinPatchesInU : Join two NURBS patches   **********/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::joinPatchesInU (int cn, Nurbs3D *nrb1, Nurbs3D *nrb2, bool force)
{
  if (nrb1->getType() != nrb2->getType())  // Test for different NURBS types
  {
    Report::warning ("[Nurbs3DManipulator::joinPatchesInU] patches are of different kind - please adjust");
    return;
  }
  if (myNurbs->myDecomposition != NULL)  // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  Nurbs3DPoints  *points1, *points2;
  Nurbs3DWeights *weights1, *weights2;

  register int x, y;
  int  n1, n2, m, p, r;
  Real offset, knot1, knot2;

  if (nrb1->getType() == Nurbs3DTypes::Curve)    // Handle joining of two curve segments
  {
    p = nrb1->myKnotsU->getDegree ();           // Get degree of curves

    if (p != nrb2->myKnotsU->getDegree())   // Test for different degrees
    {
      Report::warning ("[Nurbs3DManipulator::joinAtU] u-knot vectors have to be of same degree");
      return;
    }

    r = nrb2->myKnotsU->getCount ();            // Get length of second knot vector
    knot1 = nrb1->myKnotsU->getLastKnot ();     // Get last knot of first knot vector
    knot2 = nrb2->myKnotsU->getFirstKnot ();    // Get first knot of second knot vector

    if (knot1 == knot2)                  // Knots are equal, no offset required
      offset = 0.0;
    else                                 // Calculate offset of knot vectors
      offset = knot1 - knot2;

    KnotArray *kts = new KnotArray;      // Calculate new knot vector
    nrb1->myKnotsU->copyKnots (kts);     // Copy knots of first part
    for (x = p; x < r; x++)              // Append knots of second part
      kts->append (nrb2->myKnotsU->get(x)+offset);

    points1 = nrb1->copyPoints ();   // Get control points
    points2 = nrb2->copyPoints ();
    weights1 = nrb1->copyWeights (); // Get weights
    weights2 = nrb2->copyWeights ();
    n1 = points1->getCountU ();          // Get number of control points
    n2 = points2->getCountU ();

    if ((points1->get(n1-1)-points2->get(0)).length() > EPSILON)
      Report::recoverable ("[Nurbs3DManipulator::joinPatchesInU] joining curves at your risk - control points differ");

    PtArray1D *pts = new PtArray1D;      // Calculate new control polygon with weights
    WtArray1D *wts = new WtArray1D;
    points1->copyPoints (pts);           // Copy control points and weights from first part
    weights1->copyWeights (wts);
    for (x = 1; x < n2; x++)             // Append control points and weights from second part
    {
      pts->append (points2->get(x));
      wts->append (weights2->get(x));
    }

    delete points1;                       // Clean up temporary data
    delete points2;
    delete weights1;
    delete weights2;
    
    myNurbs->adoptKnotsU (new Nurbs3DKnots(p, kts));     // Initialize u-knot vector
    myNurbs->adoptKnotsV (NULL);                       // Initialize v-knot vector
    myNurbs->adoptPoints (new Nurbs3DPoints(pts));       // Initialize control polygon
    myNurbs->adoptWeights (new Nurbs3DWeights(wts));     // Initialize weights
    myNurbs->myType = Nurbs3DTypes::Curve;

    removeKnotU (knot1, cn, 0.0, force); // Remove knot to create C^n continuity
    splitAtU (knot1, nrb1, nrb2);       // Adjust patches to have C^n boundary
  }
  else if (nrb1->getType() == Nurbs3DTypes::Surface)
  {
    p = nrb1->myKnotsU->getDegree ();

    if (p != nrb2->myKnotsU->getDegree())    // Test for different degrees
    {
      Report::warning ("[Nurbs3DManipulator::joinPatchesInU] u-knot vectors have to be of same degree");
      return;
    }
    if (nrb1->myKnotsV->getDegree() != nrb2->myKnotsV->getDegree())    // Test for different degrees
    {
      Report::warning ("Nurbs3DManipulator::joinPatchesInU] v-knot vectors have to be of same degree");
      return;
    }
    if (nrb1->myKnotsV->getCount() != nrb2->myKnotsV->getCount())      // Test for different counts
    {
      Report::warning ("[Nurbs3DManipulator::joinPatchesInU] v-knot vectors have to have same number of knots");
      return;
    }

    r = nrb2->myKnotsU->getCount ();            // Get length of second knot vector
    knot1 = nrb1->myKnotsU->getLastKnot ();         // Get last knot of first knot vector
    knot2 = nrb2->myKnotsU->getFirstKnot ();            // Get first knot of second knot vector

    if (knot1 == knot2)                 // Knots are equal, no offset required
      offset = 0.0;
    else                                // Calculate offset of knot vectors
      offset = knot1 - knot2;

    KnotArray *kts = new KnotArray;     // Calculate new knot vector
    nrb1->myKnotsU->copyKnots (kts);            // Copy knots of first part
    for (x = p; x < r; x++)                 // Append knots of second part
      kts->append (nrb2->myKnotsU->get(x)+offset);

    points1 = nrb1->copyPoints ();        // Get control points
    points2 = nrb2->copyPoints ();
    weights1 = nrb1->copyWeights ();      // Get weights
    weights2 = nrb2->copyWeights ();
    n1 = points1->getCountU ();          // Get number of control points
    n2 = points2->getCountU ();
    m = points1->getCountV ();

    for (y = 0; y < m; y++)             // Check control points at joining side
    {
      if ((points1->get(n1-1, m-1)-points2->get(0, m-1)).length() > EPSILON)
      {
	Report::recoverable ("[Nurbs3DManipulator::joinPatchesInU] joining curves at your risk - control points differ");
	break;
      }
    }

    PtArray2D *pts = new PtArray2D (n1+n2-1, m);  // Calculate new control polygon with weights
    WtArray2D *wts = new WtArray2D (n1+n2-1, m);
    
    for (x = 0; x < n1; x++)            // Copy control points and weights from first part
    {
      for (y = 0; y < m; y++)
      {
	pts->set (x, y, points1->get(x, y));
	wts->set (x, y, weights1->get(x, y));
      }
    }
    for (x = 1; x < n2; x++)            // Copy control points and weights from second part
    {
      for (y = 0; y < m; y++)
      {
	pts->set (x+n1-1, y, points2->get(x, y));
	wts->set (x+n1-1, y, weights2->get(x, y));
      }
    }

    delete points1;                       // Clean up temporary data
    delete points2;
    delete weights1;
    delete weights2;
    
    myNurbs->adoptKnotsU (new Nurbs3DKnots(p, kts));       // Initialize u-knot vector
    myNurbs->adoptKnotsV (nrb1->copyKnotsV());           // Initialize v-knot vector
    myNurbs->adoptPoints (new Nurbs3DPoints(pts));         // Initialize control polygon
    myNurbs->adoptWeights (new Nurbs3DWeights(wts));       // Initialize weights
    myNurbs->myType = Nurbs3DTypes::Surface;

    removeKnotU (knot1, cn, 0.0, force);     // Remove knot to create C^n continuity
    splitAtU (knot1, nrb1, nrb2);            // Adjust patches to have C^n boundary
  }
}

/***   joinPatchesInV : Join two NURBS patches   **********/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::joinPatchesInV (int cn, Nurbs3D *nrb1, Nurbs3D *nrb2, bool force)
{
  nrb1->transpose ();                    // Transpose original patches             
  nrb2->transpose ();
  joinPatchesInU (cn, nrb1, nrb2, force);    // Join patches in u-direction
  myNurbs->transpose ();                              // Retranspose joined patch
  nrb1->transpose ();                    // Retranspose original patches
  nrb2->transpose ();
}

/*
 * refineU : Refine u-knot vector
 *
 * The u-knot vector is refined according to object type
 */

void Nurbs3DManipulator::refineU (Nurbs3DKnots *refineKnots)
{
  if (myNurbs->myType == Nurbs3DTypes::Curve)
    refineCurve (refineKnots);
  else if (myNurbs->myType == Nurbs3DTypes::Surface)
    refineSurface (refineKnots);
}

/***   refineV : Refine the v-knot vector   ***************/
//                                                        //
//  The knot vector of the surface is refined, i.e.       //
//  the given knot vector is merged with the existing     //
//  one and the new control points are calculated.        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::refineV (Nurbs3DKnots *refineKnots)
{
  myNurbs->transpose ();               // Transpose data structure
  refineU (refineKnots);               // Refine u-knots
  myNurbs->transpose ();               // Retranspose
}

/*
 * removeKnotU : Remove knot from u-knot vector
 *
 * The knot is removed according to the object type
 */

int Nurbs3DManipulator::removeKnotU (Real u, int num, Real tol, bool force)
{
  if (myNurbs->myType == Nurbs3DTypes::Curve)
    return removeKnotCurve (u, num, tol, force);
  else if (myNurbs->myType == Nurbs3DTypes::Surface)
    return removeKnotSurface (u, num, tol, force);
  return 0;
}

/***   removeKnotV : Remove knot from knot vector   *******/
//                                                        //
//  The indicated knot is removed from the v-knot         //
//  vector. To avoid implementing everything twice,       //
//  the data is transposed and the knot is removed        //
//  from the u-knot vector.                               //
//                                                        //
/**********************************************************/

int Nurbs3DManipulator::removeKnotV (Real v, int num, Real tol, bool force)
{
  int t;

  myNurbs->transpose ();                    // Transpose surface
  t = removeKnotU (v, num, tol, force);     // Remove knot from u-knot vector
  myNurbs->transpose ();                    // Retranspose
  return t;                                 // Knot was removed t-times
}

/***   splitAtU : Split NURBS at u-value   ****************/
//                                                        //
//  This function splits a NURBS by inserting "u" to      //
//  create a knot with full multiplicity. Then the        //
//  NURBS is split into two independent objects by        //
//  creating the appropriate knot vectors, control        //
//  points and weights.                                   //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::splitAtU (Real u, Nurbs3D *nrb1, Nurbs3D *nrb2)
{
  register int x, y;
  int n, m, p, r;
  int n1, n2, r1, r2;

  Nurbs3D      *copy = new Nurbs3D (*myNurbs);
  Nurbs3DKnots   *uknots, *vknots;
  Nurbs3DPoints  *points;
  Nurbs3DWeights *weights;
  Nurbs3DManipulator manip;

  if (myNurbs->myType == Nurbs3DTypes::Curve)                  // Handle curve splitting
  {
    manip.adoptNurbs (copy);            // Initialize manipulator
    manip.insertKnotCurve (u, -1);           // Force corresponding control point to lie on curve
    copy = manip.orphanNurbs ();        // Get new NURBS
    uknots = copy->copyKnotsU ();        // Get u-knot vector
    points = copy->copyPoints ();        // Get control points
    weights = copy->copyWeights ();      // Get weights

    n = points->getCountU ();            // Total number of points
    p = uknots->getDegree ();            // Degree of curve
    r = uknots->getCount ();             // Number of knots
    
    for (x = 0; x < r; x++)             // Find knot index
    {
      if (uknots->get(x) < u+EPSILON)    // Save position
	r1 = x;
      else                              // Exit loop when finished
	break;
    }
    r1++;                               // Number of knots of first patch
    r2 = r1 - p;                        // First knot of second patch
    n1 = r1 - p + 1;                    // Number of control points of first patch
    n2 = n1 - 1;                        // First control point of second patch

    KnotArray *kts = new KnotArray;     // Create first knot vector
    for (x = 0; x < r1; x++)            // Copy knots
      kts->append (uknots->get(x));
    uknots->adoptKnots (kts);            // "uknots" already got correct degree

    PtArray1D *pts = new PtArray1D;     // Create control points and weights of first patch
    WtArray1D *wts = new WtArray1D;
    for (x = 0; x < n1; x++)            // Copy points and weights
    {
      pts->append (points->get(x));
      wts->append (weights->get(x));
    }
    points->adoptPoints (pts);
    weights->adoptWeights (wts);
    nrb1->adoptParameters (uknots, points, weights);

    uknots = copy->copyKnotsU ();        // Get original u-knot vector
    points = copy->copyPoints ();        // Get original control points
    weights = copy->copyWeights ();      // Get original weights

    kts = new KnotArray;                // Create second knot vector
    for (x = r2; x < r; x++)            // Copy knots
      kts->append (uknots->get(x));
    uknots->adoptKnots (kts);            // "uknots" already got correct degree

    pts = new PtArray1D;                // Create control points and weights of second patch
    wts = new WtArray1D;
    for (x = n2; x < n; x++)            // Copy points and weights
    {
      pts->append (points->get(x));
      wts->append (weights->get(x));
    }
    points->adoptPoints (pts);
    weights->adoptWeights (wts);
    nrb2->adoptParameters (uknots, points, weights);
  }
  else if (myNurbs->myType == Nurbs3DTypes::Surface)           // Handle surface splitting
  {
    manip.adoptNurbs (copy);            // Initialize manipulator
    manip.insertKnotSurface (u, -1);          // Force corresponding control point to lie on curve
    copy = manip.orphanNurbs ();        // Get new NURBS
    uknots = copy->copyKnotsU ();        // Get u-knot vector
    vknots = copy->copyKnotsV ();        // Get v-knot vector
    points = copy->copyPoints ();        // Get control points
    weights = copy->copyWeights ();      // Get weights

    n = points->getCountU ();            // Total number of points
    m = points->getCountV ();
    p = uknots->getDegree ();            // Degree of curve
    r = uknots->getCount ();             // Number of knots
    
    for (x = 0; x < r; x++)             // Find knot index
    {
      if (uknots->get(x) < u+EPSILON)    // Save position
	r1 = x;
      else                              // Exit loop when finished
	break;
    }
    r1++;                               // Number of knots of first patch
    r2 = r1 - p;                        // First knot of second patch
    n1 = r1 - p + 1;                    // Number of control points of first patch
    n2 = n1 - 1;                        // First control point of second patch

    KnotArray *kts = new KnotArray;     // Create first knot vector
    for (x = 0; x < r1; x++)            // Copy knots
      kts->append (uknots->get(x));
    uknots->adoptKnots (kts);            // "uknots" already got correct degree

    PtArray2D *pts = new PtArray2D (n1, m);  // Create control points and weights of first patch
    WtArray2D *wts = new WtArray2D (n1, m);
    for (x = 0; x < n1; x++)                 // Copy points and weights
    {
      for (y = 0; y < m; y++)
      {
	pts->set (x, y, points->get(x, y));
	wts->set (x, y, weights->get(x, y));
      }
    }
    points->adoptPoints (pts);
    weights->adoptWeights (wts);
    nrb1->adoptParameters (uknots, vknots, points, weights);

    uknots = copy->copyKnotsU ();        // Get original u-knot vector
    vknots = copy->copyKnotsV ();        // Get v-knot vector
    points = copy->copyPoints ();        // Get original control points
    weights = copy->copyWeights ();      // Get original weights

    kts = new KnotArray;                // Create second knot vector
    for (x = r2; x < r; x++)            // Copy knots
      kts->append (uknots->get(x));
    uknots->adoptKnots (kts);            // "uknots" already got correct degree

    pts = new PtArray2D (n-n1+1, m);    // Create control points and weights of second patch
    wts = new WtArray2D (n-n1+1, m);
    for (x = n2; x < n; x++)            // Copy points and weights
    {
      for (y = 0; y < m; y++)
      {
	pts->set (x-n2, y, points->get(x, y));
	wts->set (x-n2, y, weights->get(x, y));
      }
    }
    points->adoptPoints (pts);
    weights->adoptWeights (wts);
    nrb2->adoptParameters (uknots, vknots, points, weights);
  }
  delete copy;                           // Delete copy
}

/***   splitAtV: Split NURBS surface at v-value   *********/
//                                                        //
//  This function splits a NURBS surface at the given     //
//  value by transposing it and calling the function      //
//  for splitting in u-direction.                         //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::splitAtV (Real v, Nurbs3D *nrb1, Nurbs3D *nrb2)
{
  myNurbs->transpose ();                // Transpose data structure
  splitAtU (v, nrb1, nrb2);             // Now split in u-direction
  myNurbs->transpose ();                // Retranspose
  nrb1->transpose ();                    // Retranspose new patches
  nrb2->transpose ();
}

/***   createRefinedKnotsU   ******************************/
//                                                        //
//  This function creates a refined knot vector for a     //
//  surface, based on the knot interval length and        //
//  number of knots.                                      //
//                                                        //
/**********************************************************/

Nurbs3DKnots* Nurbs3DManipulator::createRefinedKnotsU (Real prec) const
{
  if (myNurbs->myType != Nurbs3DTypes::Curve && myNurbs->myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3DManipulator::createRefinedKnotsU] needs a valid object");
    return NULL;
  }

  int        p, m;
  long       steps = 0L;
  Real       interval = 0.0, first, last, knot;
  Nurbs3DKnots *refinedKnots = new Nurbs3DKnots;

  m = myNurbs->myKnotsU->getCount ();    // Get number of knots
  myNurbs->getRangeU (first, last);      // Get range of knots
  p = myNurbs->myKnotsU->getDegree ();   // Get degree of curve
  refinedKnots->setDegree (p);            // Set degree for refined knots

  interval = (last - first) / m;        // Initial length of interval
  interval = (1.0 - prec) * interval;   // Set new knot interval length
  if (interval < EPSILON)               // Prevent nonsense
    interval = 100 * EPSILON;
  steps = (long) ((last-first)/interval);    // Ensure interval length to be
  interval = (last-first)/steps;             // a partition of the knot interval

  for (knot = first+interval; knot < last-interval; knot += interval)
    refinedKnots->insertKnot (knot, p-1);

  return refinedKnots;
}

/***   createRefinedKnotsU   ******************************/
//                                                        //
//  This function creates a transposes the data and       //
//  calls the function for u-knot vector refining.        //
//                                                        //
/**********************************************************/

Nurbs3DKnots* Nurbs3DManipulator::createRefinedKnotsV (Real prec) const
{
  myNurbs->transpose ();                             // Transpose data structure
  Nurbs3DKnots *retKnots = createRefinedKnotsU (prec);  // Refine knots
  myNurbs->transpose ();                             // Retranspose
  return retKnots;                    // Return refined knots
}

/***   insertKnot : Insert knot into knot vector   ********/
//                                                        //
//  A knot is inserted into the curve's u-knot vector.    //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::insertKnotCurve (Real u, int r)
{
  if (myNurbs->myDecomposition != NULL)         // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int i, j;
  int      k, s = 0, L;
  int      p = myNurbs->myKnotsU->getDegree (), n;

  if (r > p)                           // A knot is inserted at most p times !!!
    r = p;
  else if (r < 0)                      // Force knot to be inserted p times
    r = p;
  n = myNurbs->myPoints->getCountU ();

  if (myNurbs->myKnotsU->findSpanMult(u, k, s) == false)  // Find knot span and multiplicity
  {
    Report::warning ("[Nurbs3DManipulator::insertKnotCurve] value out of bounds");
    return;
  }
  if (s == p)                          // Knot is sufficiently often in knot vector
    return;
  if (s + r > p)                       // Knot would be inserted too many times
    r = p - s;

  PtArray1D  *pts = new PtArray1D (n+r);    // Algorithm by Piegl follows
  WtArray1D  *wts = new WtArray1D (n+r);
  Vec4DArr1D Rw (p+1);
  Real       al;

  k++;                                 // My k is Piegl's k - 1 !!!
  for (i = 0; i <= k-p+r-1; i++)       // Assign unchanged points in front
  {
    pts->set (i, myNurbs->myPoints->get(i));
    wts->set (i, myNurbs->myWeights->get(i));
  }
  for (i = k; i < n; i++)              // Assign unchanged points at end
  {
    pts->set (i+r, myNurbs->myPoints->get(i));
    wts->set (i+r, myNurbs->myWeights->get(i));
  }
  for (i = 0; i <= p; i++)             // Initialize intermediate points "Rw" (!!!)
    Rw.set (i, Vector4D(myNurbs->myPoints->get(k-p+i), myNurbs->myWeights->get(k-p+i)));
  for (j = 1; j <= r; j++)             // Caculate "rpt" of order "j"
  {
    L = k - p + j;
    for (i = 0; i <= p-j-s; i++)
    {
      al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+k) - 
                                                  myNurbs->myKnotsU->get(L+i-1));     // -1 because of k !!!
      Rw[i] = al * Rw[i+1] + (1.0 - al) * Rw[i];
    }
    pts->set (L, Rw[0].make3D());      // Points at start and end of "Rw" are extracted
    wts->set (L, Rw[0].w());
    pts->set (k+r-j, Rw[p-j].make3D());
    wts->set (k+r-j, Rw[p-j].w());
  }
  for (i = L+1; i < k; i++)            // Assign remaining points
  {
    pts->set (i, Rw[i-L].make3D());
    wts->set (i, Rw[i-L].w());
  }

  myNurbs->myKnotsU->insertKnot (u, r);          // Insert knot into knot vector
  myNurbs->myPoints->adoptPoints (pts);          // Initialize new control points and weights
  myNurbs->myWeights->adoptWeights (wts);
}

/***   insertKnotU : Insert knot into u-vector   **********/
//                                                        //
//  A knot is inserted into surface's u-knot vector.      //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::insertKnotSurface (Real u, int r)
{
  if (myNurbs->myDecomposition != NULL)         // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int i, l, j;
  int      k, s = 0, L;
  int      p = myNurbs->myKnotsU->getDegree (), n, m;

  if (r > p)                           // A knot is inserted at most p times !!!
    r = p;
  else if (r < 0)                      // Force knot to be inserted p times
    r = p;
  n = myNurbs->myPoints->getCountU ();
  m = myNurbs->myPoints->getCountV ();

  if (myNurbs->myKnotsU->findSpanMult(u, k, s) == false)   // Find knot span and mutliplicity
  {
    Report::warning ("[Nurbs3DManipulator::insertKnotSurface] Knot out of bounds");
    return;
  }
  if (s == p)                          // Knot is sufficiently often in knot vector
    return;
  if (s + r > p)                       // Knot would be inserted too many times
    r = p - s;

  PtArray2D  *pts = new PtArray2D (n+r, m); // Algorithm by Piegl follows, modified
  WtArray2D  *wts = new WtArray2D (n+r, m); // for surfaces
  Vec4DArr2D Rw (p+1, m);
  Real      al;

  k++;                                 // My k is Piegl's k - 1 !!!
  for (i = 0; i <= k-p+r-1; i++)       // Assign unchanged points in front
  {
    for (l = 0; l < m; l++)            // m rows of points in v
    {
      pts->set (i, l, myNurbs->myPoints->get(i, l));
      wts->set (i, l, myNurbs->myWeights->get(i, l));
    }
  }
  for (i = k; i < n; i++)              // Assign unchanged points at end
  {
    for (l = 0; l < m; l++)            // m rows of points in v
    {
      pts->set (i+r, l, myNurbs->myPoints->get(i, l));
      wts->set (i+r, l, myNurbs->myWeights->get(i, l));
    }
  }
  for (i = 0; i <= p; i++)             // Initialize intermediate points "Rw" (!!!)
  {
    for (l = 0; l < m; l++)
    {
      Rw.set (i, l, Vector4D(myNurbs->myPoints->get(k-p+i, l), myNurbs->myWeights->get(k-p+i, l)));
    }
  }
  for (j = 1; j <= r; j++)             // Calculate "rpt" of order "j"
  {
    L = k - p + j;
    for (i = 0; i <= p-j-s; i++)
    {
      al = (u - myNurbs->myKnotsU->get(L+i-1)) / (myNurbs->myKnotsU->get(i+k) - 
                                                  myNurbs->myKnotsU->get(L+i-1));     // -1 because of k !!!
      for (l = 0; l < m; l++)
	Rw[i][l] = al * Rw[i+1][l] + (1.0 - al) * Rw[i][l];
    }
    for (l = 0; l < m; l++)            // Points at start and end of "Rw" are extracted
    {
      pts->set (L, l, Rw[0][l].make3D());
      wts->set (L, l, Rw[0][l].w());
      pts->set (k+r-j, l, Rw[p-j][l].make3D());
      wts->set (k+r-j, l, Rw[p-j][l].w());
    }
  }
  for (i = L+1; i < k; i++)            // Assign remaining points
  {
    for (l = 0; l < m; l++)
    {
      pts->set (i, l, Rw[i-L][l].make3D());
      wts->set (i, l, Rw[i-L][l].w());
    }
  }

  myNurbs->myKnotsU->insertKnot (u, r);          // Insert knot into u-knot vector
  myNurbs->myPoints->adoptPoints (pts);          // Initialize new control points and weights
  myNurbs->myWeights->adoptWeights (wts);
}

/***   refine : Refine the knot vector   ******************/
//                                                        //
//  The knot vector of the curve is refined, i.e.         //
//  the given knot vector is merged with the existing     //
//  one and the new control points are calculated.        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::refineCurve (Nurbs3DKnots *refineKnots)
{
  if (myNurbs->myDecomposition != NULL) // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int i, j, k, l;
  int  n, p, r, a, b, ind;
  int  pos, mult, omult, rem;
  Real alfa, knot;

  p = myNurbs->myKnotsU->getDegree ();  // Get degree of curve
  refineKnots->setDegree (p);            // Force degree of "refineKnots"
  refineKnots->scanKnots ();             // Check multiplicities
  r = refineKnots->getCount ();          // Number of new knots

  for (i = 0; i < r;)                   // Remove unnecessary knots 
  {
    knot = refineKnots->get (i);                   // Get knot value
    mult = refineKnots->getMultiplicityByMap (i);  // and multiplicity
    pos = myNurbs->myKnotsU->getKnotInVector (knot);     // Search knot in original knot vector
    if (pos != -1)                           // Found knot -> remove knot in new vector
    {
      omult = myNurbs->myKnotsU->getMultiplicityByMap (pos);
      if ((rem = mult + omult - p) > 0)
      {
	refineKnots->removeKnot (knot, rem);  // Remove surplus knots from vector
	mult -= rem;                         // Adjust multiplicity and number of knots
	r -= rem;
      }
    }
    i += mult;                          // Go to next knot
  }
    
  Nurbs3DKnots *newKnots = myNurbs->copyKnotsU ();     // Initialize new knot vector
  newKnots->merge (refineKnots);       // Merge with given knot vector

  n = myNurbs->myPoints->getCountU ();          // Number of control points
  r = refineKnots->getCount ();        // Recalculate number of new knots
  //m = n + p + 1;

  myNurbs->myKnotsU->findSpan (refineKnots->getFirstKnot(), a);     // Get interval boundaries
  myNurbs->myKnotsU->findSpan (refineKnots->getLastKnot(), b);

  a++; b += 2;                        // My intervals are different from piegl's

  Vec4DArr1D Pw (n);                  // 4D control points
  Vec4DArr1D Qw (n+r);                // New control points

  for (i = 0; i < n; i++)
    Pw.set (i, Vector4D(myNurbs->myPoints->get(i), myNurbs->myWeights->get(i)));
  
  for (j = 0; j <= a-p; j++)
    Qw.set (j, Pw.get(j));
  for (j = b-1; j < n; j++)
    Qw.set (j+r, Pw.get(j));

  i = b + p - 1;
  k = b + p + r - 1;
  for (j = r-1; j >= 0; j--)
  {
    while (refineKnots->get(j) <= myNurbs->myKnotsU->get(i-1) && i > a)
    {
      Qw.set (k-p-1, Pw.get(i-p-1));
      k--, i--;
    }
    Qw.set (k-p-1, Qw.get(k-p));
    for (l = 1; l <= p; l++)
    {
      ind = k - p + l;
      alfa = newKnots->get (k+l-1) - refineKnots->get (j);
      if (fabs(alfa) == 0.0)
	Qw.set (ind-1, Qw.get(ind));
      else
      {
	alfa /= newKnots->get (k+l-1) - myNurbs->myKnotsU->get (i-p+l-1);
	Qw.set (ind-1, alfa*Qw.get(ind-1)+(1.0-alfa)*Qw.get(ind));
      }
    }
    k--;
  }
  myNurbs->adoptKnotsU (newKnots);
  myNurbs->myPoints->initSize (n+r);
  myNurbs->myWeights->initSize (n+r);
  for (i = 0; i < n+r; i++)
  {
    myNurbs->myPoints->set (i, Qw[i].make3D());
    myNurbs->myWeights->set (i, Qw[i].w());
  }
}

/***   refineU : Refine the u-knot vector   ***************/
//                                                        //
//  The knot vector of the surface is refined, i.e.       //
//  the given knot vector is merged with the existing     //
//  one and the new control points are calculated.        //
//                                                        //
/**********************************************************/

void Nurbs3DManipulator::refineSurface (Nurbs3DKnots *refineKnots)
{
  if (myNurbs->myDecomposition != NULL) // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int i, j, k, l, row;
  int  n, m, p, r, a, b, ind;
  int  pos, mult, omult, rem;
  Real alfa, knot;

  p = myNurbs->myKnotsU->getDegree (); // Get degree of curve
  refineKnots->setDegree (p);            // Force degree of "refineKnots"
  refineKnots->scanKnots ();             // Check multiplicities
  r = refineKnots->getCount ();          // Number of new knots

  for (i = 0; i < r;)                   // Remove unnecessary knots 
  {
    knot = refineKnots->get (i);                         // Get knot value
    mult = refineKnots->getMultiplicityByMap (i);        // and multiplicity
    pos = myNurbs->myKnotsU->getKnotInVector (knot);  // Search knot in original knot vector
    if (pos != -1)                                      // Found knot -> remove knot in new vector
    {
      omult = myNurbs->myKnotsU->getMultiplicityByMap (pos);
      if ((rem = mult + omult - p) > 0)
      {
	refineKnots->removeKnot (knot, rem);  // Remove surplus knots from vector
	mult -= rem;                         // Adjust multiplicity and number of knots
	r -= rem;
      }
    }
    i += mult;                          // Go to next knot
  }
    

  Nurbs3DKnots *newKnots = myNurbs->copyKnotsU ();     // Initialize new knot vector
  newKnots->merge (refineKnots);         // Merge with given knot vector

  n = myNurbs->myPoints->getCountU ();          // Number of control points
  m = myNurbs->myPoints->getCountV ();
  r = refineKnots->getCount ();        // Number of new knots

  myNurbs->myKnotsU->findSpan (refineKnots->getFirstKnot(), a);     // Get interval boundaries
  myNurbs->myKnotsU->findSpan (refineKnots->getLastKnot(), b);

  a++; b += 2;                        // My intervals are different from piegl's

  Vec4DArr2D Pw (n, m);               // 4D control points
  Vec4DArr2D Qw (n+r, m);             // New control points

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      Pw.set (i, j, Vector4D(myNurbs->myPoints->get(i, j), myNurbs->myWeights->get(i, j)));
  
  for (row = 0; row < m; row++)       // Save unaltered control points
  {
    for (k = 0; k <= a-p; k++)
      Qw.set (k, row, Pw.get(k, row));
    for (k = b-1; k < n; k++)
      Qw.set (k+r, row, Pw.get(k, row));
  }

  i = b + p - 1;                      // Compute new control points
  k = b + p + r - 1;
  for (j = r-1; j >= 0; j--)
  {
    while (refineKnots->get(j) <= myNurbs->myKnotsU->get(i-1) && i > a)
    {
      for (row = 0; row < m; row++)
	Qw.set (k-p-1, row, Pw.get(i-p-1, row));
      k--, i--;
    }
    for (row = 0; row < m; row++)
      Qw.set (k-p-1, row, Qw.get(k-p, row));
    for (l = 1; l <= p; l++)
    {
      ind = k - p + l;
      alfa = newKnots->get (k+l-1) - refineKnots->get (j);
      if (fabs(alfa) == 0.0)
      {
	for (row = 0; row < m; row++)
	  Qw.set (ind-1, row, Qw.get(ind, row));
      }
      else
      {
	alfa /= newKnots->get (k+l-1) - myNurbs->myKnotsU->get (i-p+l-1);
	for (row = 0; row < m; row++)
	  Qw.set (ind-1, row, alfa*Qw.get(ind-1, row)+(1.0-alfa)*Qw.get(ind, row));
      }
    }
    k--;
  }
  myNurbs->adoptKnotsU (newKnots);
  myNurbs->myPoints->initSize (n+r, m);
  myNurbs->myWeights->initSize (n+r, m);
  for (i = 0; i < n+r; i++)
  {
    for (j = 0; j < m; j++)
    {
      myNurbs->myPoints->set (i, j, Qw[i][j].make3D());
      myNurbs->myWeights->set (i, j, Qw[i][j].w());
    }
  }
}

/***   removeKnot : Remove knot from knot vector   ********/
//                                                        //
//  The knot "val" is removed "num"-times from the        //
//  knot vector i.e. if possible. The actual number       //
//  of removals is returned. The algorithm is an          //
//  adaption of Piegl and Tiller's knot removal           //
//  algorithm for curves.                                 //
//                                                        //
/**********************************************************/

int Nurbs3DManipulator::removeKnotCurve (Real u, int num, Real tol, bool force)
{
  int r = myNurbs->myKnotsU->getKnotInVector (u);
  if (r == -1)
  {
    Report::warning ("[Nurbs3DManipulator::removeKnot] knot not found in knot vector");
    return 0;
  }
  if (num == 0)
  {
    Report::warning ("[Nurbs3DManipulator::removeKnot] knot has to be removed at least once");
    return 0;
  }
  if (myNurbs->myDecomposition != NULL)         // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  int  i, j, ii, jj, forceCounter = 0;
  int  n, p, s, t = 0;
  int  fout, first, last, off;
  bool remFlag;
  Real alfi, alfj;
  Real tolerance;

  if (tol > 0.0)                       // Set initial tolerance
    tolerance = tol;
  else
    tolerance = TOLERANCE;

  n = myNurbs->myPoints->getCountU ();
  p = myNurbs->myKnotsU->getDegree ();
  s = myNurbs->myKnotsU->getMultiplicityByMap (r);
  //m = n + p + 1;
  //ord = p + 1;

  if (num > s)                         // Knot can be removed at most "s"-times
    num = s;
  else if (num < 0)                    // Remove knot "s"-times
    num = s;

  Vec4DArr1D Pw (n);                   // Array of 4D control points
  Vec4DArr1D temp (2*p+1);             // Temporary array of 4D points

  for (i = 0; i < n; i++)
    Pw.set (i, Vector4D(myNurbs->myPoints->get(i), myNurbs->myWeights->get(i)));

  fout = (2*r - s - p) / 2;            // First control point out
  first = r - p;
  last = r - s;

  for (t = 0; t < num; t++)
  {
    off = first - 1;                   // Difference in index between temp and P
    temp[0] = Pw[off];
    temp[last+1-off] = Pw[last+1];
    i = first;
    j = last;
    ii = 1;
    jj = last - off;
    remFlag = false;

    while (j-i > t)                    // Compute new control points for one removal step
    {
      alfi = (u - myNurbs->myKnotsU->get(i-1)) / (myNurbs->myKnotsU->get(i+p+t) - myNurbs->myKnotsU->get(i-1));
      alfj = (u - myNurbs->myKnotsU->get(j-t-1)) / (myNurbs->myKnotsU->get(j+p) - myNurbs->myKnotsU->get(j-t-1));
      temp[ii] = (Pw[i] - (1.0 - alfi) * temp[ii-1]) / alfi;
      temp[jj] = (Pw[j] - alfj * temp[jj+1]) / (1.0 - alfj);

      i++, ii++;
      j--, jj--;
    }
    if (j-i < t)                       // Check if knot is removable
    {
      if (temp[ii-1].distance(temp[jj+1]) <= tolerance)
	remFlag = true;
    }
    else
    {
      alfi = (u - myNurbs->myKnotsU->get(i-1)) / (myNurbs->myKnotsU->get(i+p+t) - myNurbs->myKnotsU->get(i-1));
      if (Pw[i].distance(alfi*temp[ii+t+1]+(1.0-alfi)*temp[ii-1]) <= tolerance)
	remFlag = true;
    }
    if (remFlag == false)              // Cannot remove any more knots
    {
      if (force == true)               // Force removal
      {
	tolerance *= 2;                // Be less exact next time
	t--;                           // Assure continuation with correct "t"
	forceCounter++;                // Keep track of forcings
      }
      else                       
	break;                         // Exit for-loop
    }
    else                               // Removal was successful, save new control points
    {
      i = first;
      j = last;
      while (j-i > t)
      {
	Pw[i] = temp[i-off];
	Pw[j] = temp[j-off];
	i++, j--;
      }
      first--, last++;
    }
  }

  if (t != num)
    Report::recoverable ("[Nurbs3DManipulator::removeKnot] failed to remove knot desired number of times");

  if (t == 0)
    return 0;

  myNurbs->myKnotsU->removeKnot (u, t);          // Remove knot "t" times from knot vector
  i = j = fout;                        // Pw_j thru Pw_i will be overwritten
  int k;
  for (k = 1; k < t; k++)
  {
    if (k % 2 == 1)
      i++;
    else
      j--;
  }
  for (k = i+1; k < n; k++, j++)       // Shift control points
    Pw[j] = Pw[k];
  myNurbs->myPoints->initSize (n-t);             // Set new sizes
  myNurbs->myWeights->initSize (n-t);
  for (k = 0; k < n-t; k++)            // Set new control points
  {
    myNurbs->myPoints->set (k, Pw[k].make3D());
    myNurbs->myWeights->set (k, Pw[k].w());
 }
 return t;                            // Return number of removals
}

/***   removeKnotU : Remove knot from knot vector   *******/
//                                                        //
//  The knot "u" is removed "num"-times from the knot     //
//  vector i.e. if possible. The actual number of         //
//  removals is returned. The algorithm is implemented    //
//  to work on surfaces.                                  //
//                                                        //
/**********************************************************/

int Nurbs3DManipulator::removeKnotSurface (Real u, int num, Real tol, bool force)
{
  if (myNurbs->myDecomposition != NULL)         // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int x;
  int      m;
  int      t, tMin = MAXINT;

  Nurbs3D      *curve;
  Nurbs3DKnots   *knots;
  Nurbs3DPoints  *points;
  Nurbs3DWeights *weights;
  Nurbs3DManipulator manip;

  m = myNurbs->myPoints->getCountV ();
  for (x = 0; x < m; x++)              // Loop over v-direction
  {
    knots = myNurbs->copyKnotsU ();       // Get u-knots
    points = myNurbs->myPoints->extractAtV (x);
    weights = myNurbs->myWeights->extractAtV (x);
    curve = new Nurbs3D (knots, points, weights);
    manip.adoptNurbs (curve);
    t = manip.removeKnotCurve (u, num, tol, force);   // Remove knot from curve
    if (t < tMin)                                // Got a new minimum for removal
      tMin = t;
  }

  if (tMin == 0)
    return 0;

  PtArray1D pt1;
  PtArray2D *pts = new PtArray2D;
  WtArray1D wt1;
  WtArray2D *wts = new WtArray2D;

  for (x = 0; x < m; x++)               // Loop over v-direction
  {
    knots = myNurbs->copyKnotsU ();       // Get u-knots
    points = myNurbs->myPoints->extractAtV (x);  // Get points and weights
    weights = myNurbs->myWeights->extractAtV (x);
    curve = new Nurbs3D (knots, points, weights); // Initialize control curve
    manip.adoptNurbs (curve);
    manip.removeKnotCurve (u, tMin, tol, force);  // Remove knot from curve
    curve = manip.orphanNurbs ();
    curve->myPoints->copyPoints (&pt1);
    curve->myWeights->copyWeights (&wt1);
    delete curve;                          // Delete control curve
    pts->append (pt1);
    wts->append (wt1);
  }

  myNurbs->myKnotsU->removeKnot (u, tMin);
  myNurbs->adoptPoints (new Nurbs3DPoints (pts));
  myNurbs->adoptWeights (new Nurbs3DWeights (wts));
  myNurbs->myPoints->transpose ();
  myNurbs->myWeights->transpose ();
  return tMin;
}

