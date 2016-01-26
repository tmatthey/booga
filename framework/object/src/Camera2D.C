/*
 * $RCSfile: Camera2D.C,v $
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
 *  $Id: Camera2D.C,v 1.19 1997/09/19 07:13:57 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Camera2D.h"
#include "booga/object/Camera2DAttr.h"
#include "booga/object/Path2D.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

//_______________________________________________________________________ Camera2D

implementRTTI(Camera2D, Object2D);

Camera2D::Camera2D()
{
  myViewing = new Viewing2D;
  myIsOn = true;
  myBackgroundColor = Color(0,0,0);
}

Camera2D::Camera2D(Exemplar exemplar)
: Object2D(exemplar)
{
  myViewing = new Viewing2D;
  myIsOn = true;
  myBackgroundColor = Color(0,0,0);
}

Camera2D::Camera2D(const Camera2D& camera)
{
  myViewing = new Viewing2D(*(camera.myViewing));
  myIsOn = camera.myIsOn;
  myBackgroundColor = camera.myBackgroundColor;
}

Camera2D::~Camera2D()
{
  delete myViewing;
}

Object2D* Camera2D::copy() const
{
  return new Camera2D(*this);
}

long Camera2D::countSubobject() const
{
  return 0;
}

Object2D* Camera2D::getSubobject(long)
{
  Report::error("[Camera2D::getSubobject] index out of range");

  return NULL;
}
 
Object2D* Camera2D::makeUnique(Path2D* path, bool shared)
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
    Object2D* newCamera2D = copy();
    path->replace(newCamera2D);
    return newCamera2D;
  }
  else
    return this;
}

void Camera2D::doComputeBounds()
{}

bool Camera2D::doIntersect(Ray2D&)
{
  return false;
}

int Camera2D::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  Camera2DAttr* attr = dynamic_cast<Camera2DAttr*>(specifier);
  if (attr != NULL) {
    // The Camera2DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Object2D::setSpecifier(errMsg, specifier);
}

Makeable* Camera2D::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return copy();
}

static const RCString camera2DKeyword("camera");

RCString Camera2D::getKeyword() const {
  return camera2DKeyword;
}

void Camera2D::iterateAttributes(MakeableHandler *handler) {
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

  DummyMakeable window("window", Value(getViewing()->getWindowOrigin()));
  window.addParameter(Value(getViewing()->getWindowSize()));
  handler->handle(&window);

  DummyMakeable resolution("resolution", Value(getViewing()->getResolutionX()));
  resolution.addParameter(Value(getViewing()->getResolutionY()));
  handler->handle(&resolution);
}
