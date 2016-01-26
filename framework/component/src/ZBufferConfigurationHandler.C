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

#include "booga/component/ZBufferConfigurationHandler.h"

//__________________________________________________ ZBufferConfigurationHandler

implementInitStatics(ZBufferConfigurationHandler);

const Name ZBufferConfigurationHandler::OPTIONTriangleInterpolator_("ZBuffer.TriangleInterpolator");
const Name ZBufferConfigurationHandler::VALUETriangleInterpolator_Flat_("Flat");
const Name ZBufferConfigurationHandler::VALUETriangleInterpolator_Gouraud_("Gouraud");
const Name ZBufferConfigurationHandler::VALUETriangleInterpolator_Phong_("Phong");

/*
 * ZBuffer is a rendering component
 */
Option* ZBufferConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONTriangleInterpolator_)
    return handleOptionTriangleInterpolator(option);
  else
    return NULL;
}

/*
 * Option TriangleInterpolator defines how colors are interpolated
 * in triangles
 */
Option* ZBufferConfigurationHandler::handleOptionTriangleInterpolator(const Name& option)
{
  if (option == VALUETriangleInterpolator_Flat_) {
    TriangleInterpolatorOption* opt = new TriangleInterpolatorOption(new FlatTriangleInterpolator);
    return opt;
  } else if (option == VALUETriangleInterpolator_Gouraud_) {
    TriangleInterpolatorOption* opt = new TriangleInterpolatorOption(new GouraudTriangleInterpolator);
    return opt;
  } else if (option == VALUETriangleInterpolator_Phong_) {
    TriangleInterpolatorOption* opt = new TriangleInterpolatorOption(new PhongTriangleInterpolator);
    return opt;
  } else
    return NULL;
}


void ZBufferConfigurationHandler::initClass()
{
  Configuration::addHandler(new ZBufferConfigurationHandler);
}
