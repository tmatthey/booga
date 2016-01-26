/*
 * PrimitiveTypes.h
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
 *  $Id: PrimitiveTypes.h,v 1.8 1998/01/05 09:50:00 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PrimitiveTypes_H
#define _PrimitiveTypes_H



#ifdef WIN32
#include <limits.h>

#define bool int
#define true 1
#define false 0

#define M_PI 3.14159265358979323846f
#define M_SQRT1_2   0.707106781186547524400844362104849039
#define M_LN2 0.693147180559945309417232121458176568
#define MAXDOUBLE 1.7976931348623157e+308 
#define MAXFLOAT 1.7976931348623157e+308 
#define MAXINT INT_MAX
#define STDOUT_FILENO 1

// cubic root
#define cbrt(a) pow(a,1/3.0)

#else

#include <values.h> // MAXFLOAT, MAXDOUBLES, ...
#endif

//_______________________________________________________________________ Switch
// Whenever a switch is needed
//
enum Switch { ON, OFF };

//_________________________________________________________________________ Real
// Choose the appropriate Real representation.
//

typedef double Real;
const Real MAXREAL =  MAXDOUBLE;
const Real MINREAL = -MAXDOUBLE;

// typedef float Real;
// const Real MAXREAL =  MAXFLOAT;
// const Real MINREAL = -MAXFLOAT;

const Real EPSILON = 0.00001;

//_________________________________________________________________________ bool

#ifndef __GNUC__
#ifndef WIN32 

//typedef int bool;

//const bool true  = 1;
//const bool false = 0;

#endif
#endif

#endif // _PrimitiveTypes_H
