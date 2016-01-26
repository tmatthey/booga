/*
 * $RCSfile: FaceArbour.C,v $
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
 *  $Id: FaceArbour.C,v 1.3 1997/02/22 09:16:13 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/PolygonExtrude.h"
#include "booga/building/FaceArbour.h"
#include "booga/building/FaceArbourAttr.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

static Real arbourDepthDefault = 5;
static Real bezierParameter1Default = 1;
static Real bezierParameter2Default = 0.5;
static Real columnDepthDefault = 0.1;
static Real columnWidthDefault = 0.2;
static long numberOfPointsDefault = 7;
static bool wallFlagDefault = true;


// ____________________________________________________________________ FaceArbour

implementRTTI(FaceArbour, Face);

FaceArbour::FaceArbour()
{
  myArbourDepth      = arbourDepthDefault;
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myColumnDepth      = columnDepthDefault;
  myColumnWidth      = columnWidthDefault;
  myNumberOfPoints   = numberOfPointsDefault;
  myWallFlag         = wallFlagDefault;
}

FaceArbour::FaceArbour(const Vector2D& from,const Vector2D& to, long column, Real arbourdepth)
{
  setFrom(from);
  setTo(to);
  setColumn(column);
  myArbourDepth      = arbourdepth;
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myColumnDepth      = columnDepthDefault;
  myColumnWidth      = columnWidthDefault;
  myNumberOfPoints   = numberOfPointsDefault;
  myWallFlag         = wallFlagDefault;
}

FaceArbour::FaceArbour(Exemplar exemplar)
:Face(exemplar)
{
  myArbourDepth      = arbourDepthDefault;
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myColumnDepth      = columnDepthDefault;
  myColumnWidth      = columnWidthDefault;
  myNumberOfPoints   = numberOfPointsDefault;
  myWallFlag         = wallFlagDefault;
}

Object3D* FaceArbour::copy() const
{
  return new FaceArbour(*this);
}

Object3D* FaceArbour::doCreateSubject(Building* building) const
{
  Real x = getWidth(building);
  Real y = building->getHeight();
  
  if ((myArbourDepth <= EPSILON) || (getColumn() <1))
    return new NullObject3D();

  List<Vector3D> vertices;
  //Grid3D* list = new Grid3D(15,15,15);
  List3D* list = new List3D();
  
  Real xElement = getElementSize(x,y).x();
  Real yElement = getElementSize(x,y).y();
  
  Vector3D c0 = getFromReal(x,y)   + Vector3D(0,0,-myColumnDepth*myArbourDepth);
  Vector3D c1 = getToFromReal(x,y) + Vector3D(0,0,-myColumnDepth*myArbourDepth);
  Vector3D c2 = getToReal(x,y)     + Vector3D(0,0,-myColumnDepth*myArbourDepth);
  Vector3D c3 = getFromToReal(x,y) + Vector3D(0,0,-myColumnDepth*myArbourDepth);
  Vector3D B0,B1,B2,B3,cdelta1,cdelta2;

  // first point
  vertices.append(c0);
  
  // the arcs
  for(long i=0;i<getColumn();i++){
    if (myBezierParameter2 > 0)
      vertices.append(c0 + Vector3D(i*xElement + myColumnWidth*xElement,0,0));
    cdelta1 = Vector3D(i      *xElement + myColumnWidth*xElement,0,0);
    cdelta2 = Vector3D((i + 1)*xElement - myColumnWidth*xElement,0,0);
    B0 = c0 + cdelta1 + Vector3D(0,myBezierParameter2*yElement,0);
    B1 = c0 + cdelta1 + Vector3D(0,myBezierParameter1*yElement,0);
    B2 = c0 + cdelta2 + Vector3D(0,myBezierParameter1*yElement,0);
    B3 = c0 + cdelta2 + Vector3D(0,myBezierParameter2*yElement,0);
    for(long j=0; j<=myNumberOfPoints; j++){
      vertices.append(Geometry3D::bezierPoint(B0,B1,B2,B3,(Real)j/(Real)myNumberOfPoints));
    }
    if (myBezierParameter2 > 0)
      vertices.append(c0 + Vector3D((i + 1)*xElement - myColumnWidth*xElement,0,0));
  }
  // the last three points
  vertices.append(c1);
  vertices.append(c2);
  vertices.append(c3);
  
  list->adoptObject(new PolygonExtrude(myColumnDepth*myArbourDepth, vertices));
  
  
  if (isWall()) {
    // top
    vertices.removeAll();
    vertices.append(getFromReal(x,y)   + Vector3D(0,0,-myArbourDepth + 0));
    vertices.append(getToFromReal(x,y) + Vector3D(0,0,-myArbourDepth + 0));
    vertices.append(getToReal(x,y)     + Vector3D(0,0,-myArbourDepth + 0));
    vertices.append(getFromToReal(x,y) + Vector3D(0,0,-myArbourDepth + 0));
    list->adoptObject(new Polygon3D(vertices));

    // back 
    vertices.removeAll();
    vertices.append(getToReal(x,y)     + Vector3D(0,0,-myArbourDepth + 0));
    vertices.append(getFromToReal(x,y) + Vector3D(0,0,-myArbourDepth + 0));
    vertices.append(getFromToReal(x,y)  );
    vertices.append(getToReal(x,y)      );
    list->adoptObject(new Polygon3D(vertices));
  }

  return list;
}

void FaceArbour::setNumberOfPoints(long numberofpoints)
{
  myNumberOfPoints = (numberofpoints < 3) ? 3 : numberofpoints;
}

void FaceArbour::setBezierParameter2(Real bezierparameter2)
{
  myBezierParameter2 = (bezierparameter2 > 0) ? bezierparameter2 : 0;
}

int FaceArbour::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for FaceArbour attributes
  FaceArbourAttr* attr = dynamic_cast<FaceArbourAttr*>(specifier);
  if (attr != NULL) {
    // The FaceArbour object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  // 
  // Let papa do the rest ...
  //
  return Face::setSpecifier(errMsg, specifier);
}

Makeable* FaceArbour::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FaceArbour* newFaceArbour = NULL;

  if ((parameters == NULL) || (parameters->count() != 3))
    errMsg = "Wrong number of parameters.";   
  else {
    newFaceArbour = new FaceArbour(*this);
    getParameter(1, Vector2D, from);   
    getParameter(2, Vector2D, to);
    getParameter(3, Real    , column)   
    newFaceArbour->setFrom(from);
    newFaceArbour->setTo(to);
    newFaceArbour->setColumn((long)column);
  }

  return newFaceArbour;
}

List<Value*>* FaceArbour::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  parameters->append(new Value(getColumn()));
  return parameters;
}

void FaceArbour::iterateAttributes(MakeableHandler *handler) {
  this->Face::iterateAttributes(handler);
  if (!equal(myArbourDepth , arbourDepthDefault)) {
    DummyMakeable arbourdepth("arbourdepth");  
    arbourdepth.addParameter(Value(myArbourDepth));
    handler->handle(&arbourdepth);
  }

  if (!equal(myBezierParameter1 , bezierParameter1Default)) {
    DummyMakeable bezierparm1("bezierparm1");  
    bezierparm1.addParameter(Value(myBezierParameter1));
    handler->handle(&bezierparm1);
  }
  if (!equal(myBezierParameter2 , bezierParameter2Default)) {
    DummyMakeable bezierparm2("bezierparm2");  
    bezierparm2.addParameter(Value(myBezierParameter2));
    handler->handle(&bezierparm2);
  }
  if (!equal(myColumnDepth , columnDepthDefault)) {
    DummyMakeable columndepth("columndepth");  
    columndepth.addParameter(Value(myColumnDepth));
    handler->handle(&columndepth);
  }
  if (!equal(myColumnWidth , columnWidthDefault)) {
    DummyMakeable columnwidth("columnwidth");  
    columnwidth.addParameter(Value(myColumnWidth));
    handler->handle(&columnwidth);
  }
  if (myNumberOfPoints != numberOfPointsDefault) {
    DummyMakeable numberofpoints("numberofpoints");  
    numberofpoints.addParameter(Value(myNumberOfPoints));
    handler->handle(&numberofpoints);
  }
  if (myWallFlag != wallFlagDefault) {
    DummyMakeable nowall("walloff");  
    handler->handle(&nowall);
  }
}

static const RCString facearbourKeyword("facearbour");

RCString FaceArbour::getKeyword() const {
  return facearbourKeyword;
}
