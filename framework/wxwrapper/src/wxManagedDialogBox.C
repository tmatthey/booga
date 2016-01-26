/*
 * wxManagedDialogBox.C 
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
 *  $Id: wxManagedDialogBox.C,v 1.3 1997/12/12 13:33:27 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedDialogBox.h"

//_____________________________________________________________________ wxManagedDialogBox

wxManagedDialogBox::wxManagedDialogBox(wxDialogDirector* director, wxWindow* parent, 
  char* title, bool modal, int x, int y, int width, int height, long style, char* name)
  : wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedDialogBox::wxManagedDialogBox] NULL DialogDirector passed!");
}


Bool wxManagedDialogBox::OnClose()
{
  wxDialogDirector::ActionRequest val = myDirector->widgetOnClose(this);

  // Non-default action: 
  // 1. delete director (it's up to him not to delete *this;
  //    otherwise you'll get a segmentation fault.
  // 2. return true (==> *this will be deleted too)
  if (val == wxDialogDirector::NO_DEFAULT_ACTION) {
    return true;
  }

  // by default, OnClose() returns false
  return false;
}


void wxManagedDialogBox::OnPaint()
{
  if (myDirector->widgetOnPaint(this) == wxDialogDirector::DEFAULT_ACTION)
    wxDialogBox::OnPaint();
}


void wxManagedDialogBox::OnSize(int width, int height)
{
  if (myDirector->widgetOnSize(this, width, height) == wxDialogDirector::DEFAULT_ACTION)
    wxDialogBox::OnSize(width, height);
}


