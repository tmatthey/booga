/*
 * $RCSfile: InterpolatorTexture2D.C,v $
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
 *  $Id: InterpolatorTexture2D.C,v 1.6 1997/09/19 07:14:12 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/base/mathutilities.h"
#include "booga/object/Line2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/Texture2DContext.h"
#include "booga/object/InterpolatorTexture2D.h"

//________________________________________________________ InterpolatorTexture2D

implementRTTI(InterpolatorTexture2D, Texture2D);

InterpolatorTexture2D::InterpolatorTexture2D() {}

InterpolatorTexture2D::InterpolatorTexture2D(Exemplar) {}

Makeable* InterpolatorTexture2D::make(RCString& errMsg, 
				  const List<Value*>* parameters) const
{
  //
  // We accept 0 (just make a copy of ourselves) or 2 parameters.
  //
  if (parameters != NULL && parameters->count() > 2) {
     errMsg = "expecting 1 parameter";
     return NULL;
  }
  
  InterpolatorTexture2D* newTexture = (InterpolatorTexture2D*) copy();
  
  if (parameters != NULL) { 
    //
    // There are two parameters present; have to be two Vector3D values.
    //
    getParameter(1, Vector3D, from);
    getParameter(2, Vector3D, to);

    if ((!(from.x() > -EPSILON && from.y() > -EPSILON && from.z() > -EPSILON)) || 
        (!(to.x()   > -EPSILON && to.y()   > -EPSILON && to.z()   > -EPSILON))) {
      errMsg = "negative component for color value";
      return NULL;
    }
    newTexture->setColor(Color(fabs(from.x()), fabs(from.y()), fabs(from.z())),
                         Color(fabs(to.x()),   fabs(to.y()),   fabs(to.z())));
  }
  
  return newTexture;
}

Texture2D* InterpolatorTexture2D::copy() const
{
  return new InterpolatorTexture2D(*this);
}

void InterpolatorTexture2D::doTexturing(Texture2DContext& context) const
{
  float lerpFactor = 0.5;

  Line2D* line;
  Circle2D* circle;
  
  if ((line = dynamic_cast<Line2D*>(const_cast<Object2D*>(context.getObject()))) != NULL) {
    lerpFactor = (context.getPositionOCS()-line->getFrom()).sqr()/
	        (line->getTo()-line->getFrom()).sqr();
  }
  else if ((circle = dynamic_cast<Circle2D*>(const_cast<Object2D*>(context.getObject()))) != NULL) {
    lerpFactor = context.getPositionOCS().x()-circle->getCenter().x()+circle->getRadius();
    lerpFactor /= 2*circle->getRadius();
  }  

  if (lerpFactor > 1)       lerpFactor = 1;
  if (lerpFactor < EPSILON) lerpFactor = 0;
    
  context.setColor(lerp(myColorFrom, myColorTo, lerpFactor));
}

static const RCString interpolatorTexture2DKeyword("interpolate");

RCString InterpolatorTexture2D::getKeyword() const {
  return interpolatorTexture2DKeyword;
}

List<Value*>* InterpolatorTexture2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getColorFrom()));
  parameters->append(new Value(getColorTo()));
  return parameters;
}
