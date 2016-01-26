/*
 * $RCSfile: Operation3D.C,v $
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
 *  $Id: Operation3D.C,v 1.5 1996/09/13 08:05:24 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/PreorderTraversal3D.h"
#include "booga/component/Operation3D.h"

//__________________________________________________________________ Operation3D

implementRTTI(Operation3D, Visitor);

Operation3D::Operation3D()
{
  adoptTraversal(new PreorderTraversal3D);
}
