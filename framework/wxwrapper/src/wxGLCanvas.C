/*
 * $RCSfile: wxGLCanvas.C,v $
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
 *
 * -----------------------------------------------------------------------------
 *  $Id: wxGLCanvas.C,v 1.6 1998/05/24 16:57:39 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>

#include "booga/base/RCString.h"
#include "booga/glwrapper/GLUtilities.h"

#include "booga/wxwrapper/wxGLCanvas.h"
#include "booga/wxwrapper/wxWindowsBridge.h"

#include "common.h"
#include "wx_main.h"
#include "wx_panel.h"
#include "wx_utils.h"
#include "wx_frame.h"
#include "wx_privt.h"
#include "wx_stdev.h"

implementInitStatics(wxGLCanvas);

#ifdef wx_motif

#include <Xm/Frame.h>
#include <GL/GLwMDrawA.h>
#include <sys/types.h>
#include <sys/stat.h>


IMPLEMENT_DYNAMIC_CLASS(wxGLCanvas, wxWindow)

static int dblBuf[] = {
  //    GLX_DOUBLEBUFFER, GLX_RGBA, GLX_DEPTH_SIZE, 16,
  GLX_DOUBLEBUFFER, GLX_RGBA,
  GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1,
  None
};
static int *snglBuf = &dblBuf[1];

wxGLCanvas::wxGLCanvas ()
{
  display = NULL;
}


void wxGLCanvasRepaintProc (Widget, XtPointer, XmDrawingAreaCallbackStruct * cbs);
void wxGLCanvasResizeProc (Widget, XtPointer, XmDrawingAreaCallbackStruct * cbs);
void wxGLCanvasInputEvent (Widget, XtPointer, XmDrawingAreaCallbackStruct * cbs);
void wxGLCanvasMotionEvent (Widget, XButtonEvent * event);


wxGLCanvas::wxGLCanvas (wxWindow * parent, int x, int y, int width, int height,
	      long style, char *name)
{
  Create (parent, x, y, width, height, style, name);
}

Bool wxGLCanvas::Create (wxWindow * parent, int x, int y, int width, int height,
	long style, char *name)
{
  myWidth  = width  + 4;
  myHeight = height + 4;
  
  windowStyle = style;

  windowName = copystring (name);

  Widget parentWidget = 0;
  if (parent->IsKindOf(CLASSINFO(wxFrame)))
    parentWidget = ((wxFrame *)parent)->clientArea;
  else if (parent->IsKindOf(CLASSINFO(wxPanel)))
    parentWidget = (Widget)parent->handle;
  else
  {
    wxError("Text subwindow must be a child of either a frame or panel!");
    return FALSE;
  }

  display = XtDisplay (parentWidget);
 /* GLX stuff: */
  // Check for the presence of the GLX extension
  //  wxDebugMsg("GLCanvas: beginning context\n");

  if(!glXQueryExtension(display, NULL, NULL)) {
    wxDebugMsg("GLCanvas: GLX extension is missing\n");
    return 0;
  }
  
  // wxDebugMsg("GLCanvas: GLX extension ok\n");

  /* find an OpenGL-capable RGB visual with depth buffer */
  XVisualInfo *vi = glXChooseVisual(display, DefaultScreen(display), dblBuf);
  // wxDebugMsg("GLCanvas: glXChooseVisual ok\n");
  
  if (vi == NULL) {
    // wxDebugMsg("GLCanvas: glXChooseVisual second try\n");
    vi = glXChooseVisual(display, DefaultScreen(display), snglBuf);
    if (vi == NULL)
      wxDebugMsg("GLCanvas: no RGB visual with depth buffer");
    //    doubleBuffer = GL_FALSE;
  }
  /* create an OpenGL rendering context */
  glx_cx = glXCreateContext(display, vi, /* no display list sharing */ None,
			    /* favor direct */ GL_TRUE);
  // wxDebugMsg("GLCanvas: context created\n");

  if (glx_cx == NULL)
    wxDebugMsg("GLCanvas: could not create rendering context");
    
  borderWidget = XtVaCreateManagedWidget ("canvasBorder",
					  xmFrameWidgetClass, 
					  parentWidget,
//					  XmNshadowType, XmSHADOW_IN,
					  NULL);
						
