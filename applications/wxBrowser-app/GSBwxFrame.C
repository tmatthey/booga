/*
 * GSBwxFrame.C 
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
 *  $Id: GSBwxFrame.C,v 1.5 1997/04/08 11:05:30 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxFrame.h"

//_____________________________________________________________________ GSBwxFrame


GSBwxFrame::GSBwxFrame(GSBwxDialogDirector* director, wxFrame* parent, 
  char* title, int x, int y, int width, int height, long style, char* name)
  : wxFrame(parent, title, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxFrame::GSBwxFrame] NULL DialogDirector passed!");
}


Bool GSBwxFrame::OnClose()
{
  GSBwxDialogDirector::ActionRequest val = myDirector->widgetOnClose(this);

  // Non-default action: 
  // 1. delete director (it's up to him not to delete *this;
  //    otherwise you'll get a segmentation fault.
  // 2. return true (==> *this will be deleted too)
  if (val == GSBwxDialogDirector::NO_DEFAULT_ACTION) {
    return True;
  }

  // by default, OnClose() returns false
  return False;
}


void GSBwxFrame::OnMenuCommand(int id)
{
  myDirector->widgetOnMenuCommand(this, id);
}


void GSBwxFrame::OnSize(int width, int height)
{
  if (myDirector->widgetOnSize(this, width, height) == GSBwxDialogDirector::DEFAULT_ACTION)
    wxFrame::OnSize(width, height);
}

