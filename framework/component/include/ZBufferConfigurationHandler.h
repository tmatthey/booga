/*
 * ZBufferConfigurationHandler.h
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

#ifndef _ZBufferConfigurationHandler_H
#define _ZBufferConfigurationHandler_H

#include "booga/component/TriangleInterpolator.h"
#include "booga/component/FlatTriangleInterpolator.h"
#include "booga/component/GouraudTriangleInterpolator.h"
#include "booga/component/PhongTriangleInterpolator.h"
#include "booga/component/TriangleInterpolatorOption.h"
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/StaticInit.h"

//__________________________________________________ ZBufferConfigurationHandler

class ZBufferConfigurationHandler : public ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option);
  // ZBuffer is a rendering component

protected:
  virtual Option* handleOptionTriangleInterpolator(const Name& option);
  // Option TriangleInterpolator defines how colors are interpolated
  // in triangles

private:
  static const Name OPTIONTriangleInterpolator_;
  static const Name VALUETriangleInterpolator_Flat_;
  static const Name VALUETriangleInterpolator_Gouraud_;
  static const Name VALUETriangleInterpolator_Phong_;

public:
  static void initClass();
  // enable initialization of static members
};

//___________________ ensure initialization of class ZBufferConfigurationHandler

declareInitStatics(ZBufferConfigurationHandler);

#endif // _ZBufferConfigurationHandler_H
