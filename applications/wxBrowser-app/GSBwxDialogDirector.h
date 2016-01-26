/*
 * GSBwxDialogDirector.h
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
 *  $Id: GSBwxDialogDirector.h,v 1.5 1997/04/08 11:05:26 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxDialogDirector_H
#define _GSBwxDialogDirector_H

#include "booga/base/RTTI.h"

#include "wx.h"


//_____________________________________________________________________ GSBwxDialogDirector

class GSBwxDialogDirector {
declareRTTI(GSBwxDialogDirector);
// enable RTTI support

enum ActionRequest {
        NO_DEFAULT_ACTION,
        DEFAULT_ACTION
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxDialogDirector() {};

private:
  GSBwxDialogDirector(const GSBwxDialogDirector&);  // No copies.

public:
  // virtual ~GSBwxDialogDirector();                // Use default version.

private:
  GSBwxDialogDirector& operator=(const GSBwxDialogDirector&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void createGUI() = 0;
  
  // interface for wxObjects widgets
  virtual void widgetCallbackFunction(wxObject*, wxCommandEvent&) {};
  virtual ActionRequest widgetOnChar(wxObject* widget, wxKeyEvent& event);
  virtual ActionRequest widgetOnClose(wxObject* widget);
  virtual ActionRequest widgetOnEvent(wxObject* widget, wxMouseEvent& event);
  virtual ActionRequest widgetOnMenuCommand(wxObject* widget, int id);
  virtual ActionRequest widgetOnPaint(wxObject* widget);
  virtual ActionRequest widgetOnSize(wxObject* widget, int width, int height);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // none
};

//______________________________________________________________________ INLINES

#endif // _GSBwxDialogDirector_H
