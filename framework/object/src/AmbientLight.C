/*
 * $RCSfile: AmbientLight.C,v $
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
 *  $Id: AmbientLight.C,v 1.10 1996/10/04 09:45:45 collison Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/AmbientLight.h"

//_________________________________________________________________ AmbientLight

implementRTTI(AmbientLight, LightSource);

AmbientLight::AmbientLight(Exemplar exemplar)
: LightSource(exemplar)
{}

AmbientLight::AmbientLight(Real luminance, const Color& color)
: LightSource(luminance, color)
{}

Object3D* AmbientLight::copy() const
{
  return new AmbientLight(*this);
}

static const RCString ambientLightKeyword("ambientLight");

RCString AmbientLight::getKeyword() const {
  return ambientLightKeyword;
}
