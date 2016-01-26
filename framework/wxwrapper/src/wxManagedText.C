/*
 * $RCSfile: wxManagedText.C,v $
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
 *  $Id: wxManagedText.C,v 1.2 1997/09/19 08:42:13 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/Report.h" 
#include "booga/wxwrapper/wxManagedText.h"

//_____________________________________________________________________ wxManagedText

//implementRTTI(NewClass, BaseClass);
wxManagedText::wxManagedText(wxDialogDirector* director, wxPanel* parent, char* label,
    char *value, int x, int y, int width, int height, long style, char* name) : wxText (parent, 
    (wxFunction) wxManagedTextCallback, label, value, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedText::wxManagedText] NULL DialogDirector passed!");

}
// define button callback function:
void wxManagedTextCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedText* text = (wxManagedText*) object;
  
  text->getDirector()->widgetCallbackFunction(text, event);
}

