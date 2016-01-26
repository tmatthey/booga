/*
 * GSBView.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBView.C,v 1.5 1997/04/08 11:05:06 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBView.h"

//_____________________________________________________________________ GSBView

implementRTTIBase(GSBView);


GSBView::GSBView(World3D* world, RCString& viewIDStr)
: myWorld(world), 
  myViewIDStr(viewIDStr)
{}
