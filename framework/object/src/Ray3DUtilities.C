/*
 * $RCSfile: Ray3DUtilities.C,v $
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
 *  $Id: Ray3DUtilities.C,v 1.9 1996/08/16 12:40:53 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Color.h"

#include "booga/object/Ray3D.h" 
#include "booga/object/Ray3DUtilities.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DContext.h"
#include "booga/object/World3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"

//_______________________________________________________________ Ray3DUtilities

bool Ray3DUtilities::shadeSecondary(Ray3D* ray, Color& color, const Texture3DContext& context)
{
  if (ray != NULL) {
    const Path3D* path = NULL;
    const World3D* world = context.getWorld();
    if (world!=NULL && world->getObjects()->intersect(*ray) && ((path = ray->getPath()) != NULL)) {
      Texture3DContext newContext;
      newContext.setWorld(context.getWorld());
      newContext.setAmbientLightSources(context.getAmbientLightSources());
      newContext.setDirectedLightSources(context.getDirectedLightSources());
      newContext.setIncidenceRay(ray);
  
      newContext.setOCS2WCS(path->getLastTransform());
      newContext.setPositionWCS(ray->getHitPoint());
      newContext.setNormalOCS(ray->getBestHitObject()->normal(newContext.getPositionOCS()));
      newContext.setColor(color);
  
      Texture3D::texturing(newContext, path);
        
      color = newContext.getColor();   
      return true;
    }
  }
  
  return false;
}

