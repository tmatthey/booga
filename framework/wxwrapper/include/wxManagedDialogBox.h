/*
 * wxManagedDialogBox.h
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
 *  $Id: wxManagedDialogBox.h,v 1.2 1997/09/19 08:42:05 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedDialogBox_H
#define _wxManagedDialogBox_H

#include "booga/wxwrapper/wxDialogDirector.h"


//_____________________________________________________________________ wxManagedDialogBox

class wxManagedDialogBox : public wxDialogBox {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedDialogBox(wxDialogDirector* director, wxWindow* parent, 
    char* title, bool modal = false, int x = 300, int y = 300, int width = 500, 
    int height = 500, long style = wxDEFAULT_DIALOG_STYLE, char* name = "dialogBox");

private:
  wxManagedDialogBox(const wxManagedDialogBox&);             // No copies.

public:
  // virtual ~wxManagedDialogBox();                  // Use default version.

private:
  wxManagedDialogBox& operator=(const wxManagedDialogBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedDialogBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Bool OnClose();
  void OnPaint();
  void OnSize(int width, int height);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _wxManagedDialogBox_H


