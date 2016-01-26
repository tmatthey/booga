/*
 * $RCSfile: TriangleInterpolator.C,v $ 
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
 *  $Id: TriangleInterpolator.C,v 1.1 1996/09/13 08:06:38 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <math.h>

#include "booga/object/Viewing3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/TriangleInterpolator.h"

enum blabla { lerpX, lerpY } test = lerpY;

#include <sstream>
Real mylerp(Real a, Real b, Real k)
{ 
  if (k<0 || k>1) {
    std::stringstream os;
    os << "[lerp] : k out of range: " << k;
    if (test == lerpX)
      os << " in X";
    else
      os << " in Y";
    Report::warning(os); 
  }
  
  return a-(a-b)*k; 
} 

Vector3D mylerp(Vector3D a, Vector3D b, Real k)
{ 
  if (k<0 || k>1) {
    std::stringstream os;
    os << "[lerp] : k out of range: " << k;
    if (test == lerpX)
      os << " in X";
    else
      os << " in Y";
    Report::warning(os); 
  }
  
  return a-(a-b)*k; 
} 

//_________________________________________________________ TriangleInterpolator

TriangleInterpolator::TriangleInterpolator()
{
  myDefaultColor = Color::getDefault();
  myIsDone = false;
}

// We need it, even if it is empty!
TriangleInterpolator::~TriangleInterpolator()
{}

void TriangleInterpolator::setViewing(Viewing3D* viewing)
{
  myViewing = viewing;
  mySizeX = myViewing->getResolutionX();
  mySizeY = myViewing->getResolutionY();
  myTextureContext.setIncidencePosition(myViewing->getEye());
}

/*
 * The whole initialization phase is really very, *VERY*
 * large and awesome!
 * No way, we have to go through it... :-(
 */
