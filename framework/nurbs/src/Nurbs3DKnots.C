/*
 * Nurbs3DKnots.C 
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
 *  $Id: Nurbs3DKnots.C,v 1.2 1996/01/12 16:06:23 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/nurbs/Nurbs3DKnots.h"

//_________________________________________________________________ Nurbs3DKnots
/***********************************************************
  Class Nurbs3DKnots : NURBS Knot sequence
***********************************************************/

implementRTTI (Nurbs3DKnots, Nurbs3DParameters);

/***   Nurbs3DKnots : Constructor   *************************/
//                                                        //
//  Initialize from scratch.                              //
//                                                        //
/**********************************************************/

Nurbs3DKnots::Nurbs3DKnots (void)
  : Nurbs3DParameters (), myDegree (0), myNumKnots (0), myNumSingKnots (0)
{
  myKnots = NULL;
  myMultiplicities = NULL;
  myMapping = NULL;
}

/***   Nurbs3DKnots : Constructor   *************************/
//                                                        //
//  Initialize from given data.                           //
//                                                        //
/**********************************************************/

Nurbs3DKnots::Nurbs3DKnots (int n, KnotArray *adoptKts)
  : Nurbs3DParameters ()
{
  myKnots = NULL;
  myMultiplicities = NULL;
  myMapping = NULL;
  myDegree = n;
  if (adoptKts != NULL)
    myNumKnots = adoptKts->getCount ();
  else
    myNumKnots = 0;
  myNumSingKnots = myNumKnots;

  adoptKnots (adoptKts);                // Adopt knot sequence
}

/***   Nurbs3DKnots : Copy-constructor   ********************/
//                                                        //
//  Initialize a copy from given knot sequence.           //
//                                                        //
/**********************************************************/

Nurbs3DKnots::Nurbs3DKnots (const Nurbs3DKnots& nrb)
  : Nurbs3DParameters ()
{
  myKnots = NULL;
  myMultiplicities = NULL;
  myMapping = NULL;
  *this = nrb;
}

/***   ~Nurbs3DKnots : Destructor   *************************/
//                                                        //
//  Free all assigned dynamic memory.                     //
//                                                        //
/**********************************************************/

Nurbs3DKnots::~Nurbs3DKnots (void)
{
  if (myKnots != NULL)
    delete myKnots;
  if (myMultiplicities != NULL)
    delete myMultiplicities;
  if (myMapping != NULL)
    delete myMapping;
}

/***   operator= : Assignment   ***************************/
//                                                        //
//  Assign data from given knot sequence.                 //
//                                                        //
/**********************************************************/

Nurbs3DKnots& Nurbs3DKnots::operator= (const Nurbs3DKnots& nrb)
{
  myDegree = nrb.myDegree;             // Assign basic data
  myNumKnots = nrb.myNumKnots;
  myNumSingKnots = nrb.myNumSingKnots;    
  if (nrb.myKnots)                     // Assign only if "nrb" has points
  {
    if (myKnots == NULL)               // No arrays assigned so initialize
    {                                  // arrays
      myKnots = new KnotArray;
      myMultiplicities = new IndexArray;
      myMapping = new IndexArray;
    }
    *myKnots = *nrb.myKnots;                     // Assign knot sequence
    *myMultiplicities = *nrb.myMultiplicities;
    *myMapping = *nrb.myMapping;
  }
  else if (myKnots != NULL)            // "nrb" has no knots, so delete "myKnots",
  {                                    // "myMultiplicities" and "myMapping"
    delete myKnots;
    delete myMultiplicities;
    delete myMapping;
    myKnots = NULL;
    myMultiplicities = NULL;
    myMapping = NULL;
  }
  return *this;
}

/***   operator() : Get element   *************************/
//                                                        //
//  Get the i-th element in the knot sequence. Because    //
//  of the special form of the knot sequence (only        //
//  mulitplicities <= p (degree), knots nr. -1 and        //
//  mynumKnots are treated specially.                     //
//                                                        //
/**********************************************************/

