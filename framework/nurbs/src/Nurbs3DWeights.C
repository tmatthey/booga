/*
 * Nurbs3DWeights.C
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
 *  $Id: Nurbs3DWeights.C,v 1.2 1996/01/12 16:06:29 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/nurbs/Nurbs3DWeights.h"

//_______________________________________________________________ Nurbs3DWeights
/***********************************************************
  Class Nurbs3DWeights : NURBS Control Weights
***********************************************************/

implementRTTI (Nurbs3DWeights, Nurbs3DParameters);

/***   Nurbs3DWeights : Constructor   ***********************/
//                                                        //
//  Initialize from scratch.                              //
//                                                        //
/**********************************************************/

Nurbs3DWeights::Nurbs3DWeights (void)
  : Nurbs3DParameters (), myNumU (0), myNumV (0)
{
  myCurvWeights = NULL;
  mySurfWeights = NULL;
  setType (Nurbs3DTypes::None);
}

/***   Nurbs3DWeights : Constructor   ***********************/
//                                                        //
//  Initialize from given data (curve).                   //
//                                                        //
/**********************************************************/

Nurbs3DWeights::Nurbs3DWeights (WtArray1D *adoptWts)
  : Nurbs3DParameters (), myNumV (0)
{
  if (adoptWts != NULL)
    myNumU = adoptWts->getCount ();
  else
    myNumU = 0;
  myCurvWeights = adoptWts;
  mySurfWeights = NULL;
  setType (Nurbs3DTypes::Curve);
}

/***   Nurbs3DWeights : Constructor   ***********************/
//                                                        //
//  Initialize from given data (surface).                 //
//                                                        //
/**********************************************************/

Nurbs3DWeights::Nurbs3DWeights (WtArray2D *adoptWts)
  : Nurbs3DParameters ()
{
  if (adoptWts != NULL)
  {
    myNumU = adoptWts->getCountU ();
    myNumV = adoptWts->getCountV ();
  }
  else
    myNumU = myNumV = 0;
  mySurfWeights = adoptWts;
  myCurvWeights = NULL;
  setType (Nurbs3DTypes::Surface);
}

/***   Nurbs3DWeights : Copy constructor   ******************/
//                                                        //
//  Initialize a copy from given weights.                 //
//                                                        //
/**********************************************************/

Nurbs3DWeights::Nurbs3DWeights (const Nurbs3DWeights& nrb)
  : myCurvWeights (NULL), mySurfWeights (NULL)
{
  *this = nrb;
}

/***   ~Nurbs3DWeights : Destructor   ***********************/
//                                                        //
//  Free all assigned dynamic memory.                     //
//                                                        //
/**********************************************************/

Nurbs3DWeights::~Nurbs3DWeights (void)
{
  if (myCurvWeights != NULL)
    delete myCurvWeights;
  if (mySurfWeights != NULL)
    delete mySurfWeights;
}

/***   operator= : Assignment   ***************************/
//                                                        //
//  Assign data from given weights.                       //
//                                                        //
/**********************************************************/

Nurbs3DWeights& Nurbs3DWeights::operator= (const Nurbs3DWeights& nrb)
{
  myNumU = nrb.myNumU;
  myNumV = nrb.myNumV;
  setType (nrb.getType());

  if (myCurvWeights != NULL)           // Delete curve weights
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
  if (mySurfWeights != NULL)           // Delete surface weights
  {
    delete mySurfWeights;
    mySurfWeights = NULL;
  }

  if (getType() == Nurbs3DTypes::Curve)     // Assign weights for curve
  {
    myCurvWeights = new WtArray1D;          // Assign empty array
    nrb.copyWeights (myCurvWeights);        // Assign weights
  }
  else if (getType() == Nurbs3DTypes::Surface)   // Assign weights for surface
  {
    mySurfWeights = new WtArray2D;          // Assign empty array
    nrb.copyWeights (mySurfWeights);        // Assign weights
  }
  return *this;
}

/***   operator() : Get weight by index   *****************/
//                                                        //
//  This function returns the indicated weight of a       //
//  curve.                                                //
//                                                        //
/**********************************************************/

Real& Nurbs3DWeights::operator() (int i)
{
  if (getType() != Nurbs3DTypes::Curve)
    Report::error ("[Nurbs3DWeights::operator()] needs a curve");

  return (*myCurvWeights)[i];
}

