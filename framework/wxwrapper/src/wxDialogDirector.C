/*
 * $RCSfile: wxDialogDirector.C,v $ 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
 *                     Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxDialogDirector.C,v 1.1 1996/09/27 11:45:53 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxDialogDirector

implementRTTIBase(wxDialogDirector);


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnChar(wxObject*, wxKeyEvent&)
{
  return DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnClose(wxObject* )
{
  return DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnEvent(wxObject*, wxMouseEvent&)
{
  return DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnMenuCommand(wxObject*, int)
{
  return DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnPaint(wxObject*)
{
  return DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest wxDialogDirector::widgetOnSize(wxObject*, int, int)
{
  return DEFAULT_ACTION;
}



