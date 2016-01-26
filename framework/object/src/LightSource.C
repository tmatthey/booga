/*
 * $RCSfile: LightSource.C,v $
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
 *  $Id: LightSource.C,v 1.19 1997/09/19 07:14:18 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/object/LightSource.h"
#include "booga/object/LightSourceAttr.h"
#include "booga/object/LightTexture.h"
#include "booga/object/Path3D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//__________________________________________________________________ LightSource

implementRTTI(LightSource, Object3D);

LightSource::LightSource(Exemplar exemplar)
: Object3D(exemplar)
{
  myLightRep = NULL;
  myIsOn = true;
  appendTexture(new LightTexture(Color(1,1,1)));
}

LightSource::LightSource(Real luminance, const Color& color)
: myLuminance(luminance), myColor(color)     
{
  myLightRep = NULL;
  myIsOn = true;
  appendTexture(new LightTexture(color));
}

LightSource::LightSource(const LightSource& lightSource)
: Object3D(lightSource),myLuminance(lightSource.myLuminance), 
  myColor(lightSource.myColor),
  myIsOn(lightSource.myIsOn)
{
  if (lightSource.myLightRep != NULL)
    myLightRep = lightSource.myLightRep->copy();
  else
    myLightRep = NULL;
}

LightSource::~LightSource()
{
  if (myLightRep) delete myLightRep;
}

long LightSource::countSubobject() const
{
  return (myLightRep == NULL) ? 0 : 1;
}

Object3D* LightSource::getSubobject(long index) 
{
  if (index != 0)
    Report::error("[LightSource::getSubobject] index out of range");

  return myLightRep;
}

Object3D* LightSource::makeUnique(Path3D* path, bool shared)
{
  //
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;
  
  // !!!!! Test! Test!!
  if (shared == true) {
    LightSource* newLight = (LightSource*)copy();

    if (newLight->myLightRep != NULL) {
      delete myLightRep;
      path->next();
      newLight->myLightRep = myLightRep->makeUnique(path, true);
      path->prev();
    }
    path->replace(newLight);
    return newLight;
  }
  else {
    path->next();
    path->getObject()->makeUnique(path, false);
    path->prev();

    return this;
  }
}

void LightSource::doComputeBounds()
{
  if (myLightRep)
    myBounds = myLightRep->getBounds();
}

bool LightSource::doIntersect(Ray3D& ray)
{
  if (myLightRep)
    return myLightRep->intersect(ray);
  else
    return false;
}

int LightSource::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  LightSourceAttr* attr = dynamic_cast(LightSourceAttr, specifier);
  if (attr != NULL) {
    // The PointLightAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

Makeable* LightSource::make(RCString& errMsg, 
			    const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, luminance);
  getParameter(2, Vector3D, color);

  if (luminance < -EPSILON) {
    errMsg = "negative luminance";
    return NULL;
  }

  LightSource* lightSource = (LightSource*)copy();
  
  lightSource->setLuminance(luminance);
  lightSource->setColor(Color(color.x(), color.y(), color.z()));

  return lightSource;
}

List<Value*>* LightSource::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  Color col = getColor();
  parameters->append(new Value(getLuminance()));
  parameters->append(new Value(Vector3D(col.getRed(), 
                                        col.getGreen(), 
                                        col.getBlue())));
  return parameters;
}

void LightSource::iterateAttributes(MakeableHandler *handler) {
  Object3D::iterateAttributes(handler);
  if (!RCString(getName()).isEmpty()) {
    RCString quoteName(RCString("\"") + getName() + RCString("\""));
    Value v(quoteName);
    DummyMakeable m("name", v);
    handler->handle(&m);
  }
  if (isOn()) {
    DummyMakeable m("on");
    handler->handle(&m);
  } 
  else {
    DummyMakeable m("off");
    handler->handle(&m);
  }
}