void TriangleInterpolator::init(Triangle3D* triangle)
{
  // 
  // Is everything set?
  // 
  if (myTraversal == NULL) {
    Report::warning("[TriangleInterpolator::init] : call setTraversal first");
    myIsDone = true;
    return;
  }
  if (myViewing == NULL) {
    Report::warning("[TriangleInterpolator::init] : call setViewing first");
    myIsDone = true;
    return;
  }

  // 
  // Some Initialization
  //
  myCurTriangle = triangle;
  Transform3D transform = myTraversal->getPath()->getLastTransform();
  register int i;
  
  //
  // Apply Transformation to triangle and transform to view coordinate system
  //
  Vector3D wcPoint;
  for (i=0; i<3; i++) {
    myOCPoints[i]   = triangle->getVertex(i);
    myOCNormals[i]  = triangle->getNormal(i);
    wcPoint         = transform.transformAsPoint(myOCPoints[i]);
    myViewPoints[i] = myViewing->transformWorld2View(wcPoint);
  }                               

  //
  // Front plane clipping (z<EPSILON)
  //
  // If one point of triangle is behind the camera, forget the whole triangle
  //
  if (myViewPoints[0].z() < EPSILON || 
      myViewPoints[1].z() < EPSILON || 
      myViewPoints[2].z() < EPSILON) {
    myIsDone = true;
    return;
  }
  
  //
  // Transform to screen coordinate system
  //
  for (i=0; i<3; i++) {
    myNSCPoints[i] = myViewing->transformView2NormalScreen(myViewPoints[i]);
    mySCPoints[i]  = myViewing->transformNormalScreen2Screen(myNSCPoints[i]);
    mySCPoints[i].x() += 0.5;
    mySCPoints[i].y() += 0.5;
  }
  
  // 
  // Sort Points: origin is lower left corner of screen, sort points
  //              by descending y and ascending x coordinate.
  //
  //
  // index 0 should contain points with maximal y value on screen
  if (mySCPoints[0][1] < mySCPoints[1][1]) 
    swapPoints(0,1);
  if (mySCPoints[0][1] < mySCPoints[2][1]) 
    swapPoints(0,2);
  // index 2 should contain points with minimal y value on screen
  if (mySCPoints[1][1] < mySCPoints[2][1]) 
    swapPoints(1,2);
  // if y values of first two points are equal index 0 should 
  // have minimal x value
  if (floor(mySCPoints[0][1]) == floor(mySCPoints[1][1]) &&
      mySCPoints[0][0] > mySCPoints[1][0]) 
    swapPoints(0,1);
  // if y values of last two points are equal index 2 should 
  // have maximal x value
  else if (floor(mySCPoints[1][1]) == floor(mySCPoints[2][1]) &&
      mySCPoints[2][0] < mySCPoints[1][0]) 
    swapPoints(2,1);
  
  //
  // Perform clipping of whole (sorted) triangle
  //
  int minX, maxX;
  minmax(minX, maxX, 
         (int)mySCPoints[0].x(), 
         (int)mySCPoints[1].x(), 
         (int)mySCPoints[2].x());
  if ((int)mySCPoints[0].y() < 0 ||        // too low
      (int)mySCPoints[2].y() >= mySizeY || // too high
      minX >= mySizeX ||                   // too right
      maxX < 0) {                          // too left
    myIsDone = true;
    return;
  }
   
  //
  // Test for degenerated triangle in screen coordinate system
  //
  if ((((int)mySCPoints[0].x() == (int)mySCPoints[1].x()) &&
       ((int)mySCPoints[0].y() == (int)mySCPoints[1].y())) ||
      (((int)mySCPoints[1].x() == (int)mySCPoints[2].x()) &&
       ((int)mySCPoints[1].y() == (int)mySCPoints[2].y())) ||
      (((int)mySCPoints[0].x() == (int)mySCPoints[2].x()) &&
       ((int)mySCPoints[0].y() == (int)mySCPoints[2].y()))) {
    myIsDone = true;
    return;
  }

  // 
  // Initialize edges
  //
  myStartVertex[0] = 0; myEndVertex[0] = 1;
  myStartVertex[1] = 1; myEndVertex[1] = 2;
  myStartVertex[2] = 0; myEndVertex[2] = 2;
  
  //
  // Compute deltas
  //
  Real denom, dy, invDenom, fraction;
  unsigned char startV, endV;
  for (i=0; i<3; i++) {
    startV = myStartVertex[i];
    endV   = myEndVertex[i];
    
    // How many scan lines ?
    denom = mySCPoints[endV].y()-mySCPoints[startV].y();

    if (equal(denom, 0)) {
      myDeltaNSCX[i] = 0;    // delta x per scanline
      dy = 0;                // delta y (NSC) per scanline
    } else {
      invDenom = 1/denom;
      // delta x per scanline
      myDeltaNSCX[i] = (myNSCPoints[endV].x()-myNSCPoints[startV].x())*invDenom;
    
      // delta y (NSC) per scanline
      dy = (myNSCPoints[endV].y()-myNSCPoints[startV].y())*invDenom;
    }
    
    myDy1[i] = dy*myViewPoints[startV].z();
    myDy2[i] = dy*(myViewPoints[endV].z()-myViewPoints[startV].z());
    
    fraction = frac(mySCPoints[startV].y());         
    myAy1[i] = -fraction*myDy1[i];
    myAy2[i] = myViewPoints[endV].y() - myViewPoints[startV].y() - 
               myNSCPoints[endV].y()*(myViewPoints[endV].z()-myViewPoints[startV].z()) -
               fraction*myDy2[i];
  }

  // 
  // Where to change the deltas?
  //
  // Which vertex will be visited first?
  const bool firstPoint = floor(mySCPoints[0].y()) == floor(mySCPoints[1].y());
  myChangeDelta = firstPoint ? MAXINT : (int)floor(mySCPoints[1].y());
  myLastVertex  = (int)floor(mySCPoints[2].y());
  
  // 
  // Check for orientation of projected triangle
  //
  myOrientation = ((mySCPoints[0].x()-mySCPoints[1].x()) *
                   (mySCPoints[0].y()-mySCPoints[2].y()) -
                   (mySCPoints[0].x()-mySCPoints[2].x()) *
                   (mySCPoints[0].y()-mySCPoints[1].y())) < 0 ? 
                  CLOCKWISE : COUNTERCLOCKWISE;
  
  //
  // Determine left and right delta, depending on orientation
  //
  if (myOrientation == CLOCKWISE) {
    myLeftEdge  = 2;
    myRightEdge = firstPoint;  
  } else {
    myLeftEdge  = 0;
    myRightEdge = 2;
  }
  
  //
  // Set termination flag to false (not finished)
  //
  myIsDone = false;
  
  //
  // Initialize specialized TriangleInterpolator
  //
  doInit(firstPoint);
  
  // 
  // Compute screen coordinates of first scan line
  //
  mySCY = (int)floor(mySCPoints[myStartVertex[myLeftEdge]].y());
  myStartNSCX = myNSCPoints[myStartVertex[myLeftEdge]].x();
  myEndNSCX   = myNSCPoints[myStartVertex[myRightEdge]].x();
  
  //
  // Compute delta on scanline
  //
  computeScanLine();
  
  //
  // Advance while not in window
  //
  if (!myIsDone && 
      (mySCX<0 || mySCX>=mySizeX || mySCY<0 || mySCY>=mySizeY))
    next();
} // Don't scream, I told you, it's gonna be hard !!

bool TriangleInterpolator::isDone() const 
{
  return myIsDone;
}

/*
 * Advance to next valid pixel in triangle on screen
 */
void TriangleInterpolator::next()
{
  // 
  // Advance on current scan line
  //
  do 
    if (!nextPoint())
      nextScanLine();
  while (!myIsDone && 
         (mySCX<0 || mySCX>=mySizeX || mySCY<0 || mySCY>=mySizeY));
}
     
void TriangleInterpolator::getSCPoint(int& x, int& y, Real& z) const
{
  x = mySCX;
  y = mySCY;
  test = lerpX;
  // Report::warning("TriangleInterpolator::getSCPoint");
  z = mylerp(myStartZ, myEndZ, equal(myAx2,0) ? 0 : myAx1/myAx2);
  test= lerpY;
}

