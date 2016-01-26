/*
 * $RCSfile: FaceTunnel.C,v $
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
 *  $Id: FaceTunnel.C,v 1.8 1997/04/17 14:39:55 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Geometry2D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/base/Geometry3D.h"
#include "booga/building/FaceTunnel.h"
#include "booga/building/FaceTunnelAttr.h"
#include "booga/building/FaceDummy.h"
#include "booga/building/Building.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"

static Real bezierParameter1Default = 1;
static Real bezierParameter2Default = 0.5;
static long numberOfPointsDefault = 7;
static bool wallFlagDefault = true;
static Real columnWidthDefault = 0.2;


// ____________________________________________________________________ FaceTunnel

implementRTTI(FaceTunnel, Face);

FaceTunnel::FaceTunnel()
:Face()
{
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myColumnWidth      = columnWidthDefault;
  myNumberOfPoints   = numberOfPointsDefault;
  myWallFlag         = wallFlagDefault;
  myOtherFace        = NULL;
}

FaceTunnel::FaceTunnel(const Vector2D& from,const Vector2D& to,
             const Vector2D& otherfrom,const Vector2D& otherto,
             long otherfrontindex, long otherpolygonindex)
:Face()
{
  setFrom(from);
  setTo(to);
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myColumnWidth      = columnWidthDefault;
  myNumberOfPoints   = numberOfPointsDefault;
  myWallFlag         = wallFlagDefault;
  myOtherFace        = new FaceDummy(otherfrom, otherto, otherfrontindex, otherpolygonindex);
}

FaceTunnel::FaceTunnel(Exemplar exemplar)
:Face(exemplar)
{
  myBezierParameter1 = bezierParameter1Default;
  myBezierParameter2 = bezierParameter2Default;
  myNumberOfPoints   = numberOfPointsDefault;
  myColumnWidth      = columnWidthDefault;
  myWallFlag         = wallFlagDefault;
  myOtherFace        = NULL;
}

FaceTunnel::FaceTunnel(const FaceTunnel& face) : Face(face)
{
  myColumnWidth      = face.myColumnWidth;
  myBezierParameter1 = face.myBezierParameter1;
  myBezierParameter2 = face.myBezierParameter2;
  myNumberOfPoints   = face.myNumberOfPoints;
  myWallFlag         = face.myWallFlag;
  
  if (face.myOtherFace)
    myOtherFace = dynamic_cast(FaceDummy,face.myOtherFace->copy());
  else
    myOtherFace = NULL;
}    

FaceTunnel::~FaceTunnel()
{
  delete myOtherFace;
}

Object3D* FaceTunnel::copy() const
{
  return new FaceTunnel(*this);
}

Object3D* FaceTunnel::doCreateSubject(Building* building) const
{
  Real x1 = getWidth(building);
  Real y  = building->getHeight();
  Vector2D from = myOtherFace->getFrom();
  Vector2D to   = myOtherFace->getTo();
  
  TransMatrix3D transform = getFrontTransform().getInvTransMatrix();

  List<Vector3D> side1, side2, temp;
  Real dx = getElementSize(x1,y).x();
  Real dy = getElementSize(x1,y).y();
   
  
  Vector3D a0 = getFromReal(x1,y);
  Vector3D a1 = getToFromReal(x1,y);
  Vector3D a2 = getToReal(x1,y);
  Vector3D a3 = getFromToReal(x1,y);
  Vector3D B0 = a0 + Vector3D(myColumnWidth*dx,    myBezierParameter2*dy,0);
  Vector3D B1 = a0 + Vector3D(myColumnWidth*dx,    myBezierParameter1*dy,0);
  Vector3D B2 = a0 + Vector3D((1-myColumnWidth)*dx,myBezierParameter1*dy,0);
  Vector3D B3 = a0 + Vector3D((1-myColumnWidth)*dx,myBezierParameter2*dy,0);

  Vector3D u00 = myOtherFace->getVertexStart(building);
  Vector3D u10 = myOtherFace->getVertexEnd(building);
  Vector3D u11 = myOtherFace->getVertexEnd(building) + Vector3D(0,0,y);
  Vector3D u01 = myOtherFace->getVertexStart(building) + Vector3D(0,0,y);


  Vector3D c0 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x(),from.y())* transform;
  Vector3D c1 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,to.x(),from.y()) * transform;
  Vector3D c2 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,to.x(),to.y()) * transform;
  Vector3D c3 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x(),to.y()) * transform;

  dx = to.x() - from.x();
  dy = to.y() - from.y();
  
  Vector3D D0 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x() + myColumnWidth * dx,
                                               from.y()+ myBezierParameter2*dy) * transform;
  Vector3D D1 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x() + myColumnWidth * dx,
                                               from.y()+ myBezierParameter1*dy) * transform;
  Vector3D D2 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x() + (1-myColumnWidth) * dx,
                                               from.y()+ myBezierParameter1*dy) * transform;
  Vector3D D3 = Geometry3D::bilinearInterpolation(u00,u10,u01,u11,from.x() + (1-myColumnWidth) * dx,
                                               from.y()+ myBezierParameter2*dy) * transform;

  
  // first point
  side1.append(a0);
  side2.append(c1);
  
  // the arcs
  if (myBezierParameter2 > 0){
    side1.append(Vector3D(B0.x(),a0.y(),0));
    side2.append(Vector3D(D3.x(),c0.y(),c0.z()));
  }
  
  long j;
  
  for(j=0; j<=myNumberOfPoints; j++){
    side1.append(Geometry3D::bezierPoint(B0,B1,B2,B3,(Real)j/(Real)myNumberOfPoints));
    side2.append(Geometry3D::bezierPoint(D3,D2,D1,D0,(Real)j/(Real)myNumberOfPoints));
  }
  if (myBezierParameter2 > 0){
    side1.append(Vector3D(B3.x(),a0.y(),0));
    side2.append(Vector3D(D0.x(),c0.y(),c0.z()));
  }

  // the last three points
  side1.append(a1);
  side1.append(a2);
  side1.append(a3);
  side2.append(c0);
  side2.append(c3);
  side2.append(c2);
  
  
  if (c0.z() > - EPSILON || c1.z() > - EPSILON || c0.x() < c1.x()){
    Report::recoverable("[FaceTunnel::doCreateSubject] the other face is not opposite");
    return new Polygon3D(side1);
  }
  
  //Grid3D* list = new Grid3D(15,15,15);
  List3D* list = new List3D();
  List<Front*> fronts = building->getFrontObjects(myOtherFace->getFrontIndex(),myOtherFace->getPolygonIndex());
  if (fronts.count() > 0)
    myOtherFace->setParentFront(fronts.item(0));
    
  if (isFaceInFront())
    list->adoptObject(new Polygon3D(side1));
  if (myOtherFace->isFaceInFront())
    list->adoptObject(new Polygon3D(Geometry3D::changeOrientation(side2)));
  
  // the polygons inside the tunnel
  for(j=1; j < side1.count() - 4;j++){
    temp.removeAll();
    temp.append(side1.item(j));
    temp.append(side2.item(j));
    temp.append(side2.item(j+1));
    temp.append(side1.item(j+1));
    list->adoptObject(new Polygon3D(temp));
  }
  // the floor of the tunnel
  // if (getFrom().y() > EPSILON || from.y() > EPSILON){
  if (isWall()){
    temp.removeAll();
    temp.append(side1.item(side1.count() - 4));
    temp.append(side2.item(side1.count() - 4));
    temp.append(side2.item(1));
    temp.append(side1.item(1));
    list->adoptObject(new Polygon3D(temp));
  }
  
  return list;
}

void FaceTunnel::setNumberOfPoints(long numberofpoints)
{
  myNumberOfPoints = (numberofpoints < 3) ? 3 : numberofpoints;
}

void FaceTunnel::setBezierParameter2(Real bezierparameter2)
{
  myBezierParameter2 = (bezierparameter2 > 0) ? bezierparameter2 : 0;
}

Makeable* FaceTunnel::make(RCString& errMsg, const List<Value*>* parameters) const
{
  FaceTunnel* newFaceTunnel = NULL;

  if ((parameters == NULL) || (parameters->count() != 6))
    errMsg = "Wrong number of parameters.";   
  else {
    newFaceTunnel = new FaceTunnel(*this);
    getParameter(1, Vector2D, from);   
    getParameter(2, Vector2D, to);
    getParameter(3, Vector2D, otherfrom)   
    getParameter(4, Vector2D, otherto)   
    getParameter(5, Real,     frontindex)   
    getParameter(6, Real,     polygonindex)   
    newFaceTunnel->setFrom(from);
    newFaceTunnel->setTo(to);
    newFaceTunnel->setOtherFace(new FaceDummy(otherfrom,otherto,(long)frontindex,(long)polygonindex));
  }

  return newFaceTunnel;
}

int FaceTunnel::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for FaceTunnel attributes
  FaceTunnelAttr* attr = dynamic_cast(FaceTunnelAttr, specifier);
  if (attr != NULL) {
    // The FaceTunnel object knows best which method has to be called.
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

List<Value*>* FaceTunnel::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getFrom()));
  parameters->append(new Value(getTo()));
  parameters->append(new Value(myOtherFace->getFrom()));
  parameters->append(new Value(myOtherFace->getTo()));
  parameters->append(new Value(myOtherFace->getFrontIndex()));
  parameters->append(new Value(myOtherFace->getPolygonIndex()));
  return parameters;
}

void FaceTunnel::iterateAttributes(MakeableHandler *handler) {
  this->Face::iterateAttributes(handler);
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

static const RCString facetunnelKeyword("facetunnel");

RCString FaceTunnel::getKeyword() const {
  return facetunnelKeyword;
}

void FaceTunnel::getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const
{
  if (isOn() && myOtherFace && 
      myOtherFace->getFrontIndex() == frontindex && 
      myOtherFace->getPolygonIndex() == polygonindex){

    // compute alternative holes for the indirect face
    // just in case
    // the coords are defined locale in the front [0,0]-[1,1]
    List<List<Vector2D> > holes;
    List<Vector2D> temp;
  
    Real dx = myOtherFace->getElementSize(1,1).x();
    Real dy = myOtherFace->getElementSize(1,1).y();
    Vector2D a0 = myOtherFace->getFrom();
    Vector2D B0 = a0 + Vector2D(myColumnWidth*dx,    myBezierParameter2*dy);
    Vector2D B1 = a0 + Vector2D(myColumnWidth*dx,    myBezierParameter1*dy);
    Vector2D B2 = a0 + Vector2D((1-myColumnWidth)*dx,myBezierParameter1*dy);
    Vector2D B3 = a0 + Vector2D((1-myColumnWidth)*dx,myBezierParameter2*dy);

    if (myBezierParameter2 > 0){
      temp.append(Vector2D(B3.x(),a0.y()));
      temp.append(Vector2D(B0.x(),a0.y()));
    }

    // the arc
    for(long j=0; j<=myNumberOfPoints; j++)
      temp.append(Geometry2D::bezierPoint(B0,B1,B2,B3,(Real)j/(Real)myNumberOfPoints));

    holes.append(temp);
    myOtherFace->setAlternativeHoles(holes);                 
    facelist->append(myOtherFace);
  }
}

List<List<Vector3D> > FaceTunnel::getAlternativeHoles(Building* building) const
{
  List<List<Vector3D> > holes;
  List<Vector3D> temp;
  
  Real x = getWidth(building);
  Real y = building->getHeight();
  Real dx = getElementSize(x,y).x();
  Real dy = getElementSize(x,y).y();
  
  Vector3D a0 = getFromReal(x,y);
  Vector3D B0 = a0 + Vector3D(myColumnWidth*dx,    myBezierParameter2*dy,0);
  Vector3D B1 = a0 + Vector3D(myColumnWidth*dx,    myBezierParameter1*dy,0);
  Vector3D B2 = a0 + Vector3D((1-myColumnWidth)*dx,myBezierParameter1*dy,0);
  Vector3D B3 = a0 + Vector3D((1-myColumnWidth)*dx,myBezierParameter2*dy,0);

  if (myBezierParameter2 > 0){
    temp.append(Vector3D(B3.x(),a0.y(),0));
    temp.append(Vector3D(B0.x(),a0.y(),0));
  }

  // the arc
  for(long j=0; j<=myNumberOfPoints; j++)
    temp.append(Geometry3D::bezierPoint(B0,B1,B2,B3,(Real)j/(Real)myNumberOfPoints));
  holes.append(temp);
  return holes;
}
