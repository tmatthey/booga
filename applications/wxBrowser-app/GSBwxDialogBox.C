/*
 * GSBwxDialogBox.C 
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
 *  $Id: GSBwxDialogBox.C,v 1.4 1997/04/08 11:05:22 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxDialogBox.h"

//_____________________________________________________________________ GSBwxDialogBox

GSBwxDialogBox::GSBwxDialogBox(GSBwxDialogDirector* director, wxWindow* parent, 
  char* title, Bool modal, int x, int y, int width, int height, long style, char* name)
  : wxDialogBox(parent, title, modal, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxDialogBox::GSBwxDialogBox] NULL DialogDirector passed!");
}


Bool GSBwxDialogBox::OnClose()
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


void GSBwxDialogBox::OnPaint()
{
  if (myDirector->widgetOnPaint(this) == GSBwxDialogDirector::DEFAULT_ACTION)
    wxDialogBox::OnPaint();
}


void GSBwxDialogBox::OnSize(int width, int height)
{
  if (myDirector->widgetOnSize(this, width, height) == GSBwxDialogDirector::DEFAULT_ACTION)
    wxDialogBox::OnSize(width, height);
}


