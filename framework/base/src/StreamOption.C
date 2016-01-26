/*
 * StreamOption.C
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: StreamOption.C,v 1.4 1995/10/18 10:09:18 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream.h>   
#include "booga/base/StreamOption.h"

implementRTTI(StreamOption, Option);

Option* StreamOption::copy() const
{
  return new StreamOption(*this);
}