//  Widget frame = XmCreateFrame (parentWidget, "frame", NULL, 0);
//  XtManageChild (frame);

  drawingArea = XtVaCreateWidget (windowName,
                                  glwMDrawingAreaWidgetClass, borderWidget,
                                  XmNunitType, XmPIXELS,
                                  //XmNresizePolicy, XmRESIZE_ANY,
                                  //XmNresizePolicy, XmRESIZE_NONE,
 /* GLX stuff: */	 	       GLwNvisualInfo, vi,
                                  // XmNmarginHeight, 0,
                                  // XmNmarginWidth, 0,
                                  NULL);

  if (wxWidgetHashTable->Get ((long) drawingArea)) {
    wxError ("Widget table clash in wxGLCanvas.C");
  }
  wxWidgetHashTable->Put ((long) drawingArea, this);

  XtManageChild (drawingArea);

  xwindow = XtWindow (drawingArea);
 
  XtAddCallback (drawingArea, XmNexposeCallback, (XtCallbackProc) wxGLCanvasRepaintProc, (XtPointer) this);
  //  XtAddCallback (drawingArea, XmNresizeCallback, (XtCallbackProc) wxGLCanvasResizeProc, (XtPointer) this);
  XtAddCallback (drawingArea, XmNinputCallback, (XtCallbackProc) wxGLCanvasInputEvent, (XtPointer) this);

  handle = (char *) drawingArea;

  if (IsKindOf(CLASSINFO(wxPanel)))
    ((wxPanel *)parent)->AttachWidget(this, 0, x, y, myWidth, myHeight);
  else
    SetSize (x, y, myWidth, myHeight);

  if (parent)
    parent->AddChild (this);
  window_parent = parent;

  return TRUE;
}

wxGLCanvas::~wxGLCanvas(void)
{
//    if(glx_cx) glXDestroyContext(display, glx_cx);
    // We should really XFree() the XVisualInfo structure here,
    // but this may not work with Mesa.
    // So a small memory leak remains.
}


void 
wxGLCanvasRepaintProc (Widget drawingArea, XtPointer clientData, XmDrawingAreaCallbackStruct * cbs)
{
  if (!wxWidgetHashTable->Get ((long) drawingArea))
    return;

  XEvent * event = cbs->event;
  wxGLCanvas * canvas = (wxGLCanvas *) clientData;
  //  Display * display = (Display *) canvas->GetXDisplay();
  
  switch (event->type) {
  case Expose:
    canvas->GetEventHandler()->OnPaint();
    break;
    
  default:
    cout << "\n\nNew Event ! is = " << event -> type << "\n";
    break;
  }
}


void 
wxGLCanvasResizeProc (Widget drawingArea, XtPointer /*clientData*/, XmDrawingAreaCallbackStruct */*cbs*/)
{
 
  if (!wxWidgetHashTable->Get ((long) drawingArea))
    return;

  // XEvent * event = cbs->event;
  // wxGLCanvas * canvas = (wxGLCanvas *) clientData;
  //  Display * display = (Display *) canvas->GetXDisplay();

  //  canvas->GetEventHandler()->OnPaint();
}


// Fix to make it work under Motif 1.0 (!)
#if   XmVersion<=1000
void wxGLCanvasMotionEvent (Widget drawingArea, XButtonEvent * event)
{

  XmDrawingAreaCallbackStruct cbs;
  XEvent ev;

  //ev.xbutton = *event;
  ev = *((XEvent *) event);
  cbs.reason = XmCR_INPUT;
  cbs.event = &ev;

  wxGLCanvasInputEvent (drawingArea, (XtPointer) NULL, &cbs);
}
#else
void wxGLCanvasMotionEvent (Widget, XButtonEvent *)
{}
#endif /* XmVersion<=1000 */

static Bool wait_dclick = FALSE;
static Bool dclick = FALSE;
static lose_up = FALSE;

static long timerId;
static void 

wxDClickCallback (XtPointer)
{
  dclick = FALSE;
  wait_dclick = FALSE;
//wxDebugMsg("Timer dclick\n") ;
}

