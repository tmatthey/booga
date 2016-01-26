/*
 * PhongTriangleInterpolator.C 
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: PhongTriangleInterpolator.C,v 1.1 1996/09/13 08:05:30 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Triangle3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/PhongTriangleInterpolator.h"

//____________________________________________________ PhongTriangleInterpolator

TriangleInterpolator* PhongTriangleInterpolator::copy() const
{
  return new PhongTriangleInterpolator(*this);
}

void PhongTriangleInterpolator::getColor(Color& color)
{
  Vector3D point;
  getOCPoint(point);
  
  myTextureContext.setOCS2WCS(myTraversal->getPath()->getLastTransform());
  myTextureContext.setPositionOCS(point);
  myTextureContext.setNormalOCS(lerp(myStartNormal, 
                                     myEndNormal, 
                                     equal(myAx2,0) ? 0 : myAx1/myAx2));
  myTextureContext.setColor(getDefaultColor());
 
  Texture3D::texturing(myTextureContext, (Path3D*)myTraversal->getPath());
  
  color = myTextureContext.getColor();
}

void PhongTriangleInterpolator::doInit(int) {}

void PhongTriangleInterpolator::doComputeScanLine(Real startFactor, Real endFactor)
{
  myStartNormal = lerp(myOCNormals[myStartVertex[myLeftEdge]],
                       myOCNormals[myEndVertex[myLeftEdge]], startFactor);
  myEndNormal   = lerp(myOCNormals[myStartVertex[myRightEdge]],
                       myOCNormals[myEndVertex[myRightEdge]], endFactor);
}