void TriangleInterpolator::getOCPoint(Vector3D& point) const
{
  test = lerpX;
  // Report::warning("TriangleInterpolator::getOCPoint");
  point = mylerp(myStartOCPoint, myEndOCPoint, equal(myAx2,0) ? 0 : myAx1/myAx2);
  test = lerpY;
}

void TriangleInterpolator::swapPoints(int i, int j)
{
  swap(mySCPoints[i], mySCPoints[j]);
  swap(myNSCPoints[i], myNSCPoints[j]);
  swap(myViewPoints[i], myViewPoints[j]);
  swap(myOCPoints[i], myOCPoints[j]);
  swap(myOCNormals[i], myOCNormals[j]);
}

/*
 * Advance to next valid scanline:
 * - compute new deltas
 * - change deltas in midpoint
 * - test, if triangle is finished
 * - ensure, that actual scan line is in screen
 */
void TriangleInterpolator::nextScanLine()
{
  // Not yet in window?
  do {
    mySCY--;
    myStartNSCX -= myDeltaNSCX[myLeftEdge];
    myEndNSCX   -= myDeltaNSCX[myRightEdge];

    // Have we reached the last vertex or the end of the viewport?
    if (mySCY <= myLastVertex || mySCY<0) { 
      myIsDone = true; 
      return; 
    }

    myAy1[myLeftEdge]  -=  myDy1[myLeftEdge];
    myAy2[myLeftEdge]  -=  myDy2[myLeftEdge];
    myAy1[myRightEdge] -=  myDy1[myRightEdge];
    myAy2[myRightEdge] -=  myDy2[myRightEdge];
    
    // Have we reached the middle vertex?
    if (mySCY == myChangeDelta) { // has to be == !
      if (myOrientation == CLOCKWISE) { // Change end point of scan line
        myRightEdge = 1;
        myEndNSCX = myNSCPoints[myStartVertex[myRightEdge]].x();
      } else {                          // change start point of scan line
        myLeftEdge = 1;
        myStartNSCX = myNSCPoints[myStartVertex[myLeftEdge]].x();
      }
    } 

    // Initialize new Scanline
    computeScanLine();
    
  } while (mySCY>=mySizeY);
}

/*
 * Advance to next valid point
 * - ensure point is on screen
 * - returns false, if scan line is finished or end of screen reached
 */
bool TriangleInterpolator::nextPoint()
{
  do {
    myAx1 +=  myDx1;
    myAx2 +=  myDx2;

    mySCX++;
  } while (mySCX<0 && mySCX<=myEndSCX);
  
  if (mySCX>myEndSCX || mySCX>=mySizeX)
    return false;
  else
    return true;
}

void TriangleInterpolator::computeScanLine()
{
  //
  // Determine start and end points of scan line in
  // screen and object coordinate system.
  //
  const Real scX    = myViewing->transformNormalScreen2ScreenX(myStartNSCX);
  const Real endSCX = myViewing->transformNormalScreen2ScreenX(myEndNSCX);
  mySCX    = (int)floor(scX);
  myEndSCX = (int)floor(endSCX);
  
  //
  // Compute factors for interpolating new start and end points
  // of scan line.
  //
  const Real startFactor = equal(myAy2[myLeftEdge],0)  ? 0 : myAy1[myLeftEdge]/myAy2[myLeftEdge];
  const Real endFactor   = equal(myAy2[myRightEdge],0) ? 0 : myAy1[myRightEdge]/myAy2[myRightEdge];
  
  const unsigned char sLV = myStartVertex[myLeftEdge];  // start vertex of left edge
  const unsigned char eLV = myEndVertex[myLeftEdge];    // end vertex of left edge 
  const unsigned char sRV = myStartVertex[myRightEdge]; // start vertex of right edge
  const unsigned char eRV = myEndVertex[myRightEdge];   // end vertex of right edge
  
  myStartZ = mylerp(myViewPoints[sLV].z(), myViewPoints[eLV].z(), startFactor);
  myEndZ   = mylerp(myViewPoints[sRV].z(), myViewPoints[eRV].z(), endFactor);

  myStartOCPoint = mylerp(myOCPoints[sLV], myOCPoints[eLV], startFactor);
  myEndOCPoint   = mylerp(myOCPoints[sRV], myOCPoints[eRV], endFactor);
  
  //
  // Compute specialized parameters for start and end point of scan line.
  //
  doComputeScanLine(startFactor, endFactor);

  //
  // Compute deltas for increment on scan line
  //
  const Real startX = mylerp(myViewPoints[sLV].x(), myViewPoints[eLV].x(), startFactor);
  const Real endX   = mylerp(myViewPoints[sRV].x(), myViewPoints[eRV].x(), endFactor);
  const Real dx = equal(endSCX,scX) ? 0 : (myEndNSCX-myStartNSCX)/(endSCX-scX);
  const Real fraction = frac(scX);                    
  myDx1 = dx * myStartZ;
  myDx2 = dx * (myEndZ-myStartZ);
  myAx1 = fraction*myDx1;
  myAx2 = endX-startX - myStartNSCX*(myEndZ-myStartZ) + fraction*myDx2;
}