void 
wxGLCanvasInputEvent (Widget drawingArea, XtPointer /*data*/, XmDrawingAreaCallbackStruct * cbs)
{
  wxGLCanvas *canvas = (wxGLCanvas *) wxWidgetHashTable->Get ((long) drawingArea);
  XEvent local_event;

  if (canvas==NULL)
    return ;

  if (cbs->reason != XmCR_INPUT)
    return;

  local_event = *(cbs->event);	// We must keep a copy!

  if (wait_dclick)
    {
      // If we are waiting for a double-click, we only handle Button events
      // in a special fashion.
      if (local_event.xany.type == ButtonPress)
	{
	  wait_dclick = FALSE;
	  dclick = TRUE;
	  lose_up = FALSE;
	  XtRemoveTimeOut (timerId);
	  return;
	}
      if (local_event.xany.type == ButtonRelease)
	{
	  lose_up = TRUE;
	  return;
	}
    }

  switch (local_event.xany.type)
    {
    case EnterNotify:
    case LeaveNotify:
    case ButtonPress:
    case ButtonRelease:
    case MotionNotify:
      {
	WXTYPE eventType = 0;

	if (local_event.xany.type == EnterNotify)
	  {
	    //if (local_event.xcrossing.mode!=NotifyNormal)
	    //  return ; // Ignore grab events
	    eventType = wxEVENT_TYPE_ENTER_WINDOW;
//            canvas->GetEventHandler()->OnSetFocus();
	  }
	else if (local_event.xany.type == LeaveNotify)
	  {
	    //if (local_event.xcrossing.mode!=NotifyNormal)
	    //  return ; // Ignore grab events
	    eventType = wxEVENT_TYPE_LEAVE_WINDOW;
//            canvas->GetEventHandler()->OnKillFocus();
	  }
	else if (local_event.xany.type == MotionNotify)
	  {
	    eventType = wxEVENT_TYPE_MOTION;
	    if (local_event.xmotion.is_hint == NotifyHint)
	      {
		Window root, child;
		Display *dpy = XtDisplay (drawingArea);

		XQueryPointer (dpy, XtWindow (drawingArea),
			       &root, &child,
			       &local_event.xmotion.x_root,
			       &local_event.xmotion.y_root,
			       &local_event.xmotion.x,
			       &local_event.xmotion.y,
			       &local_event.xmotion.state);
//fprintf(stderr,"*") ; fflush(stderr) ;
	      }
	    else
	      {
//fprintf(stderr,".") ; fflush(stderr) ;
	      }
	  }

	else if (local_event.xany.type == ButtonPress)
	  {

	    // Not reached if we are already waiting a double click.
	    // @@@ Double Clicks allowed ONLY for left button!
	    // [JACS: if the right button is used for PopUp menus it seems
	    // to interfere with this code and the button seems to be down
	    // always]
	    if (canvas->doubleClickAllowed && local_event.xbutton.button == Button1)
	      {
		timerId = XtAppAddTimeOut (wxTheApp->appContext,
					   canvas->doubleClickAllowed,
				     (XtTimerCallbackProc) wxDClickCallback,
					   (XtPointer) 0);

		wait_dclick = TRUE;
		lose_up = FALSE;
		dclick = FALSE;
		// Not so trivial code... I've carefully looked Xt code to find
		// that THIS seq. is the good one!!
		do
		  {
		    if (XtAppPending (wxTheApp->appContext))
		      XtAppProcessEvent (wxTheApp->appContext, XtIMAll);
		  }
		while (wait_dclick);
		// So here, dclick&lose_up have correct values.
	      }
	    else
	      {
		lose_up = FALSE;
		dclick = FALSE;
	      }

	    // Setup correct event type, depending on dclick.
	    if (local_event.xbutton.button == Button1)
	      {
		eventType = dclick ? wxEVENT_TYPE_LEFT_DCLICK : wxEVENT_TYPE_LEFT_DOWN;
		canvas->button1Pressed = TRUE;
	      }
	    else if (local_event.xbutton.button == Button2)
	      {
		eventType = dclick ? wxEVENT_TYPE_MIDDLE_DCLICK : wxEVENT_TYPE_MIDDLE_DOWN;
		canvas->button2Pressed = TRUE;
	      }
	    else if (local_event.xbutton.button == Button3)
	      {
		eventType = dclick ? wxEVENT_TYPE_RIGHT_DCLICK : wxEVENT_TYPE_RIGHT_DOWN;
		canvas->button3Pressed = TRUE;
	      }
	  }
	else if (local_event.xany.type == ButtonRelease)
	  {
	    // Not reached if we are already waiting a double click.
	    if (local_event.xbutton.button == Button1)
	      {
		eventType = wxEVENT_TYPE_LEFT_UP;
		canvas->button1Pressed = FALSE;
	      }
	    else if (local_event.xbutton.button == Button2)
	      {
		eventType = wxEVENT_TYPE_MIDDLE_UP;
		canvas->button2Pressed = FALSE;
	      }
	    else if (local_event.xbutton.button == Button3)
	      {
		eventType = wxEVENT_TYPE_RIGHT_UP;
		canvas->button3Pressed = FALSE;
	      }
	  }

	wxMouseEvent wxevent (eventType);
	wxevent.eventHandle = (char *) &local_event;

	wxevent.x = local_event.xbutton.x;
	wxevent.y = local_event.xbutton.y;

	wxevent.leftDown = canvas->button1Pressed;
	wxevent.middleDown = canvas->button2Pressed;
	wxevent.rightDown = canvas->button3Pressed;

	wxevent.shiftDown = local_event.xbutton.state & ShiftMask;
	wxevent.controlDown = local_event.xbutton.state & ControlMask;
        wxevent.altDown = local_event.xbutton.state & Mod3Mask;
        wxevent.metaDown = local_event.xbutton.state & Mod1Mask;
	wxevent.eventObject = canvas;
        wxevent.SetTimestamp(local_event.xbutton.time);

	canvas->GetEventHandler()->OnEvent (wxevent);

	if (eventType == wxEVENT_TYPE_ENTER_WINDOW ||
	    eventType == wxEVENT_TYPE_LEAVE_WINDOW ||
	    eventType == wxEVENT_TYPE_MOTION
	  )
	  return;

	if (lose_up)		// Simple click, but ButtonRelease event was losed.

	  {
	    if (local_event.xbutton.button == Button1)
	      {
		eventType = wxEVENT_TYPE_LEFT_UP;
		canvas->button1Pressed = FALSE;
	      }
	    else if (local_event.xbutton.button == Button2)
	      {
		eventType = wxEVENT_TYPE_MIDDLE_UP;
		canvas->button2Pressed = FALSE;
	      }
	    else if (local_event.xbutton.button == Button3)
	      {
		eventType = wxEVENT_TYPE_RIGHT_UP;
		canvas->button3Pressed = FALSE;
	      }
	    wxevent.eventType = eventType;
	    canvas->GetEventHandler()->OnEvent (wxevent);
	  }
	wait_dclick = FALSE;
	dclick = FALSE;
	lose_up = FALSE;
	break;
      }
    case KeyPress:
      {
	KeySym keySym;
	XComposeStatus compose;
	(void) XLookupString ((XKeyEvent *) & local_event, wxBuffer, 20, &keySym, &compose);
	int id = CharCodeXToWX (keySym);

	wxKeyEvent event (wxEVENT_TYPE_CHAR);

	if (local_event.xkey.state & ShiftMask)
	  event.shiftDown = TRUE;
	if (local_event.xkey.state & ControlMask)
	  event.controlDown = TRUE;
	if (local_event.xkey.state & Mod3Mask)
	  event.altDown = TRUE;
	if (local_event.xkey.state & Mod1Mask)
	  event.metaDown = TRUE;
	event.eventObject = canvas;
	event.keyCode = id;
        event.SetTimestamp(local_event.xkey.time);

	event.x = local_event.xbutton.x;
	event.y = local_event.xbutton.y;

	if (id > -1)
	  canvas->GetEventHandler()->OnChar (event);
	break;
      }
    case FocusIn:
      {
        if (local_event.xfocus.detail != NotifyPointer)
          canvas->GetEventHandler()->OnSetFocus ();
	break;
      }
    case FocusOut:
      {
        if (local_event.xfocus.detail != NotifyPointer)
	  canvas->GetEventHandler()->OnKillFocus ();
        break;
      }
    default:
      break;
    }
}

