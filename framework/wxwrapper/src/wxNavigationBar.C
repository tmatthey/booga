/*
 * $RCSfile: wxNavigationBar.C,v $
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
 *  $Id: wxNavigationBar.C,v 1.2 1998/05/01 07:11:20 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Viewing3D.h"
#include "booga/object/Camera3D.h"

#include "booga/component/Collector3DFor.h"

#include "booga/wxwrapper/wxNavigationBar.h"
#include "booga/wxwrapper/wxMotionCommands.h"

wxNavigationBar::wxNavigationBar (wxView3D* v, wxWindow *parent) : wxViewCommand(v), wxPanel(parent)
{
  createGUI();
  myCameraIndex = -1;
}

void wxNavigationBar::createGUI()
{
  myBackwardButton = new wxManagedButton (this,this,"<<");
  myForwardButton = new wxManagedButton (this,this,">>");
  myPanButton = new wxManagedButton (this,this,"Pan");
  myInspectButton = new wxManagedButton (this,this,"Inspect");
  myLookButton = new wxManagedButton (this,this,"Look");
  myZoomButton = new wxManagedButton (this,this,"Zoom");
  myWalkButton = new wxManagedButton (this,this,"Walk");
  myGetCloseButton = new wxManagedButton (this,this,"Approach");
  myPointToButton = new wxManagedButton (this,this,"Point To");
  myHomeButton = new wxManagedButton (this,this,"Home");
  NewLine();

  myCameraChoice = new wxManagedChoice (this, this, "Cameras", -1,-1,300,-1,0,NULL);
  myAddCameraButton = new wxManagedButton (this,this,"Add Camera");
  mySetCameraButton = new wxManagedButton (this,this,"Set Camera");

  Fit();
}

void wxNavigationBar::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget==myInspectButton) 
    getView()->adoptMouseCommand (new wxInspectCommand (getView()));
  if (widget==myLookButton) 
    getView()->adoptMouseCommand (new wxLookCommand (getView()));
  if (widget==myZoomButton) 
    getView()->adoptMouseCommand (new wxZoomCommand (getView()));
  if (widget==myPanButton) 
    getView()->adoptMouseCommand (new wxPanCommand (getView()));
  if (widget==myGetCloseButton) 
    getView()->adoptMouseCommand (new wxGetCloseCommand (getView()));
  if (widget==myPointToButton) 
    getView()->adoptMouseCommand (new wxPointToCommand (getView()));
  if (widget==myWalkButton) 
    getView()->adoptMouseCommand (new wxWalkCommand (getView()));
  if (widget==myHomeButton) {
    wxHomeCommand h(getView());
    h.execute();
  }
  if (widget==myForwardButton) {
    if (myCameraIndex < (myCameraList.count() - 1) ) {
      // switch to next camera:
      myCameraIndex++;
	  interpolateCamera(getView()->getRenderer()->getCamera(),
		                myCameraList.item(myCameraIndex));
    }
  }
  
  if (widget==myBackwardButton) {
    if (myCameraIndex > 0) {
      // switch to next camera:
      myCameraIndex--;
  	  interpolateCamera(getView()->getRenderer()->getCamera(),
		                myCameraList.item(myCameraIndex));
    }
  }

  if (widget ==	myCameraChoice) {
	// switch all cameras off
	for (int i=0; i<myDefinedCameraList.count(); i++)
		myDefinedCameraList.item(i)->turnOff();				 
    interpolateCamera(getView()->getRenderer()->getCamera(),
                      myDefinedCameraList.item(myCameraChoice->GetSelection()));
    myDefinedCameraList.item(myCameraChoice->GetSelection())->turnOn();
    getView()->getRenderer()->adoptCamera((Camera3D *)myDefinedCameraList.item(myCameraChoice->GetSelection())->copy());
    getView()->OnPaint();
  }

  if (widget ==	myAddCameraButton) {
	Camera3D *c =  (Camera3D *) getView()->getRenderer()->getCamera()->copy();
	c->setName(wxGetTextFromUser("Name of new camera", "Input name", "Camera"));
	myDefinedCameraList.append(c);
	getViewManager()->getWorld()->getObjects()->adoptObject(c);
	myCameraChoice->Append((char*)RCString(c->getName()).chars());
  }												

  if (widget == mySetCameraButton) {
	Viewing3D *v =  (Viewing3D *) getView()->getRenderer()->getCamera()->getViewing();
	myDefinedCameraList.item(myCameraChoice->GetSelection())->adoptViewing(v->copy());
  }
}

void wxNavigationBar::interpolateCamera(const Camera3D *cold, const Camera3D *cnew)
{
  Viewing3D* viewing = getView()->getRenderer()->getCamera()->getViewing();
  Vector3D oldlookat = cold->getViewing()->getLookat();
  Vector3D oldeye = cold->getViewing()->getEye();  
  Vector3D newlookat = cnew->getViewing()->getLookat();
  Vector3D neweye = cnew->getViewing()->getEye();  
	  
  Vector3D dlookat = newlookat - oldlookat;
  Vector3D deye = neweye - oldeye;


  Real intervall = 100;
  Real frames = 10;
  for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
    Real value = log (i) / log (intervall);
    Vector3D clookat = oldlookat + value*dlookat;
    Vector3D ceye = oldeye + value*deye;
    viewing->setLookat(clookat);
    viewing->setEye(ceye);
    getView()->useMotionQuality();
    getView()->OnPaint();
  }
  getView()->useRenderingQuality();
  getView()->OnPaint();
}

void wxNavigationBar::update(wxViewManager::NotifyEvent event, Object3D*  obj)
{
  switch (event) {
    case wxViewManager::REPAINT:
      break;
    case wxViewManager::WORLD_CHANGED:      
    case wxViewManager::WORLD_NEW: {
	  // remove all cameras from history
	  for (int i=0; i<myCameraList.count(); i++)
		  delete myCameraList.item(i);
	  myCameraList.removeAll();
      myCameraIndex = -1;

	  // remove all cameras from defined list
      myDefinedCameraList.removeAll();
	  // clear cameras from choice
	  myCameraChoice->Clear();

	  // collect all cameras and init choice
      Collector3DFor<Camera3D> camCollector;
      camCollector.execute(getViewManager()->getWorld());
	  int j = 0;
	  for (camCollector.first(); !camCollector.isDone(); j++, camCollector.next()) {
		Camera3D *c = camCollector.getObject(); 
	    myDefinedCameraList.append(c);
		if (c->getName() == Name(""))
		  myCameraChoice->Append("Camera");
		else 
		  myCameraChoice->Append((char*)RCString(c->getName()).chars());
	  }
      myCameraChoice->SetSelection(0);

      break;
    }
    
    case wxViewManager::CAMERAS_CHANGED: {
      Camera3D *cam = dynamic_cast(Camera3D,obj);
      if (cam) {
        // remove all cameras after the current index:
		for (int i=myCameraList.count()-1; i > myCameraIndex; i--) {
			delete myCameraList.item(i);
			myCameraList.remove(i);
		}

        myCameraList.append((Camera3D *)cam->copy());
        myCameraIndex = myCameraList.count() - 1;
      }
      break;
    }

    default:
      break;
  }
}
