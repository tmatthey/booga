/*
 * $RCSfile: wxNavigationBar.h,v $
 *
 * Copyright (C) 1996, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxNavigationBar.h,v 1.1 1998/01/06 08:49:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxManagedChoice.h"

#include "wx_panel.h"

class Camera3D; // forward declaration

class wxNavigationBar : public wxDialogDirector, public wxBOOGAView, public wxViewCommand, public wxPanel {

public:
	wxNavigationBar(wxView3D *v, wxWindow *parent);

	void interpolateCamera(const Camera3D *cold, const Camera3D *cnew);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void createGUI();
  
  // interface for wxObjects widgets
  void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	void execute() {};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
    
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  wxManagedButton* myPanButton;
  wxManagedButton* myInspectButton;
  wxManagedButton* myLookButton;
  wxManagedButton* myZoomButton;
  wxManagedButton* myGetCloseButton;
  wxManagedButton* myPointToButton;
  wxManagedButton* myWalkButton;
  wxManagedButton* myHomeButton;
  wxManagedButton* myForwardButton;
  wxManagedButton* myBackwardButton;
  wxManagedChoice* myCameraChoice;
  wxManagedButton* myAddCameraButton;
  wxManagedButton* mySetCameraButton;


  // the camera history
  List<Camera3D*> myCameraList;
  int myCameraIndex;

  // list of all defined cameras in the world
  List<Camera3D*> myDefinedCameraList;
};

