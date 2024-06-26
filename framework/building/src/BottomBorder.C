/*
 * $RCSfile: BottomBorder.C,v $
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
 *  $Id: BottomBorder.C,v 1.3 1997/02/22 09:15:47 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Geometry3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/PolygonExtrude.h"
#include "booga/building/BottomBorder.h"
#include "booga/building/BottomBorderAttr.h"
#include "booga/building/Building.h"
#include "booga/object/DummyMakeable.h"
#include "booga/object/MakeableHandler.h"

// ____________________________________________________________________ BottomBorder

implementRTTI(BottomBorder, Bottom);

BottomBorder::BottomBorder(Exemplar exemplar)
:Bottom(exemplar)
{
  myLedge = 0;
  myBorderWidth = 0;
  myBorderHeight = 0;
  myBorderDepth = 0;
  close();
}

BottomBorder::BottomBorder()
{
  myLedge = 0;
  myBorderWidth = 0;
  myBorderHeight = 0;
  myBorderDepth = 0;
  close();
}

BottomBorder::  BottomBorder(Real ledge, Real borderwidth,Real borderheight,Real borderdepth)
{
  setLedge(ledge);
  setBorderWidth(borderwidth);
  setBorderHeight(borderheight);
  setBorderDepth(borderdepth);
}

Object3D* BottomBorder::copy() const
{
  return new BottomBorder(*this);
}

int BottomBorder::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  BottomBorderAttr* attr = dynamic_cast<BottomBorderAttr*>(specifier);
  if (attr) {
    // The Cylinder3DAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Bottom::setSpecifier(errMsg, specifier);
}

List<Vector3D> BottomBorder::computeLedge(const List<Vector3D>& vertices) const
{
//  return Geometry3D::computeLayerXYPlane(myLedge, vertices);
  return Geometry3D::removeCollinearPoints(Geometry3D::computeLayerXYPlane(myLedge, vertices));
}

Makeable* BottomBorder::make(RCString& errMsg, const List<Value*>* parameters) const
{
  BottomBorder* newBottom = new BottomBorder(*this);
  if ((!parameters ? 0 : parameters->count())>0) {
    checkParameterNumber(4);
    getParameter(1, Real, ledge);  
    getParameter(2, Real, borderwidth);  
    getParameter(3, Real, borderheight);  
    getParameter(4, Real, borderdepth);  
    newBottom->setLedge(ledge);
    newBottom->setBorderWidth(borderwidth);
    newBottom->setBorderHeight(borderheight);
    newBottom->setBorderDepth(borderdepth);
  }
  return newBottom;
}

Object3D* BottomBorder::doCreateSubject(Building* building) const
{
  //Grid3D* bottom = new Grid3D(15,15,15);
  List3D* bottom = new List3D();
  List<Vector3D> temp = computeLedge(building->getPolygon(0));
  PolygonExtrude* extrude = new PolygonExtrude(myBorderDepth,temp);
  if (extrude){
    if(!isClosed()){
      extrude->addHole(building->getPolygon(0));
      if (getLedge() > EPSILON + getBorderHeight()) 
	bottom->adoptObject(extrude);
      else
	delete extrude;
    }
    else{
      for(long i=0;i < building->getHoles().count(); i++)
	extrude->addHole(computeLedge(building->getPolygon(i+1)));   
      bottom->adoptObject(extrude);
    }
  }
  if (getBorderWidth() > EPSILON)
    bottom->adoptObject(new PolygonExtrude(getBorderHeight(),temp, 
                                         Geometry3D::computeLayerXYPlane(-getBorderWidth(),temp)));
  return bottom;
}

List<Value*>* BottomBorder::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getLedge()));
  parameters->append(new Value(getBorderWidth()));
  parameters->append(new Value(getBorderHeight()));
  parameters->append(new Value(getBorderDepth()));
  return parameters;
}

static const RCString bottomborderKeyword("bottomborder");

RCString BottomBorder::getKeyword() const {
  return bottomborderKeyword;
}

void BottomBorder::iterateAttributes(MakeableHandler *handler) {
  this->Bottom::iterateAttributes(handler);
  if (!isClosed()) {
    DummyMakeable m("open");
    handler->handle(&m);
  }
}
