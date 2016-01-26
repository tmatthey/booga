/*
 * $RCSfile: Picker3D.C,v $
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
 *  $Id: Picker3D.C,v 1.10 1996/09/13 08:05:38 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/Picker3D.h"

//_____________________________________________________________________ Picker3D

implementRTTI(Picker3D, Operation3D);

Picker3D::Picker3D()
{
  myRay = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(0,0,1));
  myOrigX = myOrigY = 0;
  myCamera = NULL;
}

Picker3D::~Picker3D()
{
  delete myRay;
}

bool Picker3D::doExecute()
{
  //
  // Find an appropriate camera if none is provided.
  //
  if (myCamera == NULL) {
    Collector3DFor<Camera3D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        myCamera = camCollector.createTransformedObject(); 
        break;
      }
  }
 
  if (myCamera == NULL) {
    Report::warning("[Picker3D::doExecute] no camera available");
    return false;
  }
  
  if (myOrigX < 0 || myOrigX >= myCamera->getViewing()->getResolutionX() || 
      myOrigY < 0 || myOrigY >= myCamera->getViewing()->getResolutionY())
  {
    Report::warning("[Picker3D::doExecute] illegal values for pick origin");
    return false;
  }

  myRay->reset();
  myCamera->getViewing()->computeRayThrough(myOrigX, myOrigY, *myRay);

  getWorld()->getObjects()->intersect(*myRay);
  
  return true;
}
