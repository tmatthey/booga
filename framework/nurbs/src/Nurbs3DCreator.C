/*
 * Nurbs3DCreator.C 
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
 *  $Id: Nurbs3DCreator.C,v 1.6 1996/03/28 14:07:47 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/nurbs/Nurbs3DTypes.h"
#include "booga/nurbs/Nurbs3DCreator.h"
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

//_______________________________________________________________ Nurbs3DCreator

implementRTTI(Nurbs3DCreator, Nurbs3DHandler);

/***   extrude : Create an extruded object   **************/
//                                                        //
//  This function creates an extruded object from an      //
//  outline curve by extending it in direction "d" by     //
//  length "len". An example would be a cylinder created  //
//  from a circle.                                        //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::extrude (Vector3D d, Real len)
{
  if (myNurbs->myType != Nurbs3DTypes::Curve)  // Element has to be curve
  {
    Report::warning ("[Nurbs3DCreator::extrued] needs a curve");
    return;
  }
  if (myNurbs->myDecomposition != NULL) // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int u;
  int      uc, vc;

  d *= len / d.length ();               // Create vector of desired length

  KnotArray *kts = new KnotArray (2);   // Create v-knot sequence for straight line
  kts->set (0, 0.00);
  kts->set (1, 1.00);
  myNurbs->adoptKnotsV (new Nurbs3DKnots(1, kts));        // Setup knot vector

  uc = myNurbs->myPoints->getCountU ();      // Get u-count
  vc = 2;                               // Set v-count for straight line

  PtArray2D *pts = new PtArray2D (uc, vc);   // Create control polygon
  for (u = 0; u < uc; u++)
  {
    (*pts)[u][0] = myNurbs->myPoints->get (u);
    (*pts)[u][1] = myNurbs->myPoints->get (u) + d;     // New point is offset by "d"
  }
  myNurbs->myPoints->adoptPoints (pts);      // Setup controlpoints

  WtArray2D *wts = new WtArray2D (uc, vc);   // Create weights
  for (u = 0; u < uc; u++)
  {
    (*wts)[u][0] = myNurbs->myWeights->get (u);   // Similar weights for old and corresponding new points
    (*wts)[u][1] = myNurbs->myWeights->get (u);
  }
  myNurbs->myWeights->adoptWeights (wts);    // Setup weights

  myNurbs->myType = Nurbs3DTypes::Surface;     // Now we got a surface
  Report::debug ("[Nurbs3DCreator::extrude] created surface");
}

/***   fitData : Fit curve thru given data points   *******/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::fitData (int, PtArray1D*, int)
{
  Report::warning("[Nurbs3DCreator::fitData] not yet implemented");
}

/***   fitData : Fit surface thru given data points   *****/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::fitData (int, int, PtArray2D*, int, int)
{
  Report::warning ("[Nurbs3DCreator::fitData] not yet implemented");
}

/***   interpolate : Interpolate curve thru points   ******/
//                                                        //
//  This function interpolates a curve of given degree    //
//  thru the given data points. The algorithm is adopted  //
//  from Piegl & Tiller's curve interpolation             //
//  algorithm.                                            //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::interpolate (PtArray1D *dataPts, int deg)
{
  myNurbs->reset ();
  myNurbs->myType = Nurbs3DTypes::Curve;

  register   int i, j;
  int        ctrlCt = dataPts->getCount ();
  int        knotCt = ctrlCt - deg + 1;
  Real       sum, *val = new Real[ctrlCt];
  KnotArray  *kts = new KnotArray (knotCt);
  PtArray1D  *pts = new PtArray1D (ctrlCt);
  WtArray1D  *wts = new WtArray1D (ctrlCt);

  if (ctrlCt <= deg)                   // Curve needs at least "deg" + 1 control points
  {
    Report::warning ("[Nurbs3DManipulator::interpolate] too few data points for degree");
    return;
  }

//   val[0] = 0.0;	                       // Calculate parameter values
//   val[ctrlCt-1] = 1.0;	               // Use chord length method
//   sum = 0.0;
//   for (i = 1; i < ctrlCt; i++)
//     sum += ((*dataPts)[i] - (*dataPts)[i-1]).length();
//   for (i = 1; i < ctrlCt - 1; i++)
//     val[i] = val[i-1] + ((*dataPts)[i] - (*dataPts)[i-1]).length() / sum;

  val[0] = 0.0;                         // Calculate parameter values
  val[ctrlCt-1] = 1.0;                  // Use centripetal method
  sum = 0.0;
  for (i = 1; i < ctrlCt; i++)
    sum += sqrt (((*dataPts)[i] - (*dataPts)[i-1]).length());
  for (i = 1; i < ctrlCt - 1; i++)
    val[i] = val[i-1] + sqrt (((*dataPts)[i] - (*dataPts)[i-1]).length()) / sum;

  kts->set (0, 0.0);                    // Calculate knot sequence
  kts->set (knotCt-1, 1.0);
  for (i = 1; i < knotCt - 1; i++)
  {
    sum = 0.0;
    for (j = i; j < i + deg; j++)
      sum += val[j];
    kts->set (i, sum / deg);
  }
  myNurbs->adoptKnotsU (new Nurbs3DKnots(deg, kts));  // Initialize knot sequence

  interpolateC (dataPts, pts, val, deg);    // Interpolate curve thru data points
  for (i = 0; i < ctrlCt; i++)               // Calculate weights
    (*wts)[i] = 1.0;

  myNurbs->adoptPoints (new Nurbs3DPoints(pts));      // Initialize control points
  myNurbs->adoptWeights (new Nurbs3DWeights(wts));    // Initialize weights

  delete val;                                // Clean up
  Report::debug ("[Nurbs3DCreator::interpolate] created curve");
}

