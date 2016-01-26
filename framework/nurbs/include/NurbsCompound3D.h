/*
 * NurbsCompound3D.h
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
 *  $Id: NurbsCompound3D.h,v 1.1 1996/01/12 16:09:54 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _NurbsCompound3D_H
# define _NurbsCompound3D_H

#include "booga/nurbs/Nurbs3D.h"

//______________________________________________________________ NurbsCompound3D

class NurbsCompound3D : public Nurbs3D {
  declareRTTI(NurbsCompound3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  NurbsCompound3D (void);
  NurbsCompound3D (Exemplar exemplar);
  NurbsCompound3D (Nurbs3D *adoptSection, Nurbs3D *adoptPath);
  virtual ~NurbsCompound3D (void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class NurbsCompound3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void    adoptSectionCurve (Nurbs3D *sectionCurve);
  virtual Nurbs3D *copySectionCurve (void) const;
  virtual Nurbs3D *orphanSectionCurve (void);

  virtual void    adoptPathCurve (Nurbs3D *pathCurve);
  virtual Nurbs3D *copyPathCurve (void) const;
  virtual Nurbs3D *orphanPathCurve (void);

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
  Nurbs3D *mySectionCurve;
  Nurbs3D *myPathCurve;

private:
  bool    myChangedFlag;
};

//______________________________________________________________________ INLINES

inline bool NurbsCompound3D::isChanged (void) const
{
  return myChangedFlag;
}

inline void NurbsCompound3D::setChanged (bool changed)
{
  myChangedFlag = changed;
}

#endif // _NurbsCompound3D_H
