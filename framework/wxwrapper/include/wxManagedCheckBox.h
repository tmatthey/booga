/*
 * wxManagedCheckBox.h
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
 *  $Id: wxManagedCheckBox.h,v 1.1 1996/09/27 11:45:59 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedCheckBox_H
#define _wxManagedCheckBox_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxManagedCheckBox

class wxManagedCheckBox : public wxCheckBox {
declareRTTI(wxManagedCheckBox);
// enable RTTI support
friend void wxManagedCheckBoxCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedCheckBox(wxDialogDirector* director, wxPanel* parent, char* label,
    int x=-1, int y=-1, int width=-1, int height=-1, 
    long style = 0, char* name = "checkBox");
    
private:
  wxManagedCheckBox(const wxManagedCheckBox&);             // No copies.

public:
  // virtual ~wxManagedCheckBox();                   // Use default version.

private:
  wxManagedCheckBox& operator=(const wxManagedCheckBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedCheckBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* getDirector() const { return myDirector; };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _wxManagedCheckBox_H



