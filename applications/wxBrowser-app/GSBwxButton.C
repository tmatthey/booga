/*
 * GSBwxButton.C 
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
 *  $Id: GSBwxButton.C,v 1.4 1997/04/08 11:05:12 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxButton.h"

//_____________________________________________________________________ GSBwxButton

implementRTTI(GSBwxButton, wxButton);


GSBwxButton::GSBwxButton(GSBwxDialogDirector* director, wxPanel* parent, char* label, 
  int x, int y, int width, int height, long style, char* name)
: wxButton(parent, (wxFunction) GSBwxButtonCallback, label, x, y, 
    width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxButton::GSBwxButton] NULL DialogDirector passed!");
}


// define button callback function:
void GSBwxButtonCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  GSBwxButton* button = (GSBwxButton*) object;
  
  button->getDirector()->widgetCallbackFunction(button, event);
}