/***   interpolate : Interpolate surface thru points   ****/
//                                                        //
//  This function interpolates a surface of given         //
//  degrees thru the given data points. The algorithm     //
//  is adopted from Piegl & Tiller's surface              //
//  interpolation algorithm.                              //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::interpolate (PtArray2D *dataPts, int udeg, int vdeg)
{
  myNurbs->reset ();
  myNurbs->myType = Nurbs3DTypes::Surface;

  register   int k, l;
  int        ctrlCtU = dataPts->getCountU (),
	     ctrlCtV = dataPts->getCountV (),
	     knotCtU = ctrlCtU - udeg + 1,
	     knotCtV = ctrlCtV - vdeg + 1;
  int        num, maxpts = ctrlCtU >  ctrlCtV ? ctrlCtU : ctrlCtV;
  Real       *cds = new Real[maxpts],
	     *uk = new Real[ctrlCtU], 
             *vl = new Real[ctrlCtV],
	     total, d;
  KnotArray  *ukt = new KnotArray (knotCtU);
  KnotArray  *vkt = new KnotArray (knotCtV);
  PtArray2D  *pts = new PtArray2D (ctrlCtU, ctrlCtV);
  WtArray2D  *wts = new WtArray2D (ctrlCtU, ctrlCtV);

  if (ctrlCtU <= udeg || ctrlCtV <= vdeg)   // Assure correct number of points in u- and v-direction
  {
    Report::warning ("[Nurbs3DManipulator::interpolate] too few data points for degree");
    return;
  }

  num = ctrlCtV;                       // Number of nondegenerate rows
  uk[0] = 0.0;                         // Calculate parameter values
  uk[ctrlCtU-1] = 1.0;
  for (k = 1; k < ctrlCtU - 1; k++)
    uk[k] = 0.0;
  for (l = 0; l < ctrlCtV; l++)
  {
    total = 0.0;                       // Total chord length of row
    for (k = 1; k < ctrlCtU; k++)
    {
      cds[k] = ((*dataPts)[k][l] - (*dataPts)[k-1][l]).length ();
      total += cds[k];
    }
    if (total == 0.0)                  // Row is degenerate
      num--;                           // Adjust number
    else
    {
      d = 0.0;
      for (k = 1; k < ctrlCtU - 1; k++)
      {
	d += cds[k];
	uk[k] += d / total;            // Calculate parameter
      }
    }
  }
  if (num == 0)
    Report::error ("[Nurbs3DManipulator::interpolate] degenerate data points");
  for (k = 1; k < ctrlCtU - 1; k++)
    uk[k] /= num;

  ukt->set (0, 0.0);                   // Calculate u-knot sequence
  ukt->set (knotCtU-1, 1.0);
  for (k = 1; k < knotCtU - 1; k++)
  {
    total = 0.0;
    for (l = k; l < k + udeg; l++)
      total += uk[l];
    ukt->set (k, total / udeg);
  }
  myNurbs->adoptKnotsU (new Nurbs3DKnots(udeg, ukt));

  num = ctrlCtU;                       // Number of nondegenerate rows
  vl[0] = 0.0;                         // Calculate parameter values
  vl[ctrlCtV-1] = 1.0;
  for (l = 0; l < ctrlCtV - 1; l++)
    vl[l] = 0.0;
  for (k = 0; k < ctrlCtU; k++)
  {
    total = 0.0;                       // Total chord length of row
    for (l = 1; l < ctrlCtV; l++)
    {
      cds[l] = ((*dataPts)[k][l] - (*dataPts)[k][l-1]).length ();
      total += cds[l];
    }
    if (total == 0.0)                  // Row is degenerate
      num--;                           // Adjust number
    else
    {
      d = 0.0;
      for (l = 1; l < ctrlCtV - 1; l++)
      {
	d += cds[l];
	vl[l] += d / total;            // Calculate parameter
      }
    }
  }
  if (num == 0)
    Report::error ("[Nurbs3DManipulator::interpolate] degenerate data points");
  for (l = 1; l < ctrlCtV - 1; l++)
    vl[l] /= num;

  vkt->set (0, 0.0);                   // Calculate v-knot sequence
  vkt->set (knotCtV-1, 1.0);
  for (l = 1; l < knotCtV - 1; l++)
  {
    total = 0.0;
    for (k = l; k < l + vdeg; k++)
      total += vl[k];
    vkt->set (l, total / vdeg);
  }
  myNurbs->adoptKnotsV (new Nurbs3DKnots(vdeg, vkt));

  PtArray1D dat (ctrlCtU), ctl (ctrlCtU);
  for (l = 0; l < ctrlCtV; l++)             // U-directional curve interpolation
  {                                         // yields R_k,l
    for (k = 0; k < ctrlCtU; k++)
      dat[k] = (*dataPts)[k][l];
    interpolateC (&dat, &ctl, uk, udeg);    // Interpolate iso-u-curve
    for (k = 0; k < ctrlCtU; k++)
      pts->set (k, l, ctl[k]);              // R_k,l
  }

  dat.initSize (ctrlCtV); ctl.initSize (ctrlCtV);
  for (k = 0; k < ctrlCtU; k++)             // V-directional curve interpolation
  {                                         // yields P_k,l
    for (l = 0; l < ctrlCtV; l++)
      dat[l] = pts->get (k, l);
    interpolateC (&dat, &ctl, vl, vdeg, 1); // Interpolate iso-v-curve
    for (l = 0; l < ctrlCtV; l++)
      pts->set (k, l, ctl[l]);         // P_k,l
  }

  for (k = 0; k < ctrlCtU; k++)
    for (l = 0; l < ctrlCtV; l++)
      wts->set (k, l, 1.0);

  myNurbs->adoptPoints (new Nurbs3DPoints(pts));      // Initialize control points
  myNurbs->adoptWeights (new Nurbs3DWeights(wts));    // Initialize weights

  delete cds;                             // Clean up
  delete uk;
  delete vl;
  Report::debug ("[Nurbs3DCreator::interpolate] created surface");
}

