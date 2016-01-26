/*
 * wxDialogDirector.h
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
 *  $Id: wxDialogDirector.h,v 1.3 1998/05/22 10:58:32 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxDialogDirector_H
#define _wxDialogDirector_H

#include "booga/base/RTTI.h"

#include "wx.h"


//_____________________________________________________________________ wxDialogDirector

class wxDialogDirector {
declareRTTI(wxDialogDirector);
// enable RTTI support
public:
enum ActionRequest {
        NO_DEFAULT_ACTION,
        DEFAULT_ACTION
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxDialogDirector() {};

private:
  wxDialogDirector(const wxDialogDirector&);  // No copies.

public:
  // virtual ~wxDialogDirector();                // Use default version.

private:
  wxDialogDirector& operator=(const wxDialogDirector&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void createGUI() = 0;
  
  // interface for wxObjects widgets
  virtual void widgetCallbackFunction(wxObject* /*widget*/, wxCommandEvent& /*event*/) {};
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

#endif // _wxDialogDirector_H
