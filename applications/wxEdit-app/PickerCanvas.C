/*
 * $RCSfile: PickerCanvas.C,v $ 
 *
 * Copyright (C) 1995-96, Bernhard Buhlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: PickerCanvas.C,v 1.8 1996/09/13 08:05:39 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Viewing3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Object3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/List3D.h"


#include "booga/object/DirectedLight.h"
#include "booga/object/AmbientLight.h"
#include "booga/component/Collector3DFor.h"


#include "PickerCanvas.h"

#include "wx.h"

//_____________________________________________________________________ PickerCanvas

implementRTTI(PickerCanvas, wxView3D);

PickerCanvas::PickerCanvas (wxWindow *frame, int x, int y, int w, int h) : wxView3D (frame, x, y, w, h)
{
	toolWorld = new World3D;
	auxilaryWorld = new World3D;
	List3D *l = new List3D;
	for (Real i=-100; i<100; i+=10) {
      l->adoptObject (new Cylinder3D (.01, Vector3D(i, -100, 0), Vector3D(i,100,0)));
      l->adoptObject (new Cylinder3D (.01, Vector3D(-100,i, 0), Vector3D(100,i,0))); 
//      for (Real j=-100; j<100; j+=10) {
//        List<Vector3D> v;
//        v.append (Vector3D (i,j,0));
//        v.append (Vector3D (i+10,j,0));
//        v.append (Vector3D (i+10,j+10,0));
//        l->adoptObject (new Polygon3D(v));
      }
      
//        	Box3D *b = new Box3D (Vector3D(-1000, -1000, 0), Vector3D(1000,1000,-.001));
  auxilaryWorld->getObjects()->adoptObject(l);
  auxilaryWorld->getObjects()->computeBounds();
  clipBoard = NULL;
  toolWorld->getObjects()->adoptObject(new Box3D (Vector3D(-100, -100, 0),
                                                  Vector3D(100, 100, 0)));
  toolWorld->getObjects()->computeBounds();
                                       
}

void PickerCanvas::OnPaint()
{  
  if (getViewManager()->getWorld()) {
    GLSetCurrent();
    glDrawBuffer(GL_BACK);
  
    execute(getViewManager()->getWorld());
 
    GLint drawBuffer;
    glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
    if (drawBuffer == GL_BACK) 
      GLSwapBuffers();
  } else {
    GLClear();
    GLSwapBuffers();
  }
}

void PickerCanvas::movePickedObject(int x, int y)
{
  if (myPicker.getPath() != NULL) {
    // get the second object in the path. the fisrt object is the world.
		
    myPicker.getPath()->first(); myPicker.getPath()->next(); 
    Object3D *obj = (Object3D *)myPicker.getPath()->getObject();

    // store old picker position
    Vector3D oldToolPosition = toolPicker.getHitPoint();

    // find point on plane: pick object in toolWorld

    toolPicker.setCamera(getCamera()); 
    toolPicker.setPickOrigin(x, getCamera()->getViewing()->getResolutionY()-y);
    toolPicker.execute(toolWorld);
		
    if (toolPicker.getPath() != NULL) {
      // we've hit the plane!
      // calculate the offset to the previous hit-point on the plane
      Vector3D offset = toolPicker.getHitPoint() - oldToolPosition;
																					
      TransMatrix3D t;
      Transform3D myTrans = obj->getTransform();
      obj->addTransform (t.makeTranslate (offset));
      obj->recomputeBounds(*myPicker.getPath());
      useMotionQuality();
      OnPaint();
    }		
  }
}

void PickerCanvas::rotatePickedObject(int alpha)
{
	if (myPicker.getPath() != NULL) {
		// get the second object in the path. the first object is the world.
		
		myPicker.getPath()->first(); myPicker.getPath()->next(); 
		Object3D *obj = (Object3D *)myPicker.getPath()->getObject();

		// get the middle of the boundingbox

		Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

		TransMatrix3D t;
		Transform3D myTrans = obj->getTransform();
		t = t * t.makeTranslate(-bbmid); // translate to origin
		t = t * t.makeRotateZ (dtor(alpha)); // rotate around z axis
		t = t * t.makeTranslate(bbmid); // translate back to bbmid
		
		obj->addTransform (t); // add the new transformation
		obj->recomputeBounds(*myPicker.getPath()); // recompute the boundingboxes 
		useMotionQuality();
		OnPaint();
	}		
}

void PickerCanvas::inspectPickedObject()
{
	if (myPicker.getPath() != NULL) {
		myPicker.getPath()->first(); myPicker.getPath()->next(); 
		Object3D *obj = myPicker.getPath()->getObject();
		Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

		Camera3D *myCam = new Camera3D();

//		TransMatrix3D m = myPicker.getPath()->getLastTransform().getTransMatrix();
//		myCam->getViewing()->setView (obj->getBounds().getMin()*m, obj->getBounds().getMax()*m);
//		myCam->getViewing()->setLookat (bbmid*m);
//		TransMatrix3D m = myPicker.getPath()->getLastTransform().getTransMatrix();
		myCam->getViewing()->setView (obj->getBounds().getMin(), obj->getBounds().getMax());
		myCam->getViewing()->setLookat (bbmid);
		interpolateCamera (myCam);
//		Vector3D deye = myCam->getViewing()->getEyep() - getCamera()->getViewing()->getEyep();
//		Vector3D dlook= myCam->getViewing()->getLookat() - getCamera()->getViewing()->getLookat();
		
//		getCamera()->getViewing()->setLookat (Vector3D(0,0,0)*t.getTransMatrix());
		setMotionMode(INSPECT);
		useRenderingQuality();
		OnPaint();
		delete myCam;
	}		
}

void PickerCanvas::renderPicker()
{
  //
  // Got a hit?
  //
  if (myPicker.getPath() != NULL) {
    myPicker.getPath()->first(); myPicker.getPath()->next();
    Object3D *pickedObject = myPicker.getPath()->getObject();

    // Set rendering quality to bounding box
    // remember old rendering quality

    GLRenderer::RenderingQuality oldQuality = getRenderingQuality();
    setRenderingQuality(GLRenderer::BOUNDING_BOX);
    //
    // The second last cummulated transform has to be applied, since the bounding
    // box is already transformed with the object's own transformation.
    //
    
    //
    // Select the color of the bounding box.
    //
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    Color bgColor = getCamera()->getBackground();
    if ((bgColor[0] + bgColor[1] + bgColor[2])/3.0 > .5)
      glColor3f (0, 0, 0);
    else
      glColor3f (1, 1, 1);
//    glDrawBuffer(GL_FRONT);

    //
    // Draw the object in bounding box mode!
    //

    drawBounds(pickedObject); 

    glFlush();
      setRenderingQuality(oldQuality);
  }
}

void PickerCanvas::pick (int x, int y)
{
  myPicker.setCamera(getCamera()); 
  myPicker.setPickOrigin(x, getCamera()->getViewing()->getResolutionY()-y-1);
  myPicker.execute(getViewManager()->getWorld());
  toolPicker.setCamera(getCamera()); 
  toolPicker.setPickOrigin(x, getCamera()->getViewing()->getResolutionY()-y);
  toolPicker.execute(toolWorld);
}

void PickerCanvas::OnEvent(wxMouseEvent& event)
{
  static float oldx, oldy;
  float x, y;
  event.Position(&x, &y);
  if (event.LeftDClick()) {
    cerr << "left dclick...\n";
    inspectPickedObject();
  } else if (event.LeftDown() && !event.Dragging()) {
    pick (int(x), int(y));
  } else if (event.LeftIsDown() && event.Dragging() && event.ShiftDown()) {
    rotatePickedObject (int(x-oldx));	
  } else if (event.LeftIsDown() && event.Dragging()) {
    movePickedObject(int(x), int(y));
  } else if (event.LeftUp()) {
    getViewManager()->getWorld()->getObjects()->computeBounds();
    useRenderingQuality();
    OnPaint();
  } else
    wxView3D::OnEvent (event);
  oldx = x; oldy = y;
}

void PickerCanvas::interpolateCamera (Camera3D *newc)
{
  Vector3D oldeye = getCamera()->getViewing()->getEye();
  Vector3D oldlookat = getCamera()->getViewing()->getLookat();
  Real oldfov = getCamera()->getViewing()->getHFov();
  
  Vector3D neweye = newc->getViewing()->getEye();
  Vector3D newlookat = newc->getViewing()->getLookat();
  Real newfov = newc->getViewing()->getHFov();

  Vector3D deye = neweye - oldeye;
  Vector3D dlookat = newlookat - oldlookat;
  Real dfov = newfov - oldfov;

  Real intervall = 100.0;
  Real frames = 20;

  for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
    Real value = log (i) / log (intervall);
    Vector3D ceye = oldeye + value*deye;
    Vector3D clookat = oldlookat + value*dlookat;
    Real cfov = oldfov +i*dfov; 
    getCamera()->getViewing()->setEye(ceye); 
    getCamera()->getViewing()->setLookat(clookat); 
    getCamera()->getViewing()->setFov(cfov); 
    useMotionQuality();

    OnPaint();
  }
  getCamera()->getViewing()->setEye(neweye); 
  getCamera()->getViewing()->setLookat(newlookat); 
  getCamera()->getViewing()->setFov(newfov);  
}

void PickerCanvas::cut ()
{
  if (myPicker.getPath() != NULL) {
    myPicker.getPath()->first(); myPicker.getPath()->next(); 
    if (clipBoard)
      delete clipBoard;
    clipBoard=myPicker.getPath()->getObject();
    if (getViewManager()->getWorld()->getObjects()->orphanObject(myPicker.getPath()->getObject())) {
      getViewManager()->getWorld()->getObjects()->recomputeBounds(*myPicker.getPath());
    }
    Path3D *thePath = (Path3D *)myPicker.getPath();
    thePath->reset();
  }
}

void PickerCanvas::copy ()
{
	if (myPicker.getPath() != NULL) {
		myPicker.getPath()->first(); myPicker.getPath()->next(); 
		if (clipBoard)
			delete clipBoard;
		clipBoard = (Object3D *)myPicker.getPath()->getObject()->copy();
		Transform3D myTrans = clipBoard->getTransform();
		TransMatrix3D t;		
		clipBoard->addTransform (t.makeTranslate (Vector3D(.5,.5,0)));
	}
}

void PickerCanvas::adoptAuxilaryWorld (World3D *a)
{
	if (auxilaryWorld)
		delete auxilaryWorld;
	auxilaryWorld = a;
}

void PickerCanvas::paste ()
{
	if (clipBoard) {
		getViewManager()->getWorld()->getObjects()->adoptObject(clipBoard->copy());
		getViewManager()->getWorld()->getObjects()->recomputeBounds(*myPicker.getPath());
	}
}

bool PickerCanvas::doExecute()
{
  if (!traverse(getViewManager()->getWorld()))
    return false;

//  RenderingQuality oldQuality = getRenderingQuality();
//
//  setRenderingQuality(WIREFRAME); 
//
//  glDisable(GL_DEPTH_TEST);
//  glDisable(GL_LIGHTING);
//  glDisable(GL_COLOR_MATERIAL);

//  traverse(toolWorld);

//  setRenderingQuality(oldQuality);
   
  if (auxilaryWorld)
    traverse(auxilaryWorld);


//  GLint drawBuffer;
//    glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
//  if (drawBuffer == GL_BACK) 
//    GLSwapBuffers();
  renderPicker();
    
  return true;
}

void PickerCanvas::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
{
  switch (event) {
    case wxViewManager::REPAINT:
      OnPaint();
      break;

    case wxViewManager::CAMERA_CHANGED:
      break;
     
    case wxViewManager::WORLD_CHANGED: {
      
      if (!getViewManager()->getWorld())
        break; // NULL World detected
        
      Path3D *thePath = (Path3D *)myPicker.getPath();
      if (thePath)
        thePath->reset();
      
      //  
      //
      // Collect all cameras in the newWorld.
      //  
      Collector3DFor<Camera3D> camCollector;
      camCollector.execute(myViewManager->getWorld());
      Camera3D* camera = NULL;


      //
      // Look for first camera in newWorld, that is switched on.
      //
      for (camCollector.first(); !camCollector.isDone(); camCollector.next())
        if (camCollector.getObject()->isOn()) {
          camera = camCollector.createTransformedObject(); 
          break;
        }

      if (camera == NULL) {
        Report::error("scene contains no active camera");
        exit(1);
      }

      adoptCamera(camera);

      //
      // Collect all directed light sources in the newWorld.
      //  
      Collector3DFor<DirectedLight> directedCollector;
      directedCollector.execute(myViewManager->getWorld());
      List<DirectedLight*>* directed = new List<DirectedLight*>;

      for (directedCollector.first(); !directedCollector.isDone();
           directedCollector.next())
        if (directedCollector.getObject()->isOn())
          directed->append(directedCollector.createTransformedObject());

      //
      // Collect all ambient light sources in the newWorld.
      //  
      Collector3DFor<AmbientLight> ambientCollector;
      ambientCollector.execute(myViewManager->getWorld());
      List<AmbientLight*>* ambient = new List<AmbientLight*>;

      for (ambientCollector.first(); !ambientCollector.isDone(); 
           ambientCollector.next())
      if (ambientCollector.getObject()->isOn())
        ambient->append(ambientCollector.createTransformedObject());


      if (directed->count() + ambient->count() <= 0) {
        Report::error("scene contains no active light source");
      }


      adoptDirectedLightSources(directed);
      adoptAmbientLightSources(ambient);
      
      // Set size:
//      SetSize (camera->getViewing()->getResolutionX(), 
//               camera->getViewing()->getResolutionY());	
      OnPaint();
      break;        
    }
  }
}

