/*
 * $RCSfile: Copy3D.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Copy3D.C,v 1.5 1996/08/01 11:59:39 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/base/Report.h"
#include "booga/component/Copy3D.h"

//_______________________________________________________________________ Copy3D

implementRTTI(Copy3D, Operation3D);

bool Copy3D::doExecute()
{
  adoptResult(dynamic_cast(World3D, getWorld()->copy()));
  
  return true;
}
