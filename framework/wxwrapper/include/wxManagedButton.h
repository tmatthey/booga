/*
 * wxManagedButton.h
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
 *  $Id: wxManagedButton.h,v 1.1 1996/09/27 11:45:56 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedButton_H
#define _wxManagedButton_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxManagedButton

class wxManagedButton : public wxButton {
// declareRTTI(wxManagedButton);
// enable RTTI support
friend void wxManagedButtonCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedButton(wxDialogDirector* director, wxPanel* parent, char* label,
    int x = -1, int y = -1, int width = -1, int height = -1, long style = 0, char* name = "button");
    
private:
  wxManagedButton(const wxManagedButton&);             // No copies.

public:
  // virtual ~wxManagedButton();                   // Use default version.

private:
  wxManagedButton& operator=(const wxManagedButton&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedButton
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

#endif // _wxManagedButton_H

