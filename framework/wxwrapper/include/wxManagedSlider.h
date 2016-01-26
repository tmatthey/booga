/*
 * wxManagedSlider.h
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
 *  $Id: wxManagedSlider.h,v 1.1 1996/09/27 11:46:12 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedSlider_H
#define _wxManagedSlider_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ wxManagedSlider

class wxManagedSlider : public wxSlider {
// declareRTTI(wxManagedSlider);
// enable RTTI support
friend void wxManagedSliderCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedSlider(wxDialogDirector* director, wxPanel* parent, char* label,
    int value, int min_value, int max_value, int width, int x = -1, int y = -1,
    long style = wxHORIZONTAL, char* name = "slider");
    
private:
  wxManagedSlider(const wxManagedSlider&);             // No copies.

public:
  // virtual ~wxManagedSlider();                   // Use default version.

private:
  wxManagedSlider& operator=(const wxManagedSlider&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedSlider
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

#endif // _wxManagedSlider_H


