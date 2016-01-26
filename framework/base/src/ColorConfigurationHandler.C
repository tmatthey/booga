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

#include "booga/base/ColorConfigurationHandler.h"

//____________________________________________________ ColorConfigurationHandler

implementInitStatics(ColorConfigurationHandler);

const Name ColorConfigurationHandler::OPTIONDefault_("Color.Default");

Option* ColorConfigurationHandler::handleOption(const Name& name, const Name& option)
{
  if (name == OPTIONDefault_)
    return handleOptionDefault(option);
  else
    return NULL;
}

/*
 * Default Color for Textures, Pixels, ...
 */
Option* ColorConfigurationHandler::handleOptionDefault(const Name& option)
{
  istrstream iss(((const RCString&)option).chars());
  Color col;
  iss >> col;
  return new ColorOption(col);
}

void ColorConfigurationHandler::initClass()
{
  Configuration::addHandler(new ColorConfigurationHandler);
}
