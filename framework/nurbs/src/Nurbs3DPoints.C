/*
 * Nurbs3DPoints.C
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
 *  $Id: Nurbs3DPoints.C,v 1.2 1996/01/12 16:06:27 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/nurbs/Nurbs3DPoints.h"

//________________________________________________________________ Nurbs3DPoints
/***********************************************************
  Class Nurbs3DPoints : NURBS Control points
***********************************************************/

implementRTTI (Nurbs3DPoints, Nurbs3DParameters);

/***   Nurbs3DPoints : Constructor   ************************/
//                                                        //
//  Initialize from scratch.                              //
//                                                        //
/**********************************************************/

Nurbs3DPoints::Nurbs3DPoints (void)
  : Nurbs3DParameters (), myNumU (0), myNumV (0)
{
  myCurvPoints = NULL;
  mySurfPoints = NULL;
}

/***   Nurbs3DPoints : Constructor   ************************/
//                                                        //
//  Initialize from given data (curve).                   //
//                                                        //
/**********************************************************/

Nurbs3DPoints::Nurbs3DPoints (PtArray1D *adoptPts)
  : Nurbs3DParameters (), myNumV (0)
{
  if (adoptPts != NULL)
    myNumU = adoptPts->getCount ();
  else
    myNumU = 0;
  myCurvPoints = adoptPts;             // Assign control points
  mySurfPoints = NULL;
  setType (Nurbs3DTypes::Curve);
}

/***   Nurbs3DPoints : Constructor   ************************/
//                                                        //
//  Initialize from given data (surface).                 //
//                                                        //
/**********************************************************/

Nurbs3DPoints::Nurbs3DPoints (PtArray2D *adoptPts)
  : Nurbs3DParameters ()
{
  if (adoptPts != NULL)
  {
    myNumU = adoptPts->getCountU ();
    myNumV = adoptPts->getCountV ();
  }
  else
    myNumU = myNumV = 0;
  mySurfPoints = adoptPts;             // Assign control points
  myCurvPoints = NULL;
  setType (Nurbs3DTypes::Surface);
}

/***   Nurbs3DPoints : Copy constructor   *******************/
//                                                        //
//  Initialize a copy from given control points.          //
//                                                        //
/**********************************************************/

Nurbs3DPoints::Nurbs3DPoints (const Nurbs3DPoints& nrb)
  : Nurbs3DParameters (), myCurvPoints (NULL), mySurfPoints (NULL)
{
  *this = nrb;
}

/***   ~Nurbs3DPoints : Destructor   ************************/
//                                                        //
//  Free all assigned dynamic memory.                     //
//                                                        //
/**********************************************************/

Nurbs3DPoints::~Nurbs3DPoints (void)
{
  if (myCurvPoints != NULL)
    delete myCurvPoints;
  if (mySurfPoints != NULL)
    delete mySurfPoints;
}

/***   operator= : Assignment   ***************************/
//                                                        //
//  Assign data from given control points                 //
//                                                        //
/**********************************************************/

Nurbs3DPoints& Nurbs3DPoints::operator= (const Nurbs3DPoints& nrb)
{
  myNumU = nrb.myNumU;                 // Assign basic data
  myNumV = nrb.myNumV;
  setType (nrb.getType());

  if (myCurvPoints != NULL)            // Delete curve points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
  if (mySurfPoints != NULL)            // Delete surface points
  {
    delete mySurfPoints;
    mySurfPoints = NULL;
  }

  if (getType() == Nurbs3DTypes::Curve)     // Assign points for curve
  {
    myCurvPoints = new PtArray1D;      // Assign empty array
    *myCurvPoints = *nrb.myCurvPoints; // Assign control points
  }
  else if (getType() == Nurbs3DTypes::Surface)   // Assign points for surface
  {
    mySurfPoints = new PtArray2D;      // Assign empty array
    *mySurfPoints = *nrb.mySurfPoints; // Assign control points
  }
  return *this;
}

/***   operator() : Get control point by index   **********/
//                                                        //
//  This function returns the indicated control point     //
//  of a curve.                                           //
//                                                        //
/**********************************************************/

Vector3D& Nurbs3DPoints::operator() (int u)
{
  if (getType() != Nurbs3DTypes::Curve)
    Report::error ("[Nurbs3DPoints::operator()] needs a curve");

  return (*myCurvPoints)[u];
}

