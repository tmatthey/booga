/*
 * $RCSfile: Building.C,v $
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
 *  $Id: Building.C,v 1.8 1997/04/24 11:37:25 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Value.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/MakeableHandler.h"
#include "booga/object/DummyMakeable.h"
#include "booga/building/Building.h"
#include "booga/building/BuildingAttr.h"
#include "booga/building/BuildingObject.h"
#include "booga/building/Front.h"
#include "booga/building/FrontRect.h"
#include "booga/building/FrontTriangle.h"
#include "booga/building/Roof.h"

// ____________________________________________________________________ Building

implementRTTI(Building, Object3D);

Building::Building(Exemplar exemplar)
: Object3D(exemplar)
{
  mySubject = NULL;
  myHeight  = 0;
  myIsOn    = true;
  
  for (long i = 0; i < myObjectList.count(); i++)
    delete myObjectList.item(i);
  myObjectList.removeAll();
}

Building::Building(Real height, const List<Vector3D>& vertices)
: myVertices(vertices)
{
  mySubject = NULL;
  myHeight  = height;
  myIsOn    = true;
  
  for (long i = 0; i < myObjectList.count(); i++)
    delete myObjectList.item(i);
  myObjectList.removeAll();
}

Building::Building(const Building& building)
: Object3D(building), myVertices(building.myVertices),myHoles(building.myHoles)
{
  myHeight = building.myHeight;
  myIsOn   = building.myIsOn;
  
  if (building.mySubject != NULL)
    mySubject = building.mySubject->copy();
  else
    mySubject = NULL;

  for (long i=0; i<building.myObjectList.count(); i++)
    this->adoptObject(building.myObjectList.item(i)->copy());
}
 
Building::~Building()
{
  for (long i = 0; i < myObjectList.count(); i++)
    delete myObjectList.item(i);
  myObjectList.removeAll();
 
  delete mySubject;
}

void Building::adoptObject(Object3D* object)
{
  BuildingObject* buildingobject = dynamic_cast(BuildingObject,object);
  if (buildingobject){
    // do NOT compute the bounds here, because you could miss attributes
    buildingobject->setParentBuilding(this);    // the parent building
    buildingobject->subjectChanged();           // delete cache
    myObjectList.append(buildingobject);
  }
  else
    myObjectList.append(object);          // something else likes to join 
}

Object3D* Building::orphanObject(long index)
{
  if ((index < 0) || (index >= myObjectList.count())){
    Report::warning("[Building::removeObject] index out of range");
    return NULL;
  }
  
  Object3D* tmp = myObjectList.item(index);
  myObjectList.remove(index);
  return tmp;
}

void Building::addVertex(const Vector3D& vertex)
{
  long count = myVertices.count();

  //
  // Check for vaild vertex.
  //
  if (count > 0) {
    if (myVertices.item(count-1) == vertex) {
      ostrstream os;
      os << "[Building::addVertex] two consecutive vertices ("
         << vertex << ") must not have the same value";
      Report::recoverable(os);
      return;
    }
    if (fabs(myVertices.item(0).z()-vertex.z()) > EPSILON) {
      ostrstream os;
      os << "[Building::addVertex] the ("
         << vertex << ") has not the same z-value";
      Report::recoverable(os);
      return;
    }
  }

  if (mySubject != NULL) {
    delete mySubject;
    mySubject = NULL;
  }
  
  myVertices.append(vertex);
}

void Building::addHole(const List<Vector3D>& hole) 
{
  if (hole.count()>2){
    for(long i=1; i<hole.count();i++)
      if (!equal(hole.item(0).z() - hole.item(i).z(),0)){
        ostrstream os;
        os << "[Building::addHole] the hole "
           << i << ") has not the same z-value";
        Report::recoverable(os);
        return;
      }
      
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
//    List<Vector3D> temp = Geometry3D::removeCollinearPoints(hole);
//    if (Geometry3D::normal(temp).z() >= 0){
//      Report::hint("[Building::addHole] orientation of a hole has been corrected");
//      temp = Geometry3D::changeOrientation(temp);
//    }
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    myHoles.append(hole);
  }
  else {
    ostrstream os;
    os << "[Building::addHole] hole has less then 3 vertices ";
    Report::recoverable(os);
    return;
  }
}

List<Vector3D> Building::getPolygon(long index) const
{
  if ((myHoles.count() < index) || (index < 0))
    return List<Vector3D> (0);
  else
    if (index == 0)
      return myVertices;
    else
      return myHoles.item(index-1);
}

List<Vector3D> Building::getPolygonTop(long index) const
{
  List<Vector3D> polygon;
  List<Vector2D> temp;
  Front* front = NULL;
  Vector3D u;
  long j;
      
  List<Vector3D> base = getPolygon(index);
  
  for(long i=0; i < base.count();i ++){
    u = base.item((i+1)%base.count()) - base.item(i);
    polygon.append(base.item(i)+Vector3D(0,0,getHeight()));

    // search first for a FrontTriangle and then for a FrontRect
    front = NULL;
    for(j=0; j < myObjectList.count();j++){
      front = dynamic_cast(FrontTriangle,myObjectList.item(j));
      if (front && front->getPolygonIndex() == index && front->getFrontIndex() == i) 
        break;
      else
        front = NULL;
    }

    for(j=0; j < myObjectList.count() && front == NULL;j++){
      front = dynamic_cast(FrontRect,myObjectList.item(j));
      if (front && front->getPolygonIndex() == index && front->getFrontIndex() == i) 
        break;
      else
        front = NULL;
    }

    if (front) {
      temp = front->getPointsTop();
      for(long k=0; k<temp.count(); k++)
        polygon.append(base.item(i) + Vector3D(u.x() * temp.item(k).x(),
                                                 u.y() * temp.item(k).x(),
                                        getHeight() * temp.item(k).y()));
      
    }
  }
  
  return Geometry3D::removeCollinearPoints(polygon);
}

List<Vector3D> Building::getPolygonBottom(long index) const
{
  List<Vector3D> polygon;
  List<Vector2D> temp;
  Front* front = NULL;
  Vector3D u;
  long j;
      
  List<Vector3D> base = getPolygon(index);
  
  for(long i=0; i < base.count();i ++){
    u = base.item((i+1)%base.count()) - base.item(i);
    polygon.append(base.item(i));

    // search first for a FrontTriangle and then for a FrontRect
    front = NULL;
    for(j=0; j < myObjectList.count();j++){
      front = dynamic_cast(FrontTriangle,myObjectList.item(j));
      if (front && front->getPolygonIndex() == index && front->getFrontIndex() == i) 
        break;
      else
        front = NULL;
    }

    for(j=0; j < myObjectList.count() && front == NULL;j++){
      front = dynamic_cast(FrontRect,myObjectList.item(j));
      if (front && front->getPolygonIndex() == index && front->getFrontIndex() == i) 
        break;
      else
        front = NULL;
    }

    if (front) {
      temp = front->getPointsBottom();
      for(long k=0; k<temp.count(); k++)
        polygon.append(base.item(i) + Vector3D(u.x() * temp.item(k).x(),
                                                 u.y() * temp.item(k).x(),
                                        getHeight() * temp.item(k).y()));
      
    }
  }
    
  return Geometry3D::removeCollinearPoints(polygon);
}

List<Vector3D> Building::getFrontPolygon(long polygonindex, long frontindex) const
{
  List<Vector3D> polygon;
  List<Vector2D> temp;
  Front* front = NULL;
  
  long j,k;
      
  List<Vector3D> base = getPolygon(polygonindex);
  
  if (frontindex >= base.count())
    return polygon;
  
  Vector3D v0 = base.item(frontindex);
  Vector3D v1 = base.item((frontindex+1)%base.count());
  Vector3D u  = v1 - v0;

  // search first for a FrontTriangle and then for a FrontRect
  for(j=0; j < myObjectList.count();j++){
    front = dynamic_cast(FrontTriangle,myObjectList.item(j));
    if (front != NULL && front->getPolygonIndex() == polygonindex && front->getFrontIndex() == frontindex) 
      break;
    else
      front = NULL;
  }

  for(j=0; j < myObjectList.count() && front == NULL;j++){
    front = dynamic_cast(FrontRect,myObjectList.item(j));
    if (front != NULL && front->getPolygonIndex() == polygonindex && front->getFrontIndex() == frontindex) 
      break;
    else
      front = NULL;
  }

  if (front) {
    temp = front->getFrontPolygon();
    for(k=0; k<temp.count(); k++)
      polygon.append(v0 + Vector3D(u.x() * temp.item(k).x(),
                                             u.y() * temp.item(k).x(),
                                        getHeight() * temp.item(k).y()));
      
  }
  else {
    polygon.append(v0);
    polygon.append(v1);
    polygon.append(v1 + Vector3D(0,0,getHeight()));
    polygon.append(v0 + Vector3D(0,0,getHeight()));
  }

  return Geometry3D::removeCollinearPoints(polygon);  
}
 
Object3D* Building::getSubobject(long index)
{
  Object3D* retval = NULL;
  if (index < 0 || index > myObjectList.count() || (!isOn() && index > 0)) {
    ostrstream os;
    os << "[Building::getSubobject] index out of range ";
    os << "(was " << index << ")";
    Report::error(os);
  }
  else if (index == 0)
    retval = getSubject();
  else     
    retval = myObjectList.item(index-1);
  
  return retval;
}

Object3D* Building::getSubject() const
{
  if (mySubject == NULL) {
    // Cache does not affect logical constness
    Building* This = (Building*)this;
    This->mySubject = createSubject();
  } 
  return mySubject;
}

long Building::countSubobject() const
{
  if (isOn())
    return 1 + myObjectList.count();   
  else
    return 1;
}

Object3D* Building::createSubject() const
{
  if (!isOn())
    return new NullObject3D();
    
  Front* front = NULL;

  checkBuilding();
  
  for(long i=0; i<myObjectList.count(); i++){
    front = dynamic_cast(Front,myObjectList.item(i));
    if (front && front->numberOfFaces() > 0)
      return new NullObject3D();
  }
  
  return dummyBuilding();
}

Object3D* Building::dummyBuilding() const
{
  //
  //  Generate default if no faces found
  //
  //Grid3D* decomposition = new Grid3D(15,15,15);
  List3D* decomposition = new List3D();
   
  List<Vector3D> polygon;
  long count;
  
  for (long i=0; i<countPolygon(); i++){
    count = getPolygon(i).count();
    for(long j=0; j<count; j++){
      polygon = getFrontPolygon(i,j);
      if (polygon.count() > 2)
        decomposition->adoptObject(new Polygon3D(polygon));     
    }      
  }

  decomposition->computeBounds();

  return decomposition;  
}

Object3D* Building::copy() const
{
  return new Building(*this);
}
 
void Building::doComputeBounds()
{
  for(long i=0;i<countSubobject();i++)
    myBounds.expand(getSubobject(i)->getBounds());
}
  
Makeable* Building::make(RCString& errMsg, const List<Value*>* parameters) const
{
  Building* newBuilding = new Building(*this);

  getParameter(1, Real, height);
  newBuilding->setHeight(height);
  newBuilding->removeVertices();

  for (int i=2; i<=parameters->count(); i++) {
    getParameter(i, Vector3D, vertex);
    newBuilding->addVertex(vertex);
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!
//  newBuilding->setVertices(Geometry3D::removeCollinearPoints(newBuilding->getVertices()));
//  if (Geometry3D::normal(newBuilding->getVertices()).z() <= 0){
//    Report::hint("[Building::make] orientation of the building has been corrected");
//    newBuilding->setVertices(Geometry3D::changeOrientation(newBuilding->getVertices()));
//  }
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!
      
  return newBuilding;
}

int Building::setSpecifier(RCString& errMsg, Makeable* specifier)
{
  // Check for Building attributes
  BuildingAttr* attr = dynamic_cast(BuildingAttr, specifier);
  if (attr != NULL) {
    // The Building object knows best which method has to be called.
    // So let the object do the job.

    attr->setAttribute(this);
     
    delete attr;
    return 1;  
  }

  // Adopt an Object to the building
   
  Object3D* object = dynamic_cast(Object3D, specifier);
  if (object != NULL) {
    adoptObject(object);
    return 1;
  }

  // 
  // Let papa do the rest ...
  //
  return Object3D::setSpecifier(errMsg, specifier);
}

static const RCString buildingKeyword("building");

RCString Building::getKeyword() const 
{
  return buildingKeyword;
}

void Building::iterateAttributes(MakeableHandler *handler)
{
  this->Object3D::iterateAttributes(handler);
  
  // do not take the first subobject - it's the dummy building
  long i,j;
  for(i=1; i<countSubobject(); i++) {
    handler->handle(getSubobject(i));
  }
  
  for (i=0; i<myHoles.count(); i++) {
    DummyMakeable hole("hole");
    for (j=0; j<myHoles.item(i).count(); j++) {
      hole.addParameter(Value(myHoles.item(i).item(j)));
    }
    handler->handle(&hole);
  }
  
  if (!isOn()) {
    DummyMakeable m("off");
    handler->handle(&m);
  } 
}

List<Value*>* Building::createParameters()
{
  List<Value*>* parameters = new List<Value*>;
  parameters->append(new Value(getHeight()));
  for(long i=0;i<myVertices.count();i++)
    parameters->append(new Value(myVertices.item(i)));
  return parameters;
}

void Building::checkBuilding() const
{
  long i;
  
  if (myVertices.count() < 3)
    Report::warning("[Building::checkBuilding] degenerate building");
   
  if (myHeight <= EPSILON)
    Report::warning("[Building::checkBuilding] height is not positive");
  
  if (Geometry3D::normal(myVertices).z() <= 0)
    Report::warning("[Building::checkBuilding] orientation of the building is not positive");

  for(i=0;i < myHoles.count();i++){
    if (Geometry3D::normal(myHoles.item(i)).z() >= 0) {
      Report::warning("[Building::checkBuilding] orientation of a hole is not negative");
      break;
    }
    if (fabs(myVertices.item(0).z() - myHoles.item(i).item(0).z()) > EPSILON){
      Report::warning("[Building::checkBuilding] hole is not in the same plane as the buildings vertices");
      break;
    }
  }

  for(i=0; i<myObjectList.count(); i++){
    if (dynamic_cast(BuildingObject,myObjectList.item(i)) == NULL)
      Report::hint("[Building::checkBuilding] building has a non-BuildingObject");
    if (dynamic_cast(Face,myObjectList.item(i)))
      Report::warning("[Building::checkBuilding] building has a face which is not collected by a front");
  }

}

bool Building::doIntersect(Ray3D& ray)
{
  if (!isOn())
    return false;
    
  bool hit = false;
  for(long i=0; i<countSubobject(); i++)
    if (getSubobject(i)->intersect(ray))
      hit = true;
  
  return hit;
}

Object3D* Building::makeUnique(Path3D*, bool)
{
  return NULL;
}

void Building::subjectChanged() const
{
  if (mySubject != NULL) {
    // Cache does not affect logical constness
    Building* This = (Building*)this;
    delete This->mySubject;
    This->mySubject = NULL;
  } 
  
  for(long i=0; i<myObjectList.count();i++){
    BuildingObject* object = dynamic_cast(BuildingObject,myObjectList.item(i));
    if (object)
      object->subjectChanged();
  }
}

void Building::getIndirectFaceObjects(long frontindex, long polygonindex, List<Face*>* facelist) const
{
  Front* front = NULL;
  
  for(long i=0; i < myObjectList.count();i++){
    front = dynamic_cast(Front,myObjectList.item(i));
    if (front) 
      front->getIndirectFaceObjects(frontindex, polygonindex, facelist);          
  }
  
}

Vector3D Building::getVertex(long frontindex, long polygonindex) const
{
  List<Vector3D> vertices = getPolygon(polygonindex);

  if (vertices.count() <= frontindex || frontindex < 0){
    ostrstream os;
    os << "[Building::getVertex] index ("
       <<  frontindex << ","
       <<  polygonindex << ") is out of bounds";
    Report::recoverable(os);     
    return Vector3D(0,0,0);  
  }  
  
  return vertices.item(frontindex);
}

List<Front*> Building::getFrontObjects(long frontindex, long polygonindex) const
{
  List<Front*> fronttri;
  List<Front*> frontrect;
  List<Front*> other;
  Front* front;
  long i;
  
  for(i=0; i<myObjectList.count();i++){
    front = dynamic_cast(Front,myObjectList.item(i));
    if ( front && 
        (frontindex < 0 || front->getFrontIndex() == frontindex) &&
        (polygonindex < 0 || front->getPolygonIndex() == polygonindex)){
      if (dynamic_cast(FrontTriangle,front))
        fronttri.append(front);
      else if (dynamic_cast(FrontRect,front))
        frontrect.append(front);
      else
        other.append(front);
    }           
  }
  
  for(i=0; i<frontrect.count();i++)
    fronttri.append(frontrect.item(i)); 

  for(i=0; i<other.count();i++)
    fronttri.append(other.item(i)); 
    
  return fronttri;
}

long Building::countFront(long polygonindex) const
{
  if (polygonindex <= myHoles.count() && polygonindex >= 0){
    if (polygonindex == 0)
      return myVertices.count();
    else
      return myHoles.item(polygonindex -1).count();
  }
  else
    return 0;
}

List<Roof*> Building::getRoofObjects() const
{
  List<Roof*> roofs;
  Roof* roof;
  for(long i=0;i<myObjectList.count();i++){
    roof = dynamic_cast(Roof,myObjectList.item(i)); 
    if (roof)
      roofs.append(roof);
  }

  return roofs;
}
void Building::moveVertex(long frontindex, long polygonindex, const Vector2D& offset)
{
  if (testIndex(frontindex, polygonindex)){
    Vector3D temp;
    if (polygonindex == 0){
      temp = myVertices.item(frontindex);
      myVertices.remove(frontindex);
      myVertices.insert(frontindex, temp + Vector3D(offset.x(),offset.y(),0));    
    }
    else{
      temp = myHoles.item(polygonindex-1).item(frontindex);
      myHoles.item(polygonindex-1).remove(frontindex);
      myHoles.item(polygonindex-1).insert(frontindex, temp + Vector3D(offset.x(),offset.y(),0));        
    }     
  }
  else{
    Report::warning("[Building::moveVertex] index out of bounds");  
  }
}

void Building::deleteVertex(long frontindex, long polygonindex)
{
  if (testIndex(frontindex, polygonindex)){
    long i;
    if (polygonindex == 0)
      myVertices.remove(frontindex);
    else
      myHoles.item(polygonindex-1).remove(frontindex);

    for(i=myObjectList.count()-1;i>=0;i--){
      Front* front = dynamic_cast(Front,myObjectList.item(i));
      if (front){
        myObjectList.remove(i);
        delete front; 
      }
    }
    
    for(i=frontindex +1; i<countFront(polygonindex);i++) 
      changeIndex(i,polygonindex,i-1,polygonindex);
  }
  else{
    Report::warning("[Building::deleteVertex] index out of bounds");  
  }

}

void Building::insertVertex(long frontindex, long polygonindex, const Vector3D& vertex)
{
  if (polygonindex < 0 || frontindex < 0 || 
      polygonindex >= countPolygon() || frontindex > countFront(polygonindex)){
    Real z = vertex.z();
    
    if (myVertices.count() > 0)
      z = myVertices.item(0).z();
    else if(myHoles.count() > 0 && myHoles.item(0).count()>0)
      z = myHoles.item(0).item(0).z();

    Vector3D a(vertex.x(),vertex.y(),z);
    
    if (polygonindex == 0)
      myVertices.insert(frontindex,a);
    else
      myHoles.item(polygonindex-1).insert(frontindex,a);

    for(long i=countFront(polygonindex)-1;i>=frontindex +1;i++) 
      changeIndex(i-1,polygonindex,i,polygonindex);
    
  }
  else{
    Report::warning("[Building::insertVertex] index out of bounds");    
  }
}
bool Building::testIndex(long frontindex, long polygonindex) const
{
  if(polygonindex < 0 || frontindex < 0 || 
     polygonindex >= countPolygon() || frontindex >= countFront(polygonindex))
    return false;
  else
    return true;     
}
 
void Building::changeIndex(long frontindex, long polygonindex, long newfrontindex, long newpolygonindex) const
{
  long i;
  List<Front*> frontlist = getFrontObjects(frontindex,polygonindex);
  for(i=0;i<frontlist.count();i++){
    frontlist.item(i)->setFrontIndex(newfrontindex);
    frontlist.item(i)->setPolygonIndex(newpolygonindex);    
  }

  List<Face*>* facelistind = new List<Face*>;
  getIndirectFaceObjects(frontindex,polygonindex,facelistind);
  for(i=0;i<facelistind->count();i++){
    facelistind->item(i)->setFrontIndex(newfrontindex);
    facelistind->item(i)->setPolygonIndex(newpolygonindex);    
  }
  delete facelistind;

}
