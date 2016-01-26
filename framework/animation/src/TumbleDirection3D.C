/*
 * TumbleDirection3D.C
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
 *  $Id: TumbleDirection3D.C,v 1.3 1996/11/13 09:38:11 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h>
#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "booga/animation/ActionInfo.h"
#include "booga/animation/TumbleDirection3D.h"
#include "booga/object/InterpolationCurve3D.h"          
#include "booga/nurbs/Nurbs3DEvaluator.h"          
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

// ____________________________________________________________________ TumbleDirection3D

implementRTTI(TumbleDirection3D, ActionInfoAttr);

TumbleDirection3D::TumbleDirection3D(Exemplar)
{
  myNurbs = NULL;
  myCurve = NULL;
}

TumbleDirection3D::TumbleDirection3D(const TumbleDirection3D& tumbleDirection)
:ActionInfoAttr(tumbleDirection)
{
 if (tumbleDirection.myNurbs != NULL)
    myNurbs = (Nurbs3D*)tumbleDirection.myNurbs->copy();
  else
    myNurbs = NULL;

  if (tumbleDirection.myCurve != NULL)
    myCurve = (InterpolationCurve3D*)tumbleDirection.myCurve->copy();
  else
    myCurve = NULL;
}         

TumbleDirection3D::TumbleDirection3D(Nurbs3DEvaluator* nurbsEvaluator, InterpolationCurve3D* curve)
{
  if (nurbsEvaluator)
    myNurbs = (Nurbs3D*)nurbsEvaluator->copyNurbs();
  else
    myNurbs = NULL;
  if (curve)
    myCurve = (InterpolationCurve3D*)curve->copy();
  else
    myCurve = NULL;
}

TumbleDirection3D::~TumbleDirection3D()
{
  delete myCurve;
  delete myNurbs;
}

void TumbleDirection3D::setAttribute(ActionInfo* actionInfo) const
{
  if (myNurbs) {
    actionInfo->setTumbleDirection(new Nurbs3D(*myNurbs));
  }
  else if (myCurve) {
    actionInfo->adoptTumbleDirection(new InterpolationCurve3D(*myCurve));
  }
  else {
    ostrstream os;
    os << "[TumbleDirection3D::setAttribute] curve not specified";
    Report::recoverable(os);       
  }

}

Makeable* TumbleDirection3D::make(RCString&, const List<Value*>*) const
{
  TumbleDirection3D* newDirection = new TumbleDirection3D(*this);

  newDirection->myNurbs = NULL;
  newDirection->myCurve = NULL;
  
  return newDirection;
}

int TumbleDirection3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3D* nurbs = dynamic_cast(Nurbs3D, specifier);

  if (nurbs != NULL) {
    if (!strcmp(nurbs->whatAmI(),"curve")) {
      myNurbs = nurbs;
      return 1;
    }
    else {
      myNurbs = NULL;
      errMsg = "[TumbleDirection3D::setSpecifier] nurbs is not a curve";
      return 0;
    }
  }

  InterpolationCurve3D* Curve = dynamic_cast(InterpolationCurve3D, specifier);

  if (Curve != NULL) {
      myCurve = Curve;
      return 1;
  } else {
      myCurve = NULL;
      errMsg = "[TumbleDirection3D::setSpecifier] object is not a curve";
      return 0;
  } 
  
  // 
  // Let papa do the rest ...
  //
  return ActionInfoAttr::setSpecifier(errMsg, specifier);
}

static const RCString tumbledirectionKeyword("tumbledirection");

RCString TumbleDirection3D::getKeyword() const {
  return tumbledirectionKeyword;
}

void TumbleDirection3D::iterateAttributes(MakeableHandler *handler) {
  if (myNurbs)
    handler->handle(myNurbs);
  else
    handler->handle(myCurve);
}