/***   operator() : Get control point by index   **********/
//                                                        //
//  This function returns the indicated control point     //
//  of a surface.                                         //
//                                                        //
/**********************************************************/

Vector3D& Nurbs3DPoints::operator() (int u, int v)
{
  if (getType() != Nurbs3DTypes::Surface)
    Report::error ("[Nurbs3DPoints::operator()] needs a surface");

  return (*mySurfPoints)[u][v];
}

/***   initialize : Reset data   **************************/
//                                                        //
//  The data is reset.                                    //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::reset (void)
{
  myNumU = 0;                          // Reset counts
  myNumV = 0;
  setType (Nurbs3DTypes::None);
  if (myCurvPoints != NULL)            // Delete control points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
  if (mySurfPoints != NULL)            // Delete control points
  {
    delete mySurfPoints;
    myCurvPoints = NULL;
  }
}

/***   initSize : Set new size   **************************/
//                                                        //
//  The data is reset and a new size is set (curve).      //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::initSize (int size)
{
  myNumU = size;                       // Reset counts
  myNumV = 0;
  setType (Nurbs3DTypes::Curve);
  if (myCurvPoints != NULL)            // Delete control points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
  if (mySurfPoints != NULL)            // Delete control points
  {
    delete mySurfPoints;
    myCurvPoints = NULL;
  }
  myCurvPoints = new PtArray1D (size);
}

/***   initSize : Set new size   **************************/
//                                                        //
//  The data is reset and a new size is set (surface).    //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::initSize (int uSize, int vSize)
{
  myNumU = uSize;                      // Reset counts
  myNumV = vSize;
  setType (Nurbs3DTypes::Surface);
  if (myCurvPoints != NULL)            // Delete control points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
  if (mySurfPoints != NULL)            // Delete control points
  {
    delete mySurfPoints;
    myCurvPoints = NULL;
  }
  mySurfPoints = new PtArray2D (uSize, vSize);
}

/***   adoptPoints : Initialize points for curve   ********/
//                                                        //
//  The given control points are adopted.                 //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::adoptPoints (PtArray1D *pts)
{
  setType (Nurbs3DTypes::Curve);          // Set direction type
  if (pts != NULL)
    myNumU = pts->getCount ();           // Set counts
  else
    myNumU = 0;
  myNumV = 0;

  if (myCurvPoints != NULL)            // Delete control points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
  myCurvPoints = pts;                  // Assign points
  if (mySurfPoints != NULL)            // Delete surface points
  {
    delete mySurfPoints;
    mySurfPoints = NULL;
  }
}

/***   adoptPoints : Initialize points for surface   ******/
//                                                        //
//  The given control points are adopted.                 //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::adoptPoints (PtArray2D *pts)
{
  setType (Nurbs3DTypes::Surface);        // Set direction type
  if (pts != NULL)
  {
    myNumU = pts->getCountU ();          // Set counts
    myNumV = pts->getCountV ();
  }
  else
    myNumU = myNumV = 0;

  if (mySurfPoints != NULL)            // Delete control points
  {
    delete mySurfPoints;
    mySurfPoints = NULL;
  }
  mySurfPoints = pts;                  // Assign points
  if (myCurvPoints != NULL)            // Delete curve points
  {
    delete myCurvPoints;
    myCurvPoints = NULL;
  }
}

/***   copyPoints : Copy control points   *****************/
//                                                        //
//  The control points of the curve are copied to the     //
//  given array.                                          //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::copyPoints (PtArray1D *pts) const
{
  if (getType() != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3DPoints::copyPoints] needs a curve");
    return;
  }

  register int x;

  pts->initSize (myNumU);
  for (x = 0; x < myNumU; x++)
    pts->set (x, get(x));
}

/***   copyPoints : Copy control points   *****************/
//                                                        //
//  The control points of the surface are copied to the   //
//  given array.                                          //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::copyPoints (PtArray2D *pts) const
{
  if (getType() != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3DPoints::copyPoints] needs a surface");
    return;
  }

  register int x, y;

  pts->initSize (myNumU, myNumV);
  for (x = 0; x < myNumU; x++)
    for (y = 0; y < myNumV; y++)
      pts->set (x, y, get(x, y));
}

