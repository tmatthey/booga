/*
 * Nurbs3DPoints.h
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
 *  $Id: Nurbs3DPoints.h,v 1.2 1996/01/12 16:09:50 streit Exp $      
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DPoints_H
# define _Nurbs3DPoints_H

/**********************************************************/
/*  Description: Definition file for the class            */
/*               Nurbs3DPoints. Nurbs3DPoints define a        */
/*               standardinterface to handle the control  */
/*               points.                                  */
/**********************************************************/

#include "booga/nurbs/Nurbs3DParameters.h"

//________________________________________________________________ Nurbs3DPoints
/***********************************************************
  Class Nurbs3DPoints : NURBS control points
***********************************************************/

class Nurbs3DPoints : public Nurbs3DParameters {
   declareRTTI(Nurbs3DPoints);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3DPoints (void);
  Nurbs3DPoints (PtArray1D *adoptPts);
  Nurbs3DPoints (PtArray2D *adoptPts);
  Nurbs3DPoints (const Nurbs3DPoints& nrb);
  virtual ~Nurbs3DPoints (void);

  virtual Nurbs3DPoints& operator= (const Nurbs3DPoints& nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3DPoints
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Vector3D& operator() (int u);
  virtual Vector3D& operator() (int u, int v);

  virtual Nurbs3DPoints* copy (void) const;

  virtual void initSize (int size);
  virtual void initSize (int uSize, int vSize);
  virtual void adoptPoints (PtArray1D *pts);
  virtual void adoptPoints (PtArray2D *pts);
  virtual void copyPoints (PtArray1D *pts) const;
  virtual void copyPoints (PtArray2D *pts) const;
  virtual void insertAtU (int u, PtArray1D &pts);
  virtual void insertAtV (int v, PtArray1D &pts);
  virtual void removeAtU (int u);
  virtual void removeAtV (int v);
  virtual void transpose (void);

  virtual Nurbs3DPoints* extractAtU (int u) const;
  virtual Nurbs3DPoints* extractAtV (int v) const;

  virtual Vector3D get (int u) const;
  virtual Vector3D get (int u, int v) const;
  virtual void     set (int u, const Vector3D &pt);
  virtual void     set (int u, int v, const Vector3D &pt);

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
  int       myNumU, myNumV;           // Number of points in u- and v-directions
  PtArray1D *myCurvPoints;            // Array of points for curve
  PtArray2D *mySurfPoints;            // Array of points for surface
  Nurbs3DTypes::EObject myType;         // Object type
};

//______________________________________________________________________ INLINES

inline Nurbs3DPoints* Nurbs3DPoints::copy (void) const
{
  return new Nurbs3DPoints (*this);
}

inline Vector3D Nurbs3DPoints::get (int u) const
{
  return (*(Nurbs3DPoints*)this)(u);
}

inline Vector3D Nurbs3DPoints::get (int u, int v) const
{
  return (*(Nurbs3DPoints*)this)(u, v);
}

inline void Nurbs3DPoints::set (int u, const Vector3D &pt)
{
  (*this)(u) = pt;
}

inline void Nurbs3DPoints::set (int u, int v, const Vector3D &pt)
{
  (*this)(u, v) = pt;
}

inline int Nurbs3DPoints::getCountU (void) const
{
  return myNumU;
}

inline int Nurbs3DPoints::getCountV (void) const
{
  return myNumV;
}

#endif // _Nurbs3DPoints_H
