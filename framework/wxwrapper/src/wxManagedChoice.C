/*
 * wxManagedChoice.C 
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
 *  $Id: wxManagedChoice.C,v 1.2 1997/09/19 08:42:02 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedChoice.h"

//_____________________________________________________________________ wxManagedChoice

//implementRTTI(wxManagedChoice, wxChoice);
wxManagedChoice::wxManagedChoice(wxDialogDirector* director, wxPanel* parent, char* label,
  int x, int y, int width, int height, int n, char* choices[], long style, char* name)
: wxChoice(parent, (wxFunction) wxManagedChoiceCallback, label, x, y, width, height,
  n, choices, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedChoice::wxManagedChoice] NULL DialogDirector passed!");
}


// define choice callback function:
void wxManagedChoiceCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedChoice* choice = (wxManagedChoice*) object;
  
  choice->getDirector()->widgetCallbackFunction(choice, event);
}



