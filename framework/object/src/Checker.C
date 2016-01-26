/*
 * $RCSfile: Checker.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Checker.C,v 1.16 1996/10/04 09:46:07 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/Checker.h"
#include "booga/object/CheckerAttr.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
//______________________________________________________________________ Checker

implementRTTI(Checker, Texture3D);

Checker::Checker()
{
  myEven = myOdd = NULL;
}

Checker::Checker(Exemplar)
{
  myEven = myOdd = NULL;
}

Checker::Checker(const Checker& checker)
{
  myEven = ((checker.myEven != NULL) ? checker.myEven->copy() : (Texture3D*)NULL);
  myOdd  = ((checker.myOdd  != NULL) ? checker.myOdd->copy()  : (Texture3D*)NULL);
}

Checker::~Checker()
{
  if (myEven != NULL)
    delete myEven;
  if (myOdd != NULL)
    delete myOdd;
}

int Checker::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  CheckerAttr* attr = dynamic_cast(CheckerAttr, specifier);
  if (attr != NULL) {
    // The CheckerAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Texture3D::setSpecifier(errMsg, specifier);
}

Texture3D* Checker::copy() const
{
  return new Checker(*this);
}

void Checker::doTexturing(Texture3DContext& context) const
{
  Vector3D pos = context.getPositionTCS();
 
  Real xp = pos.x() < 0 ? 1+frac(pos.x()) : frac(pos.x());
  Real yp = pos.y() < 0 ? 1+frac(pos.y()) : frac(pos.y());
  Real zp = pos.z() < 0 ? 1+frac(pos.z()) : frac(pos.z());
  
  Texture3D* toApply;
  toApply = zp < .5 ?
              yp < .5 ?
                xp < .5 ? myOdd : myEven
              :
                xp < .5 ? myEven : myOdd
            :
              yp < .5 ?
                xp < .5 ? myEven : myOdd
              : 
                xp < .5 ? myOdd : myEven;

  const float aaDistance = .002; // Distance from 0.5 to start anti aliasing
  Real value;                    // need anti aliasing
  if (.5-aaDistance < xp && xp < .5+aaDistance)
    value = xp-.5;
  else if (xp < aaDistance)
    value = xp;
  else if (xp > 1-aaDistance)
    value = 1-xp;
  else if (.5-aaDistance < yp && yp < .5+aaDistance)
    value = yp-.5;
  else if (yp < aaDistance)
    value = yp;
  else if (yp > 1-aaDistance)
    value = 1-yp;
  else if (.5-aaDistance < zp && zp < .5+aaDistance)
    value = zp-.5;
  else if (zp < aaDistance)
    value = zp;
  else if (zp > 1-aaDistance)
    value = 1-zp;
  else value = 0;
  
  if (value == 0)  // not equal() !
    toApply->texturing(context);
  else { // perform anti aliasing
    Texture3DContext evenContext(context);
    myEven->texturing(evenContext);
    Texture3DContext oddContext(context);
    myOdd->texturing(oddContext);
    
    Real weight = (.5/aaDistance)*value;

    if (toApply == myEven) 
      context.setColor(evenContext.getColor()*(float)weight + oddContext.getColor()*(float)(1-weight));
    else
      context.setColor(oddContext.getColor()*(float)weight + evenContext.getColor()*(float)(1-weight));
  }
}

void Checker::computeCumulatedTransform(const Transform3D& additionalTransform)
{
  Texture3D::computeCumulatedTransform(additionalTransform);

  if (myEven != NULL)
    myEven->computeCumulatedTransform(getCumulatedTransform());
  if (myOdd != NULL)
    myOdd->computeCumulatedTransform(getCumulatedTransform());
}

void Checker::adoptEven(Texture3D* texture)
{
  if (texture == NULL) {
    Report::warning("[Checker::adoptEven] NULL pointer passed");
    return;
  }

  //
  // Self assignment?
  //
  if (myEven == texture)
    return;

  delete myEven;
  
  texture->computeCumulatedTransform(getCumulatedTransform());
  myEven = texture;
}

void Checker::adoptOdd (Texture3D* texture)
{
  if (texture == NULL) {
    Report::warning("[Checker::adoptOdd] NULL pointer passed");
    return;
  }

  //
  // Self assignment?
  //
  if (myOdd == texture)
    return;

  delete myOdd;
  
  texture->computeCumulatedTransform(getCumulatedTransform());
  myOdd = texture;
}

static const RCString checkerKeyword("checker");

RCString Checker::getKeyword() const {
  return checkerKeyword;
}

void Checker::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
  DummyMakeable even("even");
  if (myEven != NULL) {
    even.addAttribute(myEven);
  }
  DummyMakeable odd("odd");
  if (myOdd != NULL) {
    odd.addAttribute(myOdd);
  }
  handler->handle(&even);
  handler->handle(&odd);
}