/***   ruledSurface : Create ruled surface   **************/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::ruledSurface (Nurbs3D *, Nurbs3D *)
{
}

/***   surfaceOfRevolution : Create revolved surface   ****/
//                                                        //
//  This function creates a surface of revolution about   //
//  the z-axis. It assumes that the given curve lies in   //
//  the xz-plane and measures offsets from the x- and     //
//  z-axis.                                               //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::surfaceOfRevolution (void)
{
  if (myNurbs->myType != Nurbs3DTypes::Curve)  // Element has to be curve
  {
    Report::warning ("[Nurbs3DCreator::surfaceOfRevolution] needs a curve");
    return;
  }
  if (myNurbs->myDecomposition != NULL) // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int u;
  int      uc, vc;

  Nurbs3DKnots   uk, vk;
  Nurbs3DPoints  np;
  Nurbs3DWeights nw;

  KnotArray *kts = new KnotArray (10);       // Create knot sequence of circle
  kts->set (0, 0.00); kts->set (1, 0.00);    // (is used as v-sequence)  
  kts->set (2, 0.25); kts->set (3, 0.25);
  kts->set (4, 0.50); kts->set (5, 0.50);
  kts->set (6, 0.75); kts->set (7, 0.75);
  kts->set (8, 1.00); kts->set (9, 1.00);
  myNurbs->adoptKnotsV (new Nurbs3DKnots(2, kts));    // Setup v-knot sequence

  uc = myNurbs->myPoints->getCountU ();      // Control points of generatrix
  vc = 9;                                    // Circle out of 4 arcs

  PtArray2D *pts = new PtArray2D (uc, vc);   // Create control polygon
  for (u = 0; u < uc; u++)                   // Curve has to lie in xz-plane
  {
    Real dist, height;

    dist = myNurbs->myPoints->get(u).x();              // Radius of circle
    height = myNurbs->myPoints->get(u).z();            // "Height" of actual control point
    (*pts)[u][0] = Vector3D ( dist,     0, height);
    (*pts)[u][1] = Vector3D ( dist, -dist, height);
    (*pts)[u][2] = Vector3D (    0, -dist, height);
    (*pts)[u][3] = Vector3D (-dist, -dist, height);
    (*pts)[u][4] = Vector3D (-dist,     0, height);
    (*pts)[u][5] = Vector3D (-dist,  dist, height);
    (*pts)[u][6] = Vector3D (    0,  dist, height);
    (*pts)[u][7] = Vector3D ( dist,  dist, height);
    (*pts)[u][8] = Vector3D ( dist,     0, height);    // Calculate new control points
  }
  myNurbs->myPoints->adoptPoints (pts); // Setup controlpoints

  WtArray2D *wts = new WtArray2D (uc, vc);   // Calculate weights
  for (u = 0; u < uc; u++)
  {
    Real wt1, wt2;

    wt1 = myNurbs->myWeights->get (u);  // Weight of even control points
    wt2 = M_SQRT1_2 * wt1;              // Weight of odd control points (corners of arc)
    (*wts)[u][0] = wt1;                 // Assign weights
    (*wts)[u][1] = wt2;
    (*wts)[u][2] = wt1;
    (*wts)[u][3] = wt2;
    (*wts)[u][4] = wt1;
    (*wts)[u][5] = wt2;
    (*wts)[u][6] = wt1;
    (*wts)[u][7] = wt2;
    (*wts)[u][8] = wt1;
  }
  myNurbs->myWeights->adoptWeights (wts);    // Setup weights

  myNurbs->myType = Nurbs3DTypes::Surface;     // Surface of revolution is surface
  Report::debug ("[Nurbs3DCreator::surfaceOfRevolution] created surface");
}

