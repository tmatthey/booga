/*
 * wxAnimator.C 
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxAnimator.C,v 1.3 1998/05/01 07:11:14 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/List.h"
#include "booga/base/ListUtilities.h"

#include "booga/component/Collector3DFor.h"
#include "booga/object/Viewing3D.h"

#include "booga/wxwrapper/wxAnimator.h"
#include "wxstring.h"

class dialCanvas : public wxCanvas {
public:
  dialCanvas (wxWindow *parent, int x=-1, int y=-1, int width=100, int height=100);

  void OnEvent(wxMouseEvent& event);
  void OnPaint();

private:
  float oldx, oldy;
  float angle; 
  wxFont *myFont;
};


dialCanvas::dialCanvas (wxWindow *parent, int x, int y, int width, int height) : wxCanvas (parent, x, y, width, height)
{
  oldx = oldy = -1;
  angle = 0;
  myFont = new wxFont(11, wxROMAN, wxNORMAL, wxNORMAL);
}

void dialCanvas::OnEvent(wxMouseEvent& event)
{
  wxAnimator *a = (wxAnimator *) GetGrandParent();

  float x, y;
  event.Position(&x, &y);

  

  if (x > -1 && y > -1 /* && event.Dragging()*/ && event.LeftIsDown()) {
    int width, height;
    GetClientSize(&width,&height);
    if (angle > width)
      angle = width/2;
    else
      angle = x - (width/2);
      
//    angle = x > 100 ? 50 : x-50;
    a->setFrameStep (angle / 10.0);
//    if (angle > 0.0)
//      a->nextFrame();
//    else 
//      a->previousFrame();
    SetBackground (wxTRANSPARENT_BRUSH);
    GetDC()->Clear();  
    OnPaint();    
    a->getViewManager()->notify (wxViewManager::REPAINT, NULL);
    
  } else if (event.LeftUp()) {
    angle = 0;
    a->setFrameStep(1.0);
    SetBackground (wxTRANSPARENT_BRUSH);
    GetDC()->Clear();  
    OnPaint();    
  }    
  oldx = x;
}

void dialCanvas::OnPaint()
{
  wxAnimator *a = (wxAnimator *) GetGrandParent();
  wxDC *dc = GetDC();

  dc->SetBrush(wxWHITE_BRUSH);
  dc->SetPen(wxBLACK_PEN);
  int width, height;
  GetClientSize(&width,&height);
  dc->DrawEllipse (0,0,width,height);

  int knob_size = width/5;
  int factor = (width-knob_size)/2;
  dc->SetBrush(wxBLACK_BRUSH);
  dc->DrawEllipse (factor+factor*sin(dtor(angle)),factor-factor*cos(dtor(angle)),knob_size,knob_size);
  
  wxString f;
//  f.sprintf ("%f", a->getCurrentFrame());
  dc->SetFont (myFont);
  float x,y;
  GetTextExtent (f.Chars(), &x, &y);
  dc->DrawText (f.Chars(), (width/2)-(x/2), (height/2) -(y/2));
}


//_____________________________________________________________________ wxAnimator

implementRTTI(wxAnimator, wxBOOGAView);

wxAnimator::wxAnimator()
{
}

wxAnimator::wxAnimator(wxFrame* parent, int x, int y, int width, int height) : wxFrame (parent, "Animator", x, y, width, height)
{
  myAnimationList = NULL;
  myCurrentFrame  = 0;
  myLastFrame = 0;
  myFrameStep = 1.0;
  myTimer = new wxAnimationTimer (this);
  myAnimateCamera = false;
  createGUI();
}

void wxAnimator::createGUI()
{

  myPanel = new wxPanel(this);
  myPlayButton = new wxManagedButton (this, myPanel, "Play");
  myRewindButton = new wxManagedButton (this, myPanel, "Rewind");
  myStopButton = new wxManagedButton (this, myPanel, "Stop");
  myAnimateCameraCheckBox = new wxManagedCheckBox (this, myPanel, "Animate Camera");
  
  myPanel->NewLine();
  myDialBox = new dialCanvas(myPanel,30,50,60,60);
  
  myPanel->Fit();
  Fit();

}