void wxGLCanvas::GetSize (int *x, int *y)
{
  *x = myWidth;
  *y = myHeight;
}

void wxGLCanvas::SetClientSize (int w, int h)
{
  SetSize (-1, -1, w, h);
}

void wxGLCanvas::SetSize (int x, int y, int w, int h, int /*sizeFlags*/)
{

  Widget textWidget = (Widget) handle;
  Widget parent = XtParent (textWidget);
  XtUnmanageChild (parent);

  if (x > -1)
    XtVaSetValues (parent,
//                  XmNleftAttachment, XmATTACH_SELF,
		   XmNx, x,
		   NULL);

  if (y > -1)
    XtVaSetValues (parent,
//                  XmNtopAttachment, XmATTACH_SELF,
		   XmNy, y,
		   NULL);

  if (w > -1)
    XtVaSetValues (parent, XmNwidth, w, NULL);
  if (h > -1)
    XtVaSetValues (parent, XmNheight, h, NULL);

  XtManageChild (parent);

  myWidth=w;
  myHeight=h;
  GetEventHandler()->OnSize (w, h);
}

#endif // wx_motif


// ---------------- beginning of xview implementation ------------------------

#ifdef wx_xview

#ifdef MESA
// workaround for bug in Mesa's glx.c
static int bitcount( unsigned long n )
{
    int bits;
    for (bits=0; n>0;) {
	if(n & 1) bits++;
	n = n >> 1;
    }
    return bits;
}
#endif /* MESA */