/***   operator() : Get weight by index   *****************/
//                                                        //
//  This function returns the indicated weight of a       //
//  surface.                                              //
//                                                        //
/**********************************************************/

Real& Nurbs3DWeights::operator() (int u, int v)
{
  if (getType() != Nurbs3DTypes::Surface)
    Report::error ("[Nurbs3DWeights::operator()] needs a surface");

  return (*mySurfWeights)[u][v];
}

/***   initialize : Reset data   **************************/
//                                                        //
//  The data is reset.                                    //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::reset (void)
{
  myNumU = 0;                          // Reset counts
  myNumV = 0;
  setType (Nurbs3DTypes::None);
  if (myCurvWeights != NULL)           // Delete weights
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
  if (mySurfWeights != NULL)           // Delete weights
  {
    delete mySurfWeights;
    mySurfWeights = NULL;
  }
}

/***   initSize : Set new size   **************************/
//                                                        //
//  The data is reset and a new size is set (curve).      //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::initSize (int size)
{
  myNumU = size;                       // Reset counts
  myNumV = 0;
  setType (Nurbs3DTypes::Curve);
  if (myCurvWeights != NULL)           // Delete control points
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
  if (mySurfWeights != NULL)           // Delete control points
  {
    delete mySurfWeights;
    myCurvWeights = NULL;
  }
  myCurvWeights = new WtArray1D (size);
}

/***   initSize : Set new size   **************************/
//                                                        //
//  The data is reset and a new size is set (surface).    //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::initSize (int uSize, int vSize)
{
  myNumU = uSize;                      // Reset counts
  myNumV = vSize;
  setType (Nurbs3DTypes::Surface);
  if (myCurvWeights != NULL)           // Delete control points
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
  if (mySurfWeights != NULL)           // Delete control points
  {
    delete mySurfWeights;
    myCurvWeights = NULL;
  }
  mySurfWeights = new WtArray2D (uSize, vSize);
}

/***   adoptWeights : Initialize weights for curve   ******/
//                                                        //
//  The given weights are adopted.                        //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::adoptWeights (WtArray1D *wts)
{
  if (wts != NULL)
    myNumU = wts->getCount ();           // Set counts
  else
    myNumU = 0;
  myNumV = 0;
  setType (Nurbs3DTypes::Curve);          // Set direction type

  if (myCurvWeights != NULL)           // Delete weights
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
  myCurvWeights = wts;                 // Assign weights
  if (mySurfWeights != NULL)           // Delete surface weights
  {
    delete mySurfWeights;
    mySurfWeights = NULL;
  }
}

/***   adoptWeights : Initialize weights for surface   ****/
//                                                        //
//  The given weights are adopted.                        //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::adoptWeights (WtArray2D *wts)
{
  if (wts != NULL)
  {
    myNumU = wts->getCountU ();          // Set counts
    myNumV = wts->getCountV ();
  }
  else
    myNumU = myNumV = 0;
  setType (Nurbs3DTypes::Surface);        // Set direction

  if (mySurfWeights != NULL)           // Delete weights
  {
    delete mySurfWeights;
    mySurfWeights = NULL;
  }
  mySurfWeights = wts;                 // Assign weights
  if (myCurvWeights != NULL)           // Delete curve weights
  {
    delete myCurvWeights;
    myCurvWeights = NULL;
  }
}

/***   copyWeights : Copy weights   ***********************/
//                                                        //
//  The weights are copied to the given array.            //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::copyWeights (WtArray1D *wts) const
{
  if (getType() != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3DWeights::copyWeights] needs curve");
    return;
  }

  register int x;

  wts->initSize (myNumU);
  for (x = 0; x < myNumU; x++)
    wts->set (x, get(x));
}

/***   copyWeights : Copy weights   ***********************/
//                                                        //
//  The weights are copied to the given array.            //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::copyWeights (WtArray2D *wts) const
{
  if (getType() != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3DWeights::copyWeights] needs surface");
    return;
  }

  register int x, y;

  wts->initSize (myNumU, myNumV);
  for (x = 0; x < myNumU; x++)
    for (y = 0; y < myNumV; y++)
      wts->set (x, y, get(x, y));
}

