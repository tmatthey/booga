/*
 * $RCSfile: PatternTexture2D.C,v $
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: PatternTexture2D.C,v 1.6 1997/09/19 07:14:26 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/object/Line2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/Texture2DContext.h"
#include "booga/object/PatternTexture2DAttr.h"
#include "booga/object/PatternTexture2D.h"

//_____________________________________________________________ PatternTexture2D

implementRTTI(PatternTexture2D, Texture2D);

PatternTexture2D::PatternTexture2D() 
{
  myPatternLength = 0;
  mySolid = myGap = NULL;
}

PatternTexture2D::PatternTexture2D(Exemplar) 
{
  myPatternLength = 0;
  mySolid = myGap = NULL;
}

PatternTexture2D::PatternTexture2D(const PatternTexture2D& pattern) 
: myPattern(pattern.myPattern), myPatternLength(pattern.myPatternLength)
{
  mySolid = ((pattern.mySolid != NULL) ? pattern.mySolid->copy() : (Texture2D*)NULL);
  myGap   = ((pattern.myGap   != NULL) ? pattern.myGap->copy()   : (Texture2D*)NULL);
}

PatternTexture2D::~PatternTexture2D()
{
  delete mySolid;
  delete myGap;
}

Makeable* PatternTexture2D::make(RCString& errMsg, 
			      const List<Value*>* parameters) const
{
  PatternTexture2D* newTexture = new PatternTexture2D(*this);

  if (parameters != NULL) { 
    List <float> pattern;
  
    for (long i=0; i<parameters->count(); i++) {
      getParameter(i+1, Real, value);
      pattern.append((float)value); 
    }
    newTexture->setPattern(pattern);
  }

  return newTexture;
}

int PatternTexture2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  PatternTexture2DAttr* attr = dynamic_cast<PatternTexture2DAttr*>(specifier);
  if (attr != NULL) {
    // The PatternTexture2DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Texture2D::setSpecifier(errMsg, specifier);
}

Texture2D* PatternTexture2D::copy() const
{
  return new PatternTexture2D(*this);
}

void PatternTexture2D::doTexturing(Texture2DContext& context) const
{
  float distance = 0;
  Line2D* line;
  
  if ((line = dynamic_cast<Line2D*>(const_cast<Object2D*>(context.getObject()))) != NULL) {
    Vector2D from = context.getOCS2WCS().transformAsPoint(line->getFrom());
    distance = from.distance(context.getPositionWCS());
  }
  else if ((dynamic_cast<Circle2D*>(const_cast<Object2D*>(context.getObject()))) != NULL) {
    // !!!!! to do: distance on the curve in WCS !!!!!
  }  

  float pos = distance - int(distance / myPatternLength)*myPatternLength;

  long i;
  for (i=0; i<myPattern.count(); i++) {
    if (pos <= myPattern.item(i))
      break;
  }
    
  Texture2D* toApply;
  if ((i+1) % 2)    // Solid ??
    toApply = mySolid;
  else              // Gap
    toApply = myGap;

  if (toApply != NULL)
    toApply->texturing(context);
}

void PatternTexture2D::computeCumulatedTransform(const Transform2D& additionalTransform)
{
  Texture2D::computeCumulatedTransform(additionalTransform);

  if (mySolid != NULL)
    mySolid->computeCumulatedTransform(getCumulatedTransform());
  if (myGap != NULL)
    myGap->computeCumulatedTransform(getCumulatedTransform());
}

void PatternTexture2D::setPattern(const List<float>& pattern)
{
  myPattern.removeAll();
  myPatternLength = 0;
  for (long i=0; i<pattern.count(); i++) {
    myPatternLength += pattern.item(i);
    myPattern.append(myPatternLength);
  } 
}

void PatternTexture2D::adoptSolid(Texture2D* texture)
{
  if (texture == NULL) {
    Report::warning("[PatternTexture2D::adoptSolid] NULL pointer passed");
    return;
  }

  //
  // Self assignment?
  //
  if (mySolid == texture)
    return;
    
  if (mySolid != NULL)
    delete mySolid;
  
  texture->computeCumulatedTransform(getCumulatedTransform());
  mySolid = texture;
}

void PatternTexture2D::adoptGap(Texture2D* texture)
{
  if (texture == NULL) {
    Report::warning("[PatternTexture2D::adoptGap] NULL pointer passed");
    return;
  }

  //
  // Self assignment?
  //
  if (myGap == texture)
    return;

  if (myGap != NULL)
    delete myGap;
  
  texture->computeCumulatedTransform(getCumulatedTransform());
  myGap = texture;
}

