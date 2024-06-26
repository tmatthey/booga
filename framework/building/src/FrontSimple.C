/*
 * $RCSfile: FrontSimple.C,v $
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
 *  $Id: FrontSimple.C,v 1.6 1997/05/09 13:23:31 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/building/FrontSimple.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ FrontSimple

implementRTTI(FrontSimple, Front);

FrontSimple::FrontSimple()
{}

FrontSimple::FrontSimple(long frontindex, long polygonindex)
{
  setFrontIndex(frontindex);
  setPolygonIndex(polygonindex);
}

FrontSimple::FrontSimple(Exemplar exemplar)
:Front(exemplar)
{
}

Object3D* FrontSimple::copy() const
{
  return new FrontSimple(*this);
}

Makeable* FrontSimple::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FrontSimple* newFrontSimple = NULL;

  if ((parameters == NULL) || (parameters->count() < 1) || (parameters->count() > 2))
    errMsg = "Wrong number of parameters.";   
  else {
    newFrontSimple = new FrontSimple(*this);
    getParameter(1, Real, frontindex);
    newFrontSimple->setFrontIndex((long)frontindex);
    if (parameters->count() >1){
      getParameter(2, Real, polygonindex);
      newFrontSimple->setPolygonIndex((long)polygonindex);
    }
  }

  return newFrontSimple;
}

List<Value*>* FrontSimple::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrontIndex()));
  parameters->append(new Value(getPolygonIndex()));
  return parameters;
}

void FrontSimple::iterateAttributes(MakeableHandler* handler) {
  this->Front::iterateAttributes(handler);
}

static const RCString frontsimpleKeyword("front");

RCString FrontSimple::getKeyword() const {
  return frontsimpleKeyword;
}

Object3D* FrontSimple::doCreateSubject(Building*)  const
{  
  return new NullObject3D();
}

List<Vector2D> FrontSimple::getPointsTop() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,1));
  temp.append(Vector2D(1,1));
  return temp;
}

List<Vector2D> FrontSimple::getPointsBottom() const
{
  List<Vector2D> temp;
  temp.append(Vector2D(0,0));
  temp.append(Vector2D(1,0));
  return temp;
}

bool FrontSimple::isFaceInFront(Face*) const
{
  return true;
}
