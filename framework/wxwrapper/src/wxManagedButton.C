/*
 * wxManagedButton.C 
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
 *  $Id: wxManagedButton.C,v 1.2 1997/09/19 08:41:59 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedButton.h"

//_____________________________________________________________________ wxManagedButton

//implementRTTI(wxManagedButton, wxButton);


wxManagedButton::wxManagedButton(wxDialogDirector* director, wxPanel* parent, char* label, 
  int x, int y, int width, int height, long style, char* name)
: wxButton(parent, (wxFunction) wxManagedButtonCallback, label, x, y, 
    width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedButton::wxManagedButton] NULL DialogDirector passed!");
}


// define button callback function:
void wxManagedButtonCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedButton* button = (wxManagedButton*) object;
  
  button->getDirector()->widgetCallbackFunction(button, event);
}
