/*
 * ColorConfigurationHandler.h
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

#ifndef _ColorConfigurationHandler_H
#define _ColorConfigurationHandler_H

#include <stdlib.h>
#include <strstream.h>
#include "booga/base/Color.h"
#include "booga/base/ColorOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//____________________________________________________ ColorConfigurationHandler

class ColorConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);

protected:
  virtual Option* handleOptionDefault(const Name& option);
  // Default Color for Textures, Pixels, ...

private:
  static const Name OPTIONDefault_;

public:
  static void initClass();
  // enable initialization of static members
};

//_____________________ ensure initialization of class ColorConfigurationHandler

declareInitStatics(ColorConfigurationHandler);

#endif // _ColorConfigurationHandler_H
