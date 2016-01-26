/*
 * wxManagedSlider.C 
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
 *  $Id: wxManagedSlider.C,v 1.2 1997/09/19 08:42:11 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedSlider.h"

//_____________________________________________________________________ wxManagedSlider

implementRTTI(wxManagedSlider, wxSlider);


wxManagedSlider::wxManagedSlider(wxDialogDirector* director, wxPanel* parent, char* label, 
  int value, int min_value, int max_value, int width, int x, int y, long style, char* name)
: wxSlider(parent, (wxFunction) wxManagedSliderCallback, label, value, min_value,
    max_value, width, x, y, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedSlider::wxManagedSlider] NULL DialogDirector passed!");
}


// define button callback function:
void wxManagedSliderCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedSlider* slider = (wxManagedSlider*) object;
  
  slider->getDirector()->widgetCallbackFunction(slider, event);
}

