/*
 * GSBwxConetreeView.h
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
 *  $Id: GSBwxConetreeView.h,v 1.7 1997/04/17 09:39:03 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxConetreeView_H
#define _GSBwxConetreeView_H

// order of included files is relevant!
#include "booga/glwrapper/GLRenderer.h"
#include "booga/wxwrapper/wxDialogDirector.h"
//#include "booga/wxwrapper/wxManagedButton.h"
//#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedFrame.h"
//#include "booga/wxwrapper/wxManagedSlider.h"

#include "wxManagedCanvas.h"
#include "GSBView.h"
#include "GSBConetreeLayouter.h"

//_____________________________________________________________________ GSBwxConetreeView


class GSBwxConetreeView : public GSBView, public wxDialogDirector {
declareRTTI(GSBwxConetreeView);
// enable RTTI support

public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBwxConetreeView(World3D* world, RCString& IDStr);
  virtual ~GSBwxConetreeView();
  
private:
  GSBwxConetreeView(const GSBwxConetreeView&);             // No copies.

private:
  GSBwxConetreeView& operator=(const GSBwxConetreeView&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBwxConetreeView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void layout();
  void rotateAroundLookp(Real theta, Real phi);
  void moveCamera(Real dx, Real dy);
  void adoptTree(World3D* newWorld);
  void updateViewing();
  void pickObject(int x, int y);
  void rotateBranch(Real phi);
  
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
  World3D*                          myTree;
  GSBConetreeLayouter*              myLayouter;
  Object3D*                         myPickedObject;
  Object3D*                         myPivotObject;
  Path3D*                           myPivotObjectPath;
  
  // my widgets (wxObjects):
  wxManagedFrame*                   myFrame;
  wxManagedCanvas*                  myCanvas;
  wxMenu*                           myViewMenu;
//  wxMenu*                           myEditMenu;
  wxMenuBar*                        myMenuBar;
//  wxManagedDialogBox*               myPrefs;
//  wxManagedChoice*                  myLayoutChoice;
//  wxManagedChoice*                  myTreeMotionQualityChoice;
//  wxManagedSlider*                  myLayoutBorderSlider;
//  wxManagedSlider*                  myLayoutDistanceToParentsSlider;
//  wxManagedSlider*                  myPickingCanvasSizeSlider;
//  wxManagedButton*                  myApplyButton;
//  wxManagedButton*                  myCloseButton;

  // canvas stuff:
  float                             myXPos, myYPos;    // record last mouse position on canvas
  GLRenderer*                       myRenderer;
  GLRenderer::RenderingQuality      myTreeRenderingQuality;
  GLRenderer::RenderingQuality      myTreeMotionQuality;

  // layouting:
  long                              myLayoutBorder;
  long                              myLayoutDistanceToParents;
  bool                              myLayoutVertical;
  
  wxObject*                         deletionPending;
};


//______________________________________________________________________ INLINES

#endif // _GSBwxConetreeView_H

