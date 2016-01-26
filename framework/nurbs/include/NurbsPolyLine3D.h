/*
 * $RCSfile: NurbsPolyLine3D.h,v $
 *
 * Copyright(C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: NurbsPolyLine3D.h,v 1.5 1996/09/12 13:51:34 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _NurbsPolyLine3D_H
#define _NurbsPolyLine3D_H

#include "booga/nurbs/Nurbs3D.h"

//______________________________________________________________ NurbsPolyLine3D

class NurbsPolyLine3D : public Nurbs3D {
  declareRTTI(NurbsPolyLine3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  NurbsPolyLine3D();
  NurbsPolyLine3D(Exemplar exemplar);
  NurbsPolyLine3D(PtArray1D *adoptPoints);
  NurbsPolyLine3D(const NurbsPolyLine3D &nrb);

public:
  virtual ~NurbsPolyLine3D();

public:
  NurbsPolyLine3D& operator=(const NurbsPolyLine3D &nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class NurbsPolyLine3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptLinePoints(PtArray1D *points);

  int getPointCount() const;

  const Vector3D getLinePoint(int pos) const;
  void setLinePoint(int pos, const Vector3D &point);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From Nurbs3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void rebuild();
  virtual void setAttribute(Nurbs3DPathAttr *attr);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TPrimitive
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BOOGAObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  virtual Makeable* make(RCString &errMsg, const List<Value*> *parameters) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int       myPointCount;
  PtArray1D *myPoints;
  bool      myCalculatedFlag;
};

//______________________________________________________________________ INLINES

inline int NurbsPolyLine3D::getPointCount() const
{
  return myPointCount;
}

inline const Vector3D NurbsPolyLine3D::getLinePoint(int pos) const
{
  if(pos >= 0 && pos < myPointCount)
    return myPoints->get(pos);
  else
    return Vector3D();
}

#endif // _NurbsPolyLine3D_H