/***   insertAtU : Insert points at u-value   *************/
//                                                        //
//  Insert "myNumV" points at given u-value.              //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::insertAtU (int u, PtArray1D &pts)
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to insert multiple points
  {
    Report::warning ("[Nurbs3DPoints::insertAtU] needs a surface");
    return;
  }
  if (pts.getCount() != myNumV)        // Wrong number of points to be inserted
  {
    Report::warning ("[Nurbs3DPoints::insertAtU] wrong number of points");
    return;
  }
  if (u < 0 || u > myNumU)       // Check for valid insertion location
  {
    Report::warning ("[Nurbs3DPoints::insertAtU] wrong location");
    return;
  }

  if (mySurfPoints == NULL)            // Initialize array if necessary
    mySurfPoints = new PtArray2D;
  mySurfPoints->insert (u, pts);    // Insert new control points
  myNumU++;
}

/***   insertAtV : Insert points at v-value   *************/
//                                                        //
//  Insert "myNumU" points at given v-value.              //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::insertAtV (int v, PtArray1D &pts)
{
  transpose ();                        // Transpose points
  insertAtU (v, pts);               // Now insert in u-direction
  transpose ();                        // Retranspose
}

/***   removeAtU : Remove points at u-value   *************/
//                                                        //
//  Remove "myNumV" points at given u-value (if           //
//  possible).                                            //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::removeAtU (int u)
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to remove multiple points
  {
    Report::warning ("[Nurbs3DPoints::removeAtU] needs a surface");
    return;
  }
  if (u < 0 || u >= myNumU)      // Need valid location for removal
  {
    Report::warning ("[Nurbs3DPoints::removeAtU] wrong location");
    return;
  }

  mySurfPoints->remove (u);         // Remove control points
  myNumU--;

  if (myNumU == 0)                     // No more points left
  {
    setType (Nurbs3DTypes::None);         // Reset data
    myNumV = 0;
    delete mySurfPoints;
    mySurfPoints = NULL;
  }
}

/***   removeAtV : Remove points at v-value   *************/
//                                                        //
//  Remove "myNumU" points at given v-value (if           //
//  possible).                                            //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::removeAtV (int v)
{
  transpose ();                        // Transpose points
  removeAtU (v);                    // Now remove in u-direction
  transpose ();                        // Retranspose
}

/***   extractAtU : Extract points at u-value   ***********/
//                                                        //
//  Extract "myNumV" points at given u-value (if          //
//  possible).                                            //
//                                                        //
/**********************************************************/

Nurbs3DPoints* Nurbs3DPoints::extractAtU (int u) const
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to extract points
    Report::error ("[Nurbs3DPoints::extractAtU] needs a surface");
  if (u < 0 || u >= myNumU)      // Need valid location for extraction
    Report::error ("[Nurbs3DPoints::extractAtU] wrong location");

  register int x;
  Nurbs3DPoints  *newPoints = new Nurbs3DPoints;

  newPoints->initSize (myNumV);        // "myNumV" points are extracted
  for (x = 0; x < myNumV; x++)
    newPoints->set (x, mySurfPoints->get (u, x));
  return newPoints;
}

/***   extractAtV : Extract points at v-value   ***********/
//                                                        //
//  Extract "myNumU" points at given v-value (if          //
//  possible).                                            //
//                                                        //
/**********************************************************/

Nurbs3DPoints* Nurbs3DPoints::extractAtV (int v) const
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to extract points
    Report::error ("[Nurbs3DPoints::extractAtV] needs a surface");
  if (v < 0 || v >= myNumV)      // Need valid location for extraction
    Report::error ("[Nurbs3DPoints::extractAtV] wrong location");

  register int x;
  Nurbs3DPoints  *newPoints = new Nurbs3DPoints;

  newPoints->initSize (myNumU);        // "myNumU" points are extracted
  for (x = 0; x < myNumU; x++)
    newPoints->set (x, mySurfPoints->get(x, v));
  return newPoints;
}

/***   transpose : Transpose control points   *************/
//                                                        //
//  The control points are swapped between u- and v-      //
//  directions. This function is used to allow single     //
//  implementations of surface algorithms.                //
//                                                        //
/**********************************************************/

void Nurbs3DPoints::transpose (void)
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to transpose
  {
    Report::warning ("[Nurbs3DPoints::transpose] needs a surface");
    return;
  }

  register   int u, v;
  PtArray2D *temp = new PtArray2D (myNumV, myNumU);

  for (u = 0; u < myNumU; u++)         // Swap points
    for (v = 0; v < myNumV; v++)
      temp->set (v, u, mySurfPoints->get(u, v));
  adoptPoints (temp);                  // Adopt new points
}
