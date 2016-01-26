/*
 * $RCSfile: wxCameraEditor.C,v $
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxCameraEditor.C,v 1.17 1998/05/01 07:11:15 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"

#include "booga/component/Collector3DFor.h"
 
#include "booga/animation/Tumble3D.h"
#include "booga/animation/ActionInfo.h"

#include "booga/wxwrapper/wxCameraEditor.h"

//_____________________________________________________________________ wxCameraEditor

implementRTTI(wxCameraEditor, wxBOOGAView);

wxCameraEditor::wxCameraEditor(wxView3D *v, wxWindow *parent) : wxViewCommand(v), wxPanel (parent)
{
  myTumbleChoice = NULL;
  myListBox = NULL;
  myStartFrameText = NULL;
  myEndFrameText = NULL;
  mySetButton = NULL;
  myAppendButton = NULL;
  myInsertButton = NULL;
  myDeleteButton = NULL;
  myNewButton = NULL;
  myPreviewButton = NULL;
  
  myTumbleListIndex = -1;
  myCurrentKeyFrame = -1;
  createGUI();
  updateGUI();
}

wxCameraEditor::~wxCameraEditor()
{
}  

void wxCameraEditor::update(wxViewManager::NotifyEvent event, Object3D*)
{
  switch (event) {
	case wxViewManager::WORLD_CHANGED: 
  case wxViewManager::WORLD_NEW: {
    // collecting all animated cameras:
    Collector3DFor<Tumble3D> tumbleCollector;
    tumbleCollector.execute(getViewManager()->getWorld());
        
    // clear all tumbles:
    myTumbleList.removeAll();
	myTumbleListIndex = -1;

    // check all cameras if it is a tumblepath-animated camera
    // camera should be stored as followed:
    // World3D->ActionInfo->Camera3D
    // so we have to find an appropriate path
    cerr << "#tumbles: " << tumbleCollector.count() << "\n"; 
    for (tumbleCollector.first(); !tumbleCollector.isDone(); tumbleCollector.next()) {
      // check if the first subobject of tumplepath is a camera
      if (dynamic_cast(Camera3D, tumbleCollector.getObject()->getSubobject(0))) {
				// check if TumblePath and TumbleDirection have equal control points
        List<ActionInfo*> l = tumbleCollector.getObject()->getActions();
        if(l.item(0)->getTumbleMove()->getVectors().count() != l.item(0)->getTumbleMove()->getVectors().count()) {
					Report::warning("[wxCameraEditor::update] TumblePath and TumbleDirection not equal # of points!");
				} else {
          myTumbleList.append(tumbleCollector.getObject());
				}
			}
    }
    createGUI(); // this must come after initialisation of myTumbleList

	if (myTumbleList.count()) {
		myTumbleListIndex = 0;
		myTumbleChoice->SetSelection(0);
		updateGUI();
	}
  }
  default:
      break;
  }
}

void wxCameraEditor::createGUI()
{
  if (myTumbleChoice){ 
    delete myTumbleChoice;
    myTumbleChoice = NULL;
  }
  if (myListBox){ 
    delete myListBox;
    myListBox = NULL;
  }
  if (mySetButton){ 
    delete mySetButton;
    mySetButton = NULL;
  }
  if (myInsertButton){ 
    delete myInsertButton;
    myInsertButton = NULL;
  }
  if (myDeleteButton){ 
    delete myDeleteButton;
    myDeleteButton = NULL;
  }
  if (myAppendButton){ 
    delete myAppendButton;
    myAppendButton = NULL;
  }
  if (myStartFrameText){ 
    delete myStartFrameText;
    myStartFrameText = NULL;
  }
  if (myEndFrameText){ 
    delete myEndFrameText;
    myEndFrameText = NULL;
  }
  if (myPreviewButton){ 
    delete myPreviewButton;
    myPreviewButton = NULL;
  }
  if (myNewButton){ 
    delete myNewButton;
    myNewButton = NULL;
  }


  if (!myTumbleList.count()) {
    myNewButton = new wxManagedButton(this,this,"Add New Camera");
    NewLine();
	Fit();
  } else {
    myTumbleChoice = new wxManagedChoice(this, this, "Cameras", -1,-1,250,-1,0,NULL);
    for (int i=0; i<myTumbleList.count(); i++)
      myTumbleChoice->Append((char*)RCString(myTumbleList.item(i)->getSubobject(0)->getName()).chars());

	NewLine();
    myListBox = new wxManagedListBox(this, this, "Keyframes", wxSINGLE, -1, -1, 150, 100);
    NewLine();
    mySetButton = new wxManagedButton(this,this,"Set");
    myInsertButton = new wxManagedButton(this,this,"Insert");
    NewLine();
    myAppendButton = new wxManagedButton(this,this,"Append");
    myDeleteButton = new wxManagedButton(this,this,"Delete");
    NewLine();
    myStartFrameText = new wxManagedText(this,this,"Startframe","0", -1,-1,120);
    NewLine();
    myEndFrameText = new wxManagedText(this,this,"Endframe","0", -1,-1,120);
    NewLine();
    myPreviewButton = new wxManagedButton(this,this,"Preview");
    NewLine();
    myNewButton = new wxManagedButton(this,this,"Add New Camera");

    Fit();
  }
}

void wxCameraEditor::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget == myTumbleChoice) {
    myTumbleListIndex = myTumbleChoice->GetSelection();
  	updateGUI();
  }
  if (widget == myNewButton) {	
	// insert a new animated camera
		Camera3D *c = (Camera3D *)getView()->getRenderer()->getCamera()->copy();
		c->setName(wxGetTextFromUser("Name of new camera", "Input name", "Camera"));
        Tumble3D *t = new Tumble3D();
		ActionInfo *a = new ActionInfo(0, 10, 1, 0);

		List<Vector3D> e;
		e.append(c->getViewing()->getEye());
		e.append(c->getViewing()->getEye()+Vector3D(1,1,0));
		e.append(c->getViewing()->getEye()+Vector3D(2,2,0));

		List<Vector3D> l;
		l.append(c->getViewing()->getLookat());
		l.append(c->getViewing()->getLookat()+Vector3D(1,1,0));
		l.append(c->getViewing()->getLookat()+Vector3D(2,2,0));
        a->adoptTumblePath(new InterpolationCurve3D(e),RCString("id"),0,20,0);
        a->adoptTumbleDirection(new InterpolationCurve3D(l));
		t->adoptAction(a);
		// set lookat to (eye+[1,0,0]) for proper direction
		c->getViewing()->setLookat(c->getViewing()->getEye()+Vector3D(1,0,0));

		t->adoptObject(c); // add the camera to the tumble object

		getViewManager()->getWorld()->getObjects()->adoptObject(t);
		getViewManager()->notify(wxViewManager::WORLD_CHANGED, getViewManager()->getWorld()->getObjects());
  }

	// all other functions can only be executed if some animated cameras are present
  if (myTumbleListIndex	< 0)
	  return; // evaluate events only if something is in the list

  if (widget == myListBox) {
    myCurrentKeyFrame = myListBox->GetSelection();

    Camera3D *cnew = (Camera3D *)getView()->getRenderer()->getCamera()->copy();
		
    cnew->getViewing()->setEye(myEyeList.item(myCurrentKeyFrame));
    cnew->getViewing()->setLookat(myLookatList.item(myCurrentKeyFrame));
    interpolateCamera(getView()->getRenderer()->getCamera(), cnew);
    delete cnew;
  }

  if (widget == mySetButton) {
    if (myCurrentKeyFrame >= 0) {
	  // update our lists:
	  myEyeList.item(myCurrentKeyFrame) = getView()->getRenderer()->getCamera()->getViewing()->getEye();
	  myLookatList.item(myCurrentKeyFrame) = getView()->getRenderer()->getCamera()->getViewing()->getLookat();
      updateTumblePath();
	}
  }
  if (widget == myInsertButton) {
    if (myCurrentKeyFrame >= 0) {
	  // append the last item at the end of the list
	  myEyeList.append(myEyeList.item(myEyeList.count()-1));
	  myLookatList.append(myEyeList.item(myEyeList.count()-1));

	  for (int i=myEyeList.count()-1; i>myCurrentKeyFrame; i--) {
		myEyeList.item(i) = myEyeList.item(i-1);
		myLookatList.item(i) = myLookatList.item(i-1);
	  }
	  // set the current entry
	  myEyeList.item(myCurrentKeyFrame) = getView()->getRenderer()->getCamera()->getViewing()->getEye();
	  myLookatList.item(myCurrentKeyFrame) = getView()->getRenderer()->getCamera()->getViewing()->getLookat();

      updateTumblePath();
	  updateGUI();
	}
  }

  if (widget == myAppendButton) {
    if (myCurrentKeyFrame >= 0) {
	  // append the current camera to the end of the list
	  myEyeList.append(getView()->getRenderer()->getCamera()->getViewing()->getEye());
	  myLookatList.append(getView()->getRenderer()->getCamera()->getViewing()->getLookat());

	  updateTumblePath();
	  updateGUI();
	}
  }

  if (widget == myDeleteButton) {
    if (myCurrentKeyFrame >= 0 && myEyeList.count() > 3) {
	  // remove only if more than 3 elements
	  // append the current camera to the end of the list
	  int answer = wxMessageBox("Delete this Keyframe?", "Confirm",
                            wxYES_NO | wxCANCEL);
      if (answer == wxYES) {
        myEyeList.remove(myCurrentKeyFrame);
	    myLookatList.remove(myCurrentKeyFrame);

        updateTumblePath();

		updateGUI();
	  }
	}
  }

  if (widget == myStartFrameText) {
    Real theStartFrame = atof (myStartFrameText->GetValue());
    List<ActionInfo*> l = myTumbleList.item(myTumbleListIndex)->getActions();
    ActionInfo *a = l.item(0);
    a->setParameters(theStartFrame,a->getEndFrame(), a->getTimes(), a->getWait());
  }

  if (widget == myEndFrameText) {
    Real theEndFrame = atof (myEndFrameText->GetValue());
    List<ActionInfo*> l = myTumbleList.item(myTumbleListIndex)->getActions();
    ActionInfo *a = l.item(0);
    a->setParameters(a->getStartFrame(),theEndFrame, a->getTimes(), a->getWait());
  }
  if ((widget == myPreviewButton) && (myTumbleListIndex >= 0)) {
	// collect all animated objects
	Collector3DFor<Animation3D> animCollector;
    animCollector.execute(getViewManager()->getWorld());

	// create the path to the camera:
  	Path3D myPath;

	myPath.reset();
	myPath.append(myTumbleList.item(myTumbleListIndex));
	myPath.append(myTumbleList.item(myTumbleListIndex)->getSubobject(0));

    List<ActionInfo*> l = myTumbleList.item(myTumbleListIndex)->getActions();
    ActionInfo *a = l.item(0);
	int startFrame = (int)(a->getStartFrame());
	int endFrame = (int)(a->getEndFrame());


	for (int i=startFrame; i<=endFrame; i++) {
		// position animation objects
        for (animCollector.first(); !animCollector.isDone(); animCollector.next())
          animCollector.getObject()->frame(i);

		Transform3D myTransform;
        Path3D tempPath;
        for (myPath.first(); !myPath.isDone(); myPath.next())
//          myTransform.addTransform(myPath.getObject()->getTransform());
		  tempPath.append(myPath.getObject());
      
        myTransform = tempPath.getLastTransform();
  
        // make a copy of this camera and modify it
  
        Camera3D *myCamera = dynamic_cast(Camera3D, myPath.getLastObject());

		getView()->getRenderer()->getCamera()->getViewing()->setEye(myCamera->getViewing()->getEye()*myTransform.getTransMatrix());
		getView()->getRenderer()->getCamera()->getViewing()->setLookat(myCamera->getViewing()->getLookat()*myTransform.getTransMatrix());
		getView()->OnPaint();
		/*
        Camera3D *copyCam = (Camera3D *) myCamera->copy();
        if (copyCam) {
  
          copyCam->getViewing()->setEye(myCamera->getViewing()->getEye()*myTransform.getTransMatrix());
          copyCam->getViewing()->setLookat(myCamera->getViewing()->getLookat()*myTransform.getTransMatrix());
  
          // now tell all the views to update their camera.
          getViewManager()->notify(wxViewManager::CAMERAS_CHANGED, copyCam);

          // get rid of the temporary camera again.
          delete copyCam;
        }
		*/
	}
    for (animCollector.first(); !animCollector.isDone(); animCollector.next())
      animCollector.getObject()->frame(0);
  
  }
}

