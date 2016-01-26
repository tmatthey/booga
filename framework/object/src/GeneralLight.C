/*
 * $RCSfile: GeneralLight.C,v $
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
 *  $Id: GeneralLight.C,v 1.15 1996/09/13 08:04:15 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/object/List3D.h"
#include "booga/object/GeneralLight.h"

//_________________________________________________________________ GeneralLight

implementRTTI(GeneralLight, DirectedLight);

GeneralLight::GeneralLight(Exemplar exemplar)
: DirectedLight(exemplar)
{
  myLightRep = new List3D;
}

GeneralLight::GeneralLight(Real luminance, const Color& color)
: DirectedLight(luminance, color)
{
  myLightRep = new List3D;
}

void GeneralLight::adoptObject(Object3D* newObject)
{
  dynamic_cast<List3D*>(myLightRep)->adoptObject(newObject);
}

void GeneralLight::orphanObject(const Object3D* object)
{
  dynamic_cast<List3D*>(myLightRep)->orphanObject(object);
}

void GeneralLight::getDirection(Texture3DContext&) const
{
  return;
}

bool GeneralLight::isVisible(Texture3DContext&) const
{
  return true;
}

Object3D* GeneralLight::copy() const
{
  return new GeneralLight(*this);
}

int GeneralLight::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  //
  // There might be an object passed, so lets try to cast
  // specifier to Object3D* :
  //
  Object3D* object = dynamic_cast<Object3D*>(specifier);
  if (object != NULL) {
    adoptObject(object);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return DirectedLight::setSpecifier(errMsg, specifier);
}
