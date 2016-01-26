/*
 * $RCSfile: Camera3D.C,v $
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
 *  $Id: Camera3D.C,v 1.21 1997/09/19 07:13:59 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Camera3D.h"
#include "booga/object/Camera3DAttr.h"
#include "booga/object/Path3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/PerspectiveViewing3D.h"
#include "booga/object/Viewing3DAttr.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_______________________________________________________________________ Camera3D

implementRTTI(Camera3D, Object3D);

Camera3D::Camera3D()
{
  myViewing = new PerspectiveViewing3D;
  myIsOn = true;
  myBackgroundColor = Color(0,0,0);
}

Camera3D::Camera3D(Exemplar exemplar)
: Object3D(exemplar)
{
  myViewing = new PerspectiveViewing3D;
  myIsOn = true;
  myBackgroundColor = Color(0,0,0);
}

Camera3D::Camera3D(const Camera3D& camera)
: Object3D(camera) 
{
  myViewing = camera.myViewing->copy();
  myIsOn = camera.myIsOn;
  myBackgroundColor = camera.myBackgroundColor;
}

Camera3D::~Camera3D()
{
  delete myViewing;
}

void Camera3D::adoptViewing(Viewing3D* viewing)
{
  //
  // Self assignment?
  //
  if (myViewing == viewing)
    return;

  delete myViewing;
  myViewing = viewing;
}

Object3D* Camera3D::copy() const
{
  return new Camera3D(*this);
}

long Camera3D::countSubobject() const
{
  return 0;
}

Object3D* Camera3D::getSubobject(long)
{
  Report::error("[Camera3D::getSubobject] index out of range");

  return NULL;
}
 
Object3D* Camera3D::makeUnique(Path3D* path, bool shared)
{
  // If we are at the end of the path or path == NULL, don't do anything.
  //
  if (path == NULL || path->isDone())
    return this;

  //
  // If a predecessor is shared more than once, we have to provide a copy
  // of ourself.
  //
  if (shared == true) {
    Object3D* newCamera3D = copy();
    path->replace(newCamera3D);
    return newCamera3D;
  }
  else
    return this;
}

void Camera3D::doComputeBounds()
{
}

bool Camera3D::doIntersect(Ray3D&)
{
  return false;
}

int Camera3D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Camera3D attributes
  Camera3DAttr* attr = dynamic_cast<Camera3DAttr*>(specifier);
  if (attr != NULL) {
    // The Camera3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // Check for Viewing3D
  Viewing3D* viewing = dynamic_cast<Viewing3D*>(specifier);
  if (viewing != NULL) {
    if (myViewing != NULL)
      delete myViewing;
      
    myViewing = viewing;
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

Makeable* Camera3D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

static const RCString camera3DKeyword("camera");

RCString Camera3D::getKeyword() const {
  return camera3DKeyword;
}

void Camera3D::iterateAttributes(MakeableHandler *handler) {
  //
  // add Makeable name "cameraName" (if not empty)
  // 
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
  DummyMakeable m("background", Value(getBackground()));
  handler->handle(&m);
  handler->handle(getViewing());
}
