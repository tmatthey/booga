/*
 * $RCSfile: RoofFlat.C,v $
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
 *  $Id: RoofFlat.C,v 1.3 1997/02/22 09:16:21 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/TransMatrix3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/building/RoofFlat.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ RoofFlat

implementRTTI(RoofFlat, Roof);

RoofFlat::RoofFlat(Exemplar exemplar)
:Roof(exemplar)
{}

RoofFlat::RoofFlat()
{}

RoofFlat::RoofFlat(Real ledge)
{
  setLedge(ledge);
}


Object3D* RoofFlat::copy() const
{
  return new RoofFlat(*this);
}

Makeable* RoofFlat::make(RCString& errMsg, const List<Value*>* parameters) const
{
  RoofFlat* newRoof = new RoofFlat(*this);
  if ((!parameters ? 0 : parameters->count())>0) {
    checkParameterNumber(1);
    getParameter(1, Real, ledge);  
    newRoof->setLedge(ledge);
  }
  return newRoof;
}

Object3D* RoofFlat::doCreateSubject(Building* building) const
{
  Polygon3D* polygon = new Polygon3D(computeLedge(building->getPolygon(0)));
  if (polygon)
    for(long i=0;i < building->getHoles().count(); i++)
       polygon->addHole(computeLedge(building->getPolygon(i+1)));   
  polygon->addTransform(TransMatrix3D::makeTranslate(0,0,building->getHeight()));

  return polygon;
}

List<Value*>* RoofFlat::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  if (!equal(getLedge(),0))
    parameters->append(new Value(getLedge()));
  return parameters;
}

static const RCString roofflatKeyword("roofflat");

RCString RoofFlat::getKeyword() const {
  return roofflatKeyword;
}
