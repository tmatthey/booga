/*
 * GSBwxSlider.C 
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
 *  $Id: GSBwxSlider.C,v 1.4 1997/04/08 11:05:35 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxSlider.h"

//_____________________________________________________________________ GSBwxSlider

//implementRTTI(GSBwxSlider, wxSlider);


GSBwxSlider::GSBwxSlider(GSBwxDialogDirector* director, wxPanel* parent, char* label, 
  int value, int min_value, int max_value, int width, int x, int y, long style, char* name)
: wxSlider(parent, (wxFunction) GSBwxSliderCallback, label, value, min_value,
    max_value, width, x, y, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxSlider::GSBwxSlider] NULL DialogDirector passed!");
}


// define button callback function:
void GSBwxSliderCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  GSBwxSlider* slider = (GSBwxSlider*) object;
  
  slider->getDirector()->widgetCallbackFunction(slider, event);
}

