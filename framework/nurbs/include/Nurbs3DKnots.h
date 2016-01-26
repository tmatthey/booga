/*
 * Nurbs3DKnots.h
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
 *  $Id: Nurbs3DKnots.h,v 1.3 1996/01/12 16:09:46 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DKnots_H
# define _Nurbs3DKnots_H

/**********************************************************/
/*  Description: Definition file for the class            */
/*               Nurbs3DKnots. Nurbs3DKnots define a standard */
/*               interface to handle the knot sequence.   */
/**********************************************************/

#include "booga/nurbs/Nurbs3DParameters.h"

//_________________________________________________________________ Nurbs3DKnots
/***********************************************************
  Class Nurbs3DKnots : NURBS knot sequence
***********************************************************/

class Nurbs3DKnots : public Nurbs3DParameters {
  declareRTTI(Nurbs3DPoints);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DKnots (void);
  Nurbs3DKnots (int n, KnotArray *adoptKts);
  Nurbs3DKnots (const Nurbs3DKnots& nrb);
  virtual ~Nurbs3DKnots (void);
  
  virtual Nurbs3DKnots& operator= (const Nurbs3DKnots& nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DPoints
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  virtual Real& operator() (int pos);

  virtual Nurbs3DKnots* copy (void) const;

  virtual void adoptParameters (int n, KnotArray *knots);
  virtual void adoptKnots (KnotArray *knots);
  virtual void copyKnots (KnotArray *knots) const;
  virtual void insertKnot (Real knot, int cnt = 1);
  virtual void removeKnot (Real knot, int cnt = 1);
  virtual void deleteKnot (Real knot);
  
  virtual void merge (Nurbs3DKnots *knots);
  
  virtual Real get (int pos) const;
  virtual void set (int pos, Real kt);

  virtual int  getDegree (void) const;
  virtual void setDegree (int deg);

  virtual int  getCount (void) const;
  virtual int  getMultiplicity (int pos) const;
  virtual int  getMapping (int pos) const;
  virtual int  getMultiplicityByMap (int pos) const;

  virtual Real getFirstKnot (void) const;
  virtual Real getLastKnot (void) const;

  virtual int  getKnotInVector (Real knot) const;
  virtual bool findSpan (Real u, int &span) const;
  virtual bool findSpanMult (Real u, int &span, int &mult) const;
  virtual int  getKnotsRequired (int n, int k) const;
  
  virtual void scanKnots (void);
  virtual void reMap (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Nurbs3DParameters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void reset (void);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int        myDegree;               // Degree of associated curve (=> multiplicities !!! )
  int        myNumKnots;             // Total number of knots in knot sequence
  int        myNumSingKnots;         // Number of unique knots stored in "myKnots"
  KnotArray  *myKnots;               // Stored knot values
  IndexArray *myMultiplicities;      // Corresponding knot multiplicities
  IndexArray *myMapping  ;           // Mapping from i-th knot to stored value in "myKnots"
};

//______________________________________________________________________ INLINES

inline Nurbs3DKnots* Nurbs3DKnots::copy (void) const
{
  return new Nurbs3DKnots (*this);
}

inline Real Nurbs3DKnots::get (int pos) const
{
  return (*(Nurbs3DKnots*)this)(pos);
}

inline void Nurbs3DKnots::set (int pos, Real val)
{
  (*this)(pos) = val;
}

inline int Nurbs3DKnots::getDegree (void) const
{
  return myDegree;
}

inline void Nurbs3DKnots::setDegree (int val)
{
  myDegree = val;
}

inline int Nurbs3DKnots::getCount (void) const
{
  return myNumKnots;
}

inline int Nurbs3DKnots::getMultiplicity (int pos) const
{
  if (myMultiplicities != NULL)
    return myMultiplicities->get (pos);
  return 0;
}

inline int Nurbs3DKnots::getMapping (int pos) const
{
  if (myMapping != NULL)
    return myMapping->get (pos);
  return 0;
}

inline int Nurbs3DKnots::getMultiplicityByMap (int pos) const
{
  if (myMultiplicities != NULL)
    return myMultiplicities->get (myMapping->get(pos));
  return 0;
}

inline Real Nurbs3DKnots::getFirstKnot (void) const
{
  if (myKnots != NULL)
    return myKnots->get (0);
  return 0.0;
}

inline Real Nurbs3DKnots::getLastKnot (void) const
{
  if (myKnots != NULL)
    return myKnots->get (myNumSingKnots-1);
  return 0.0;
}

/***   getKnotsRequired : Return number of knots   ********/
//                                                        //
//  The number of knots needed to construct the knot      //
//  sequence is returned.                                 //
//                                                        //
/**********************************************************/

inline int Nurbs3DKnots::getKnotsRequired (int p, int n) const
{
  return n + p - 1;
}

#endif // _Nurbs3DKnots_H

