/*
 * GSBNode.C 
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
 *  $Id: GSBNode.C,v 1.4 1997/04/08 11:04:46 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBNode.h"

//_____________________________________________________________________ GSBNode

implementRTTI(GSBNode, Option);

GSBNode::GSBNode(long viewID)
: myViewID(viewID)
{}

