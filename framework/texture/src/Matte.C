/*
 * Matte.C 
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
 *  $Id: Matte.C,v 1.5 1996/10/04 11:32:30 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/AmbientLight.h"
#include "booga/object/DirectedLight.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"
#include "booga/texture/TextureUtilities.h"
#include "booga/texture/Matte.h"
#include "booga/texture/MatteAttr.h"

//________________________________________________________________________ Matte

implementRTTI(Matte, Texture3D);

Matte::Matte()
: myAmbient(Color(0,0,0)), 
  myDiffuse(Color(1,0,0))
{}

Matte::Matte(Exemplar)
: myAmbient(Color(0,0,0)), 
  myDiffuse(Color(1,0,0)) 
{}

Texture3D* Matte::copy() const
{
  return new Matte(*this);
}

void Matte::doTexturing(Texture3DContext& context) const
{
  // collect ambient illumination
  Color ambientIllumination(0,0,0);
  forEachLight(AmbientLight, ambLight) {
    ambLight->getIllumination(context);
    ambientIllumination += context.getIllumination();
  }
  
  // collect directed illumination
  float cosAlpha;
  Color directedIllumination(0,0,0);
  forEachLight(DirectedLight, dirLight) {
    dirLight->getDirection(context);
    if ((cosAlpha = context.getNormalWCS() ^ context.getLightDirection()) > 0) {
      dirLight->getIllumination(context);
      directedIllumination += context.getIllumination() * cosAlpha;
    }        
  }
  
  context.setColor(myAmbient*ambientIllumination + myDiffuse*directedIllumination);
}

int Matte::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  MatteAttr* attr = dynamic_cast<MatteAttr*>(specifier);
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

static const RCString matteKeyword("matte");

RCString Matte::getKeyword() const {
  return matteKeyword;
}

void Matte::iterateAttributes(MakeableHandler *handler) {
  Texture3D::iterateAttributes(handler);
  {
    DummyMakeable m("diffuse", Value(getDiffuse()));
    handler->handle(&m);
  }
  if (!equal(getAmbient().brightness(), 0.0)) {
    DummyMakeable m("ambient", Value(getAmbient()));
    handler->handle(&m);
  }
}
