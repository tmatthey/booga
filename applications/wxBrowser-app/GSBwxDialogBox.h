/*
 * GSBwxDialogBox.h
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
 *  $Id: GSBwxDialogBox.h,v 1.4 1997/04/08 11:05:23 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxDialogBox_H
#define _GSBwxDialogBox_H

#include "GSBwxDialogDirector.h"


//_____________________________________________________________________ GSBwxDialogBox

class GSBwxDialogBox : public wxDialogBox {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxDialogBox(GSBwxDialogDirector* director, wxWindow* parent, 
    char* title, Bool modal = False, int x = 300, int y = 300, int width = 500, 
    int height = 500, long style = wxDEFAULT_DIALOG_STYLE, char* name = "dialogBox");

private:
  GSBwxDialogBox(const GSBwxDialogBox&);             // No copies.

public:
  // virtual ~GSBwxDialogBox();                  // Use default version.

private:
  GSBwxDialogBox& operator=(const GSBwxDialogBox&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxDialogBox
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
  GSBwxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _GSBwxDialogBox_H


