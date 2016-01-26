/*
 * $RCSfile: Boundary2D.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 * -----------------------------------------------------------------------------
 *  $Id: Boundary2D.C,v 1.2 1997/01/17 09:46:22 matthey Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"  // swap()
#include "booga/base/Geometry2D.h"
#include "booga/object/Polygon2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Texture2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Transform2D.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/component/Collector2DFor.h"
#include "booga/pixmapOp/ComputeBoundary.h"
#include "booga/component/Boundary2D.h"


//_________________________________________________________________ Boundary2D

implementRTTI(Boundary2D, Operation2D);

Boundary2D::Boundary2D(long maxVertex, double precision) :
myMaxVertex(maxVertex),
myPrecision(precision)
{
  myBoundaryTexture = NULL;
}

Boundary2D::~Boundary2D()
{
  if (myBoundaryTexture != NULL)
    delete myBoundaryTexture;
}

void Boundary2D::adoptTexture(Texture2D* boundaryTexture)
{
  if (boundaryTexture == NULL) {
    Report::warning("[Boundary2D::adoptTexture] NULL pointer passed");
    return;
  }

  if (myBoundaryTexture != NULL && myBoundaryTexture != boundaryTexture)
    delete myBoundaryTexture;

  myBoundaryTexture = boundaryTexture;
}

bool Boundary2D::doExecute()
{
  //
  // Collect all Point2D objects in the world.
  //
  Collector2DFor<Pixmap2D> pixmapCollector;
  ComputeBoundary boundaryComputer;
  int i;
  pixmapCollector.execute(getWorld());
  for (pixmapCollector.first(), i=0; !pixmapCollector.isDone(); pixmapCollector.next(), i++) {
    AbstractPixmap* boundaryPM = 
      boundaryComputer.generate(pixmapCollector.getObject()->getPixmap());
    delete boundaryPM; // we do not need the pixmap
    Polygon2D* boundary = new Polygon2D(Geometry2D::approximatePolygon(
           boundaryComputer.getBoundaryPoints(),
           myMaxVertex,
           myPrecision));
    if (myBoundaryTexture != NULL) {
      boundary->appendTexture(myBoundaryTexture->copy());
    }
    Path2D* path = pixmapCollector.getPath();
    path->last();
    path->prev();
    Aggregate2D* agg = NULL;
    agg = dynamic_cast<Aggregate2D*>(path->getObject());
    if (agg != NULL) {
      boundary->setTransform(pixmapCollector.getObject()->getTransform());
      agg->adoptObject(boundary);
    }
    else {
      getWorld()->getObjects()->adoptObject(boundary);
    }
  }
  getWorld()->getObjects()->computeBounds();
  
  return true;
}
