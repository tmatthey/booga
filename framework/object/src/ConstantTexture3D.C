/*
 * ConstantTexture3D.C 
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: ConstantTexture3D.C,v 1.7 1996/10/04 09:46:24 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/object/ConstantTexture3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
//____________________________________________________________ ConstantTexture3D

implementRTTI(ConstantTexture3D, Texture3D);

ConstantTexture3D::ConstantTexture3D(Exemplar)
{}

Texture3D* ConstantTexture3D::copy() const
{
  return new ConstantTexture3D(*this);
}

void ConstantTexture3D::doTexturing(Texture3DContext& context) const
{
  context.setColor(myColor);
}

Makeable* ConstantTexture3D::make(RCString& errMsg, 
			       const List<Value*>* parameters) const
{
  if (parameters != NULL && parameters->count() > 1) {
     errMsg = "expecting 1 parameter";
     return NULL;
  }

  ConstantTexture3D* newTexture = new ConstantTexture3D(*this);

  if (parameters != NULL && parameters->count() == 1) {
    getParameter(1, Vector3D, color);
    if (!(color.x()>-EPSILON && color.y()>-EPSILON && color.z()>-EPSILON)) {
      errMsg = "negative component for color value";
      return NULL;
    }
    newTexture->setColor(Color(fabs(color.x()), 
			    fabs(color.y()), 
			    fabs(color.z())));
  }	

  return newTexture;
}

static const RCString constantTexture3DKeyword("constant");

RCString ConstantTexture3D::getKeyword() const {
  return constantTexture3DKeyword;
}

void ConstantTexture3D::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
  DummyMakeable m("color", Value(getColor()));
  handler->handle(&m);
}
