/*
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
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
 */

#include "booga/component/RaytracerConfigurationHandler.h"

//________________________________________________ RaytracerConfigurationHandler

implementInitStatics(RaytracerConfigurationHandler);

const Name RaytracerConfigurationHandler::OPTIONRayDepth_("Raytracer.Ray.Depth");
const Name RaytracerConfigurationHandler::OPTIONRayCutoff_("Raytracer.Ray.Cutoff");

/*
 * Raytracer is a rendering component
 */
Option* RaytracerConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONRayDepth_)
    return handleOptionRayDepth(option);
  else if (name == OPTIONRayCutoff_)
    return handleOptionRayCutoff(option);
  else
    return NULL;
}

/*
 * Option Ray.Depth defines how deep the ray tree may be.
 */
Option* RaytracerConfigurationHandler::handleOptionRayDepth(const Name& option)
{
  istrstream iss((char *)((const RCString&)option).chars());
  Real depth;
  iss >> depth;
  return new ValueOption(depth);
}
/*
 * Option Ray.Cutoff the minimum contribution of a ray.
 */
Option* RaytracerConfigurationHandler::handleOptionRayCutoff(const Name& option)
{
  istrstream iss((char *)((const RCString&)option).chars());
  Real cutoff;
  iss >> cutoff;
  return new ValueOption(cutoff);
}

void RaytracerConfigurationHandler::initClass()
{
  Configuration::addHandler(new RaytracerConfigurationHandler);
}
