/*
 * LightTexture.C
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
 *  $Id: LightTexture.C,v 1.5 1996/02/23 07:33:57 streit Exp buhlmann $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Texture3DContext.h"
#include "booga/object/LightTexture.h"   

//_________________________________________________________________ LightTexture

implementRTTI(LightTexture, Texture3D);

LightTexture::LightTexture(const Color& color)
{
  myColor = color;
}

Texture3D* LightTexture::copy() const
{
  return new LightTexture(*this);
}

void LightTexture::doTexturing(Texture3DContext& context) const
{
  context.setColor(myColor);
}

static const RCString lightTextureKeyword("lightTexture");

RCString LightTexture::getKeyword() const {
  return lightTextureKeyword;
}

void LightTexture::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
//  DummyMakeable m("diffuse", Value(myColor)));
//  handler->handle(&m);
}
