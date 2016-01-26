/*
 * GSBwxChoice.h
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
 *  $Id: GSBwxChoice.h,v 1.4 1997/04/08 11:05:18 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxChoice_H
#define _GSBwxChoice_H

#include "wx.h"
#include "GSBwxDialogDirector.h"

//_____________________________________________________________________ GSBwxChoice

class GSBwxChoice : public wxChoice {
declareRTTI(GSBwxChoice);
// enable RTTI support
friend void GSBwxChoiceCallback(wxObject*, wxCommandEvent&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxChoice(GSBwxDialogDirector* director, wxPanel* parent, char* label,
    int x, int y, int width, int height, int n, char* choices[], 
    long style = wxHORIZONTAL, char* name = "choice");
    
private:
  GSBwxChoice(const GSBwxChoice&);             // No copies.

public:
  // virtual ~GSBwxChoice();                   // Use default version.

private:
  GSBwxChoice& operator=(const GSBwxChoice&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxChoice
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

#endif // _GSBwxChoice_H
