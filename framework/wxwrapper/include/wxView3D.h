/*
 * $RCSfile: wxView3D.h,v $
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
 *  $Id: wxView3D.h,v 1.6 1998/05/01 07:11:24 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _wxView3D_h_
#define _wxView3D_h_

#include "booga/wxwrapper/wxGLCanvas.h"
#include "booga/wxwrapper/wxBOOGAView.h"

#include "booga/glwrapper/GLRenderer.h"
#include "booga/glwrapper/GLWhitted.h"

class wxViewCommand;

//___________________________________________________________________ wxView3D

class wxView3D : public wxGLCanvas, public wxBOOGAView {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  wxView3D(wxWindow *parent, int x, int y, int w, int h, 
             long style=wxRETAINED, char *name="test");

private:
  wxView3D(const wxView3D&);                // No copies
  
public:
  ~wxView3D();                             
  
private:
  wxView3D& operator=(const wxView3D&);    // No assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class wxView3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void OnPaint(void);
  void OnSize(int w, int h);
  void OnEvent(wxMouseEvent& event);
  void renderSelection();

public: // ---- Rendering Quality ----
  void useRenderingQuality();
  void useMotionQuality();
  void changeRenderingQuality (GLRenderer::RenderingQuality q);
  GLRenderer::RenderingQuality getRenderingQuality ();
  void changeMotionQuality (GLRenderer::RenderingQuality q);
  GLRenderer::RenderingQuality getMotionQuality ();
  
public:  // ---- Mouse Motion ----
  wxMouseEvent getMouseEvent() const { return myMouseEvent; };

public: // ---- Motion Command ----
  void adoptMouseCommand (wxViewCommand* c);
  wxViewCommand *orphanMouseCommand();
   
public:  // ---- Access GLRenderer ----
  GLRenderer *getRenderer() {return myGLRenderer;};
//  void adoptRenderer (GLRenderer *r);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxViewCommand*       myMouseCommand;  // command for middle mouse button  
  wxMouseEvent         myMouseEvent;    // store wxMouseEvent 

  GLRenderer::RenderingQuality myMotionQuality;
  GLRenderer::RenderingQuality myRenderingQuality;

  GLRenderer *myGLRenderer;
};

//_________________________________________________________________________ inline's

inline GLRenderer::RenderingQuality wxView3D::getRenderingQuality () 
{
  return myRenderingQuality;
}

inline void wxView3D::changeRenderingQuality (GLRenderer::RenderingQuality q)
{
  myRenderingQuality = q;
}

inline void wxView3D::useRenderingQuality()
{ 
  getRenderer()->setRenderingQuality (myRenderingQuality);
}

inline GLRenderer::RenderingQuality wxView3D::getMotionQuality ()
{
  return myMotionQuality;
}

inline void wxView3D::changeMotionQuality (GLRenderer::RenderingQuality q)
{
  myMotionQuality = q;
}

inline void wxView3D::useMotionQuality()
{
  getRenderer()->setRenderingQuality (myMotionQuality);
}

#endif
