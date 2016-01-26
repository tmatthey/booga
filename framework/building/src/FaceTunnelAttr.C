/*
 * FaceTunnelAttr.C
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
#include "booga/building/FaceTunnelAttr.h"
#include "booga/building/FaceTunnel.h"

//_______________________________________________________________ FaceTunnelAttr

implementRTTI(FaceTunnelAttr, ObjectAttr);

//_________________________________________________ FaceTunnelAttrNumberOfPoints

implementRTTI(FaceTunnelAttrNumberOfPoints, FaceTunnelAttr);

FaceTunnelAttrNumberOfPoints::FaceTunnelAttrNumberOfPoints(const Real& numberOfPoints)
: myNumberOfPoints(numberOfPoints)
{}

Makeable* FaceTunnelAttrNumberOfPoints::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, numberOfPoints);

  return new FaceTunnelAttrNumberOfPoints(numberOfPoints);
}

void FaceTunnelAttrNumberOfPoints::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->setNumberOfPoints(int(myNumberOfPoints));
}

//_______________________________________________ FaceTunnelAttrBezierParameter1

implementRTTI(FaceTunnelAttrBezierParameter1, FaceTunnelAttr);

FaceTunnelAttrBezierParameter1::FaceTunnelAttrBezierParameter1(const Real& bezierParameter1)
: myBezierParameter1(bezierParameter1)
{}

Makeable* FaceTunnelAttrBezierParameter1::make(RCString& errMsg,
                                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceTunnelAttrBezierParameter1(value);
}

void FaceTunnelAttrBezierParameter1::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->setBezierParameter1(myBezierParameter1);
}

//_______________________________________________ FaceTunnelAttrBezierParameter2

implementRTTI(FaceTunnelAttrBezierParameter2, FaceTunnelAttr);

FaceTunnelAttrBezierParameter2::FaceTunnelAttrBezierParameter2(const Real& bezierParameter2)
: myBezierParameter2(bezierParameter2)
{}

Makeable* FaceTunnelAttrBezierParameter2::make(RCString& errMsg,
                                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceTunnelAttrBezierParameter2(value);
}

void FaceTunnelAttrBezierParameter2::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->setBezierParameter2(myBezierParameter2);
}

//____________________________________________________ FaceTunnelAttrColumnWidth

implementRTTI(FaceTunnelAttrColumnWidth, FaceTunnelAttr);

FaceTunnelAttrColumnWidth::FaceTunnelAttrColumnWidth(const Real& columnWidth)
: myColumnWidth(columnWidth)
{}

Makeable* FaceTunnelAttrColumnWidth::make(RCString& errMsg,
                                          const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new FaceTunnelAttrColumnWidth(value);
}

void FaceTunnelAttrColumnWidth::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->setColumnWidth(myColumnWidth);
}

//________________________________________________________ FaceTunnelAttrWallOff

implementRTTI(FaceTunnelAttrWallOff, FaceTunnelAttr);

Makeable* FaceTunnelAttrWallOff::make(RCString& errMsg,
                                      const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceTunnelAttrWallOff(anExemplar);
}

void FaceTunnelAttrWallOff::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->wallOff();
}

//_________________________________________________________ FaceTunnelAttrWallOn

implementRTTI(FaceTunnelAttrWallOn, FaceTunnelAttr);

Makeable* FaceTunnelAttrWallOn::make(RCString& errMsg,
                                     const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new FaceTunnelAttrWallOn(anExemplar);
}

void FaceTunnelAttrWallOn::setAttribute(FaceTunnel* facetunnel) const
{
  facetunnel->wallOn();
}