/***   sweep : Sweep curve along trajectory   *************/
//                                                        //
//  This function sweeps a section curve (*this) along    //
//  a given trajectory.                                   //
//                                                        //
//  ===>>> This is a translational sweep !!! <<<===       //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::sweep (Nurbs3D *traj)
{
  if (myNurbs->myType != Nurbs3DTypes::Curve || traj->getType() != Nurbs3DTypes::Curve)     // Check for correct types
  {
    Report::warning ("[Nurbs3DCreator::sweep] needs two curves");
    return;
  }
  if (myNurbs->myDecomposition != NULL)         // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int u, v;
  int      uc, vc;

  myNurbs->adoptKnotsV (traj->copyKnotsU());    // Get knot sequence of trajectory curve

  uc = myNurbs->myPoints->getCountU ();      // Get control point counts
  vc = traj->getCtrlCountU ();

  PtArray2D *pts = new PtArray2D (uc, vc);   // Create control polygon
  for (u = 0; u < uc; u++)
    for (v = 0; v < vc; v++)
      (*pts)[u][v] = myNurbs->myPoints->get (u) + traj->getPoint (v) - traj->getPoint (0);
  myNurbs->myPoints->adoptPoints (pts);

  WtArray2D *wts = new WtArray2D (uc, vc);   // Calculate weights
  for (v = 0; v < vc; v++)
    for (u = 0; u < uc; u++)
      (*wts)[u][v] = myNurbs->myWeights->get (u) * traj->getWeight (v);
  myNurbs->myWeights->adoptWeights (wts);

  myNurbs->myType = Nurbs3DTypes::Surface;   // Sweeped surface is surface
  myNurbs->transpose ();                     // Create reasonable surface normals
  Report::debug ("[Nurbs3DCreator::sweep] created surface");
}