void wxCameraEditor::updateTumblePath()
{
  List<ActionInfo*> l = myTumbleList.item(myTumbleListIndex)->getActions();
  ActionInfo *a = l.item(0);

  a->adoptTumblePath(new InterpolationCurve3D(myEyeList),a->getAnimationFunction()->getKeyword(),a->getStartFrame(), a->getEndFrame(), a->getWait());
  a->adoptTumbleDirection(new InterpolationCurve3D(myLookatList));	

  Camera3D *myCamera = dynamic_cast(Camera3D, myTumbleList.item(myTumbleListIndex)->getSubobject(0));
  myCamera->getViewing()->setEye(myEyeList.item(0));
  myCamera->getViewing()->setLookat(myEyeList.item(0) + Vector3D(1,0,0));
}


void wxCameraEditor::updateGUI()
{
  if (myListBox)
    myListBox->Clear();
  if (myTumbleListIndex < 0) {																			 
//  myStartFrameText->SetValue("***");
//	myStartFrameText->SetEditable(FALSE);
//    myEndFrameText->SetValue("***");
//	myEndFrameText->SetEditable(FALSE);
    myEyeList.removeAll();
    myEyeList.removeAll();
	myCurrentKeyFrame = -1;
    return;
  }

  List<ActionInfo*> l = myTumbleList.item(myTumbleListIndex)->getActions();
  myEyeList.removeAll();
  myEyeList = List<Vector3D>(l.item(0)->getTumbleMove()->getVectors());
  myLookatList.removeAll();
  myLookatList = List<Vector3D>(l.item(0)->getTumbleDirection()->getVectors());

  char buf[256];
  for (int i=0; i<myEyeList.count(); i++) {
	sprintf (buf, "Keyframe %d", i);
    myListBox->Append(buf, NULL);
  }

  sprintf (buf,"%3.2f",l.item(0)->getStartFrame());
  myStartFrameText->SetValue(buf);
  myStartFrameText->SetEditable(TRUE);
  sprintf (buf,"%3.2f",l.item(0)->getEndFrame());
  myEndFrameText->SetValue(buf);
  myEndFrameText->SetEditable(TRUE);

  myCurrentKeyFrame = 0;
  myListBox->SetSelection(0);
  wxCommandEvent e(wxEVENT_TYPE_LISTBOX_COMMAND);
  widgetCallbackFunction(myListBox,e);
}

void wxCameraEditor::interpolateCamera(const Camera3D *cold, const Camera3D *cnew)
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
