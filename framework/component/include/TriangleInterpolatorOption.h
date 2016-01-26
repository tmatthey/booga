/*
 * TriangleInterpolatorOption.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: TriangleInterpolatorOption.h,v 1.1 1996/09/13 08:06:45 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TriangleInterpolatorOption_H
#define _TriangleInterpolatorOption_H

#include "booga/base/Option.h"

class TriangleInterpolator;

//___________________________________________________ TriangleInterpolatorOption

class TriangleInterpolatorOption : public Option {
declareRTTI(TriangleInterpolatorOption);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TriangleInterpolatorOption(TriangleInterpolator* adoptInterpolator);
  TriangleInterpolatorOption(const TriangleInterpolatorOption& option);      

public:
  virtual ~TriangleInterpolatorOption();

private:
  // No assignments.
  TriangleInterpolatorOption& operator=(const TriangleInterpolatorOption&);	  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TriangleInterpolatorOption
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const TriangleInterpolator* getInterpolator() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Option
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Option* copy() const;
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TriangleInterpolator* myInterpolator;
};

inline const TriangleInterpolator* 
TriangleInterpolatorOption::getInterpolator() const
{
  return myInterpolator;
}

#endif // _TriangleInterpolatorOption_H

