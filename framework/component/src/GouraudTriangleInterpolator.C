/*
 * GouraudTriangleInterpolator.C 
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
 *  $Id: GouraudTriangleInterpolator.C,v 1.1 1996/09/13 08:04:38 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Texture3D.h"
#include "booga/component/GouraudTriangleInterpolator.h"

//__________________________________________________ GouraudTriangleInterpolator

TriangleInterpolator* GouraudTriangleInterpolator::copy() const
{
  return new GouraudTriangleInterpolator(*this);
}

void GouraudTriangleInterpolator::getColor(Color& color)
{
  color = lerp(myStartColor, myEndColor, equal(myAx2,0) ? 0 : (float)(myAx1/myAx2));
}

void GouraudTriangleInterpolator::doInit(int)
{
  //
  // compute color in vertices of triangle
  //
  for (int i=0; i<3; i++) {
    myTextureContext.setOCS2WCS(myTraversal->getPath()->getLastTransform());
    myTextureContext.setPositionOCS(myOCPoints[i]);
    myTextureContext.setNormalOCS(myOCNormals[i]);
    myTextureContext.setColor(getDefaultColor());
  
    Texture3D::texturing(myTextureContext, (Path3D*)myTraversal->getPath());
  
    myColor[i] = myTextureContext.getColor();
  }
}

void GouraudTriangleInterpolator::doComputeScanLine(Real startFactor, Real endFactor)
{
  myStartColor = lerp(myColor[myStartVertex[myLeftEdge]],
                      myColor[myEndVertex[myLeftEdge]],(float)startFactor);
  myEndColor   = lerp(myColor[myStartVertex[myRightEdge]],
                      myColor[myEndVertex[myRightEdge]],(float)endFactor);
}


