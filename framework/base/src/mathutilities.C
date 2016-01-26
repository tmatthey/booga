/*
 * mathutilities.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
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
 * ---------------------------------------------------------------------
 *  $Id: mathutilities.C,v 1.5 1995/10/27 12:17:53 streit Exp $
 * ---------------------------------------------------------------------
 */

#include "booga/base/mathutilities.h"

//_______________________________________________________________ Solve Equations


/* epsilon surrounding for near zero values */

#define     EQN_EPS     1e-9
#define	   IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

int solveQuadric(double c[3], double s[2])
{
  double p, q, D;

  // Normal form: x^2 + px + q = 0 

  p = c[ 1 ] / (2 * c[ 2 ]);
  q = c[ 0 ] / c[ 2 ];

  D = p * p - q;

  if (IsZero(D)) {
    s[ 0 ] = - p;
    return 1;
  }
  else if (D < 0) {
    return 0;
  }
  else { // (D > 0)
    double sqrt_D = sqrt(D);

    s[ 0 ] =   sqrt_D - p;
    s[ 1 ] = - sqrt_D - p;
    return 2;
  }
}


int solveCubic(double c[4], double s[3])
{
  int     i, num;
  double  sub;
  double  A, B, C;
  double  sq_A, p, q;
  double  cb_p, D;

  // Normal form: x^3 + Ax^2 + Bx + C = 0

  A = c[ 2 ] / c[ 3 ];
  B = c[ 1 ] / c[ 3 ];
  C = c[ 0 ] / c[ 3 ];

  //  Substitute x = y - A/3 to eliminate quadric term:
  //	x^3 +px + q = 0

  sq_A = A * A;
  p = 1.0/3 * (- 1.0/3 * sq_A + B);
  q = 1.0/2 * (2.0/27 * A * sq_A - 1.0/3 * A * B + C);

  // Use Cardano's formula

  cb_p = p * p * p;
  D = q * q + cb_p;

  if (IsZero(D)) {
    if (IsZero(q)) { // One triple solution
      s[ 0 ] = 0;
      num = 1;
    }
    else { // One single and one double solution
      double u = cbrt(-q);
      s[ 0 ] = 2 * u;
      s[ 1 ] = - u;
      num = 2;
    }
  }
  else if (D < 0) { // Casus irreducibilis: three real solutions
    double phi = 1.0/3 * acos(-q / sqrt(-cb_p));
    double t = 2 * sqrt(-p);

    s[ 0 ] =   t * cos(phi);
    s[ 1 ] = - t * cos(phi + M_PI / 3);
    s[ 2 ] = - t * cos(phi - M_PI / 3);
    num = 3;
  }
  else { // One real solution
    double sqrt_D = sqrt(D);
    double u = cbrt(sqrt_D - q);
    double v = - cbrt(sqrt_D + q);

    s[ 0 ] = u + v;
    num = 1;
  }

  // Resubstitute 

  sub = 1.0/3 * A;

  for (i = 0; i < num; ++i)
    s[ i ] -= sub;

  return num;
}


int solveQuartic(double c[5], double s[4])
{
  double  coeffs[ 4 ];
  double  z, u, v, sub;
  double  A, B, C, D;
  double  sq_A, p, q, r;
  int     i, num;

  // Normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 

  A = c[ 3 ] / c[ 4 ];
  B = c[ 2 ] / c[ 4 ];
  C = c[ 1 ] / c[ 4 ];
  D = c[ 0 ] / c[ 4 ];

  // Substitute x = y - A/4 to eliminate cubic term:
  //	x^4 + px^2 + qx + r = 0

  sq_A = A * A;
  p = - 3.0/8 * sq_A + B;
  q = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
  r = - 3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

  if (IsZero(r)) {
    // No absolute term: y(y^3 + py + q) = 0 */

    coeffs[ 0 ] = q;
    coeffs[ 1 ] = p;
    coeffs[ 2 ] = 0;
    coeffs[ 3 ] = 1;

    num = solveCubic(coeffs, s);

    s[ num++ ] = 0;
  }
  else {
    // Solve the resolvent cubic ... */

    coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
    coeffs[ 1 ] = - r;
    coeffs[ 2 ] = - 1.0/2 * p;
    coeffs[ 3 ] = 1;

    (void) solveCubic(coeffs, s);

    // ... and take the one real solution ...

    z = s[ 0 ];

    // ... to build two quadric equations

    u = z * z - r;
    v = 2 * z - p;

    if (IsZero(u))
      u = 0;
    else if (u > 0)
      u = sqrt(u);
    else
      return 0;

    if (IsZero(v))
      v = 0;
    else if (v > 0)
      v = sqrt(v);
    else
       return 0;

    coeffs[ 0 ] = z - u;
    coeffs[ 1 ] = q < 0 ? -v : v;
    coeffs[ 2 ] = 1;

    num = solveQuadric(coeffs, s);

    coeffs[ 0 ]= z + u;
    coeffs[ 1 ] = q < 0 ? v : -v;
    coeffs[ 2 ] = 1;

    num += solveQuadric(coeffs, s + num);
  }

  // Resubstitute

  sub = 1.0/4 * A;

  for (i = 0; i < num; ++i)
    s[ i ] -= sub;

  return num;
}

//_________________________________________________________________________ MISC

/*
 * Copied from lsys by Jonathan P. Leech.
 *
 * Computes sine and cosine of angle similar to the 
 * sincos(double, double*, double*) function. Checkes if
 * the results are close to -1, 0, 1 and rounds 
 * appropriately.
 */
void sincos(Real alpha, Real& sinAlpha, Real& cosAlpha)
{
  sinAlpha = sin(alpha);
  cosAlpha = cos(alpha);

  if (cosAlpha > 1-EPSILON) {
    cosAlpha = 1.; sinAlpha = 0.;
  }
  else if (cosAlpha < -1+EPSILON) {
    cosAlpha = -1.; sinAlpha = 0.;
  }

  if (sinAlpha > 1-EPSILON) {
    cosAlpha = 0.; sinAlpha = 1.;
  }
  else if (sinAlpha < -1+EPSILON) {
    cosAlpha = 0.; sinAlpha = -1.;
  }
}




