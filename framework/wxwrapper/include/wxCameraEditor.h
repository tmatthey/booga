/*
 * $RCSfile: wxCameraEditor.h,v $
 *
 * Copyright (C) 1995, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxCameraEditor.h,v 1.11 1998/05/01 07:11:16 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxCameraEditor_H
#define _wxCameraEditor_H

#include "booga/animation/Tumble3D.h"
#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedListBox.h"
#include "booga/wxwrapper/wxManagedText.h"
#include "booga/wxwrapper/wxManagedButton.h"

//_____________________________________________________________________ wxCameraEditor

class wxCameraEditor : public wxBOOGAView, wxViewCommand, public wxDialogDirector, public wxPanel {
declareRTTI(wxCamerEditor);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxCameraEditor(wxView3D *v, wxWindow *parent);
private:
  wxCameraEditor(const wxCameraEditor&);             // No copies.

public:
  ~wxCameraEditor();                

private:
  wxCameraEditor& operator=(const wxCameraEditor&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxCameraEditor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void updateGUI();
  void interpolateCamera(const Camera3D *cold, const Camera3D *cnew);
  void updateTumblePath();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	void execute() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void createGUI();
  
  // interface for wxObjects widgets
  void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxManagedChoice   *myTumbleChoice;
  wxManagedListBox  *myListBox;
  wxManagedText     *myStartFrameText;
  wxManagedText     *myEndFrameText;
  wxManagedButton   *mySetButton;
  wxManagedButton   *myAppendButton;
  wxManagedButton   *myInsertButton;
  wxManagedButton   *myDeleteButton;
  wxManagedButton   *myNewButton;
  wxManagedButton   *myPreviewButton;

  List<Tumble3D*> myTumbleList;
  int myTumbleListIndex;
  List<Vector3D> myEyeList;
  List<Vector3D> myLookatList;
  int myCurrentKeyFrame;
};

//______________________________________________________________________ INLINES

#endif // _wxCameraEditor_H

