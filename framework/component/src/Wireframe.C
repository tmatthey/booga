/*
 * $RCSfile: Wireframe.C,v $
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
 *  $Id: Wireframe.C,v 1.30 1997/05/01 12:55:15 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/TransMatrix3D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Texture2D.h"
#include "booga/object/InterpolatorTexture2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Polygon3D.h"
#include "booga/object/Line3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Wireframe.h"

//____________________________________________________________________ Wireframe

implementRTTI(Wireframe, Renderer);

Wireframe::Wireframe()
{
  mySortList     = false;
  myOptimizeList = false;
  myRemovedLines = -1;
}

void Wireframe::setSortList(bool sort)
{
  mySortList = sort;
  if (!sort)
    myOptimizeList = false;
    
}

bool Wireframe::getSortList() const
{
  return myOptimizeList;
}
void Wireframe::setOptimizeList(bool opt)
{
  if (opt)
    mySortList = true;
  myOptimizeList = opt;
}

bool Wireframe::getOptimizeList() const
{
  return myOptimizeList;
}

void Wireframe::addLine(const Vector2D& from, const Vector2D& to, const Color& c0, const Color& c1)
{

  Line2D* line;
  InterpolatorTexture2D* texture;


  if (mySortList) {
    Vector2D v,w,o,p;
    Color a,b;

    if ((from-to).length()< EPSILON){
      myRemovedLines++;      
      return;
    }

    if ((from.x() < (to.x() - EPSILON)) || ((fabs(from.x() - to.x()) < EPSILON ) 
                                         && ( from.y() < (to.y() - EPSILON)))){
      v = from;
      w = to;
      a = c0;
      b = c1;
    }
    else {
      v = to;
      w = from;
      a = c1;
      b = c0;
    }

    long first = 0;
    long last = myLines.count();
    long i = (last + first) / 2;
    bool same = false;
    
    while ((last - first) > 0){
      o = myLines.item(i)->getFrom();
      p = myLines.item(i)->getTo();
      
      if (v.x() < (o.x()-EPSILON)){ 
	last = i;
      }
      else if (v.x() > (o.x()+EPSILON)){  
	first = i + 1;
      }
      else if (v.y() < (o.y()-EPSILON)){ 
	last = i;
      }
      else if (v.y() > (o.y()+EPSILON)){  
	first = i + 1;
      }
      else if (w.x() < (p.x()-EPSILON)){  
	last = i;
      }
      else if (w.x() > (p.x()+EPSILON)){  
	first = i + 1;
      }
      else if (w.y() < (p.y()-EPSILON)){ 
	last = i;
      }
      else if (w.y() > (p.y()+EPSILON)){  
	first = i + 1;
      }
      else {
        last  = i;
	first = i;
	same = true;
      }

      i = (last + first) / 2;

    }

    if (!myOptimizeList || (myLines.count() < 1) || !same ){
      line = new Line2D(v,w);
      texture = new InterpolatorTexture2D();
      texture->setColor(a,b);
      line->appendTexture(texture);
      myLines.insert(i,line);
    }
    else
      myRemovedLines++;
  }
  else{
    line = new Line2D(from,to);
    texture = new InterpolatorTexture2D();
    texture->setColor(c0,c1);
    line->appendTexture(texture);

    getResult()->getObjects()->adoptObject(line); 
  }

}

Traversal::Result Wireframe::visit(Triangle3D* obj)
{
  Vector3D v3D[3];
  Vector2D v2D[3];
  Color vColor[3];
  const Path3D* path = getTraversal()->getPath();

  //
  // Perform viewing transformation and color computation 
  // for the provided triangle.
  // 
  int i;
  for (i=0; i<3; i++) {
    v3D[i] = getCamera()->getViewing()->transformWorld2Screen(
	       getTraversal()->getPath()->getLastTransform().transformAsPoint(
	         obj->getVertex(i)));
        
    //
    // Clip triangles behind the eye.
    //
    if (v3D[i].z() < EPSILON)
      return Traversal::CONTINUE;

    v2D[i].x() = v3D[i].x();
    v2D[i].y() = v3D[i].y();
    
    myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
    myTextureContext.setPositionOCS(obj->getVertex(i));
    myTextureContext.setNormalOCS(obj->getNormal(i));
    myTextureContext.setColor(myDefaultColor);
    Texture3D::texturing(myTextureContext, path);
    vColor[i] = myTextureContext.getColor();
  }                
        
  for (i=0; i<3; i++)
    addLine(v2D[i], v2D[(i+1)%3], vColor[i], vColor[(i+1)%3]);

  return Traversal::CONTINUE;
}

Traversal::Result Wireframe::visit(Line3D* obj)
{
  Vector3D a,b;
  Color c0,c1;
  const Path3D* path = getTraversal()->getPath();
 
  //
  // Perform viewing transformation and color computation 
  // for the provided line.
  // 
  a = getCamera()->getViewing()->transformWorld2Screen(
	       getTraversal()->getPath()->getLastTransform().transformAsPoint(
	         obj->getFrom()));
 
  b = getCamera()->getViewing()->transformWorld2Screen(
	       getTraversal()->getPath()->getLastTransform().transformAsPoint(
	         obj->getTo()));
        
  //
  // Clip line behind the eye.
  //
  if (a.z() < EPSILON || b.z() < EPSILON)
    return Traversal::CONTINUE;
 
    
  myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
  myTextureContext.setPositionOCS(obj->getFrom());
  myTextureContext.setNormalOCS(Vector3D(0,0,1));
  myTextureContext.setColor(myDefaultColor);
  Texture3D::texturing(myTextureContext, path);
  c0 = myTextureContext.getColor();
 
  myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
  myTextureContext.setPositionOCS(obj->getTo());
  myTextureContext.setNormalOCS(Vector3D(0,0,1));
  myTextureContext.setColor(myDefaultColor);
  Texture3D::texturing(myTextureContext, path);
  c1 = myTextureContext.getColor();
        
  addLine(Vector2D(a.x(),a.y()),Vector2D(b.x(),b.y()), c0, c1);
 
  return Traversal::CONTINUE;
}
 
Traversal::Result Wireframe::visit(Box3D* obj)
{
  Vector3D v[8];
  Vector3D v3D[8];
  Vector2D v2D[8];
  Color vColor[8];
  Vector3D from(obj->getFrom());
  Vector3D to(obj->getTo());
  const Path3D* path = getTraversal()->getPath();
 
  v[0] = Vector3D(from.x(), from.y(), from.z());
  v[1] = Vector3D(from.x(), from.y(), to.z());
  v[2] = Vector3D(from.x(), to.y(),   to.z());
  v[3] = Vector3D(from.x(), to.y(),   from.z());
  v[4] = Vector3D(to.x(),   from.y(), from.z());
  v[5] = Vector3D(to.x(),   from.y(), to.z());
  v[6] = Vector3D(to.x(),   to.y(),   to.z());
  v[7] = Vector3D(to.x(),   to.y(),   from.z());

  //
  // Perform viewing transformation and color computation 
  // for the provided box.
  // 
  int i;
  for (i=0; i<8; i++) {
    
    v3D[i] = getCamera()->getViewing()->transformWorld2Screen(
	       getTraversal()->getPath()->getLastTransform().transformAsPoint(
	         v[i]));        
    //
    // Clip triangles behind the eye.
    //
    if (v3D[i].z() < EPSILON)
      return Traversal::CONTINUE;
 
    v2D[i].x() = v3D[i].x();
    v2D[i].y() = v3D[i].y();
    
    myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
    myTextureContext.setPositionOCS(v[i]);
    myTextureContext.setNormalOCS(obj->normal(v[i]));
    myTextureContext.setColor(myDefaultColor);
    Texture3D::texturing(myTextureContext, path);
    vColor[i] = myTextureContext.getColor();
  }                
        
  for (i=0; i<4; i++) { 
    addLine(v2D[i],   v2D[(i+1)%4],  vColor[i],   vColor[(i+1)%4]);
    addLine(v2D[4+i], v2D[4+(i+1)%4],vColor[4+i], vColor[4+(i+1)%4]);
    addLine(v2D[i],   v2D[i+4],      vColor[i],   vColor[i+4]);
  }
 
  return Traversal::CONTINUE;
}
 
Traversal::Result Wireframe::visit(Polygon3D* obj)
{
  long i,j;
  Vector3D point;
  List<List<Vector3D> > polygons;
  List<List<Vector2D> > v2D;
  List<List<Color> > vColor;
  const Path3D* path = getTraversal()->getPath();
 
  polygons = obj->getHoles();
  polygons.append(obj->getVertices());
  
  //
  // Perform viewing transformation and color computation 
  // for the provided triangle.
  // 
  
  for (i=0; i<polygons.count(); i++) {
    List<Vector2D> temp2D;
    List<Color> tempC;
    for(j=0; j<polygons.item(i).count(); j++) {
      point = getCamera()->getViewing()->transformWorld2Screen(
                 getTraversal()->getPath()->getLastTransform().transformAsPoint(
                   polygons.item(i).item(j)));
        
      //
      // Clip triangles behind the eye.
      //
      if (point.z() < EPSILON)
        return Traversal::CONTINUE;
 
      temp2D.append(Vector2D(point.x(),point.y()));
    
      myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
      myTextureContext.setPositionOCS(polygons.item(i).item(j));
      myTextureContext.setNormalOCS(obj->getNormal());
      myTextureContext.setColor(myDefaultColor);
      Texture3D::texturing(myTextureContext, path);
      tempC.append(myTextureContext.getColor());
    }                
    v2D.append(temp2D);
    vColor.append(tempC);
  }  
      
  for (i=0; i<v2D.count(); i++)
    for(j=0; j<v2D.item(i).count(); j++)
      addLine(v2D.item(i).item(j), v2D.item(i).item((j+1)%v2D.item(i).count()),
	      vColor.item(i).item(j), vColor.item(i).item((j+1)%v2D.item(i).count()));
 
  return Traversal::CONTINUE;
}
 
Traversal::Result Wireframe::visit(Disc3D* obj)
{
  // The precision argument is converted to 'resolution' by using 
  // the following formula:
  //
  //     resolution = 20 * precison 
  //
  int resolution = (int)rint(20*obj->getPrecision());
  
  TransMatrix3D rot(TransMatrix3D::makeRotate(obj->getNormal(), 2*M_PI/resolution));

  Vector3D pointA;
  
  if (1 - fabs(obj->getNormal().z()) < EPSILON) {
    pointA.x() = 1;
    pointA.y() = pointA.z() = 0;
  }
  else {
    pointA.x() =  obj->getNormal().y();
    pointA.y() = -obj->getNormal().x();
    pointA.z() = 0;
  }

  pointA = (obj->getNormal() * pointA).normalized()*obj->getRadius();

  Vector3D v3D[resolution];
  Vector2D v2D[resolution] ;
  Color    vColor[resolution];

  const Path3D* path = getTraversal()->getPath();

  //
  // Sweep around the normal.
  //
  //
  // Perform viewing transformation and color computation 
  // for the provided triangle.
  //
  for (int i=0; i<resolution; i++) {
    v3D[i] = getCamera()->getViewing()->transformWorld2Screen(
	       getTraversal()->getPath()->getLastTransform().transformAsPoint(
	       obj->getCenter()+pointA)); 
    //
    // Clip triangles behind the eye.
    //
    if (v3D[i].z() < EPSILON){
      
      return Traversal::CONTINUE;
    }

    v2D[i].x() = v3D[i].x();
    v2D[i].y() = v3D[i].y();
    
    myTextureContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
    myTextureContext.setPositionOCS(obj->getCenter()+pointA);
    myTextureContext.setNormalOCS(obj->getNormal());
    myTextureContext.setColor(myDefaultColor);
    Texture3D::texturing(myTextureContext, path);
    vColor[i] = myTextureContext.getColor();

    pointA = pointA * rot;
  }
    
  for (i=0; i<resolution; i++)
    addLine(v2D[i], v2D[(i+1)%resolution],vColor[i], vColor[(i+1)%resolution]);

  return Traversal::CONTINUE;
}

bool Wireframe::preprocessing()
{
  if (!Renderer::preprocessing())
    return false;

  if (myOptimizeList)
    myRemovedLines = 0;
    
  myDefaultColor = Color::getDefault();
  myTextureContext.setWorld(getWorld());
  myTextureContext.setAmbientLightSources(getAmbientLightSources());
  myTextureContext.setDirectedLightSources(getDirectedLightSources());

  return true;
}

bool Wireframe::postprocessing()
{
  // add the sorted list to the world
  if (mySortList){
    if (myOptimizeList) {
      ostrstream os;
      long m = myRemovedLines;
      long n = myLines.count() + myRemovedLines;
      os << "Removed " << m << " ("<< (m*100)/n << "%) lines of " << n;
      Report::debug(os);
    }
      
    for(long i = 0; i < myLines.count(); i++)
      getResult()->getObjects()->adoptObject(myLines.item(i));
    myLines.removeAll();
  }

  Camera2D* camera = new Camera2D;
  camera->getViewing()->setResolution(getCamera()->getViewing()->getResolutionX(),
				  getCamera()->getViewing()->getResolutionY());
  camera->getViewing()->setWindow(Vector2D(0,0), 
			       Vector2D(getCamera()->getViewing()->getResolutionX(),
				       getCamera()->getViewing()->getResolutionY()));
  
  camera->setBackground(getCamera()->getBackground());
  
  getResult()->getObjects()->adoptObject(camera);
  getResult()->getObjects()->computeBounds();

  return Renderer::postprocessing();
}


Traversal::Result Wireframe::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D, obj);
  tryConcrete(Box3D, obj);
  tryConcrete(Polygon3D, obj);
  tryConcrete(Line3D, obj);
  tryConcrete(Disc3D, obj);
  
  //
  // Create decomposition for objects other than triangles.
  //
  return Traversal::UNKNOWN;
}
