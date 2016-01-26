/*
 * wxManagedRadioBox.h
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
 *  $Id: wxManagedRadioBox.h,v 1.1 1996/09/27 11:46:10 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedRadioBox_H
#define _wxManagedRadioBox_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxManagedRadioBox

class wxManagedRadioBox : public wxRadioBox {
declareRTTI(wxManagedRadioBox);
// enable RTTI support
friend void wxManagedRadioBoxCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedRadioBox(wxDialogDirector* director, wxPanel* parent, char* label,
    int x, int y, int width, int height, int n, char* choices[],
    int majorDim = 0, long style = wxHORIZONTAL, char* name = "radioBox");
    
private:
  wxManagedRadioBox(const wxManagedRadioBox&);             // No copies.

public:
  // virtual ~wxManagedRadioBox();                   // Use default version.

private:
  wxManagedRadioBox& operator=(const wxManagedRadioBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedRadioBox
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

#endif // _wxManagedRadioBox_H



