/*
 * Function.C
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Function.C,v 1.3 1995/04/24 12:47:36 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include <math.h>
#include <stdlib.h>
#include "booga/object/Function.h"
#include "booga/object/ValueMakeable.h"

//_____________________________________________________________________ Function

implementRTTI(Function, Makeable);

//__________________________________________________________________ FunctionSin

implementRTTI(FunctionSin, Function);

Makeable* FunctionSin::make(RCString& errMsg, 
                            const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(sin(dtor(argument)));
}

//__________________________________________________________________ FunctionCos

implementRTTI(FunctionCos, Function);

Makeable* FunctionCos::make(RCString& errMsg, 
			    const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(cos(dtor(argument)));
}

//__________________________________________________________________ FunctionTan

implementRTTI(FunctionTan, Function);

Makeable* FunctionTan::make(RCString& errMsg, 
			    const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);

  return new ValueMakeable(tan(dtor(argument)));
}

//_________________________________________________________________ FunctionASin

implementRTTI(FunctionASin, Function);

Makeable* FunctionASin::make(RCString& errMsg, 
                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(rtod(asin(argument)));
}

//_________________________________________________________________ FunctionACos

implementRTTI(FunctionACos, Function);

Makeable* FunctionACos::make(RCString& errMsg, 
                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(rtod(acos(argument)));
}

//_________________________________________________________________ FunctionATan

implementRTTI(FunctionATan, Function);

Makeable* FunctionATan::make(RCString& errMsg, 
                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(rtod(atan(argument)));
}

//_________________________________________________________________ FunctionRand

implementRTTI(FunctionRand, Function);

Makeable* FunctionRand::make(RCString& errMsg, 
			     const List<Value*>* parameters) const
{
  checkParameterNumber(0);
  return new ValueMakeable(drand48());
}

//_________________________________________________________________ FunctionSqrt

implementRTTI(FunctionSqrt, Function);

Makeable* FunctionSqrt::make(RCString& errMsg, 
                             const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);

  if (argument < 0) {
    errMsg = "illegal root operation";
    return NULL;
  }

  return new ValueMakeable(sqrt(argument));
}

//__________________________________________________________________ FunctionPow

implementRTTI(FunctionPow, Function);

Makeable* FunctionPow::make(RCString& errMsg, 
                            const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, Real, base);
  getParameter(2, Real, exponent);
  return new ValueMakeable(pow(base, exponent));
}

//__________________________________________________________________ FunctionExp

implementRTTI(FunctionExp, Function);

Makeable* FunctionExp::make(RCString& errMsg, 
                            const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);
  return new ValueMakeable(exp(argument));
}

//__________________________________________________________________ FunctionLog

implementRTTI(FunctionLog, Function);

Makeable* FunctionLog::make(RCString& errMsg, 
                            const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);

  if (argument < 0) {
    errMsg = "argument for logarithm (10) function is < 0";
    return NULL;
  }

  return new ValueMakeable(log10(argument));
}

//___________________________________________________________________ FunctionLn

implementRTTI(FunctionLn, Function);

Makeable* FunctionLn::make(RCString& errMsg, 
                           const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, argument);

  if (argument < 0) {
    errMsg = "argument for logarithm (e) function is < 0";
    return NULL;
  }

  return new ValueMakeable(log(argument));
}

