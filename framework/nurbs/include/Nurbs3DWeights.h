/*
 * Nurbs3DWeights.h
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
 *  $Id: Nurbs3DWeights.h,v 1.2 1996/01/12 16:09:52 streit Exp $      
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DWeights_H
# define _Nurbs3DWeights_H

/**********************************************************/
/*  Description: Definition file for the class            */
/*               Nurbs3DWeights. Nurbs3DWeights defines a     */
/*               standard interface to handle control     */
/*               point weights.                           */
/**********************************************************/

#include "booga/nurbs/Nurbs3DParameters.h"

//_______________________________________________________________ Nurbs3DWeights
/***********************************************************
  Class Nurbs3DWeights : NURBS control Weights
***********************************************************/

class Nurbs3DWeights : public Nurbs3DParameters {
  declareRTTI(Nurbs3DWeights);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DWeights (void);
  Nurbs3DWeights (WtArray1D *adoptWts);
  Nurbs3DWeights (WtArray2D *adoptWts);
  Nurbs3DWeights (const Nurbs3DWeights& nrb);
  virtual ~Nurbs3DWeights (void);

  virtual Nurbs3DWeights& operator= (const Nurbs3DWeights& nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DWeights
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Real& operator() (int u);
  virtual Real& operator() (int u, int v);

  virtual Nurbs3DWeights* copy (void) const;

  virtual void initSize (int size);
  virtual void initSize (int uSize, int vSize);
  virtual void adoptWeights (WtArray1D *wts);
  virtual void adoptWeights (WtArray2D *wts);
  virtual void copyWeights (WtArray1D *wts) const;
  virtual void copyWeights (WtArray2D *wts) const;
  virtual void insertAtU (int u, WtArray1D &wts);
  virtual void insertAtV (int v, WtArray1D &wts);
  virtual void removeAtU (int u);
  virtual void removeAtV (int v);
  virtual void transpose (void);
  
  virtual Nurbs3DWeights* extractAtU (int u) const;
  virtual Nurbs3DWeights* extractAtV (int v) const;

  virtual Real get (int u) const;
  virtual Real get (int u, int v) const;
  virtual void set (int u, Real wt);
  virtual void set (int u, int v, Real wt);

  virtual int getCountU (void) const;
  virtual int getCountV (void) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Nurbs3DParameters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void reset (void);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int       myNumU, myNumV;           // Number of weights in u- and v-directions
  WtArray1D *myCurvWeights;           // Array of weights for curve
  WtArray2D *mySurfWeights;           // Array of weights for surface
};

//______________________________________________________________________ INLINES

inline Nurbs3DWeights* Nurbs3DWeights::copy (void) const
{
  return new Nurbs3DWeights (*this);
}

inline Real Nurbs3DWeights::get (int u) const
{
  return (*(Nurbs3DWeights*)this)(u);
}

inline Real Nurbs3DWeights::get (int u, int v) const
{
  return (*(Nurbs3DWeights*)this)(u, v);
}

inline void Nurbs3DWeights::set (int u, Real wt)
{
  (*this)(u) = wt;
}

inline void Nurbs3DWeights::set (int u, int v, Real wt)
{
  (*this)(u, v) = wt;
}

inline int Nurbs3DWeights::getCountU (void) const
{
  return myNumU;
}

inline int Nurbs3DWeights::getCountV (void) const
{
  return myNumV;
}

#endif // _Nurbs3DWeights_H
