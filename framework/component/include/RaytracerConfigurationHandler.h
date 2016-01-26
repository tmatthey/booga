/*
 * RaytracerConfigurationHandler.h
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

#ifndef _RaytracerConfigurationHandler_H
#define _RaytracerConfigurationHandler_H

#include <strstream.h>
#include "booga/base/ValueOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//________________________________________________ RaytracerConfigurationHandler

class RaytracerConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);
  // Raytracer is a rendering component

protected:
  virtual Option* handleOptionRayDepth(const Name& option);
  // Option Ray.Depth defines how deep the ray tree may be.
  virtual Option* handleOptionRayCutoff(const Name& option);
  // Option Ray.Cutoff the minimum contribution of a ray.

private:
  static const Name OPTIONRayDepth_;
  static const Name OPTIONRayCutoff_;

public:
  static void initClass();
  // enable initialization of static members
};

//_________________ ensure initialization of class RaytracerConfigurationHandler

declareInitStatics(RaytracerConfigurationHandler);

#endif // _RaytracerConfigurationHandler_H
