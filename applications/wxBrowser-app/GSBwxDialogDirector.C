/*
 * GSBwxDialogDirector.C 
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
 *  $Id: GSBwxDialogDirector.C,v 1.5 1997/04/08 11:05:25 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxDialogDirector.h"

//_____________________________________________________________________ GSBwxDialogDirector

implementRTTIBase(GSBwxDialogDirector);


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnChar(wxObject*, wxKeyEvent&)
{
  return DEFAULT_ACTION;
}


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnClose(wxObject* )
{
  return DEFAULT_ACTION;
}


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnEvent(wxObject*, wxMouseEvent&)
{
  return DEFAULT_ACTION;
}


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnMenuCommand(wxObject*, int)
{
  return DEFAULT_ACTION;
}


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnPaint(wxObject*)
{
  return DEFAULT_ACTION;
}


GSBwxDialogDirector::ActionRequest GSBwxDialogDirector::widgetOnSize(wxObject*, int, int)
{
  return DEFAULT_ACTION;
}



