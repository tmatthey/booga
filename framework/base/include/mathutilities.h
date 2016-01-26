/*
 * mathutilities.h 
 *
 * Some mathematical functions.
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
 *  $Id: mathutilities.h,v 1.14 1997/09/19 07:14:19 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MathUtilities_H
# define _MathUtilities_H

#include <math.h>
#include "booga/base/PrimitiveTypes.h"

//__________________________________________________________ Radians <-> Degrees

inline Real dtor(Real degree) 
{ 
  return degree*M_PI/180.0; 
}

inline Real rtod(Real rad)
{ 
  return rad*180.0/M_PI; 
}

//_________________________________________________ Tolerant comparision of Real

inline int equal(Real a, Real b) 
{ 
  return fabs(a-b) < EPSILON; 
}

inline int equal(Real a, Real b, Real epsilon) 
{ 
  return fabs(a-b) < epsilon; 
}

//_____________________________________________________________________ MIN, MAX

#ifndef min
template <class T> 
inline T min(T a, T b)
{ 
  return ((a < b) ? a : b); 
}

template <class T> 
inline T min(T a, T b, T c)
{ 
  return ((a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c));
}
#endif

#ifndef max
template <class T> 
inline T max(T a, T b)  
{ 
  return ((a > b) ? a : b); 
}

template <class T> 
inline T max(T a, T b, T c)
{ 
  return ((a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c));
}
#endif

template <class T> 
inline void minmax(T& min, T& max, T a, T b)
{
  if (a<b) {
    min = a;
    max = b;  
  } else {
    min = b;
    max = a;
  }
}

template <class T> 
inline void minmax(T& min, T& max, T a, T b, T c)
{
  if (a<b) {
    if (b<c) {
      min = a; max = c;
    } else { // b>=c 
      max = b; min = (a<c) ? a : c;
    }
  } else {   // a>=b
    if (b>c) {
      min = c; max = a;
    } else { // b<=c
      min = b; max = (a<c) ? c: a;
    }
  }
}

//_________________________________________________________________________ LERP

template <class T>
inline T lerp(T a, T b, float k)
{
  return a+(a+b)*k;
}

template <class T>
inline T lerp(T a, T b, double k)
{
  return a+(a+b)*k;
}

//_______________________________________________________________ Solve Equations
//
//  Solve quartic equation:
//
//                     4        3        2
//                c * x  + c * x  + c * x  + c * x + c  = 0
//                 4        3        2        1       0

//
// The functions return the number of non-complex roots of the quartic with
// coefficients c[] and put the values into the s array.
// 
// Graphics Gem I, p.741
extern int solveQuadric(double c[3], double s[2]);
extern int solveCubic  (double c[4], double s[3]);
extern int solveQuartic(double c[5], double s[4]);

//_________________________________________________________________________ MISC

template <class T>
inline T sqr(T a)
{
  return a*a;
}

template <class T> 
inline void swap(T& a, T& b) 
{ 
  T tmp = a; a = b; b = tmp; 
}

/*
 * Compute tolerant sin and cos values from angle 'alpha' (radians)
 */
extern void sincos(Real alpha, Real& sinAlpha, Real& cosAlpha);

template <class T> 
inline int sign(T a) 
{
  if (a < 0)
    return -1;
  else if (a > 0)
    return 1;
  else
    return 0;
}
 
inline int sign(Real a)
{
  if (a < -EPSILON)
    return -1;
  else if (a > EPSILON)
    return 1;
  else
    return 0;
}

inline Real frac(Real a)
{
  if (a < 0)
    return a + floor(-a); 
  else
    return a - floor(a); 
}

#ifdef WIN32
#include <stdlib.h>
inline int rint(Real a)
{
  return (int)a;	
}

inline Real drand48()
{
  int r = rand();
  return (Real)r/(Real)RAND_MAX;
}

inline void srand48(long r)
{
  srand(r);
}

#endif

#endif // _MathUtilities_H
