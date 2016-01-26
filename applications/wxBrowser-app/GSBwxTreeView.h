/*
 * GSBwxTreeView.h
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
 *  $Id: GSBwxTreeView.h,v 1.13 1997/04/17 09:39:12 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxTreeView_H
#define _GSBwxTreeView_H

#include "booga/glwrapper/GLRasterizer.h"
#include "booga/glwrapper/GLRenderer.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedDialogBox.h"
#include "booga/wxwrapper/wxManagedFrame.h"
#include "booga/wxwrapper/wxManagedSlider.h"

#include "GSBView.h"
#include "GSBTreeLayouter.h"
#include "wxManagedCanvas.h"

//_____________________________________________________________________ GSBwxTreeView

class GSBwxTreeView : public GSBView, public wxDialogDirector {
declareRTTI(GSBwxTreeView);
// enable RTTI support

enum DisplayMode {
        NORMAL,
        SHARED
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxTreeView(World3D* world, RCString& IDStr);
  
public:
  virtual ~GSBwxTreeView();

private:
  GSBwxTreeView& operator=(const GSBwxTreeView&);      // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxTreeView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  // Canvas stuff:
  void pan(Real dx, Real dy);                // panning
  void zoom(Real /* dx */, Real dy);         // zooming
  void moveCamera(Real dx, Real dy);
  void rotateAroundLookp(Real theta, Real phi);
  void pickObject(int x, int y);             // picking
  void fitToScreen();                        // make the tree fit into the screen
  void bestFitToScreen();
  void pruneNode();                          // pruning
  void showPicking(Object3D* obj);
  
  void updateViewing();
  void layout();
  void adoptTree(World2D* newWorld);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GSBView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void init();
  virtual void update(GSBViewManager::NotifyEvent event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GSBwxDialogDirector
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
  World2D*                          myTree;
  GSBTreeLayouter*                  myLayouter;
  World3D*                          mySharedWorld;
  World3D*                          myPickingWorld;
  
  // my widgets:
  wxManagedFrame*                   myFrame;
  wxManagedCanvas*                  myCanvas;
  wxManagedCanvas*                  myPickingCanvas;
  wxMenu*                           myViewMenu;
  wxMenu*                           myEditMenu;
  wxMenuBar*                        myMenuBar;
  wxManagedDialogBox*               myPrefs;
  wxManagedChoice*                  myLayoutChoice;
  wxManagedChoice*                  myTreeMotionQualityChoice;
  wxManagedSlider*                  myLayoutBorderSlider;
  wxManagedSlider*                  myLayoutDistanceToParentsSlider;
  wxManagedSlider*                  myPickingCanvasSizeSlider;
  wxManagedButton*                  myApplyButton;
  wxManagedButton*                  myCloseButton;

  // canvas stuff:
  float                             myXPos, myYPos;    // record last mouse position on canvas
  float                             myPickingXPos, myPickingYPos;
  GLRasterizer*                     myRasterizer;
  GLRenderer*                       myRenderer;
  DisplayMode                       myDisplayMode;
  Object3D*                         myMarkedObject;
  int                               myPickingCanvasSize;
  GLRasterizer::RenderingQuality    myTreeRenderingQuality;
  GLRasterizer::RenderingQuality    myTreeMotionQuality;
  GLRenderer::RenderingQuality      myPickingRenderingQuality;
  GLRenderer::RenderingQuality      myPickingMotionQuality;
  
  // layouting:
  long                              myLayoutBorder;
  long                              myLayoutDistanceToParents;
  bool                              myLayoutVertical;
  
  wxObject*                         deletionPending;
};


//______________________________________________________________________ INLINES

#endif // _GSBwxTreeView_H

