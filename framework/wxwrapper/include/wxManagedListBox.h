/*
 * $RCSfile: wxManagedListBox.h,v $
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
 *  $Id: wxManagedListBox.h,v 1.1 1996/09/27 11:46:07 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedListBox_H
#define _wxManagedListBox_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxManagedListBox

class wxManagedListBox : public wxListBox {
//declareRTTI(wxManagedListBox);
// enable RTTI support
friend void wxManagedListBoxCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedListBox(wxDialogDirector* director, wxPanel *panel, char *Title,
  Bool Multiple = wxSINGLE|wxNEEDED_SB, int x = -1, int y=-1, int width=-1, int height=-1,
  int N = 0, char **Choices = NULL, long style = 0, char *name = "listBox");
  // wxManagedListBox();                         // Use default version.
private:
  wxManagedListBox(const wxManagedListBox&);             // No copies.

public:
  // virtual ~wxManagedListBox();                // Use default version.

private:
  wxManagedListBox& operator=(const wxManagedListBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedListBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* getDirector() const { return myDirector; };


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BaseClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _wxManagedListBox_H

