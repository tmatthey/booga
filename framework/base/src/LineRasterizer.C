/*
 * LineRasterizer.C
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: LineRasterizer.C,v 1.3 1995/06/20 10:33:39 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h>   // abs(int) function 
#include "booga/base/mathutilities.h"
#include "booga/base/LineRasterizer.h"

//_______________________________________________________________ LineRasterizer
//
// Reference:
//
// D.F. Rogers, Procedural Elements for Computer Graphics, p.40, McGraw-Hill
//

LineRasterizer::LineRasterizer()
{
  myCurrentX = myCurrentY = 0;
  myDeltaX = myDeltaY = 0;
  myS1 = myS2 = 0;
  myError = 0;
  myStepsToPerform = 0;
  myInterchanged = false;
}

void LineRasterizer::init(int fromX, int fromY, int toX, int toY)
{
  myCurrentX = fromX; 
  myCurrentY = fromY;

  myDeltaX = abs(toX - fromX);
  myDeltaY = abs(toY - fromY);

  myS1 = sign(toX - fromX);
  myS2 = sign(toY - fromY);

  if (myDeltaY > myDeltaX) {
    swap(myDeltaX, myDeltaY);
    myInterchanged = true;
  }
  else
    myInterchanged = false;

  // Initialize the error term to compensate for a nonzero intercept and
  // the number of steps to be performed by the next() method.
  //
  myError = 2*myDeltaY - myDeltaX;
  myStepsToPerform = myDeltaX;
}

void LineRasterizer::next()
{
  if (isDone())
    return;

  // Rogers p.41: error >= 0 !!
  while (myError > 0) {
    if (myInterchanged)
      myCurrentX += myS1;
    else
      myCurrentY += myS2;

    myError -= 2*myDeltaX;
  }

  if (myInterchanged)
    myCurrentY += myS2;
  else
    myCurrentX += myS1;

  myError += 2*myDeltaY;

  myStepsToPerform--;
}  
