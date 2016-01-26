/*
 * TumblePath3D.C
 *
 * Copyright (C) 1995-96, Thierry Matthey <matthey@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: TumblePath3D.C,v 1.3 1996/11/13 09:38:13 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h>
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/TumblePath3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

// ____________________________________________________________________ TumblePath3D

implementRTTI(TumblePath3D, ActionInfoAttr);

TumblePath3D::TumblePath3D(Exemplar)
{
  myNurbs = NULL;
}

TumblePath3D::TumblePath3D(const TumblePath3D& tumblePath)
:ActionInfoAttr(tumblePath)
{
 if (tumblePath.myNurbs != NULL)
    myNurbs = (Nurbs3D*)tumblePath.myNurbs->copy();
  else
    myNurbs = NULL;

  if (tumblePath.myCurve != NULL)
    myCurve = (InterpolationCurve3D*)tumblePath.myCurve->copy();
  else
    myCurve = NULL;
}         

TumblePath3D::TumblePath3D(AnimationFunction* function, Nurbs3DEvaluator* nurbsEvaluator, InterpolationCurve3D* curve)
{
  myFunctionName = function->getKeyword();
  myStart = function->getStart();
  myEnd = function->getEnd();
  myStep = function->getStep();
  if (nurbsEvaluator)
    myNurbs = (Nurbs3D*)nurbsEvaluator->copyNurbs();
  else
    myNurbs = NULL;
  if (curve)
    myCurve = (InterpolationCurve3D*)curve->copy();
  else
    myCurve = NULL;
}

TumblePath3D::~TumblePath3D()
{
  delete myCurve;
  delete myNurbs;
}

void TumblePath3D::setAttribute(ActionInfo* actionInfo) const
{
  if (myNurbs) {
    actionInfo->setTumblePath(new Nurbs3D(*myNurbs),myFunctionName, myStart, myEnd, myStep);
  }
  else if (myCurve) {
    actionInfo->adoptTumblePath(new InterpolationCurve3D(*myCurve), 
				myFunctionName, myStart, myEnd, myStep);
  }
  else {
    std::stringstream os;
    os << "[TumblePath3D::setAttribute] curve not specified";
    Report::recoverable(os);       
  }      
}

Makeable* TumblePath3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  TumblePath3D* newPath = new TumblePath3D(*this);

  newPath->myNurbs = NULL;
  newPath->myCurve = NULL;
  newPath->myFunctionName = "id";
  newPath->myStart = 0;
  newPath->myEnd   = 1;
  newPath->myStep  = 0;

  long provided_ = (!parameters ? 0 : parameters->count());
  if (provided_ < 0 || provided_ > 4) {
    std::stringstream str;
    str << "between 0 and 4 parameter(s) required, "
	<< provided_ << " provided";
    errMsg = RCString(str);
    return NULL;
  }

  if (provided_ > 0) {
    getParameter(1, RCString, functionName);
    newPath->myFunctionName = functionName;
  }

  if (provided_ > 1) {
    getParameter(2, Real, start);
    newPath->myStart = start;
  }

  if (provided_ > 2) {
    getParameter(3, Real, end);
    newPath->myEnd = end;
  }

  if (provided_ > 3) {
    getParameter(4, Real, step);
    newPath->myStep = step;
  }

  return newPath;
}

int TumblePath3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3D* nurbs = dynamic_cast<Nurbs3D*>(specifier);

  if (nurbs != NULL) {
    if (!strcmp(nurbs->whatAmI(),"curve")) {
      myNurbs = nurbs;
      return 1;
    }
    else {
      myNurbs = NULL;
      errMsg = "[TumblePath3D::setSpecifier] nurbs is not a curve";
      return 0;
    }
  }

  InterpolationCurve3D* curve = dynamic_cast<InterpolationCurve3D*>(specifier);
  if (curve != NULL) { 
    myCurve = curve;
    return 1;
  } else {
    myCurve = NULL;
    errMsg = "[TumblePath3D::setSpecifier] object is not a curve";
    return 0;
  }

  // 
  // Let papa do the rest ...
  //
  //return ActionInfoAttr::setSpecifier(errMsg, specifier);
}

static const RCString tumblepathKeyword("tumblepath");

RCString TumblePath3D::getKeyword() const {
  return tumblepathKeyword;
}

List<Value*>* TumblePath3D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(Value(RCString("\"") + myFunctionName + RCString("\""))));
  parameters->append(new Value(Value(myStart)));
  parameters->append(new Value(Value(myEnd))); 
  parameters->append(new Value(Value(myStep)));
  return parameters;
}

void TumblePath3D::iterateAttributes(MakeableHandler *handler) {
  if (myNurbs)
    handler->handle(myNurbs);
  else
    handler->handle(myCurve);
}
