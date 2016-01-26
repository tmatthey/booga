/*
 * wxViewCommand.C 
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxViewCommand.C,v 1.3 1996/10/11 14:55:57 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/wxwrapper/wxViewCommand.h"

//_____________________________________________________________________ wxViewCommand

implementRTTIBase(wxViewCommand);

wxViewCommand::wxViewCommand(wxView3D *v)
{
  myView = v;
}

wxViewCommand::~wxViewCommand()
{}

