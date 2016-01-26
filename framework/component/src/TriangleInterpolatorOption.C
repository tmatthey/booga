/*
 * TriangleInterpolatorOption.C 
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
 *  $Id: TriangleInterpolatorOption.C,v 1.1 1996/09/13 08:06:44 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/component/TriangleInterpolatorOption.h"
#include "booga/component/TriangleInterpolator.h"

//___________________________________________________ TriangleInterpolatorOption

implementRTTI(TriangleInterpolatorOption, Option);

TriangleInterpolatorOption::TriangleInterpolatorOption(const TriangleInterpolatorOption& option)
{
  if (option.myInterpolator == NULL)
    myInterpolator = NULL;
  else
    myInterpolator = option.myInterpolator->copy();
}

TriangleInterpolatorOption::TriangleInterpolatorOption(TriangleInterpolator* adoptInterpolator)
{
  myInterpolator = adoptInterpolator;
}

TriangleInterpolatorOption::~TriangleInterpolatorOption()
{
  delete myInterpolator;
}

Option* TriangleInterpolatorOption::copy() const
{
  return new TriangleInterpolatorOption(*this);
}
