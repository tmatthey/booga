/*
 * GSBwxCanvas.h
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
 *  $Id: GSBwxCanvas.h,v 1.5 1997/04/08 11:05:15 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxCanvas_H
#define _GSBwxCanvas_H

#include "booga/wxwrapper/wxGLCanvas.h"
#include "GSBwxDialogDirector.h"


//_____________________________________________________________________ GSBwxCanvas

class GSBwxCanvas : public wxGLCanvas {
declareRTTI(GSBwxCanvas);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxCanvas(GSBwxDialogDirector* director, wxWindow* parent, int x = -1, int y = -1,
    int width = -1, int height = -1, long style = wxRETAINED, char* name = "glcanvas");
  
private:
  GSBwxCanvas(const GSBwxCanvas&);             // No copies.

public:
  // virtual ~GSBwxCanvas();                // Use default version.

private:
  GSBwxCanvas& operator=(const GSBwxCanvas&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxCanvas
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
  GSBwxDialogDirector* myDirector;
};

//______________________________________________________________________ INLINES


inline
GSBwxCanvas::GSBwxCanvas(GSBwxDialogDirector* director, wxWindow* parent, int x, int y,
  int width, int height, long style, char* name)
: wxGLCanvas(parent, x, y, width, height, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxCanvas::GSBwxCanvas] NULL DialogDirector passed!");
}


inline
void GSBwxCanvas::OnChar(wxKeyEvent& event)
{
  if (myDirector->widgetOnChar(this, event) == GSBwxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnChar(event);
}


inline
Bool GSBwxCanvas::OnClose()
{
  return (myDirector->widgetOnClose(this) == GSBwxDialogDirector::DEFAULT_ACTION) ? false : true;
}


inline
void GSBwxCanvas::OnEvent(wxMouseEvent& event)
{
  if (myDirector->widgetOnEvent(this, event) == GSBwxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnEvent(event);
}


inline
void GSBwxCanvas::OnSize(int w, int h)
{
  GLSetCurrent();
  if (myDirector->widgetOnSize(this, w, h) == GSBwxDialogDirector::DEFAULT_ACTION) 
    wxGLCanvas::OnSize(w, h);
}

#endif // _GSBwxCanvas_H

