/*
 * FlatTriangleInterpolator.C 
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: FlatTriangleInterpolator.C,v 1.1 1996/09/13 08:04:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Texture3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/FlatTriangleInterpolator.h"

//_____________________________________________________ FlatTriangleInterpolator

TriangleInterpolator* FlatTriangleInterpolator::copy() const
{
  return new FlatTriangleInterpolator(*this);
}

void FlatTriangleInterpolator::getColor(Color& color)
{
  color = myColor;
}

void FlatTriangleInterpolator::doInit(int)
{
  myTextureContext.setOCS2WCS(myTraversal->getPath()->getLastTransform());
  myTextureContext.setPositionOCS((myOCPoints[0]+myOCPoints[1]+myOCPoints[2])/3);
  myTextureContext.setNormalOCS((myOCNormals[0]+myOCNormals[1]+myOCNormals[2])/3);
  myTextureContext.setColor(getDefaultColor());
  
  Texture3D::texturing(myTextureContext, myTraversal->getPath());
  
  myColor = myTextureContext.getColor();
}

void FlatTriangleInterpolator::doComputeScanLine(Real, Real) {}
