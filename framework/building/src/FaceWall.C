/*
 * $RCSfile: FaceWall.C,v $
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: FaceWall.C,v 1.2 1997/02/06 14:13:47 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"
#include "booga/object/Polygon3D.h"
#include "booga/building/FaceWall.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

// ____________________________________________________________________ FaceWall

implementRTTI(FaceWall, Face);

FaceWall::FaceWall()
:Face()
{}

FaceWall::FaceWall(const Vector2D& from,const Vector2D& to)
:Face()
{
  setFrom(from);
  setTo(to);
}

FaceWall::FaceWall(Exemplar exemplar)
:Face(exemplar)
{}

Object3D* FaceWall::copy() const
{
  return new FaceWall(*this);
}

Object3D* FaceWall::doCreateSubject(Building* building) const
{
  List<Vector3D> vertices(4); 
  Real x = getWidth(building);
  Real y = building->getHeight();
  
  vertices.append(getFromReal(x,y));
  vertices.append(getToFromReal(x,y));
  vertices.append(getToReal(x,y));
  vertices.append(getFromToReal(x,y));

  return new Polygon3D(vertices);
}

Makeable* FaceWall::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FaceWall* newFaceWall = NULL;

  if ((parameters == NULL) || (parameters->count() != 2))
    errMsg = "Wrong number of parameters.";   
  else {
    newFaceWall = new FaceWall(*this);
    getParameter(1, Vector2D, from);   
    getParameter(2, Vector2D, to);
    newFaceWall->setFrom(from);
    newFaceWall->setTo(to);
  }

  return newFaceWall;
}

List<Value*>* FaceWall::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  return parameters;
}

static const RCString facewallKeyword("facewall");

RCString FaceWall::getKeyword() const {
  return facewallKeyword;
}
