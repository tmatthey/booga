/*
 * $RCSfile: Rasterizer.C,v $
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
 *  $Id: Rasterizer.C,v 1.31 1996/09/13 08:06:04 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>
#include "booga/component/Collector2DFor.h"
#include "booga/base/LineRasterizer.h"
#include "booga/base/ConicRasterizer.h"

#include "booga/object/Camera2D.h"
#include "booga/object/World2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Point2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Texture2D.h"

#include "booga/component/Rasterizer.h"

//___________________________________________________________________ Rasterizer

implementRTTI(Rasterizer, Operation2D);

Rasterizer::Rasterizer()
{
  myCamera = NULL;
  myHasAdoptedCamera = false;
  myPixmap = NULL;
}

Rasterizer::~Rasterizer()
{
  if (myCamera != NULL)
    delete myCamera;
}

bool Rasterizer::preprocessing()
{
  if (!Operation2D::preprocessing())
    return false;
  
  if (!myHasAdoptedCamera) {
    //
    // Collect all cameras in the world.
    //  
    Collector2DFor<Camera2D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        if (myCamera != NULL)
          delete myCamera;
        myCamera = camCollector.createTransformedObject(); 
    }
  }

  if (myCamera == NULL) {
    Report::recoverable("[Rasterizer::preprocessing] no camera available");
    return false;
  }
    
  myPixmap = createPixmap(myCamera->getViewing()->getResolutionX(),
			myCamera->getViewing()->getResolutionY());
			
  Color bg = myCamera->getBackground();
  myPixmap->clearColor(bg[0], bg[1], bg[2]);

  myDefaultColor = Color::getDefault();
  
  return true;
}

bool Rasterizer::postprocessing()
{
  getResult()->getObjects()->adoptObject(new Pixmap2D(myPixmap));
  getResult()->getObjects()->computeBounds();
  myPixmap = NULL;

  return Operation2D::postprocessing();
}

void Rasterizer::cleanupAfterFailure()
{
  delete myPixmap;
  myPixmap = NULL;
}

Traversal::Result Rasterizer::visit(Point2D* point)
{  
  Vector2D pos = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       point->getPosition());

  //
  // Viewing transformation.
  //  
  pos = myCamera->getViewing()->transformWorld2Screen(pos);
	
  int x = (int)rint(pos.x());
  int y = (int)rint(pos.y());
	       
  setPixel(x, y);

  return Traversal::CONTINUE;
}

Traversal::Result Rasterizer::visit(Line2D* line)
{
  Vector2D from = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       line->getFrom());
  Vector2D to   = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       line->getTo());

  //
  // Viewing transformation.
  //
  from = myCamera->getViewing()->transformWorld2Screen(from);
  to   = myCamera->getViewing()->transformWorld2Screen(to);

  LineRasterizer lr;
  int x, y;
  for (lr.init((int)rint(from.x()), (int)rint(from.y()),
	      (int)rint(to.x()),   (int)rint(to.y()));
       !lr.isDone(); lr.next()) {
    lr.getPixel(x, y);
    setPixel(x, y);
  }
  
  return Traversal::CONTINUE;
}

Traversal::Result Rasterizer::visit(Circle2D* circle)
{
  Vector2D center = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       circle->getCenter());
  
  //
  // Two points on the boundary of the circle.
  //
  Vector2D a = getTraversal()->getPath()->getLastTransform().transformAsVector(
		       Vector2D(circle->getRadius(), 0)) + center;
  Vector2D b = getTraversal()->getPath()->getLastTransform().transformAsVector(
  		       Vector2D(0, circle->getRadius())) + center;

  //
  // Viewing transformation.
  //
  center = myCamera->getViewing()->transformWorld2Screen(center);
  a      = myCamera->getViewing()->transformWorld2Screen(a);
  b      = myCamera->getViewing()->transformWorld2Screen(b);

  ConicRasterizer cr;
  int x, y;
  for (cr.initEllipse((int)rint(center.x()), (int)rint(center.y()), 
		    (int)rint(a.x()), (int)rint(a.y()), 
		    (int)rint(b.x()), (int)rint(b.y()));
       !cr.isDone(); cr.next()) {
    cr.getPixel(x, y);
    setPixel(x, y);
  }
        
  return Traversal::CONTINUE;
}

Traversal::Result Rasterizer::visit(Pixmap2D* pixmap)
{
  const AbstractPixmap* pm = pixmap->getPixmap();
  
  // A Pixmap2D may have no pixmap attached to it!
  if (pm == NULL)
    return Traversal::CONTINUE;
    
  float c1, c2, c3;

  //
  // Pixmaps may be scaled, rotated, etc. The implementation below is very, very
  // simple and transformations applied to pixmaps may lead to rendering artefacts.
  // SORRY.
  //
  TransMatrix2D currTrans(getTraversal()->getPath()->getLastTransform().getTransMatrix());
  Vector2D pos;
  
  for (long y=0; y<pm->getResolutionY(); y++) {
    for (long x=0; x<pm->getResolutionX(); x++) {
      pos.x() = x; 
      pos.y() = y;
      pos = pos*currTrans;
      if (pos.x() < 0 || pos.x() >= myPixmap->getResolutionX() ||
	 pos.y() < 0 || pos.y() >= myPixmap->getResolutionY())
        continue;
        
      pm->setPosition(x, y);
      pm->getColor(c1, c2, c3);
      myPixmap->setPosition((int)rint(pos.x()), (int)rint(pos.y()));
      myPixmap->setColor(c1, c2, c3);
    }  
  }

  return Traversal::CONTINUE;
}

void Rasterizer::adoptCamera(Camera2D* camera)
{
  if (camera == NULL) {
    Report::warning("[Rasterizer::adoptCamera] NULL pointer passed");
    return;
  }
    
  if (myCamera != NULL && myCamera != camera)
    delete myCamera;

  myCamera = camera; 
  myHasAdoptedCamera = true;
}

void Rasterizer::deleteCamera()
{
  if (myCamera != NULL) {
    delete myCamera;
    myCamera = NULL;
  }
  myHasAdoptedCamera = false;
}

void Rasterizer::setPixel(int x, int y)
{
  // Perform clipping.
  if (x < 0 || x >= myPixmap->getResolutionX() ||
      y < 0 || y >= myPixmap->getResolutionY())
    return;

  Vector2D pos(x, y);
  pos = myCamera->getViewing()->transformScreen2World(pos);
  pos = getTraversal()->getPath()->getLastTransform().invTransformAsPoint(pos);

  myContext.setOCS2WCS(getTraversal()->getPath()->getLastTransform());
  myContext.setPositionOCS(pos);
  myContext.setColor(myDefaultColor);
  Texture2D::texturing(myContext, getTraversal()->getPath()); 

  myPixmap->setPosition(x, y);
  myPixmap->setColor(myContext.getColor().getRed(), 
		   myContext.getColor().getGreen(), 
		   myContext.getColor().getBlue());
}

Traversal::Result Rasterizer::dispatch(Makeable* obj)
{  
  tryConcrete(Point2D,  obj);
  tryConcrete(Line2D,   obj);
  tryConcrete(Circle2D, obj);
  tryConcrete(Pixmap2D, obj);

  return Traversal::UNKNOWN; // Perform decomposition if unknown object.
}
