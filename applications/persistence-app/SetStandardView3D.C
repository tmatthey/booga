/*
 * $RCSfile: SetStandardView3D.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: SetStandardView3D.C,v 1.2 1996/12/06 16:47:07 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/Report.h"
#include "booga/object/Camera3D.h"
#include "booga/object/LightSource.h"
#include "booga/object/PointLight.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/component/Collector3DFor.h"
#include "SetStandardView3D.h"

//_____________________________________________________________________ SetStandardView3D

implementRTTI(SetStandardView3D, Operation3D);

SetStandardView3D::SetStandardView3D(Viewing3D::ViewPlane viewplane) :
myResX(100),
myResY(100),
myHFov(dtor(45.)),
myViewPlane(viewplane)
{
}

SetStandardView3D::~SetStandardView3D()
{
}

bool SetStandardView3D::doExecute()
{
  //
  // turn existing cameras off.
  //
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(getWorld());
  
  //
  // Remove previous standard cameras and turn other cameras off
  //
  for (camCollector.first(); !camCollector.isDone(); camCollector.next()) {
    if (camCollector.getObject()->getName() == "StandardCamera") {
      Camera3D* camera = camCollector.getObject();
      getWorld()->getObjects()->orphanObject(camera);
      delete camera;
    }
    else {
      camCollector.getObject()->turnOff();
    }
  }

  Collector3DFor<LightSource> lightCollector;
  lightCollector.execute(getWorld());
  for (lightCollector.first(); !lightCollector.isDone(); lightCollector.next()) {
    if (lightCollector.getObject()->getName() == "StandardLight") {
      LightSource* light = lightCollector.getObject();
      getWorld()->getObjects()->orphanObject(light);
      delete light;
    } 
    else {
      camCollector.getObject()->turnOff();
    }
  }

  getWorld()->getObjects()->computeBounds();
  BoundingBox bb(getWorld()->getObjects()->getBounds());

  if (bb.isEmpty()) {
    Report::warning("[SetStandardView3D::doExecute] scene is empty");
    return false;
  }

  Camera3D* camera = new Camera3D();
  camera->getViewing()->setHFov(myHFov);
  camera->getViewing()->setResolution(myResX, myResY);
  camera->setBackground(Color (1., 1., 1.));
  camera->setName("StandardCamera");
  camera->getViewing()->setView(bb.getMin(), bb.getMax(),
                                  1.1, myViewPlane);
  getWorld()->getObjects()->adoptObject(camera);

  //
  // Set up two light sources
  //
  Vector3D lookdir = camera->getViewing()->getLookat() - camera->getViewing()->getEye();
  Real len = lookdir.length();
  Vector3D up = camera->getViewing()->getUp();
  up = up.normalized();
  Vector3D sidedir = (up*lookdir).normalized();
  Vector3D pos1 = camera->getViewing()->getEye() + up * (len*0.5) + sidedir * len;
  Vector3D pos2 = camera->getViewing()->getEye() + up * (len*0.5) - sidedir * len;
 
  PointLight* light1 = new PointLight(1.0, Color (.8,.8,.8));
  light1->setPosition(pos1);
  light1->setName("StandardLight");
  getWorld()->getObjects()->adoptObject(light1);

  PointLight* light2 = new PointLight(1.0, Color (.6,.6,.6));
  light2->setPosition(pos2);
  light2->setName("StandardLight");
  getWorld()->getObjects()->adoptObject(light2);
 
  return true;
}

void SetStandardView3D::setHFov(double hfov) {
  myHFov = hfov;
}

void SetStandardView3D::setViewPlane(Viewing3D::ViewPlane viewplane) {
  myViewPlane = viewplane;
}

void SetStandardView3D::setResolution(int resX, int resY) {
  myResX = resX;
  myResY = resY;
}
 
