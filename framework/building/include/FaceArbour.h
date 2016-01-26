/*
 * $RCSfile: FaceArbour.h,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: FaceArbour.h,v 1.2 1997/02/06 14:13:42 matthey Exp matthey $
 * -----------------------------------------------------------------------------
 */

#ifndef _FaceArbour_H
#define _FaceArbour_H

#include "booga/base/Vector2D.h"
#include "booga/building/Face.h"

// ____________________________________________________________________ FaceArbour

class FaceArbour : public Face {
declareRTTI(FaceArbour);
// enable RTTI support


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  FaceArbour();
  FaceArbour(Exemplar exemplar);
  // FaceArbour(const FaceArbour& face);     // Use default version.
  FaceArbour(const Vector2D& from,const Vector2D& to, long column, Real arbourdepth);

public:
  // virtual ~FaceArbour();                // Use default version.
  
private:  
  FaceArbour& operator=(const FaceArbour&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class FaceArbour
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Real getArbourDepth() const;
  void setArbourDepth(Real arbourdepth);

  Real getColumnDepth() const;
  void setColumnDepth(Real columndepth);

  Real getColumnWidth() const;
  void setColumnWidth(Real columnwidth);

  Real getBezierParameter1() const;
  void setBezierParameter1(Real bezierparameter1);

  Real getBezierParameter2() const;
  void setBezierParameter2(Real bezierparameter2);

  long getNumberOfPoints() const;
  void setNumberOfPoints(long numberofpoints);

  void wallOn();
  void wallOff();
  bool isWall() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Face
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isFilled() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BuildingObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual Object3D* doCreateSubject(Building* building) const;  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real myArbourDepth;
  Real myBezierParameter1;
  Real myBezierParameter2;
  Real myColumnDepth;
  Real myColumnWidth;
  long myNumberOfPoints;
  bool myWallFlag;
};

//______________________________________________________________________ INLINES

inline Real FaceArbour::getArbourDepth() const
{
  return myArbourDepth;
}

inline void FaceArbour::setArbourDepth(Real arbourdepth)
{
  myArbourDepth = arbourdepth;
}

inline Real FaceArbour::getColumnWidth() const
{
  return myColumnWidth;
}

inline void FaceArbour::setColumnWidth(Real columnwidth)
{
  myColumnWidth = columnwidth;
}

inline Real FaceArbour::getBezierParameter1() const
{
  return myBezierParameter1;
}

inline void FaceArbour::setBezierParameter1(Real bezierparameter1)
{
  myBezierParameter1 = bezierparameter1;
}

inline Real FaceArbour::getBezierParameter2() const
{
  return myBezierParameter2;
}

inline Real FaceArbour::getColumnDepth() const
{
  return myColumnDepth;
}

inline void FaceArbour::setColumnDepth(Real columndepth)
{
  myColumnDepth = columndepth;
}

inline long FaceArbour::getNumberOfPoints() const
{
  return myNumberOfPoints;
}

inline void FaceArbour::wallOn()
{
  myWallFlag = true;
}

inline void FaceArbour::wallOff()
{
  myWallFlag = false;
}

inline bool FaceArbour::isWall() const
{
  return myWallFlag;
}

inline bool FaceArbour::isFilled() const
{
  return true;
}


#endif // _FaceArbour_H