Real& Nurbs3DKnots::operator() (int pos)
{
  if (myKnots == NULL)
    Report::error ("[Nurbs3DKnots::operator()] called on object without knots");

  if (pos == -1)                       // Ensure correct range
    pos = 0;
  if (pos == myNumKnots)               // do.
    pos = myNumKnots - 1;
  return (*myKnots)[myMapping->get(pos)];
}

/***   initialize : Initialize data   *********************/
//                                                        //
//  All data is reset.                                    //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::reset (void)
{
  myDegree = 0;                        // Reset counts
  myNumKnots = myNumSingKnots = 0;
  if (myKnots != NULL)                 // Delete knot sequence
  {
    delete myKnots;
    delete myMultiplicities;
    delete myMapping;
    myKnots = NULL;
    myMultiplicities = NULL;
    myMapping = NULL;
  }
}

/***   initialize : Initialize data   *********************/
//                                                        //
//  Knot sequence is setup from given data.               //
//  In standard form the first and last knots are         //
//  stored once in "knots" and have their multiplicities  //
//  set automatically to p (degree)                       //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::adoptParameters (int p, KnotArray *knots)
{
  reset ();                             // Reset data

  if (p != 0 && knots->getCount() != 0) // Both degree and number of knots are required
  {
    myDegree = p;
    adoptKnots (knots);                 // Define knot sequence
  }
}

/***   adoptKnots : Adopt knot sequence   *****************/
//                                                        //
//  The given knot vector is adopted and scanned.         //
//  Multiple knots are extracted and stored only once.    //
//  Then the knot vector is remapped according to the     //
//  type.                                                 //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::adoptKnots (KnotArray *knots)
{
  if (knots != NULL && knots->getCount() > 0)
  {
    int i;

    if (myKnots != NULL)
    {
      delete myKnots;                  // Discard stored knots
      delete myMultiplicities;         //    "      "    multiplicities
      myKnots = NULL;
      myMultiplicities = NULL;
    }

    myNumKnots = myNumSingKnots = knots->getCount();  // Initial value
    myKnots = knots;
    myMultiplicities = new IndexArray (myNumSingKnots);

    Real kt1, kt2;

    myMultiplicities->set (0, 1);      // Set multiplicity of first knot
    for (i = 1; i < myNumSingKnots; )
    {
      kt1 = myKnots->get (i-1);
      kt2 = myKnots->get (i);
      if (kt1 > kt2 - EPSILON && kt1 < kt2 + EPSILON)
      {
	(*myMultiplicities)[i-1]++;    // Existing knot given -> raise multiplicity,    
	myKnots->remove (i);           // remove knot from sequence, 
	myMultiplicities->remove (i);  // remove multiplicity and
	myNumSingKnots--;              // decrease number of unique knots
      }
      else                             // New knot found -> r_i = 1
      {
	myMultiplicities->set (i, 1);  // Set multiplicity
	i++;                           // Goto next knot
      }
    }
    scanKnots ();                      // Check for knots with wrong multiplicity (> n)
  }
}

/***   copyKnots : Copy knot sequence   *******************/
//                                                        //
//  The knot sequence is copied to the given array.       //
//  Multiple knots are placed r-times into the array.     //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::copyKnots (KnotArray *knots) const
{
  register int x;

  knots->initSize (myNumKnots);
  for (x = 0; x < myNumKnots; x++)
    knots->set (x, get(x));
}

