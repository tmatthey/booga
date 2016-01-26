/*
 * NurbsData3D.h
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
 *  $Id: NurbsData3D.h,v 1.1 1996/01/12 16:09:55 streit Exp $ 
 * -----------------------------------------------------------------------------
 */

#ifndef _NurbsData3D_H
# define _NurbsData3D_H

#include "booga/nurbs/Nurbs3D.h"

//__________________________________________________________________ NurbsData3D

class NurbsData3D : public Nurbs3D {
  declareRTTI(NurbsData3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  NurbsData3D (void);
  NurbsData3D (Exemplar exemplar);
  NurbsData3D (PtArray1D *adoptCurveData);
  NurbsData3D (PtArray2D *adoptSurfaceData);
  virtual ~NurbsData3D (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class NurbsData3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void      adoptCurveData (PtArray1D *curveData);
  virtual PtArray1D *copyCurveData (void) const;
  virtual PtArray1D *orphanCurveData (void);

  virtual void      adoptSurfaceData (PtArray2D *surfaceData);
  virtual PtArray2D *copySurfaceData (void) const;
  virtual PtArray2D *orphanSurfaceData (void);

  virtual bool isChanged (void) const;
  virtual void setChanged (bool changed);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From Nurbs3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual void rebuild (void) = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  PtArray1D *myCurveData;
  PtArray2D *mySurfaceData;

private:
  bool    myChangedFlag;
};

//______________________________________________________________________ INLINES

inline bool NurbsData3D::isChanged (void) const
{
  return myChangedFlag;
}

inline void NurbsData3D::setChanged (bool changed)
{
  myChangedFlag = changed;
}

#endif // _NurbsData3D_H
