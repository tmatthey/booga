/*
 * GSBwxRadioBox.C 
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
 *  $Id: GSBwxRadioBox.C,v 1.4 1997/04/08 11:05:33 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxRadioBox.h"

//_____________________________________________________________________ GSBwxRadioBox

//implementRTTI(GSBwxRadioBox, wxRadioBox);

GSBwxRadioBox::GSBwxRadioBox(GSBwxDialogDirector* director, wxPanel* parent, char* label,
  int x, int y, int width, int height, int n, char* choices[], int majorDim, 
  long style, char* name)
: wxRadioBox(parent, (wxFunction) GSBwxRadioBoxCallback, label, x, y, width, height,
  n, choices, majorDim, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxRadioBox::GSBwxRadioBox] NULL DialogDirector passed!");
}


// define button callback function:
void GSBwxRadioBoxCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  GSBwxRadioBox* slider = (GSBwxRadioBox*) object;
  
  slider->getDirector()->widgetCallbackFunction(slider, event);
}


