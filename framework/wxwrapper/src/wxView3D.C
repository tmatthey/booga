/*
 * $RCSfile: wxView3D.C,v $
 *
 * Copyright (C) 1995-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxView3D.C,v 1.8 1997/09/19 08:42:17 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */


#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/DirectedLight.h"
#include "booga/object/AmbientLight.h"

#include "booga/component/Collector3DFor.h"
#include "booga/component/SetStandardView3D.h"

#include "booga/glwrapper/GLUtilities.h" 
#include "booga/wxwrapper/wxView3D.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxInspectCommand.h"

/*
 * wxView3D implementation
 */
wxView3D::wxView3D(wxWindow *parent, int x, int y, int w, int  h, long style, char *name)
: wxGLCanvas(parent, x, y, w, h, style, name)
{
  myRenderingQuality = GLRenderer::SOLID_FLAT;
  myMotionQuality = GLRenderer::BOUNDING_BOX;

  myGLRenderer = new GLRenderer;
  // to avoid generation of 2D world with every frame
  // speeds up things a little bit... ;)
  myGLRenderer->generateWorld(false); 
  
  myMouseCommand = new wxInspectCommand(this);
}

wxView3D::~wxView3D()
{
  getViewManager()->detach(this);
  if (myMouseCommand)
	  delete myMouseCommand;
  delete myGLRenderer;
}      

void wxView3D::OnEvent(wxMouseEvent& event)
{
  if (!getViewManager()->getWorld())
    return;

  myMouseEvent = event;  // store event

  if (myMouseCommand)
      myMouseCommand->execute();
}

void wxView3D::OnPaint( void )
{
  GLSetCurrent();
  glDrawBuffer(GL_BACK);

  getRenderer()->execute(getViewManager()->getWorld());
  getRenderer()->getTraversal()->apply((World3D *)getViewManager()->getAuxWorld(), getRenderer());
  renderSelection();
  GLint drawBuffer;
  glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
  if (drawBuffer == GL_BACK)
    GLUtilities::swapBuffers();
}

void wxView3D::OnSize(int width, int height)
{
  GLSetCurrent();
  if (getRenderer()->getCamera())
    getRenderer()->getCamera()->getViewing()->setResolution(width, height);
}

void wxView3D::update(wxViewManager::NotifyEvent event, Object3D* obj)
{
  switch (event) {
    case wxViewManager::CAMERAS_CHANGED: {
      Camera3D *cam = dynamic_cast(Camera3D,obj);
      if (cam) {
        getRenderer()->getCamera()->getViewing()->setEye(cam->getViewing()->getEye());
        getRenderer()->getCamera()->getViewing()->setLookat(cam->getViewing()->getLookat());      
      }
      break;
    }
      
    case wxViewManager::WORLD_NEW: {
      if (!getViewManager()->getWorld())
        break; // NULL World detected
  
      //  
      //
      // Collect all cameras in the newWorld.
      //  
      Collector3DFor<Camera3D> camCollector;
      camCollector.execute(myViewManager->getWorld());
      
	  if (!camCollector.count()) {
        SetStandardView3D v;
		v.execute(myViewManager->getWorld());
	  }

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

      getRenderer()->adoptCamera(camera);

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
//          directed->append(directedCollector.getObject());

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


      getRenderer()->adoptDirectedLightSources(directed);
      getRenderer()->adoptAmbientLightSources(ambient);
      
      // Set size:
//      SetSize (camera->getViewing()->getResolutionX(), 
//               camera->getViewing()->getResolutionY());	
      OnPaint();
      break;
    }
    case wxViewManager::REPAINT:
    case wxViewManager::WORLD_CHANGED:
    case wxViewManager::SELECTION_CHANGED:
      OnPaint();
      break;
    case wxViewManager::LIGHTS_CHANGED: {
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

      getRenderer()->adoptDirectedLightSources(directed);
      getRenderer()->adoptAmbientLightSources(ambient);
      break;
    }

    default: 
      break;
  }
}

void wxView3D::adoptMouseCommand (wxViewCommand *c)
{
  if (myMouseCommand) 
    delete myMouseCommand;
    
  myMouseCommand = c;
}

wxViewCommand *wxView3D::orphanMouseCommand()
{
  wxViewCommand *c = myMouseCommand;
  myMouseCommand = NULL;
  return c;
}

void wxView3D::renderSelection()
{

  Aggregate3D *selection = getViewManager()->getSelection();
  if (selection) {

    // Set rendering quality to bounding box
    // remember old rendering quality

    GLRenderer::RenderingQuality oldQuality = getRenderingQuality();
    getRenderer()->setRenderingQuality(GLRenderer::BOUNDING_BOX);
    //
    // The second last cummulated transform has to be applied, since the bounding
    // box is already transformed with the object's own transformation.
    //
    
    //
    // Select the color of the bounding box.
    //
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    Color bgColor;
    if (getRenderer()->getCamera())
      bgColor = getRenderer()->getCamera()->getBackground();
    if ((bgColor[0] + bgColor[1] + bgColor[2])/3.0 > .5)
      glColor3f (0, 0, 0);
    else
      glColor3f (1, 1, 1);
//    glDrawBuffer(GL_FRONT);

    //
    // Draw the object in bounding box mode!
    //

    for (long i=0; i<selection->countSubobject(); i++)
      getRenderer()->drawBounds(selection->getSubobject(i)); 

    glFlush();
    getRenderer()->setRenderingQuality(oldQuality);
  }
}