/***   insertAtU : Insert weights at u-value   ************/
//                                                        //
//  Insert "myNumV" weights at given u-value.             //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::insertAtU (int u, WtArray1D &wts)
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to insert multiple weights
  {
    Report::warning ("[Nurbs3DWeights::insertAtU] needs a surface");
    return;
  }
  if (wts.getCount() != myNumV)        // Wrong number of weights to be inserted
  {
    Report::warning ("[Nurbs3DWeights::insertAtU] wrong number of points");
    return;
  }
  if (u < 0 || u > myNumU)       // Check for valid insertion location
  {
    Report::warning ("[Nurbs3DWeights::insertAtU] wrong location");
    return;
  }

  if (mySurfWeights == NULL)           // Initialize array if necessary
    mySurfWeights = new WtArray2D;
  mySurfWeights->insert (u, wts);   // Insert new weights       
  myNumU++;
}

/***   insertAtV : Insert weights at v-value   ************/
//                                                        //
//  Insert "myNumU" weights at given v-value.             //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::insertAtV (int v, WtArray1D &wts)
{
  transpose ();                        // Transpose weights
  insertAtU (v, wts);               // Now insert in u-direction
  transpose ();                        // Retranspose
}

/***   removeAtU : Remove weights at u-value   ************/
//                                                        //
//  Remove "myNumV" weights at given u-value (if          //
//  possible).                                            //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::removeAtU (int u)
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to remove multiple weights
  {
    Report::warning ("[Nurbs3DWeights::removeAtU] needs a surface");
    return;
  }
  if (u < 0 || u >= myNumU)      // Need valid location for removal
  {
    Report::warning ("[Nurbs3DWeights::removeAtU] wrong location");
    return;
  }

  mySurfWeights->remove (u);        // Remove weights
  myNumU--;

  if (myNumU == 0)                     // No more weights left
  {
    setType (Nurbs3DTypes::None);         // Reset data
    myNumV = 0;
    delete mySurfWeights;
    mySurfWeights = NULL;
  }
}

/***   removeAtV : Remove weights at v-value   ************/
//                                                        //
//  Remove "myNumU" weights at given v-value (if          //
//  possible).                                            //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::removeAtV (int v)
{
  transpose ();                        // Transpose weights
  removeAtU (v);                    // Now remove in u-direction
  transpose ();                        // Retranspose
}

/***   extractAtU : Extract weights at u-value   **********/
//                                                        //
//  Extract "myNumV" weights at given u-value (if         //
//  possible).                                            //
//                                                        //
/**********************************************************/

Nurbs3DWeights* Nurbs3DWeights::extractAtU (int u) const
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to extract weights
    Report::error ("[Nurbs3DWeights::extractAtU] needs a surface");
  if (u < 0 || u >= myNumU)      // Need valid location for extraction
    Report::error ("[Nurbs3DWeights::extractAtU] wrong location");

  register int x;
  Nurbs3DWeights *newWeights = new Nurbs3DWeights;

  newWeights->initSize (myNumV);       // "myNumV" weights are extracted
  for (x = 0; x < myNumV; x++)
    newWeights->set (x, mySurfWeights->get(u, x));
  return newWeights;
}

/***   removeAtV : Remove weights at v-value   ************/
//                                                        //
//  Remove "myNumU" weights at given v-value (if          //
//  possible).                                            //
//                                                        //
/**********************************************************/

Nurbs3DWeights* Nurbs3DWeights::extractAtV (int v) const
{
  if (getType() != Nurbs3DTypes::Surface)   // Need a surface to extract weights
    Report::error ("[Nurbs3DWeights::extractAtV] needs a surface");
  if (v < 0 || v >= myNumV)      // Need valid location for extraction
    Report::error ("[Nurbs3DWeights::extractAtV] wrong location");

  register int x;
  Nurbs3DWeights *newWeights = new Nurbs3DWeights;

  newWeights->initSize (myNumU);       // "myNumU" weights are extracted
  for (x = 0; x < myNumU; x++)
    newWeights->set (x, mySurfWeights->get(x, v));
  return newWeights;
}

/***   transpose : Transpose weights   ********************/
//                                                        //
//  The weights are swapped between u- and v-directions.  //
//  This function is used to allow single                 //
//  implementations of surface algorithms.                //
//                                                        //
/**********************************************************/

void Nurbs3DWeights::transpose (void)
{
  if (getType() != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3DWeights::transpose] needs a surface");
    return;
  }

  register   int u, v;
  WtArray2D *temp = new WtArray2D (myNumV, myNumU);

  for (u = 0; u < myNumU; u++)         // Swap weights
    for (v = 0; v < myNumV; v++)
      temp->set (v, u, mySurfWeights->get(u, v));
  adoptWeights (temp);                 // Adopt new weigts
}
