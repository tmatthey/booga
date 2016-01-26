/*
 * $RCSfile: wxManagedListBox.C,v $
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
 *  $Id: wxManagedListBox.C,v 1.2 1997/09/19 08:42:09 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedListBox.h"

//_____________________________________________________________________ NewClass

//implementRTTI(NewClass, BaseClass);

wxManagedListBox::wxManagedListBox(wxDialogDirector* director, wxPanel *panel, char *Title,
  Bool Multiple, int x, int y, int width, int height, int N, char **Choices, long style,
  char *name) : wxListBox (panel, (wxFunction) wxManagedListBoxCallback, Title, Multiple, x, y,
  width, height, N, Choices, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedListBox::wxManagedListBox] NULL DialogDirector passed!");

}

// define button callback function:
void wxManagedListBoxCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  wxManagedListBox* listBox = (wxManagedListBox*) object;
  
  listBox->getDirector()->widgetCallbackFunction(listBox, event);
}