void wxAnimator::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
{
  switch (event) {
    case wxViewManager::REPAINT:
      break;
      
    case wxViewManager::CAMERAS_CHANGED:
      break;
      
    case wxViewManager::WORLD_NEW: 
    case wxViewManager::WORLD_CHANGED: {
      //
      // Collect all animation objects in the new world.
      //  
      if (myAnimationList != NULL)
        delete myAnimationList;

      if (!getViewManager()->getWorld())
        break; // NULL world
    
      myAnimationList = new List<Animation3D*>;
      Collector3DFor<Animation3D> animCollector;
      animCollector.execute(getViewManager()->getWorld());
      for (animCollector.first(); !animCollector.isDone(); animCollector.next())
        myAnimationList->append(animCollector.getObject());
      
	  myPath.reset();
	  //  
      //
      // Collect all cameras in the newWorld.
      //  
      Collector3DFor<Camera3D> camCollector;
      camCollector.execute(myViewManager->getWorld());

      //
      // Look for first camera in newWorld, that is switched on.
      //
      
      for (camCollector.first(); !camCollector.isDone(); camCollector.next())
        if (camCollector.getObject()->isOn()) {
          for (camCollector.getPath()->first(); !camCollector.getPath()->isDone(); camCollector.getPath()->next())
            myPath.append(camCollector.getPath()->getObject()); 
          break;
        }
      break;        
   }
    default:
      break;
  }
}

void wxAnimator::play ()
{
  myTimer->Start(100);
}

void wxAnimator::stop ()
{
  myTimer->Stop();
}

void wxAnimator::rewind ()
{
  myCurrentFrame = 0; 
  stop(); 
}

void wxAnimator::doFrame (Real f)
{
  if (!myAnimationList) 
    return;
    
  long count = myAnimationList->count();
  for (long i=0; i<count; i++)
    myAnimationList->item(i)->frame(f);

  getViewManager()->getWorld()->getObjects()->computeBounds();
}

void wxAnimator::nextFrame ()
{
  if (!myAnimationList) 
    return;
  myCurrentFrame+=myFrameStep;  

  long count = myAnimationList->count();
  for (long i=0; i<count; i++)
    myAnimationList->item(i)->frame(myCurrentFrame);

  if (myAnimateCamera) {
    // myPath stores the path to the first camera in the scene.
    // we have to calculate the current transformation of the camera, 
    // since it may be animated.
  
  
  
    // calculate the current transformation of the camera
  
    Transform3D myTransform;
    Path3D tempPath;
    for (myPath.first(); !myPath.isDone(); myPath.next())
      tempPath.append(myPath.getObject());
      
    myTransform = tempPath.getLastTransform();
  
    // make a copy of this camera and modify it
  
    Camera3D *myCamera = dynamic_cast<Camera3D*>(myPath.getLastObject());
    Camera3D *copyCam = (Camera3D *) myCamera->copy();
    if (copyCam) {
  
      copyCam->getViewing()->setEye(myCamera->getViewing()->getEye()*myTransform.getTransMatrix());
      copyCam->getViewing()->setLookat(myCamera->getViewing()->getLookat()*myTransform.getTransMatrix());
  
      // now tell all the views to update their camera.
      getViewManager()->notify(wxViewManager::CAMERAS_CHANGED, copyCam);

      // get rid of the temporary camera again.
      delete copyCam;
    }
  }
  getViewManager()->getWorld()->getObjects()->computeBounds();

  myDialBox->OnPaint();
}

void wxAnimator::previousFrame ()
{
  if (!myAnimationList) 
    return;
  myCurrentFrame-=myFrameStep;  

  long count = myAnimationList->count();
  for (long i=0; i<count; i++)
    myAnimationList->item(i)->frame(myCurrentFrame);

  getViewManager()->getWorld()->getObjects()->computeBounds();
  myDialBox->OnPaint();
}

int wxAnimator::OnClose ()
{
  Show(FALSE);
  return (FALSE);
}

void wxAnimator::widgetCallbackFunction(wxObject* widget, wxCommandEvent& event)
{
//  Report::warning ("wxView3DPreferences::widgetCallbackFunction..");
  if (widget == myPlayButton) {
    play();
  } else if (widget == myRewindButton) {
    rewind();
  } else if (widget == myStopButton) {
    stop();
  } else if (widget == myAnimateCameraCheckBox) {
    myAnimateCamera = myAnimateCameraCheckBox->GetValue();
  }
}

//-----------------------------------------------------
// class wxAnimationTimer
//-----------------------------------------------------

wxAnimationTimer::wxAnimationTimer (wxAnimator *a)
{
  myAnimator = a;
}

void wxAnimationTimer::Notify()
{
  myAnimator->nextFrame();
  myAnimator->getViewManager()->notify (wxViewManager::REPAINT, NULL);
}
