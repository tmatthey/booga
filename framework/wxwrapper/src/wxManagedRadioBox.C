/*
 * wxManagedRadioBox.C 
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
 *  $Id: wxManagedRadioBox.C,v 1.2 1997/09/19 08:42:10 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedRadioBox.h"

//_____________________________________________________________________ wxManagedRadioBox

//implementRTTI(wxManagedRadioBox, wxRadioBox);

wxManagedRadioBox::wxManagedRadioBox(wxDialogDirector* director, wxPanel* parent, char* label,
  int x, int y, int width, int height, int n, char* choices[], int majorDim, 
  long style, char* name)
: wxRadioBox(parent, (wxFunction) wxManagedRadioBoxCallback, label, x, y, width, height,
  n, choices, majorDim, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedRadioBox::wxManagedRadioBox] NULL DialogDirector passed!");
}


// define button callback function:
void wxManagedRadioBoxCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedRadioBox* slider = (wxManagedRadioBox*) object;
  
  slider->getDirector()->widgetCallbackFunction(slider, event);
}


