/*
 * GSBwxFrame.h
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
 *  $Id: GSBwxFrame.h,v 1.5 1997/04/08 11:05:31 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxFrame_H
#define _GSBwxFrame_H

#include "GSBwxDialogDirector.h"


//_____________________________________________________________________ GSBwxFrame

class GSBwxFrame : public wxFrame {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxFrame(GSBwxDialogDirector* director, wxFrame* parent, 
    char* title, int x = -1, int y = -1, int width = -1, int height = -1, 
    long style = wxDEFAULT_FRAME, char* name = "frame");

private:
  GSBwxFrame(const GSBwxFrame&);             // No copies.

public:
  // virtual ~GSBwxFrame();                  // Use default version.

private:
  GSBwxFrame& operator=(const GSBwxFrame&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxFrame
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
  GSBwxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES

#endif // _GSBwxFrame_H

