/*
 * $RCSfile: RoofBorder.C,v $
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
 *  $Id: RoofBorder.C,v 1.3 1997/02/22 09:16:20 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Geometry3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/PolygonExtrude.h"
#include "booga/building/RoofBorder.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ RoofBorder

implementRTTI(RoofBorder, Roof);

RoofBorder::RoofBorder(Exemplar exemplar)
:Roof(exemplar)
{}

RoofBorder::RoofBorder()
{}

RoofBorder::RoofBorder(Real ledge, Real borderwidth, Real borderheight, Real borderdepth)
{
  setLedge(ledge);
  setBorderWidth(borderwidth);
  setBorderHeight(borderheight);
  setBorderDepth(borderdepth);
}


Object3D* RoofBorder::copy() const
{
  return new RoofBorder(*this);
}

Makeable* RoofBorder::make(RCString& errMsg, const List<Value*>* parameters) const
{
  RoofBorder* newRoof = new RoofBorder(*this);
  if ((!parameters ? 0 : parameters->count())>0) {
    checkParameterNumber(4);
    getParameter(1, Real, ledge);  
    getParameter(2, Real, borderwidth);  
    getParameter(3, Real, borderheight);  
    getParameter(4, Real, borderdepth);  
    newRoof->setLedge(ledge);
    newRoof->setBorderWidth(borderwidth);
    newRoof->setBorderHeight(borderheight);
    newRoof->setBorderDepth(borderdepth);
  }
  return newRoof;
}

Object3D* RoofBorder::doCreateSubject(Building* building) const
{
  //Grid3D* roof = new Grid3D(15,15,15);
  List3D* roof = new List3D();
  List<Vector3D> temp = computeLedge(building->getPolygon(0));
  PolygonExtrude* extrude = new PolygonExtrude(myBorderDepth,temp);
  if (extrude)
    for(long i=0;i < building->getHoles().count(); i++)
       extrude->addHole(computeLedge(building->getPolygon(i+1)));   
  roof->adoptObject(extrude);
  if (getBorderWidth() > EPSILON)
    roof->adoptObject(new PolygonExtrude(getBorderHeight(),temp, 
                                         Geometry3D::computeLayerXYPlane(-getBorderWidth(),temp)));
  roof->addTransform(TransMatrix3D::makeTranslate(0,0,building->getHeight()));
  return roof;
}

List<Value*>* RoofBorder::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getLedge()));
  parameters->append(new Value(getBorderWidth()));
  parameters->append(new Value(getBorderHeight()));
  parameters->append(new Value(getBorderDepth()));
  return parameters;
}

static const RCString roofborderKeyword("roofborder");

RCString RoofBorder::getKeyword() const {
  return roofborderKeyword;
}
