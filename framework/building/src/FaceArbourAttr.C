/*
 * FaceArbourAttr.C
 *
 * Copyright (C) 1994-96, University of Berne, Switzerland
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
 */

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "booga/building/FaceArbourAttr.h"
#include "booga/building/FaceArbour.h"

//_______________________________________________________________ FaceArbourAttr

implementRTTI(FaceArbourAttr, ObjectAttr);

//_________________________________________________ FaceArbourAttrNumberOfPoints

implementRTTI(FaceArbourAttrNumberOfPoints, FaceArbourAttr);

FaceArbourAttrNumberOfPoints::FaceArbourAttrNumberOfPoints(const Real& numberOfPoints)
: myNumberOfPoints(numberOfPoints)
{}

Makeable* FaceArbourAttrNumberOfPoints::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, numberOfPoints);

  return new FaceArbourAttrNumberOfPoints(numberOfPoints);
}

void FaceArbourAttrNumberOfPoints::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setNumberOfPoints(int(myNumberOfPoints));
}

//_______________________________________________ FaceArbourAttrBezierParameter1

implementRTTI(FaceArbourAttrBezierParameter1, FaceArbourAttr);

FaceArbourAttrBezierParameter1::FaceArbourAttrBezierParameter1(const Real& bezierParameter1)
: myBezierParameter1(bezierParameter1)
{}

Makeable* FaceArbourAttrBezierParameter1::make(RCString& errMsg,
                                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceArbourAttrBezierParameter1(value);
}

void FaceArbourAttrBezierParameter1::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setBezierParameter1(myBezierParameter1);
}

//_______________________________________________ FaceArbourAttrBezierParameter2

implementRTTI(FaceArbourAttrBezierParameter2, FaceArbourAttr);

FaceArbourAttrBezierParameter2::FaceArbourAttrBezierParameter2(const Real& bezierParameter2)
: myBezierParameter2(bezierParameter2)
{}

Makeable* FaceArbourAttrBezierParameter2::make(RCString& errMsg,
                                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceArbourAttrBezierParameter2(value);
}

void FaceArbourAttrBezierParameter2::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setBezierParameter2(myBezierParameter2);
}

//____________________________________________________ FaceArbourAttrColumnDepth

implementRTTI(FaceArbourAttrColumnDepth, FaceArbourAttr);

FaceArbourAttrColumnDepth::FaceArbourAttrColumnDepth(const Real& columnDepth)
: myColumnDepth(columnDepth)
{}

Makeable* FaceArbourAttrColumnDepth::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceArbourAttrColumnDepth(value);
}

void FaceArbourAttrColumnDepth::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setColumnDepth(myColumnDepth);
}

//____________________________________________________ FaceArbourAttrColumnWidth

implementRTTI(FaceArbourAttrColumnWidth, FaceArbourAttr);

FaceArbourAttrColumnWidth::FaceArbourAttrColumnWidth(const Real& columnWidth)
: myColumnWidth(columnWidth)
{}

Makeable* FaceArbourAttrColumnWidth::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceArbourAttrColumnWidth(value);
}

void FaceArbourAttrColumnWidth::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setColumnWidth(myColumnWidth);
}

//____________________________________________________ FaceArbourAttrArbourDepth

implementRTTI(FaceArbourAttrArbourDepth, FaceArbourAttr);

FaceArbourAttrArbourDepth::FaceArbourAttrArbourDepth(const Real& arbourDepth)
: myArbourDepth(arbourDepth)
{}

Makeable* FaceArbourAttrArbourDepth::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceArbourAttrArbourDepth(value);
}

void FaceArbourAttrArbourDepth::setAttribute(FaceArbour* facearbour) const
{
  facearbour->setArbourDepth(myArbourDepth);
}

//________________________________________________________ FaceArbourAttrWallOff

implementRTTI(FaceArbourAttrWallOff, FaceArbourAttr);

Makeable* FaceArbourAttrWallOff::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceArbourAttrWallOff(anExemplar);
}

void FaceArbourAttrWallOff::setAttribute(FaceArbour* facearbour) const
{
  facearbour->wallOff();
}

//_________________________________________________________ FaceArbourAttrWallOn

implementRTTI(FaceArbourAttrWallOn, FaceArbourAttr);

Makeable* FaceArbourAttrWallOn::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceArbourAttrWallOn(anExemplar);
}

void FaceArbourAttrWallOn::setAttribute(FaceArbour* facearbour) const
{
  facearbour->wallOn();
}

