/*
 * $RCSfile: FaceTunnel.h,v $
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
 *  $Id: FaceTunnel.h,v 1.4 1997/04/17 14:39:57 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _FaceTunnel_H
#define _FaceTunnel_H

#include "booga/base/Vector2D.h"
#include "booga/building/Face.h"

class FaceDummy;

// ____________________________________________________________________ FaceTunnel

class FaceTunnel : public Face {
declareRTTI(FaceTunnel);
// enable RTTI support


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  FaceTunnel();
  FaceTunnel(Exemplar exemplar);
  FaceTunnel(const FaceTunnel& face);    
  FaceTunnel(const Vector2D& from,const Vector2D& to,
             const Vector2D& otherfrom,const Vector2D& otherto,
             long otherfrontindex, long otherpolygonindex = 0);

public:
  virtual ~FaceTunnel();                
  
private:  
  FaceTunnel& operator=(const FaceTunnel&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class FaceTunnel
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setOtherFace(FaceDummy* front);

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
// From class Face
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isFilled() const;
  virtual List<List<Vector3D> > getAlternativeHoles(Building* building) const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler* handler);
  virtual void getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const;  

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
  FaceDummy* myOtherFace;
  
  Real  myColumnWidth;
  Real  myBezierParameter1;
  Real  myBezierParameter2;
  long  myNumberOfPoints;
  bool  myWallFlag;
};

//______________________________________________________________________ INLINES

inline Real FaceTunnel::getBezierParameter1() const
{
  return myBezierParameter1;
}

inline void FaceTunnel::setBezierParameter1(Real bezierparameter1)
{
  myBezierParameter1 = bezierparameter1;
}

inline Real FaceTunnel::getBezierParameter2() const
{
  return myBezierParameter2;
}

inline long FaceTunnel::getNumberOfPoints() const
{
  return myNumberOfPoints;
}

inline void FaceTunnel::wallOn()
{
  myWallFlag = true;
}

inline void FaceTunnel::wallOff()
{
  myWallFlag = false;
}

inline bool FaceTunnel::isWall() const
{
  return myWallFlag;
}

inline Real FaceTunnel::getColumnWidth() const
{
  return myColumnWidth;
}

inline void FaceTunnel::setColumnWidth(Real columnwidth)
{
  myColumnWidth = columnwidth;
}

inline void FaceTunnel::setOtherFace(FaceDummy* face)
{
  myOtherFace = face;
}

inline bool FaceTunnel::isFilled() const
{
  return true;
}

#endif // _FaceTunnel_H
