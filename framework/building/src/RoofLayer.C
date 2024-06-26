/*
 * $RCSfile: RoofLayer.C,v $
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
 *  $Id: RoofLayer.C,v 1.4 1997/04/15 08:19:23 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Vector3D.h"
#include "booga/base/TransMatrix3D.h"
#include "booga/base/Geometry3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/NullObject3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Grid3D.h"
#include "booga/object/List3D.h"
#include "booga/building/RoofLayer.h"
#include "booga/building/Building.h"

// ____________________________________________________________________ RoofLayer

implementRTTI(RoofLayer, Roof);

RoofLayer::RoofLayer(Exemplar exemplar)
:Roof(exemplar)
{
  setLedge(0);
}

RoofLayer::RoofLayer()
{
  setLedge(0);
}

RoofLayer::RoofLayer(const List<Vector3D>& layers)
:myLayers(layers)
{
  setLedge(0);
}


Object3D* RoofLayer::copy() const
{
  return new RoofLayer(*this);
}

Makeable* RoofLayer::make(RCString& errMsg, const List<Value*>* parameters) const
{
  RoofLayer* newRoof = new RoofLayer(*this);
  newRoof->removeLayers();
  if ((!parameters ? 0 : parameters->count())>0){
    List<Vector3D> layers (parameters->count()-1);
    for (int i=1; i<=parameters->count(); i++){
      getParameter(i, Vector3D, layer);
      layers.append(layer);
    }
    newRoof->setLayers(layers);
  }
  return newRoof;
}

Object3D* RoofLayer::doCreateSubject(Building* building) const
{
  long i,j,k;
  //Grid3D* roof = new Grid3D(15,15,15);
  List3D* roof = new List3D();
  List<List<Vector3D> > polygons;
  List<Vector3D> base,top,temp;
  Polygon3D* toppolygon = NULL;
  Real area;
  Vector3D a,b,c,d;
  
  if (myLayers.count() <=0)
    return new NullObject3D();
  
  Real h = building->getVertex(0,0).z() + building->getHeight();

  polygons.append(building->getPolygonTop(0));
  for(i=0;i < building->getHoles().count(); i++)
    polygons.append(building->getPolygonTop(i+1));   

  for(i=0; i<polygons.count(); i++){
    base = polygons.item(i);
    for(j=0; j<myLayers.count(); j++){
      top.removeAll();
      temp = Geometry3D::computeLayerXYPlane(myLayers.item(j).x(),polygons.item(i));
//      Real u = (float)j/(float)(myLayers.count()-1);
      Real u = myLayers.item(j).z();

      for(k=0;k<temp.count();k++)
        top.append(Vector3D(temp.item(k).x(),
                            temp.item(k).y(),
                            myLayers.item(j).y() + u*h + (1-u)* temp.item(k).z()));  
      for(k=0;k<top.count();k++){
        a = base.item(k);
        b = base.item((k+1) % base.count());
        c = top.item((k+1) % top.count());
        d = top.item(k);
        // Do not generate degenerated triangles
        if (!a.equal(b))
          roof->adoptObject(new Triangle3D(a,b,c));
        if (!c.equal(d))
          roof->adoptObject(new Triangle3D(a,c,d));
      }
      base = top;
    }
    
    top = Geometry3D::removeCollinearPoints(top);
    if (top.count() > 2){
      if (i==0){
        area = Geometry3D::area(top);
        if (area > EPSILON)
          toppolygon = new Polygon3D(top);
      }
      else {
        if (toppolygon){
          // remove top polygon if a hole is bigger than the polygon itself
          if (Geometry3D::area(top) + EPSILON >= area){
            delete toppolygon;
            toppolygon = NULL;
          }
          else   
            toppolygon->addHole(top);
        }
      }
    }
  }

  // add the top polygon
  if (toppolygon)
    roof->adoptObject(toppolygon);
  
  return roof;
}

List<Value*>* RoofLayer::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  for(long i=0; i < myLayers.count();i++)
    parameters->append(new Value(myLayers.item(i))); 
  return parameters;
}

static const RCString rooflayerKeyword("rooflayer");

RCString RoofLayer::getKeyword() const {
  return rooflayerKeyword;
}
