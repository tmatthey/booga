/*
 * $RCSfile: Renderer.C,v $
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
 *  $Id: Renderer.C,v 1.25 1996/09/13 08:06:14 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/ListUtilities.h"
#include "booga/object/Object2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/World2D.h"
#include "booga/object/AmbientLight.h"
#include "booga/object/DirectedLight.h"
#include "booga/component/Renderer.h"
#include "booga/component/Collector3DFor.h"

//_____________________________________________________________________ Renderer

implementRTTI(Renderer, Operation3DTo2D);

Renderer::Renderer()
{
  myCamera = NULL;
  myHasAdoptedCamera = false;

  myAmbientLightSources = NULL;
  myHasAdoptedAmbientLightSources = false;
  myDirectedLightSources = NULL;
  myHasAdoptedDirectedLightSources = false;
}

Renderer::~Renderer()
{
  if (myCamera != NULL)
    delete myCamera;

  deleteList(myAmbientLightSources);
  deleteList(myDirectedLightSources);
}

void Renderer::adoptCamera(Camera3D* camera)
{
  if (camera == NULL) {
    Report::warning("[Renderer::adoptCamera] NULL pointer passed");
    return;
  }
    
  if (myCamera != NULL && myCamera != camera)
    delete myCamera;

  myCamera = camera; 
  myHasAdoptedCamera = true;
}

void Renderer::deleteCamera()
{
  if (myCamera != NULL) {
    delete myCamera;
    myCamera = NULL;
  }
  myHasAdoptedCamera = false;
}

void Renderer::adoptAmbientLightSources(List<AmbientLight*>* lightSources)
{
  if (lightSources == NULL) {
    Report::warning("[Renderer::adoptLightSources] NULL pointer passed");
    return;
  }
    
  if (myAmbientLightSources != lightSources) 
    deleteList(myAmbientLightSources);

  myAmbientLightSources = lightSources; 
  myHasAdoptedAmbientLightSources = true;
}

void Renderer::adoptDirectedLightSources(List<DirectedLight*>* lightSources)
{
  if (lightSources == NULL) {
    Report::warning("[Renderer::adoptLightSources] NULL pointer passed");
    return;
  }
    
  if (myDirectedLightSources != lightSources) 
    deleteList(myDirectedLightSources);

  myDirectedLightSources = lightSources; 
  myHasAdoptedDirectedLightSources = true;
}

void Renderer::deleteAmbientLightSources()
{
  deleteList(myAmbientLightSources);
  myHasAdoptedAmbientLightSources = false;
}

void Renderer::deleteDirectedLightSources()
{
  deleteList(myDirectedLightSources);
  myHasAdoptedDirectedLightSources = false;
}

bool Renderer::preprocessing()
{
  if (!Operation3DTo2D::preprocessing())
    return false;

  if (!myHasAdoptedCamera) {
    //
    // Collect all cameras in the world.
    //  
    Collector3DFor<Camera3D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    if (myCamera != NULL) {
      delete myCamera;
      myCamera = NULL;
    }
      
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        myCamera = camCollector.createTransformedObject(); 
        break;
      }
  }

  if (!myHasAdoptedAmbientLightSources) {
    //
    // Collect all ambient light sources in the world.
    //  
    Collector3DFor<AmbientLight> lightCollector;
    lightCollector.execute(getWorld());
  
    //
    // Register all active light sources in the list 'myLightSources'.
    //
    deleteList(myAmbientLightSources);
    myAmbientLightSources = new List<AmbientLight*>;

    for (lightCollector.first(); !lightCollector.isDone(); lightCollector.next())
      if (lightCollector.getObject()->isOn())
        myAmbientLightSources->append(lightCollector.createTransformedObject());
  }

  if (!myHasAdoptedDirectedLightSources) {
    //
    // Collect all light sources in the world.
    //  
    Collector3DFor<DirectedLight> lightCollector;
    lightCollector.execute(getWorld());
  
    //
    // Register all active light sources in the list 'myLightSources'.
    //
    deleteList(myDirectedLightSources);
    myDirectedLightSources = new List<DirectedLight*>;

    for (lightCollector.first(); !lightCollector.isDone(); lightCollector.next())
      if (lightCollector.getObject()->isOn())
        myDirectedLightSources->append(lightCollector.createTransformedObject());
  }

  if (myCamera == NULL) {
    Report::recoverable("[Renderer::preprocessing] camera declaration missing");
    return false;
  }
  
  if (((myAmbientLightSources  == NULL) || (myAmbientLightSources->count()  <= 0)) &&
      ((myDirectedLightSources == NULL) || (myDirectedLightSources->count() <= 0))) {
    Report::recoverable("[Renderer::preprocessing] light source declarations missing");
    return false;
  }

  return true;
}