/*
 * wxGLCanvas implementation
 */

wxGLCanvas::wxGLCanvas(wxWindow *parent, int x, int y, int w, int h,
		   long style, char *name, int *attrib_list):
wxCanvas(parent, x, y, w, h, style, name)
{
  XVisualInfo *vi, vi_templ;
  XWindowAttributes xwa;
  int val, n, a_list[32];

   glx_cx = 0;
   // Check for the presence of the GLX extension
   if(!glXQueryExtension(display, NULL, NULL)) {
     wxDebugMsg("wxGLCanvas: GLX extension is missing\n");
     return;
   }

  if(attrib_list) {
    // Get an appropriate visual
    vi = glXChooseVisual(display, DefaultScreen(display), attrib_list);
    if(!vi) return;

    // Here we should make sure that vi is the same visual as the
    // one used by the xwindow drawable in wxCanvas.  However,
    // there is currently no mechanism for this in wx_canvs.cc.
  } else {
    // By default, we use the visual of xwindow
    XGetWindowAttributes(display, xwindow, &xwa);
    vi_templ.visualid = XVisualIDFromVisual(xwa.visual);
    vi = XGetVisualInfo(display, VisualIDMask, &vi_templ, &n);
    if(!vi) return;
    glXGetConfig(display, vi, GLX_USE_GL, &val);
    if(!val) return;
    // Basically, this is it.  It should be possible to use vi
    // in glXCreateContext() below.  But this fails with Mesa.
    // I notified the Mesa author about it; there may be a fix.
#ifdef MESA
    // Construct an attribute list matching the visual
    n = 0;
    if(vi->c_class==TrueColor || vi->c_class==DirectColor) { // RGBA visual
      a_list[n++] = GLX_RGBA;
      a_list[n++] = GLX_RED_SIZE;
      a_list[n++] = bitcount(vi->red_mask);
      a_list[n++] = GLX_GREEN_SIZE;
      a_list[n++] = bitcount(vi->green_mask);
      a_list[n++] = GLX_BLUE_SIZE;
      a_list[n++] = bitcount(vi->blue_mask);
      glXGetConfig(display, vi, GLX_ALPHA_SIZE, &val);
      a_list[n++] = GLX_ALPHA_SIZE;
      a_list[n++] = val;
    } else { // Color index visual
	cerr << "wxGLCanvas: getting Color index visual\n";
      glXGetConfig(display, vi, GLX_BUFFER_SIZE, &val);
      a_list[n++] = GLX_BUFFER_SIZE;
      a_list[n++] = val;
    }
      a_list[n] = None;
      XFree(vi);
      vi = glXChooseVisual(display, DefaultScreen(display), a_list);
      if(!vi) return;
#endif /* MESA */
  }

  // Create the GLX context and make it current
  glx_cx = glXCreateContext(display, vi, 0, GL_TRUE);
  GLSetCurrent();
}

wxGLCanvas::~wxGLCanvas(void)
{
    if(glx_cx) glXDestroyContext(display, glx_cx);
    // We should really XFree() the XVisualInfo structure here,
    // but this may not work with Mesa.
    // So a small memory leak remains.
}
 
#endif /* wx_xview */

// the following code applies to both wx_motif and wx_xview:

#if defined(wx_motif) || defined(wx_xview)

Display *_wxGLDisplay;
Window _wxGLWindow;

void wxGLCanvas::GLSetCurrent(void)
{
  _wxGLDisplay = display;
  _wxGLWindow = xwindow;
#ifdef wx_motif  
  if(glx_cx) 
    GLwDrawingAreaMakeCurrent(drawingArea, glx_cx);
#endif /* wx_motif */
#ifdef wx_xview
  if(glx_cx) glXMakeCurrent(display, xwindow, glx_cx);
#endif /* wx_xview */
}
   
void wxGLCanvas::GLSwapBuffers(void)
{
  glXSwapBuffers(_wxGLDisplay, _wxGLWindow);
}

void wxGLCanvas::GLFlush(void)
{
  if (!glXIsDirect (_wxGLDisplay, glx_cx))
    glFinish();
}
#endif /* (wx_motif) || (wx_xview) */

#ifdef wx_msw

