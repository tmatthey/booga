/*
 * GSBwxSlider.h
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
 *  $Id: GSBwxSlider.h,v 1.4 1997/04/08 11:05:37 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxSlider_H
#define _GSBwxSlider_H

#include "wx.h"
#include "GSBwxDialogDirector.h"

//_____________________________________________________________________ GSBwxSlider

class GSBwxSlider : public wxSlider {
// declareRTTI(GSBwxSlider);
// enable RTTI support
friend void GSBwxSliderCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxSlider(GSBwxDialogDirector* director, wxPanel* parent, char* label,
    int value, int min_value, int max_value, int width, int x = -1, int y = -1,
    long style = wxHORIZONTAL, char* name = "slider");
    
private:
  GSBwxSlider(const GSBwxSlider&);             // No copies.

public:
  // virtual ~GSBwxSlider();                   // Use default version.

private:
  GSBwxSlider& operator=(const GSBwxSlider&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxSlider
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  GSBwxDialogDirector* getDirector() const { return myDirector; };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  GSBwxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _GSBwxSlider_H


