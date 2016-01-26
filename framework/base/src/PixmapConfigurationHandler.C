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

#include "booga/base/PixmapConfigurationHandler.h"

//___________________________________________________ PixmapConfigurationHandler

implementInitStatics(PixmapConfigurationHandler);

const Name PixmapConfigurationHandler::OPTIONType_("Pixmap.Type");
const Name PixmapConfigurationHandler::VALUEType_RGB_("RGB");
const Name PixmapConfigurationHandler::VALUEType_RGBChar_("RGBChar");
const Name PixmapConfigurationHandler::VALUEType_Grey_("Grey");
const Name PixmapConfigurationHandler::VALUEType_BW_("BW");
const Name PixmapConfigurationHandler::OPTIONResX_("Pixmap.ResX");
const Name PixmapConfigurationHandler::OPTIONResY_("Pixmap.ResY");

/*
 * Pixmap implements base funcionality for all pixmaps
 */
Option* PixmapConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONType_)
    return handleOptionType(option);
  else if (name == OPTIONResX_)
    return handleOptionResX(option);
  else if (name == OPTIONResY_)
    return handleOptionResY(option);
  else
    return NULL;
}

/*
 * Option Type declares which color model to use for pixmaps
 */
Option* PixmapConfigurationHandler::handleOptionType(const Name& option)
{
  if (option == VALUEType_RGB_) {
    PixmapOption* pixiOpt = new PixmapOption(new PixmapOf<RGB>(1,1));
    return pixiOpt;
  } else if (option == VALUEType_RGBChar_) {
    PixmapOption* pixiOpt = new PixmapOption(new PixmapOf<RGBChar>(1,1));
    return pixiOpt;
  } else if (option == VALUEType_Grey_) {
    PixmapOption* pixiOpt = new PixmapOption(new PixmapOf<Grey>(1,1));
    return pixiOpt;
  } else if (option == VALUEType_BW_) {
    PixmapOption* pixiOpt = new PixmapOption(new PixmapOf<BW>(1,1));
    return pixiOpt;
  } else
    return NULL;
}

/*
 * Option ResX defines X resolution for pixmap
 */
Option* PixmapConfigurationHandler::handleOptionResX(const Name& option)
{
  return new ValueOption(Value(((const RCString&)option)));
}
/*
 * Option ResY defines Y resolution for pixmap
 */
Option* PixmapConfigurationHandler::handleOptionResY(const Name& option)
{
  return new ValueOption(Value(((const RCString&)option)));
}

void PixmapConfigurationHandler::initClass()
{
  Configuration::addHandler(new PixmapConfigurationHandler);
}
