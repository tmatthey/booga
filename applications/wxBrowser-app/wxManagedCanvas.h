/*
 * wxManagedCanvas.h
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
 *  $Id: wxManagedCanvas.h,v 1.1 1997/04/17 09:39:17 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxManagedCanvas_H
#define _wxManagedCanvas_H

#include "wx.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxGLCanvas.h"

//_____________________________________________________________________ wxManagedCanvas

class wxManagedCanvas : public wxGLCanvas {
//declareRTTI(wxManagedCanvas);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxManagedCanvas(wxDialogDirector* director, wxWindow* parent, int x = -1, int y = -1,
    int width = -1, int height = -1, long style = wxRETAINED, char* name = "glcanvas");
  
private:
  wxManagedCanvas(const wxManagedCanvas&);             // No copies.

public:
  // virtual ~wxManagedCanvas();                // Use default version.

private:
  wxManagedCanvas& operator=(const wxManagedCanvas&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxManagedCanvas
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxGLCanvas
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void OnChar(wxKeyEvent& event);
  Bool OnClose();
  void OnEvent(wxMouseEvent& event);
  void OnPaint();
  void OnSize(int x, int y);

  void GLClear() { wxGLCanvas::GLClear(); };
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES


inline
wxManagedCanvas::wxManagedCanvas(wxDialogDirector* director, wxWindow* parent, int x, int y,
  int width, int height, long style, char* name)
: wxGLCanvas(parent, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[wxManagedCanvas::wxManagedCanvas] NULL DialogDirector passed!");
}


inline
void wxManagedCanvas::OnChar(wxKeyEvent& event)
{
  if (myDirector->widgetOnChar(this, event) == wxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnChar(event);
}


inline
Bool wxManagedCanvas::OnClose()
{
  return (myDirector->widgetOnClose(this) == wxDialogDirector::DEFAULT_ACTION) ? false : true;
}


inline
void wxManagedCanvas::OnEvent(wxMouseEvent& event)
{
  if (myDirector->widgetOnEvent(this, event) == wxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnEvent(event);
}


inline
void wxManagedCanvas::OnSize(int w, int h)
{
  GLSetCurrent();
  if (myDirector->widgetOnSize(this, w, h) == wxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnSize(w, h);
}

#endif // _wxManagedCanvas_H

