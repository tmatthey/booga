/*
 * Nurbs3DParameters.C 
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Nurbs3DParameters.C,v 1.3 1996/01/12 16:06:26 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/Nurbs3DParameters.h"

//____________________________________________________________ Nurbs3DParameters

implementRTTIBase (Nurbs3DParameters);

Nurbs3DParameters::Nurbs3DParameters (void)
{
  myType = Nurbs3DTypes::None;
}

