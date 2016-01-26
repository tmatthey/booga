/*
 * $RCSfile: Operation2D.C,v $
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
 *  $Id: Operation2D.C,v 1.5 1996/09/13 08:05:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/PreorderTraversal2D.h"
#include "booga/component/Operation2D.h"

//__________________________________________________________________ Operation2D

implementRTTI(Operation2D, Visitor);

Operation2D::Operation2D()
{
  adoptTraversal(new PreorderTraversal2D);
}
