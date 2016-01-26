/*
 * $RCSfile: Roof.C,v $
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
 *  $Id: Roof.C,v 1.3 1997/02/20 09:40:07 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Geometry3D.h"
#include "booga/building/Roof.h"
#include "booga/building/RoofAttr.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

// ____________________________________________________________________ Roof

implementRTTI(Roof, BuildingObject);

Roof::Roof(Exemplar exemplar)
:BuildingObject(exemplar)
{
  myLedge = 0;
  myHeight = 0;
  myLedgeFlag = true;
} 

Roof::Roof()
{
  myLedge = 0;
  myHeight = 0;
  myLedgeFlag = true;
}

Roof::Roof(const Roof& roof) : BuildingObject(roof)
{
  myLedge     = roof.myLedge;
  myHeight    = roof.myHeight;
  myLedgeFlag = roof.myLedgeFlag;
}      

Object3D* Roof::createSubject(Building* building) const
{
  if (building->getHeight() < EPSILON || ! isOn())
    return new NullObject3D();

  Roof* This = (Roof*)this;
  This->setTransform(TransMatrix3D::makeTranslate(0,0,getHeight()));
  return doCreateSubject(building);
}

List<Vector3D> Roof::computeLedge(const List<Vector3D>& vertices) const
{
//  return Geometry3D::computeLayerXYPlane(myLedge, vertices);
  return Geometry3D::removeCollinearPoints(Geometry3D::computeLayerXYPlane(myLedge, vertices));
}

int Roof::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Roof attributes
  RoofAttr* attr = dynamic_cast<RoofAttr*>(specifier);
  if (attr != NULL) {
    // The Roof object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return BuildingObject::setSpecifier(errMsg, specifier);
}

void Roof::iterateAttributes(MakeableHandler *handler) {
  this->BuildingObject::iterateAttributes(handler);
  if (!equal(myHeight,0)) {
    DummyMakeable height("height");
    height.addParameter(Value(myHeight));
    handler->handle(&height);
  }
  if (!isLedge()) {
    DummyMakeable ledge("ledgeoff");
    handler->handle(&ledge);
  }
}
