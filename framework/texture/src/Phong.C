/*
 * Phong.C 
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
 *  $Id: Phong.C,v 1.5 1996/10/04 11:33:43 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>

#include "booga/object/AmbientLight.h"
#include "booga/object/DirectedLight.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
#include "booga/texture/TextureUtilities.h"
#include "booga/texture/Phong.h"
#include "booga/texture/PhongAttr.h"
//________________________________________________________________________ Matte

implementRTTI(Phong, Texture3D);

Phong::Phong()
: myAmbient(Color(0,0,0)), 
  myDiffuse(Color(0,0,0)),
  mySpecular(Color(0,0,0)),
  mySpecPow(0)
{}

Phong::Phong(Exemplar)
: myAmbient(Color(0,0,0)), 
  myDiffuse(Color(0,0,0)), 
  mySpecular(Color(0,0,0)),
  mySpecPow(0)
{}

Texture3D* Phong::copy() const
{
  return new Phong(*this);
}

void Phong::doTexturing(Texture3DContext& context) const
{ 
  // collect ambient illumination
  Color ambientIllumination(0,0,0);

  forEachLight(AmbientLight, ambLight) {
    ambLight->getIllumination(context);
    ambientIllumination += context.getIllumination();
  }
  
  // collect directed illumination
  float cosAlpha;
  Real RV; 
  Color directedIllumination(0,0,0);
  Color specularIllumination(0,0,0);
  Vector3D normal = context.getNormalWCS();
  Vector3D toView = ( context.getIncidencePosition() - 
                      context.getPositionWCS()).normalized();

  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    cosAlpha = normal ^ context.getLightDirection();
    if (cosAlpha > 0) {
      dirLight->getIllumination(context);
      directedIllumination += context.getIllumination() * cosAlpha;
      RV = fabs((2*normal*cosAlpha-context.getLightDirection())^toView);
      specularIllumination += context.getIllumination() * (float)pow(RV,mySpecPow);
    }        
  }
  
  context.setColor(myAmbient*ambientIllumination  + 
                   myDiffuse*directedIllumination +
                   mySpecular*specularIllumination);
}

int Phong::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  PhongAttr* attr = dynamic_cast<PhongAttr*>(specifier);
  if (attr != NULL) {
    // The MatteAttr knows best which method has to be called.
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

static const RCString phongKeyword("phong");

RCString Phong::getKeyword() const {
  return phongKeyword;
}

void Phong::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);

  DummyMakeable diffuse("diffuse", Value(getDiffuse()));
  handler->handle(&diffuse);

  if (!equal(getAmbient().brightness(), 0.0)) {
    DummyMakeable ambient("ambient", Value(getAmbient()));
    handler->handle(&ambient);
  }
  if (!equal(getSpecular().brightness(), 0.0)) {
    DummyMakeable specular("specular", Value(getSpecular()));
    handler->handle(&specular);
    DummyMakeable specpow("specpow", Value(getSpecPow()));
    handler->handle(&specpow);
  }
}
