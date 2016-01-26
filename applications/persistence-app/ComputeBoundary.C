/*
 * $RCSfile: ComputeBoundary.C,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: ComputeBoundary.C,v 1.1 1996/10/09 14:11:48 collison Exp $
 * -----------------------------------------------------------------------------
 */


#include "ComputeBoundary.h"
#include "booga/base/ColorTypes.h"
#include "booga/base/PixmapOf.h"


int ComputeBoundary::ourDeltaX[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int ComputeBoundary::ourDeltaY[] = {0, 1, 1, 1, 0, -1, -1, -1};

//__________________________________________________________ ComputeBoundary

ComputeBoundary::ComputeBoundary() :
myBoundaryPoints()
{}

AbstractPixmap* ComputeBoundary::generate(const AbstractPixmap* pm)
{
  PixmapOf<BW>* newPm = new PixmapOf<BW>(pm->getResolutionX(), pm->getResolutionY());
  float c1, c2, c3;
  long size = pm->getSize();
  myBoundaryPoints.removeAll(); // remove points possibly previously used

  //
  // assume top left point has background color
  //
  pm->setPosition(0);
  pm->getColor(c1,c2,c3);
  Color backgroundColor(c1,c2,c3);
  Color testColor(0.,0.,0.);

  //
  // scan for first point
  //
  long p = 0;
  for (p = 0; p < size; p++) {
    pm->setPosition(p);
    pm->getColor(c1, c2, c3);
    testColor = Color(c1, c2, c3);
    if (testColor != backgroundColor) break;
  }
  
  int xstart = p%pm->getResolutionX();
  int ystart = p/pm->getResolutionX();
  int x = xstart;
  int y = ystart;
  int neighbourIndex = 0;

  do { // find next boundary point
    int testx;
    int testy;
    while (1) {
      // compute next neighbour point to be tested
      neighbourIndex = neighbourIndex%8;
      testx = x + ourDeltaX[neighbourIndex];
      testy = y + ourDeltaY[neighbourIndex];
      // is test position in range?
      if (0 <= testx && testx < pm->getResolutionX() &&
          0 <= testy && testy < pm->getResolutionY()) {
        pm->setPosition(testx, testy);
        pm->getColor(c1, c2, c3);
        testColor = Color(c1, c2, c3);
        if (testColor != backgroundColor) {
          x = testx; // found boundary point: now let current point be the new boundary point
          y = testy;
          neighbourIndex = neighbourIndex - neighbourIndex%1 + 6; // adjust for new pos
          newPm->setPosition(x, y); // mark boundary point in new pixmap
          newPm->setColor(true);
          myBoundaryPoints.append(Vector2D((Real)x, (Real)y));
          break; // break out of while forever
        }
      }
      neighbourIndex++; // goto next neighbour
    } // end of while forever
  } while(x != xstart || y != ystart); // until all boundary points of object found
  return newPm;
}

const List<Vector2D>& ComputeBoundary::getBoundaryPoints() const {
  return myBoundaryPoints;
}