/***   insertKnot : Insert a knot into sequence   *********/
//                                                        //
//  Insert the given knot into sequence. If the knot      //
//  value is found in the knot sequence, the              //
//  corresponding multiplicity is raised if it was        //
//  less than "myDegree". Otherwise it is inserted        //
//  at the correct location.                              //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::insertKnot (Real knot, int cnt)
{
  int pos;

  if (myKnots == NULL)
  {
    myKnots = new KnotArray;
    myMultiplicities = new IndexArray;
    myMapping = new IndexArray;
  }
    
  if ((pos = getKnotInVector(knot)) != -1)     // Knot was found in knot sequence
  {
    (*myMultiplicities)[myMapping->get(pos)] += cnt;  // Adjust multiplicity of corresponding knot
    myNumKnots += cnt;                                // Adjust total number of knots
  }
  else
  {
    pos = 0;                           // Find position for insertion
    while (pos < myNumSingKnots && myKnots->get(pos) < knot)
      pos++;
    myKnots->insert (pos, knot);            // Insert knot
    myMultiplicities->insert (pos, cnt);    // Adjust multiplicities
    myNumKnots += cnt;                      // Adjust number of knots
    myNumSingKnots++;                  // Adjust number of unique knots
  }
  scanKnots ();                        // Check for knots with wrong multiplicity (> myDegree)
}

/***   removeKnot : Remove knot from sequence   ***********/
//                                                        //
//  The given knot value is located in the knot           //
//  sequence and if it was found it is removed "cnt"      //
//  times by adjusting the corresponding multiplicity.    //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::removeKnot (Real knot, int cnt)
{
  int pos;

  if ((pos = getKnotInVector(knot)) != -1)     // Knot was found in knot sequence
  {
    int r;

    pos = myMapping->get (pos);        // Map position to position in "myKnots"
    r = myMultiplicities->get (pos);   // Get multiplicity of this knot

    if (r == cnt)                      // Knot will be removed entirely
    {
      myKnots->remove (pos);           // Remove knot
      myMultiplicities->remove (pos);  // Remove multiplicities
      myNumKnots -= r;                 // Adjust total number of knots
      myNumSingKnots--;                // Adjust number of unique knots
    }
    else                               // Knot is removed "cnt" times
    {
      myMultiplicities->set (pos, r-cnt);   // Adjust multiplicities
      myNumKnots -= cnt;                    // Adjust total number of knots
    }
    reMap ();                          // Ensure correct mapping
  }
  else
    Report::warning ("[Nurbs3DKnots::removeKnot] knot not found in knot sequence");
}

/***   deleteKnot : Delete knot from sequence   ***********/
//                                                        //
//  The given knot value is located in the knot           //
//  sequence and if it was found it is deleted.           //
//  The corresponding multiplicity is removed.            //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::deleteKnot (Real knot)
{
  int pos;

  if ((pos = getKnotInVector(knot)) != -1)     // Knot was found in knot sequence
  {
    int r;

    pos = myMapping->get (pos);        // Map position to position in "myKnots"
    r = myMultiplicities->get (pos);   // Get multiplicity of this knot

    myKnots->remove (pos);             // Remove knot
    myMultiplicities->remove (pos);    // Remove multiplicities

    myNumKnots -= r;                   // Adjust total number of knots
    myNumSingKnots--;                  // Adjust number of unique knots
    reMap ();                          // Ensure correct mapping
  }
  else
    Report::warning ("[Nurbs3DKnots::removeKnot] knot not found in knot sequence");
}

/***   merge : Merge knot vector with this one   **********/
//                                                        //
//  The knot sequence is merged with the given knot       //
//  sequence to form a new one.                           //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::merge (Nurbs3DKnots *knots)
{
  register int i;
  int      count, mult;
  Real     actKnot;

  count = knots->getCount ();          // Get number of new knots
  for (i = 0; i < count; )
  {
    actKnot = knots->get (i);                  // Get knot value
    mult = knots->getMultiplicityByMap (i);    // and multiplicity

    insertKnot (actKnot, mult);        // Insert knot into sequence
    i += mult;                         // Go to next knot
  }
}

/***   getKnotInVector : Is knot in sequence ?   ********/
//                                                        //
//  The knot sequence is searched for the given knot.     //
//  If it is found, the location of the corresponding     //
//  knot is returned.                                     //
//                                                        //
/**********************************************************/

int Nurbs3DKnots::getKnotInVector (Real knot) const
{
  int span;

  if (findSpan(knot, span) == false)  // Value not in knot interval
    return -1;

  if (equal(knot, getLastKnot()))     // Value is last knot
    return myNumKnots - 1;
  if (equal(knot, get(span)))         // Value is lower knot of span
    return span;

  return -1;                           // Signal failure
}

