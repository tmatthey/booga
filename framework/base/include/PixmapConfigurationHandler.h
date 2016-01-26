/*
 * PixmapConfigurationHandler.h
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

#ifndef _PixmapConfigurationHandler_H
#define _PixmapConfigurationHandler_H

#include "booga/base/PixmapOf.h"
#include "booga/base/ValueOption.h"
#include "booga/base/PixmapOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//___________________________________________________ PixmapConfigurationHandler

class PixmapConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);
  // Pixmap implements base funcionality for all pixmaps

protected:
  virtual Option* handleOptionType(const Name& option);
  // Option Type declares which color model to use for pixmaps
  virtual Option* handleOptionResX(const Name& option);
  // Option ResX defines X resolution for pixmap
  virtual Option* handleOptionResY(const Name& option);
  // Option ResY defines Y resolution for pixmap

private:
  static const Name OPTIONType_;
  static const Name VALUEType_RGB_;
  static const Name VALUEType_RGBChar_;
  static const Name VALUEType_Grey_;
  static const Name VALUEType_BW_;
  static const Name OPTIONResX_;
  static const Name OPTIONResY_;

public:
  static void initClass();
  // enable initialization of static members
};

//____________________ ensure initialization of class PixmapConfigurationHandler

declareInitStatics(PixmapConfigurationHandler);

#endif // _PixmapConfigurationHandler_H
