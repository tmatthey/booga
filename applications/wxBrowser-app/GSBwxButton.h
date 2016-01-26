/*
 * GSBwxButton.h
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
 *  $Id: GSBwxButton.h,v 1.4 1997/04/08 11:05:13 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxButton_H
#define _GSBwxButton_H

#include "wx.h"
#include "GSBwxDialogDirector.h"

//_____________________________________________________________________ GSBwxButton

class GSBwxButton : public wxButton {
// declareRTTI(GSBwxButton);
// enable RTTI support
friend void GSBwxButtonCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxButton(GSBwxDialogDirector* director, wxPanel* parent, char* label,
    int x = -1, int y = -1, int width = -1, int height = -1, long style = 0, char* name = "button");
    
private:
  GSBwxButton(const GSBwxButton&);             // No copies.

public:
  // virtual ~GSBwxButton();                   // Use default version.

private:
  GSBwxButton& operator=(const GSBwxButton&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxButton
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

#endif // _GSBwxButton_H

