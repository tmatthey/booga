/*
 * ConstantTexture2D.C 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: ConstantTexture2D.C,v 1.10 1996/10/04 09:46:21 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/object/Texture2DContext.h"
#include "booga/object/ConstantTexture2D.h"
#include "booga/object/MakeableHandler.h"


//____________________________________________________________ ConstantTexture2D

implementRTTI(ConstantTexture2D, Texture2D);

ConstantTexture2D::ConstantTexture2D(const Color& color) 
: myColor(color)
{}

ConstantTexture2D::ConstantTexture2D(Exemplar) 
{}

Makeable* ConstantTexture2D::make(RCString& errMsg, 
			       const List<Value*>* parameters) const
{
  //
  // We accept 0 (just make a copy of ourselves) or 1 parameters.
  //
   if (parameters != NULL && parameters->count() > 1) {
     errMsg = "expecting 1 parameter";
     return NULL;
  }

  ConstantTexture2D* newTexture = (ConstantTexture2D*) copy();

  if (parameters != NULL) { 
    //
    // There is one parameter present; has to be a Vector3D value.
    //
    getParameter(1, Vector3D, color);
    if (!(color.x() > -EPSILON && color.y() > -EPSILON && color.z() > -EPSILON)) {
      errMsg = "negative component for color value";
      return NULL;
    }
    newTexture->setColor(Color(fabs(color.x()), fabs(color.y()), fabs(color.z())));
  }	

  return newTexture;
}

Texture2D* ConstantTexture2D::copy() const
{
  return new ConstantTexture2D(*this);
}

void ConstantTexture2D::doTexturing(Texture2DContext& context) const
{
  context.setColor(myColor);
}

static const RCString constantTexture2DKeyword("color");

RCString ConstantTexture2D::getKeyword() const {
  return constantTexture2DKeyword;
}

List<Value*>* ConstantTexture2D::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getColor()));
  return parameters;
}