/*
 * findSpan
 *
 * Finds the knot span containing the given value
 */

bool Nurbs3DKnots::findSpan (Real u, int &span) const
{
  if (u < getFirstKnot() - EPSILON || u > getLastKnot() + EPSILON)
    return false;                       // value not contained in knot vector

  if (equal(u, getLastKnot()))          // Last knot is treated separately
    span = myNumKnots - myDegree - 1;   // Set correct span
  else                                  // Do binary search on knot vector
  {
    int low = myDegree - 1, high = myNumKnots - myDegree, mid;

    mid = (low + high) / 2;
    while (u < get(mid) || u >= get(mid+1))
    {
      if (u < get (mid))
	high = mid;
      else
	low = mid;
      mid = (low + high) / 2;
    }
    span = mid;                         // Set correct span
  }
  return true;                          // Signal success
}

/*
 * findSpanMult
 *
 * Finds the knot span containing the given value and the multiplicity
 * if the value was actually a knot
 */

bool Nurbs3DKnots::findSpanMult (Real u, int &span, int &mult) const
{
  if (equal(u, getLastKnot()))          // Last knot is treated separately
  {
    span = myNumKnots - myDegree - 1;   // Set correct span
    mult = myMultiplicities->get (myNumSingKnots-1);  // Set correct multiplicity
    return true;
  }

  if (findSpan(u, span) == false)       // Value is not contained in knot vector
    return false;

  if (equal(u, get(span)))              // Value is a knot
    mult = getMultiplicityByMap (span); // Set correct multiplicity
  else
    mult = 0;                           // Value isn't a knot
    
  return true;                          // Signal success
}

/***   scanKnots : Verify knot sequence   *****************/
//                                                        //
//  The knot sequence is scanned for the presence of      //
//  knots with mulitplicity > "myDegree". The found       //
//  mulitplicities are set to "myDegree".                 //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::scanKnots (void)
{
  int mult;
  
  if (myKnots == NULL)                 // Nothing to do
    return;

  if ((mult = myMultiplicities->get(0)) != myDegree)
  {
    myMultiplicities->set (0, myDegree);
    myNumKnots += myDegree - mult;
  }
  if ((mult = myMultiplicities->get(myNumSingKnots-1)) != myDegree)
  {
    myMultiplicities->set (myNumSingKnots-1, myDegree);
    myNumKnots += myDegree - mult;
  }

  for (int i = 1; i < myNumSingKnots-1; i++)
  {
    if (myMultiplicities->get(i) > myDegree)     // Knot's multiplicity is to big
    {
      mult = myMultiplicities->get (i);     // Get mulitplicity
      myNumKnots -= mult - myDegree;        // Reduce number of knots
      myMultiplicities->set (i, myDegree);  // Set multiplicity to correct value
    }
  }
  reMap ();                                 // Ensure correct mapping
}

/***   reMap : Ensure correct mapping   *******************/
//                                                        //
//  The mapping vector is rebuilt so that each index      //
//  points to the correct knot value in "myKnots".        //
//                                                        //
/**********************************************************/

void Nurbs3DKnots::reMap (void)
{
  int i, x;

  if (myNumSingKnots == 0)                       // No knots left
  {
    if (myKnots != NULL)                         // Reset data structure
    {
      delete myKnots;
      delete myMultiplicities;
      delete myMapping;
      myKnots = NULL;
      myMultiplicities = NULL;
      myMapping = NULL;
    }
    return;                                      // Nothing to do
  }

  if (myMapping != NULL)                         // Clear mapping array
  {
    delete myMapping;
    myMapping = NULL;
  }
  myMapping = new IndexArray;                    // Create empty mapping array
  for (i = 0; i < myNumSingKnots; i++)                // Perform mapping of knots to unique knot sequence
    for (x = 0; x < myMultiplicities->get(i); x++)    // insert knot i r-times into "myMapping"
      myMapping->append (i);
}
