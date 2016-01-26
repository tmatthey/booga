/*
 * $RCSfile: ZBuffer.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: ZBuffer.C,v 1.32 1996/09/13 08:07:05 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Statistic.h"
#include "booga/base/Configuration.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Camera3D.h"
#include "booga/component/TriangleInterpolatorOption.h"
#include "booga/component/FlatTriangleInterpolator.h"
#include "booga/component/ZBuffer.h"

//______________________________________________________________________ ZBuffer

implementRTTI(ZBuffer, PixmapRenderer);

ZBuffer::ZBuffer()
{
  //
  // Get default interpolator type from configuration database.
  //
  getConfigurationOption(TriangleInterpolatorOption, interpolOption, "ZBuffer.TriangleInterpolator");
  if (interpolOption != NULL)
    myTriangleInterpolator = interpolOption->getInterpolator()->copy();
  else
    myTriangleInterpolator = new FlatTriangleInterpolator();
}

ZBuffer::~ZBuffer()
{
  delete myTriangleInterpolator;
}

void ZBuffer::adoptTriangleInterpolator(TriangleInterpolator* triangleInterpolator)
{
  if (myTriangleInterpolator != triangleInterpolator) {
    delete myTriangleInterpolator;
    myTriangleInterpolator = triangleInterpolator;
  }
}

bool ZBuffer::doExecute()
{
  // initialize pixmap
  myPixmap->clearDepth(MAXFLOAT);
  myPixmap->clearAlpha(0);
  Color bg = getCamera()->getBackground();
  myPixmap->clearColor(bg[0], bg[1], bg[2]);
  
  // initialize interpolator
  myTriangleInterpolator->setTraversal(getTraversal());
  myTriangleInterpolator->setViewing(getCamera()->getViewing());
  myTriangleInterpolator->setWorld(getWorld());
  myTriangleInterpolator->setDefaultColor(Color::getDefault());
  myTriangleInterpolator->setAmbientLightSources(getAmbientLightSources());
  myTriangleInterpolator->setDirectedLightSources(getDirectedLightSources());
    
  return traverse(getWorld());
}

Traversal::Result ZBuffer::visit(Triangle3D* obj)
{
  //
  // Some statistics
  //
  Statistic::addEntry("ZBuffer: Number of triangles", 1.0);
  
  
  // variables for use in loop:
  int scPointX=0, scPointY=0;
  Real depth=MAXREAL;
  float curDepth=0;
  Color color;

  //
  // Draw pixels while rasterization is not finished
  //
  for (myTriangleInterpolator->init(obj); 
       !myTriangleInterpolator->isDone(); 
       myTriangleInterpolator->next()) {
    myTriangleInterpolator->getSCPoint(scPointX, scPointY, depth);
    myPixmap->setPosition(scPointX, scPointY);
    myPixmap->getDepth(curDepth);

    if (depth < curDepth) {
      myTriangleInterpolator->getColor(color);
      myPixmap->setDepth(depth);
      myPixmap->setAlpha(1);
      myPixmap->setColor(color.getRed(), color.getGreen(), color.getBlue());
    }
  }  

  return Traversal::CONTINUE;
}

Traversal::Result ZBuffer::dispatch(Makeable* obj)
{
  tryConcrete(Triangle3D, obj);
  
  //
  // Create decomposition for objects other than triangles.
  //
  return Traversal::UNKNOWN;
}
