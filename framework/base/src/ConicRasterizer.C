/*
 * ConicRasterizer.C
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
 *  $Id: ConicRasterizer.C,v 1.2 1995/08/14 09:21:10 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h> // abs() function
#include "booga/base/ConicRasterizer.h"
#include "booga/base/mathutilities.h"
#include "booga/base/Report.h"

//______________________________________________________________ ConicRasterizer
//
// Reference:
//
// Foley et. al, Computer Graphics, Principles and Practice, 2nd edition, 
// p.958ff, Addison-Wesley, 1990.
// 
// Implementation adapted from a K&R C version written 
// by Nick Chart <ngc@metronet.com>.

static int DX_SQUARE[] = {1,  0,  0, -1, -1,  0,  0,  1};
static int DY_SQUARE[] = {0,  1,  1,  0,  0, -1, -1,  0};
static int DX_DIAG[]   = {1,  1, -1, -1, -1, -1,  1,  1};
static int DY_DIAG[]   = {1,  1,  1,  1, -1, -1, -1, -1};

/*
 * Use gradient to identify the octant.
 */
static int getOctant(int gx, int gy)
{
  if (gx > 0)
    if (gy < 0)
      if (gx < -gy) 
	return 1;
      else 
	return 2;
    else
      if (gx > gy) 
	return 3;
      else 
	return 4;
  else
    if (gy > 0)
      if (-gx < gy) 
	return 5;
      else 
	return 6;
    else
      if (-gx > -gy) 
	return 7;
      else 
	return 8;
}

ConicRasterizer::ConicRasterizer()
{
  myCurrentLabel = -1;
  myIsDoneFlag = true;
}

void ConicRasterizer::init(int centerX, int centerY, 
			   int startX, int startY, int endX, int endY, 
			   int A, int B, int C, int D, int E, int F)
{
  myCenterX = centerX; myCenterY = centerY;
  myStartX  = startX;  myStartY  = startY;
  myEndX    = endX;    myEndY    = endY;
  myA = A; myB = B; myC = C; myD = D; myE = E; myF = F;

  octant = getOctant(myD, myE); // starting octant number

  switch (octant) {
    case 1 : d = myA + myB/2 + myC/4 + myD + myE/2 + myF;
             u = myA + myB/2 + myD;
	     v = myA + myB/2 + myD + myE;
	     k1 = 2*myA;
	     k2 = 2*myA + myB;
	     k3 = 2*myA + 2*myB + 2*myC;
	     break;
    case 2 : d = myA/4 + myB/2 + myC + myD/2 + myE + myF;
             u = myB/2 + myC + myE;
	     v = myB/2 + myC + myD + myE;
	     k1 = 2*myC;
	     k2 = myB + 2*myC;
	     k3 = 2*myA + 2*myB + 2*myC;
	     break;
    case 3 : d = myA/4 - myB/2 + myC - myD/2 + myE + myF;
             u = -myB/2 + myC + myE;
	     v = -myB/2 + myC - myD + myE;
	     k1 = 2*myC;
	     k2 = -myB + 2*myC;
	     k3 = 2*myA - 2*myB + 2*myC;
	     break;
    case 4 : d = myA - myB/2 + myC/4 - myD + myE/2 + myF;
             u = myA - myB/2 - myD;
	     v = myA - myB/2 - myD + myE;
	     k1 = 2*myA;
	     k2 = 2*myA - myB;
	     k3 = 2*myA - 2*myB + 2*myC;
	     break;
    case 5 : d = myA + myB/2 + myC/4 - myD - myE/2 + myF;
             u = myA + myB/2 - myD;
	     v = myA + myB/2 - myD - myE;
	     k1 = 2*myA;
	     k2 = 2*myA + myB;
	     k3 = 2*myA + 2*myB + 2*myC;
	     break;
    case 6 : d = myA/4 + myB/2 + myC - myD/2 - myE + myF;
             u = myB/2 + myC - myE;
             v = myB/2 + myC - myD - myE;
	     k1 = 2*myC;
	     k2 = myB + 2*myC;
	     k3 = 2*myA + 2*myB + 2*myC;
	     break;
    case 7 : d = myA/4 - myB/2 + myC + myD/2 - myE + myF;
             u = -myB/2 + myC - myE;
	     v = -myB/2 + myC + myD - myE;
	     k1 = 2*myC;
	     k2 = -myB + 2*myC;
	     k3 = 2*myA - 2*myB + 2*myC;
	     break;
    case 8 : d = myA - myB/2 + myC/4 + myD - myE/2 + myF;
             u = myA - myB/2 + myD;
	     v = myA - myB/2 + myD - myE;
	     k1 = 2*myA;
	     k2 = 2*myA - myB;
	     k3 = 2*myA - 2*myB + 2*myC;
	     break;
  }

  dxSquare = DX_SQUARE[octant-1];
  dySquare = DY_SQUARE[octant-1];
  dxDiag   = DX_DIAG[octant-1];
  dyDiag   = DY_DIAG[octant-1];
  
  // Translate to origin 
  myCurrentX = myEndX - myStartX; myCurrentY = myEndY - myStartY;
  
  // Gradient at end point
  int dSdx = 2*myA*myCurrentX + myB*myCurrentY + myD; 
  int dSdy = myB*myCurrentX + 2*C*myCurrentY + myE;

  // Determine ending octant
  octantCount = getOctant(dSdx, dSdy) - octant;
  if (octantCount <= 0) 
    octantCount += 8;

  myCurrentX = myStartX; myCurrentY = myStartY;
  myCurrentLabel = -1;
  myIsDoneFlag = false;
}

