/*
 * $RCSfile: Picker2D.C,v $
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
 *  $Id: Picker2D.C,v 1.6 1996/09/13 08:05:34 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/Report.h"
#include "booga/object/Camera2D.h"
#include "booga/component/Collector2DFor.h"
#include "booga/component/Picker2D.h"

//_____________________________________________________________________ Picker2D

implementRTTI(Picker2D, Operation2D);

Picker2D::Picker2D()
: myRay(Vector2D(0,0))
{
  myOrigX = myOrigY = 0;
  myCamera = NULL;
}

bool Picker2D::doExecute()
{
  //
  // Find an appropriate camera if none is provided.
  //
  if (myCamera == NULL) {
    Collector2DFor<Camera2D> camCollector;
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
    Report::warning("[Picker2D::doExecute] no camera available");
    return false;
  }
  
  if (myOrigX < 0 || myOrigX >= myCamera->getViewing()->getResolutionX() || 
      myOrigY < 0 || myOrigY >= myCamera->getViewing()->getResolutionY())
  {
    Report::warning("[Picker2D::doExecute] illegal values for pick origin");
    return false;
  }

  myRay.reset();
  myCamera->getViewing()->computeRayThrough(myOrigX, myOrigY, myRay);
  
  getWorld()->getObjects()->intersect(myRay);

  return true;
}
