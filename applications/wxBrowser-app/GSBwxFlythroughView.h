/*
 * GSBwxFlythroughView.h
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
 *  $Id: GSBwxFlythroughView.h,v 1.5 1997/04/17 09:39:09 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxFlythroughView_H
#define _GSBwxFlythroughView_H

#include "booga/glwrapper/GLRenderer.h"

#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedDialogBox.h"
#include "booga/wxwrapper/wxManagedFrame.h"

#include "GSBView.h"
#include "wxManagedCanvas.h"

//_____________________________________________________________________ GSBwxFlythroughView


class GSBwxFlythroughView : public GSBView, public wxDialogDirector {
declareRTTI(GSBwxFlythroughView);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxFlythroughView(World3D* world, RCString& IDStr);
  
public:
  virtual ~GSBwxFlythroughView();

private:
  GSBwxFlythroughView& operator=(const GSBwxFlythroughView&);      // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxFlythroughView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // Canvas stuff:
  void moveCamera(Real dx, Real dy);
  void rotateAroundLookp(Real theta, Real phi);
  void adoptWorld(World3D* world);
  void pickObject(int x, int y);             // picking
//  void pruneNode();                          // pruning
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GSBView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void init();
  virtual void update(GSBViewManager::NotifyEvent event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void createGUI();
  
  virtual void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);
  virtual ActionRequest widgetOnChar(wxObject* widget, wxKeyEvent& event);
  virtual ActionRequest widgetOnClose(wxObject* widget);
  virtual ActionRequest widgetOnSize(wxObject* widget, int width, int height);
  virtual ActionRequest widgetOnMenuCommand(wxObject* widget, int id);
  virtual ActionRequest widgetOnPaint(wxObject* widget);
  virtual ActionRequest widgetOnEvent(wxObject* widget, wxMouseEvent& event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // data members concerning tree
  Object3D*                         myPickedObject;
  
  // my widgets (wxObjects):
  wxManagedFrame*                   myFrame;
  wxManagedCanvas*                  myCanvas;
  wxMenu*                           myViewMenu;
  wxMenu*                           myEditMenu;
  wxMenuBar*                        myMenuBar;
  wxManagedDialogBox*               myPrefs;
  wxManagedChoice*                  myMotionQualityChoice;
  wxManagedButton*                  myApplyButton;
  wxManagedButton*                  myCloseButton;

  // canvas stuff:
  float                             myXPos, myYPos;    // record last mouse position on canvas
  float                             myPickingXPos, myPickingYPos;
  GLRenderer*                       myRenderer;
  Object3D*                         myMarkedObject;
  GLRenderer::RenderingQuality      myRenderingQuality;
  GLRenderer::RenderingQuality      myMotionQuality;

  wxObject*                         deletionPending;
};


//______________________________________________________________________ INLINES

#endif // _GSBwxFlythroughView_H