void ConicRasterizer::next()
{
  if (myIsDoneFlag == true)
    return;

  switch (myCurrentLabel) {
    case 1: goto LABEL_1;
    case 2: goto LABEL_2;
    case 3: goto LABEL_3;
    case 4: goto LABEL_4;
    default: break;
  }

  while (octantCount > 0) {
    if (octant & 1) { // octant is odd 
      while (2*v <= k2) {
	myCurrentLabel = 1; return;

LABEL_1: //----------------------------------

	if (d < 0) {
	  myCurrentX += dxSquare;
	  myCurrentY += dySquare;
	  u += k1;
	  v += k2;
	  d += u;
	}
	else {
	  myCurrentX += dxDiag;
	  myCurrentY += dyDiag;
	  u += k2;
	  v += k3;
	  d += v;
	}
      }

      //
      // We now cross the diagonal octant boundary.
      //
//      d = d - u - v/2 - k2/2 + 3*k3/8;
      d = d - u + v/2 - k2/2 + 3*k3/8;

      u = -u + v - k2/2 + k3/2;
      v = v - k2 + k3/2;
      k1 = k1 - 2*k2 + k3;
      k2 = k3 - k2;

      int tmp = dxSquare; dxSquare = -dySquare; dySquare = tmp;
    }
    else { // octant is even
      while (2*u < k2) {
	myCurrentLabel = 2; return;

LABEL_2: //----------------------------------

	if (d < 0) {
	  myCurrentX += dxDiag;
	  myCurrentY += dyDiag;
	  u += k2;
	  v += k3;
	  d += v;
	}
	else {
	  myCurrentX += dxSquare;
	  myCurrentY += dySquare;
	  u += k1;
	  v += k2;
	  d += u;
	}
      }

      //
      // We now cross the square octant boundary.
      //
      d = d + u - v + k1 - k2;
      v = 2*u - v + k1 - k2;
      u = u + k1 - k2;
      k3 = 4*(k1 - k2) + k3;
      k2 = 2*k1 - k2;

      int tmp = dxDiag; dxDiag = -dyDiag; dyDiag = tmp;
    }

    if (++octant > 8) 
      octant -= 8;
    octantCount--;
  }

  //
  // Having started the last octant, continue until final point is reached.
  //
  myStepCount = abs(dxSquare ? (myCurrentX - myEndX) : (myCurrentY - myEndY));

  while (myStepCount--) {
    if (octant & 1) { // octant is odd 
	myCurrentLabel = 3; return;

LABEL_3: //----------------------------------

      if (d < 0) {
	myCurrentX += dxSquare;
	myCurrentY += dySquare;
	u += k1;
	v += k2;
	d += u;
      }
      else {
	myCurrentX += dxDiag;
	myCurrentY += dyDiag;
	u += k2;
	v += k3;
	d += v;
      }
    }
    else { // octant is even 
	myCurrentLabel = 4; return;

LABEL_4: //----------------------------------

      if (d < 0) {
	myCurrentX += dxDiag;
	myCurrentY += dyDiag;
	u += k2;
	v += k3;
	d += v;
      }
      else {
	myCurrentX += dxSquare;
	myCurrentY += dySquare;
	u += k1;
	v += k2;
	d += u;
      }
    }
  }

  myIsDoneFlag = true;
}

void ConicRasterizer::initCircle(int centerX, int centerY, int radius)
{
  initEllipse(centerX, centerY, centerX+radius, centerY, centerX, centerY+radius);
}

void ConicRasterizer::initEllipse(int centerX, int centerY, 
				  int xp, int yp, int xq, int yq, 
				  bool isFullEllipse)
{
  int xprod, xe, ye, A, B, C, D, E, F;

  xp -= centerX; yp -= centerY;
  xq -= centerX; yq -= centerY;
  xprod = xp * yq - xq * yp;

  if (xprod != 0) {  // if points are not co-linear 
    if (xprod < 0) {
      swap(xp, xq);
      swap(yp, yq);
      xprod = -xprod;
    }

    A = yp * yp + yq * yq;
    B = -2 * (xp * yp + xq * yq);
    C = xp * xp + xq * xq;
    D = 2 * yq * xprod;
    E = -2 * xq * xprod;
    F = 0;

    if (isFullEllipse == true) {
      xe = xp;
      ye = yp;
    }
    else { // only draw from P to Q 
      xe = xq;
      ye = yq;
    }

    init(centerX, centerY, xp, yp, xe, ye, A, B, C, D, E, F);
  }
  else {
    Report::warning("[ConicRasterizer::initEllipse] points are colinear");
    myIsDoneFlag = true;
  }
}