#include "wx.h"
#include "wx_privt.h"
#include <windows.h>
#include <GL/gl.h>
//#include <GL/wgl.h>

#include "booga/wxwrapper/wxGLCanvas.h"
#include "booga/glwrapper/GLUtilities.h"
#include "booga/wxwrapper/wxWindowsBridge.h"
/*
 * GLContext implementation
 */
GLContext::GLContext(wxWindow *win)
{
  if (win) {
    hWnd = win->GetHWND();
	hDC = GetDC(hWnd);
	pixelFormatSetupFunction(hDC);

    hRC = wglCreateContext(hDC); 
    if (!hRC) 
      MessageBox(NULL, "Cannot create context.", "Error", MB_OK); 
    else  
    wglMakeCurrent(hDC, hRC);
  }
}

void GLContext::pixelFormatSetupFunction(HDC hDC)
{
  PIXELFORMATDESCRIPTOR pfd = { 
    sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
    1,                                // version number 
    PFD_DRAW_TO_WINDOW |              // support window 
    PFD_SUPPORT_OPENGL |              // support OpenGL 
    PFD_DOUBLEBUFFER,                 // double buffered 
    PFD_TYPE_RGBA,                    // RGBA type 
    24,                               // 24-bit color depth 
    0, 0, 0, 0, 0, 0,                 // color bits ignored 
    0,                                // no alpha buffer 
    0,                                // shift bit ignored 
    0,                                // no accumulation buffer 
    0, 0, 0, 0,                       // accum bits ignored 
    32,                               // 32-bit z-buffer     
    0,                                // no stencil buffer 
    0,                                // no auxiliary buffer 
    PFD_MAIN_PLANE,                   // main layer 
    0,                                // reserved 
    0, 0, 0                           // layer masks ignored 
  }; 
  int  iPixelFormat; 
  // get the device context's best-available-match pixel format 
  iPixelFormat = ChoosePixelFormat(hDC, &pfd); 
  // make that the device context's current pixel format 
  SetPixelFormat(hDC, iPixelFormat, &pfd); 
}
GLContext::~GLContext(void)
{
 	HGLRC hRC;            // rendering context handle 
    HDC   hDC;           // device context handle 
    /* Release and free the device context and rendering context. */ 
    hDC = wglGetCurrentDC; 
    hRC = wglGetCurrentContext; 
    wglMakeCurrent(NULL, NULL); 
    if (hRC) 
        wglDeleteContext(hRC); 
    if (hDC) 
        ReleaseDC(hWnd, hDC); 
}
void GLContext::GLSwapBuffers(wxDC *wxdc)
{
  SwapBuffers(hDC);
/*
	HDC dc = NULL;
  wxWnd *wnd = NULL;
  if (wxdc->canvas) wnd = (wxWnd *)wxdc->canvas->handle;
  if (wxdc->cdc)
    dc = wxdc->cdc;
  else if (wnd)
    dc = wnd->GetHDC();

  if (glContext)
  {
    WMesaMakeCurrent(glContext);
    WMesaSwapBuffers2(dc);    //blits the backbuffer into DC
  }

  if (!wxdc->cdc)
    wnd->ReleaseHDC();
*/
}
wxWindow* _wxGLWindow;
void GLContext::GLSetCurrent(void)
{
  wglMakeCurrent(hDC, hRC);
}
/*
 * wxGLCanvas implementation
 */

wxGLCanvas::wxGLCanvas(wxWindow *parent, int x, int y, int w, int h, long style, char *name):
  wxCanvas(parent, x, y, w, h, style, name)
{
  GLUtilities::adoptBridge(new wxWindowsBridge);
  glContext = new GLContext(this);
}

wxGLCanvas::~wxGLCanvas(void)
{
  if (glContext)
    delete glContext;
}

void wxGLCanvas::GLSwapBuffers(void)
{
  if (glContext)
    glContext->GLSwapBuffers(GetDC());
}
void wxGLCanvas::GLSetCurrent(void)
{
  _wxGLWindow = this;

  if (glContext)
    glContext->GLSetCurrent();
}
void wxGLCanvas::GLSetColour(const char *colour)
{
/*
  if (glContext)
    glContext->GLSetColour(colour);
*/
}
#endif /* wx_msw */

void wxGLCanvas::GLClear(void)
{
    GLSetCurrent();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
    glClearColor(0, 0, 0, 1.0);
    glClear((GLbitfield) (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void wxGLCanvas::initClass()
{
  GLUtilities::adoptBridge(new wxWindowsBridge);
}
