/*
 * LineRasterizer.h
 *
 * Implementation of a line rasterizer using the bresenham 
 * integer DDA algorithm.
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
 *  $Id: LineRasterizer.h,v 1.5 1995/06/20 10:33:49 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _LineRasterizer_H
# define _LineRasterizer_H

#include "booga/base/PrimitiveTypes.h"

//_______________________________________________________________ LineRasterizer

class LineRasterizer {
public:
  LineRasterizer();

  // LineRasterizer(const LineRasterizer& );           // Use default version.
  // ~LineRasterizer();                                // Use default version.
  // LineRasterizer& operator=(const LineRasterizer&); // Use defualt version.

  void init(int fromX, int fromY, int toX, int toY);
  void next();
  bool isDone() const;
  void getPixel(int& x, int& y) const;
  // 
  // Usage:
  //
  // LineRasterizer lr;
  // int x, y;
  //
  // for (lr.init(fromX, fromY, toX, toY); !lr.isDone(); lr.next()) {
  //   lr.getPixel(x, y);
  //   setPixel(x, y, ...);
  // }

private:
  int myCurrentX, myCurrentY;
  int myDeltaX, myDeltaY;
  int myS1, myS2;
  int myError;
  int myStepsToPerform;
  bool myInterchanged;
};

inline bool LineRasterizer::isDone() const
{
  return (myStepsToPerform >= 0) ? false : true;
}

inline void LineRasterizer::getPixel(int& x, int& y) const
{
  x = myCurrentX;
  y = myCurrentY;
}

#endif // _LineRasterizer_H