/***   swing : Swing curve along trajectory   *************/
//                                                        //
//  This function swings a section curve (*this) along    //
//  a given trajectory curve. Swinging is a special       //
//  form of rotational sweeping.                          //
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::swing (Nurbs3D *traj)
{
  if (myNurbs->myType != Nurbs3DTypes::Curve || traj->getType() != Nurbs3DTypes::Curve)     // Check for correct types
  {
    Report::warning ("[Nurbs3DCreator::swing] needs two curves");
    return;
  }
  if (myNurbs->myDecomposition != NULL)  // Delete the decomposition
  {
    delete myNurbs->myDecomposition;
    myNurbs->myDecomposition = NULL;
  }

  register int u, v;
  int      uc, vc;
  Real     alpha;
  Vector3D gp, sp;

  myNurbs->adoptKnotsV (traj->copyKnotsU());     // Get knot sequence of trajectory curve

  uc = myNurbs->myPoints->getCountU ();  // *this -> profile curve
  vc = traj->getCtrlCountU ();         // traj  ->  trajectory curve

  PtArray2D *pts = new PtArray2D (uc, vc);    // Create control polygon
  for (u = 0; u < uc; u++)
  {
    gp = myNurbs->myPoints->get (u);
    alpha = gp.x () / (traj->getPoint(0)).x ();
    for (v = 0; v < vc; v++)
    {
      sp = traj->getPoint (v);
      (*pts)[u][v] = Vector3D (alpha*sp.x(), alpha*sp.y(), gp.z());
    }
  }
  myNurbs->myPoints->adoptPoints (pts);  // Setup controlpoints

  WtArray2D *wts = new WtArray2D (uc, vc);    // Calculate weights
  for (u = 0; u < uc; u++)
    for (v = 0; v < vc; v++)
      (*wts)[u][v] = myNurbs->myWeights->get (u) * traj->getWeight (v);
  myNurbs->myWeights->adoptWeights (wts);

  myNurbs->myType = Nurbs3DTypes::Surface;
  myNurbs->transpose ();                    // Create reasonable surface normals
  Report::debug ("[Nurbs3DCreator::swing] created surface");
}

/***   interpolateC : Interpolate curve   *****************/
//                                                        //
//  The control points of an interpolated curve thru      //
//  "dataPts" are calculated using the parameter values   //
//  "val". This function is necessary to speed up         //
//  surface interpolation where the parameter values      //
//  are calculated only once. "vd" is used to indicate    //
//  whether the u- or v-knot values are used to setup     //
//  the matrix "N".                                       //
//                                                        //
/**********************************************************/

void Nurbs3DCreator::interpolateC (PtArray1D *dataPts, PtArray1D *ctrlPts, Real *val, int deg, int vd)
{
  register int i, j;
  int      ctrlCt = dataPts->getCount (), *span;

  Nurbs3DBasisFuns Ni;

  RealMatrix N (ctrlCt);               // ctrlCt x ctrlCt -Matrix

  // Initialize N

  for (i=0; i<ctrlCt; i++)
    for (j=0; j<ctrlCt; j++)
      if (i==j)
	  N[i][j] = 1.0;
	else
	  N[i][j] = 0.0;

  span = new int[ctrlCt];
  if (vd == 0)                         // Use u-knot sequence
  {
    Ni.adoptKnots (myNurbs->myKnotsU->copy());
    for (i = 0; i < ctrlCt; i++)
      myNurbs->myKnotsU->findSpan (val[i], span[i]);
  }
  else                                 // Use v-knot sequence
  {
    Ni.adoptKnots (myNurbs->myKnotsV->copy());
    for (i = 0; i < ctrlCt; i++)
      myNurbs->myKnotsV->findSpan (val[i], span[i]);
  }

  for (i = 0; i < ctrlCt; i++)         // Initialize
  {
    Ni.calculate (val[i], span[i]);    // Setup basis functions
    span[i]++;                         // My span differs from other
    for (j = 0; j <= deg; j++)
      N[i][span[i]-deg+j] = Ni.get (j);
  }
  N.inverse ();

  for (i = 0; i < ctrlCt; i++)         // Calculate control points
  {
    ctrlPts->set (i, Vector3D());
    for (j = 0; j < ctrlCt; j++)
      (*ctrlPts)[i] += N[i][j] * dataPts->get (j);
  }
}
