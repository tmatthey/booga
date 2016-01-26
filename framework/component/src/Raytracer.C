/*
 * $RCSfile: Raytracer.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Raytracer.C,v 1.26 1996/09/18 12:05:27 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include <sstream>  // std::stringstream
#include "booga/base/Statistic.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Raytracer.h"

//____________________________________________________________________ Raytracer

implementRTTI(Raytracer, PixmapRenderer);

Raytracer::Raytracer() 
{
  myComputeDepthMap = true;
  myComputeAlphaMap = true;
}

bool Raytracer::doExecute()
{
  //
  // Initialize pixmap.
  //
  if (myComputeDepthMap)
    myPixmap->clearDepth(MAXFLOAT);
    
  if (myComputeAlphaMap)
    myPixmap->clearAlpha(0);
    
  Color bg = getCamera()->getBackground();
  myPixmap->clearColor(bg[0], bg[1], bg[2]);

  //
  // Setup the texturing context.
  //
  Texture3DContext context;
  context.setWorld(getWorld());
  context.setAmbientLightSources(getAmbientLightSources());
  context.setDirectedLightSources(getDirectedLightSources());
  
  // Some variables for use in the loop.
  Color defaultColor = Color(1,0,0); // Default is red.
  long position = 0;
  int x, y;
  int resX = getCamera()->getViewing()->getResolutionX();
  int resY = getCamera()->getViewing()->getResolutionY();
  Ray3D* ray = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(1,0,0));
  const Path3D* path = NULL;
  
  //
  // Start ray tracing.
  //
  for (y=0; y<resY; y++) {
    for (x=0; x<resX; x++, position++) { 
      //
      // We send a new primary ray ...
      //
      ray->reset();
      getCamera()->getViewing()->computeRayThrough(x, y, *ray);

      if (getWorld()->getObjects()->intersect(*ray) &&
          ((path = ray->getPath()) != NULL)) {

        //
        // Setup texture context.
        //
        context.setIncidencePosition(ray->getOrigin());
        context.setOCS2WCS(path->getLastTransform());
        context.setPositionWCS(ray->getHitPoint());
        context.setNormalOCS(ray->getBestHitObject()->normal(context.getPositionOCS()));
        //context.setColor(defaultColor);
        context.setColor(bg);

        Texture3D::texturing(context, path);
        
        myPixmap->setPosition(position);
        myPixmap->setColor(context.getColor().getRed(), 
                           context.getColor().getGreen(), 
                           context.getColor().getBlue());

        if (myComputeDepthMap)
          myPixmap->setDepth(ray->getBestHitDistance());
          
        if (myComputeAlphaMap)
          myPixmap->setAlpha(1);
      }
    }
    if ((y % 10 == 0) && y > 0) {
      std::stringstream os;
      os << "Finished line " << y;
      Report::debug(os);
    }
  }  
  
  Statistic::addEntry("Raytracer: Created rays", Ray3DFactory::getNoOfPrimaryRays() +
                                                 Ray3DFactory::getNoOfReflectedRays() +
                                                 Ray3DFactory::getNoOfRefractedRays());
  Statistic::addEntry("Raytracer: Eye rays", resX*resY);
  Statistic::addEntry("Raytracer: Reflected rays", Ray3DFactory::getNoOfReflectedRays());
  Statistic::addEntry("Raytracer: Refracted rays", Ray3DFactory::getNoOfRefractedRays());
  
  delete ray;
  
  return true;
}

void Raytracer::computeDepthMap(bool flag)
{
  myComputeDepthMap = flag;
}

void Raytracer::computeAlphaMap(bool flag)
{
  myComputeAlphaMap = flag;
}
