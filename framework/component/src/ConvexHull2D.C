/*
 * $RCSfile: ConvexHull2D.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ConvexHull2D.C,v 1.6 1996/09/13 08:03:58 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"  // swap()
#include "booga/object/Point2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/List2D.h"
#include "booga/object/Texture2D.h"
#include "booga/component/Collector2DFor.h"
#include "booga/component/ConvexHull2D.h"

//___________________________________________________ Implementation Graham Scan

/*
 * Find the largest rectangle inside the convex hull of the point set and 
 * eliminate points that are inside this area.
 *
 * Input:
 *   P point set
 *   N number of points P[0]..P[N-1] in P
 *
 * Output:
 *   M = eliminate(P, N);
 *   P resulting point set
 *   M number of points after the eliminating process
 *
 * Reference:
 *   Analysis of a Simple Yet Efficient Convex Hull Algorithm
 *   Golin, Sedgewick, ACM 1988
 */ 
static int eliminate(Vector2D P[], int N)
{
  int i1, i2, i3, i4, j, numP;
  Real a1, a2, a3, a4;

  i1 = i2 = i3 = i4 = 1;
  a1 = a4 = P[0].x() + P[0].y();
  a2 = a3 = P[0].x() - P[0].y();

  for (j = 1; j<N; j++) {
    if ((P[j].x() + P[j].y()) < a1) {
      i1 = j; a1 = P[j].x() + P[j].y();
    }
    else if ((P[j].x() + P[j].y()) > a4) {
      i4 = j; a4 = P[j].x() + P[j].y();
    }

    if ((P[j].x() - P[j].y()) < a2) {
      i2 = j; a2 = P[j].x() - P[j].y();
    }
    else if ((P[j].x() - P[j].y()) > a3) {
      i3 = j; a3 = P[j].x() - P[j].y();
    }
  }

  Real lowX  = max(P[i1].x(), P[i2].x());
  Real highX = min(P[i3].x(), P[i4].x());
  Real lowY  = max(P[i1].y(), P[i3].y());
  Real highY = min(P[i2].y(), P[i4].y());
  
  numP = 0; j = N-1;

  while (j > numP)
    if ((lowX < P[j].x()) && (P[j].x() < highX) && 
	(lowY < P[j].y()) && (P[j].y() < highY))
      j--;
    else {
      numP++;
      swap(P[numP], P[j]);
    }

  return numP+1;
}

/*
 * Returns a number between 0 and 360 that is not the angle made by p1 and p2 
 * with the horizontal but which has the same order properties as that angle.
 * -> no trigonometric functions!
 *
 * Reference:
 *   Sedgewick, p. 353
 */
static double theta(const Vector2D& p1, const Vector2D& p2)
{
  Real dx, dy, ax, ay, t;

  dx = p2.x() - p1.x();  ax = fabs(dx);
  dy = p2.y() - p1.y();  ay = fabs(dy);
   
  if (equal(dx, 0) && equal(dy, 0))
    //
    // p1 and p2 are equal.
    //
    return 360.0; 
  else
    t = dy / (ax + ay);

  if (dx < 0) 
    t = 2.0 - t;
  else if (dy < 0) 
    t = 4.0 + t;

  return 90.0 * t;
}

/*
 * Finds the convex hull of the given points using the jarvis method 
 * (gift wrapping). Returns the number of points in the hull.
 *
 * Input:
 *  P array for N+1 points (P[N+1]).
 *  N number of points P[0]..P[N-1] in P
 * Output:
 *  hull = convex(P).
 *
 */
static void jarvisHull(Vector2D P[], int N,  List<Vector2D>& hull)
{
  int  M, i, min;
  Real angle, minAngle, smallestAngle;

  // 
  // Find the index of the point lowest and leftmost.
  //
  min = 0;
  for (i = 1; i<N; i = i+1)
    if (P[i].y() < P[min].y()) 
      min = i;

  //
  // P[min] is  N+1 - th element of the array.
  //
  M = -1; P[N] = P[min];  minAngle = 0.0;

  do {
    hull.append(P[min]);
    
    //
    // The element found doesn't have to be considered any longer.
    // Move it to the front of the array P.
    //
    M = M+1; 
    swap(P[min], P[M]);

    //
    // Looking for the smallest angle greater than 'smallestAngle' between
    // P[i] and the rear element of the hull ( hull.item(hull.count()-1) ).
    //
    min = N;  smallestAngle = minAngle;  minAngle = 360.0;
    for (i=M+1; i<=N; i = i+1) {
      angle = theta(hull.item(hull.count()-1), P[i]);
      if (angle >= smallestAngle && angle < minAngle) {
	min = i;
	minAngle = angle;
      }
    }
  } while ( min != N);
}

//_________________________________________________________________ ConvexHull2D

implementRTTI(ConvexHull2D, Operation2D);

ConvexHull2D::ConvexHull2D()
{
  myHullTexture = NULL;
}

ConvexHull2D::~ConvexHull2D()
{
  if (myHullTexture != NULL)
    delete myHullTexture;
}

void ConvexHull2D::adoptTexture(Texture2D* hullTexture)
{
  if (hullTexture == NULL) {
    Report::warning("[ConvexHull2D::adoptTexture] NULL pointer passed");
    return;
  }
    
  if (myHullTexture != NULL && myHullTexture != hullTexture)
    delete myHullTexture;

  myHullTexture = hullTexture;
}

bool ConvexHull2D::doExecute()
{
  //
  // Collect all Point2D objects in the world.
  //  
  Collector2DFor<Point2D> pointCollector;
  pointCollector.execute(getWorld());

  Vector2D* P = new Vector2D[pointCollector.count()+1];
  int i;
  
  for (pointCollector.first(), i=0; 
       !pointCollector.isDone();  
       pointCollector.next(), i++) {
    P[i] = Vector2D(pointCollector.getPath()->getLastTransform().transformAsPoint(
                      pointCollector.getObject()->getPosition()));
  }        
   
  //
  // Eliminate points inside the largest rectangle contained in the convex hull.
  //
  int M = eliminate(P, pointCollector.count());

  //
  // Compute the convex hull.
  //
  List<Vector2D> hull;
  jarvisHull(P, M, hull);

  delete [] P;

  //
  // Mark the computed hull by adding corresponding line segments and circles 
  // (to mark the points on the hull) to the world.
  //
  List2D* result = new List2D;
  for (i=0; i<hull.count()-1; i++) {
    result->adoptObject(new Line2D(hull.item(i), hull.item(i+1)));
    result->adoptObject(new Circle2D(hull.item(i), 0.01));
  }
  result->adoptObject(new Line2D(hull.item(hull.count()-1), hull.item(0)));
  result->adoptObject(new Circle2D(hull.item(hull.count()-1), 0.01));

  //
  // Add hull texure.
  //
  if (myHullTexture != NULL)
    result->appendTexture(myHullTexture->copy());
  
  getWorld()->getObjects()->adoptObject(result);  
  getWorld()->getObjects()->computeBounds();
  
  return true;
}
