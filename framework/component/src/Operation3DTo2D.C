/*
 * $RCSfile: Operation3DTo2D.C,v $
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
 *  $Id: Operation3DTo2D.C,v 1.5 1996/09/13 08:05:26 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/PreorderTraversal3D.h"
#include "booga/component/Operation3DTo2D.h"

//______________________________________________________________ Operation3DTo2D

implementRTTI(Operation3DTo2D, Visitor);

Operation3DTo2D::Operation3DTo2D()
{
  adoptTraversal(new PreorderTraversal3D);
}
