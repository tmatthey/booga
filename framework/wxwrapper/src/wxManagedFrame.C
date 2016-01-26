/*
 * wxManagedFrame.C 
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
 *  $Id: wxManagedFrame.C,v 1.3 1997/12/12 13:38:00 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "booga/wxwrapper/wxManagedFrame.h"

//_____________________________________________________________________ wxManagedFrame


wxManagedFrame::wxManagedFrame(wxDialogDirector* director, wxFrame* parent, 
  char* title, int x, int y, int width, int height, long style, char* name)
  : wxFrame(parent, title, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedFrame::wxManagedFrame] NULL DialogDirector passed!");
}


Bool wxManagedFrame::OnClose()
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


void wxManagedFrame::OnMenuCommand(int id)
{
  myDirector->widgetOnMenuCommand(this, id);
}


void wxManagedFrame::OnSize(int width, int height)
{
  if (myDirector->widgetOnSize(this, width, height) == wxDialogDirector::DEFAULT_ACTION)
    wxFrame::OnSize(width, height);
}

