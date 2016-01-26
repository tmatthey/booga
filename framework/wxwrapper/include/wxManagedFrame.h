/*
 * wxManagedFrame.h
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
 *  $Id: wxManagedFrame.h,v 1.3 1997/12/12 13:38:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedFrame_H
#define _wxManagedFrame_H

#include "booga/wxwrapper/wxDialogDirector.h"


//_____________________________________________________________________ wxManagedFrame

class wxManagedFrame : public wxFrame {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedFrame(wxDialogDirector* director, wxFrame* parent, 
    char* title, int x = -1, int y = -1, int width = -1, int height = -1, 
    long style = wxDEFAULT_FRAME, char* name = "frame");

private:
  wxManagedFrame(const wxManagedFrame&);             // No copies.

public:
  // virtual ~wxManagedFrame();                  // Use default version.

private:
  wxManagedFrame& operator=(const wxManagedFrame&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedFrame
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxFrame
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Bool OnClose();
  void OnMenuCommand(int id);
  void OnSize(int width, int height);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _wxManagedFrame_H

