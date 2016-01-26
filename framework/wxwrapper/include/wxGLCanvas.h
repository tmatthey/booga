/*
 * $RCSfile: wxGLCanvas.h,v $
 *
 * Copyright (C) 1995-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: wxGLCanvas.h,v 1.7 1997/09/19 08:41:55 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxGLCanvas_h
#define _wxGLCanvas_h

#ifdef wx_motif
#include <wx_win.h> // Keep this before GL-Stuff
#endif

#include <GL/gl.h>

#ifdef HAVE_X11

#include <GL/glx.h>
#endif

#include "booga/base/StaticInit.h"

#ifdef wx_motif

class wxGLCanvas: public wxWindow {

DECLARE_DYNAMIC_CLASS(wxGLCanvas)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxGLCanvas();
  wxGLCanvas(wxWindow *parent, int x=-1, int y=-1, int width=-1, int height=-1,
               long style=0, char *name = "GLCanvas");
private:
  wxGLCanvas(const wxGLCanvas&);                // No copies.
  
public:
  ~wxGLCanvas(void);

private:
  wxGLCanvas& operator=(const wxGLCanvas&);    // No assignment

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxWindow
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

  Bool Create(wxWindow *window, int x=-1, int y=-1, int width=-1, int height=-1,
               long style=0, char *name = "GLCanvas");

  void SetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO);
  void GetSize(int *x, int *y);
  
  void SetClientSize(int width, int height);
  static void initClass();  // do proper initialisation of static members

  void GLSetCurrent(void);
  void GLSwapBuffers(void);
  void GLClear(void);
  void GLFlush(void);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  GLXContext glx_cx;
  int myWidth, myHeight;
  Window xwindow;
  
  Display *display;
  Widget drawingArea;
  Widget borderWidget;

};

#endif // wx_motif

// ------------ xview implementation ----------------------------------

#ifdef wx_xview

// WX Stuff
#include <common.h>
#include <wx_frame.h>
#include <wx_canvs.h>

class wxGLCanvas : public wxCanvas {
public:
  GLXContext glx_cx;

  wxGLCanvas(wxWindow *parent, int x, int y, int w, int h,
           long style = 0, char *name = "wxGLCanvas", int *attrib_list = 0);
  ~wxGLCanvas(void);

  static void initClass();  // do proper initialisation of static members

  void GLSetCurrent(void);
  void GLSwapBuffers(void);
  void GLClear(void);
  void GLFlush(void);
};

#endif  // xview

#ifdef wx_msw

#include "wx_gdi.h"
#include "wx_canvs.h"

class GLContext: public wxObject
{
 public:
   GLContext(wxWindow *win = NULL);
   ~GLContext(void);
   void GLSetCurrent(void);
   // void GLSetColour(const char *colour);
   void GLSwapBuffers(wxDC *dc);
private:
    void pixelFormatSetupFunction(HDC hDC);

	HGLRC hRC;            // rendering context handle 
    HDC   hDC;           // device context handle 
	HWND hWnd;
 
};

class wxGLCanvas: public wxCanvas
{
 public:
 
   wxGLCanvas(wxWindow *parent, int x, int y, int w, int h, long style = 0, char *name = "GLCanvas");
   ~wxGLCanvas(void);

   void GLCreateContext(wxWindow *win = NULL);
   void GLSetCurrent(void);
   void GLClear(void);
   void GLSetColour(const char *colour);
   void GLSwapBuffers(void);
   static void initClass();  // do proper initialisation of static members

 private:
   GLContext *glContext;  // this is typedef-ed ptr, in fact

};

#endif // wx_msw

declareInitStatics(wxGLCanvas);

#endif // _wxGLCanvas_h

