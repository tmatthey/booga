/*
 * ConicRasterizer.h
 *
 *  Bresenham like rasterizer for conics. 
 *  The conic is given by Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0.
 *  If the conic is a hyperbola, the points must lie on the same branch.
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
 *  $Id: ConicRasterizer.h,v 1.1 1995/06/19 12:54:07 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ConicRasterizer_H
# define _ConicRasterizer_H

#include "booga/base/PrimitiveTypes.h"

//______________________________________________________________ ConicRasterizer

class ConicRasterizer {
public:
  ConicRasterizer();

  // ConicRasterizer(const ConicRasterizer& );           // Use default version.
  // ~ConicRasterizer();                                 // Use default version.
  // ConicRasterizer& operator=(const ConicRasterizer&); // Use default version.

  void init(int centerX, int centerY, 
	    int startX, int startY, int endX, int endY, 
	    int A, int B, int C, int D, int E, int F);
  void next();
  bool isDone() const;
  void getPixel(int& x, int& y) const;
  // 
  // Usage:
  //
  // ConicRasterizer r;
  // int x, y;
  //
  // for (r.init(...); !r.isDone(); r.next()) {
  //   r.getPixel(x, y);
  //   setPixel(x, y, ...);
  // }

  void initCircle(int centerX, int centerY, int radius);
  //
  // Convenient initialisation fro circles.
  
  void initEllipse(int centerX, int centerY, 
		   int xp, int yp, int xq, int yq, 
		   bool isFullEllipse = true);
  //
  // Specify an ellipse in terms of the end points P=(xp, yp) and Q=(xq, yq) 
  // of two congugate diameters of the ellipse.
  // If the isFullEllipse flag is false, the ellipse will only be drawn from P to Q.

private:
  int myCurrentX, myCurrentY;       // Current point

  int myCenterX, myCenterY;
  int myStartX, myStartY;           // Starting point
  int myEndX, myEndY;               // Ending point
  int myA, myB, myC, myD, myE, myF; // Coefficients of the hyperbola

  int octant;                       // Current octant
  int octantCount;                  // Number of octants to be drawn
  int dxSquare, dySquare;           // Change in (x, y) for square moves
  int dxDiag, dyDiag;               // Change in (x, y) for diagonal moves
  int d, u, v, k1, k2, k3;          // Decision variables and increments

  int myCurrentLabel;
  int myStepCount;
  bool myIsDoneFlag;
};

inline bool ConicRasterizer::isDone() const
{
  return myIsDoneFlag;
}

inline void ConicRasterizer::getPixel(int& x, int& y) const
{
  x = myCurrentX + myCenterX;
  y = myCurrentY + myCenterY;
}

#endif // _ConicRasterizer_H
