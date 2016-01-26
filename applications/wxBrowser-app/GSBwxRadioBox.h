/*
 * GSBwxRadioBox.h
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
 *  $Id: GSBwxRadioBox.h,v 1.4 1997/04/08 11:05:34 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxRadioBox_H
#define _GSBwxRadioBox_H

#include "wx.h"
#include "GSBwxDialogDirector.h"

//_____________________________________________________________________ GSBwxRadioBox

class GSBwxRadioBox : public wxRadioBox {
declareRTTI(GSBwxRadioBox);
// enable RTTI support
friend void GSBwxRadioBoxCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxRadioBox(GSBwxDialogDirector* director, wxPanel* parent, char* label,
    int x, int y, int width, int height, int n, char* choices[],
    int majorDim = 0, long style = wxHORIZONTAL, char* name = "radioBox");
    
private:
  GSBwxRadioBox(const GSBwxRadioBox&);             // No copies.

public:
  // virtual ~GSBwxRadioBox();                   // Use default version.

private:
  GSBwxRadioBox& operator=(const GSBwxRadioBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxRadioBox
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

#endif // _GSBwxRadioBox_H



