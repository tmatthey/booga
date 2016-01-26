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
 *  $Id: wxAnimator.C,v 1.7 1997/02/20 09:42:14 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/List.h"
#include "booga/base/ListUtilities.h"

#include "booga/component/Collector3DFor.h"

#include "wxAnimator.h"
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
    angle = x > 100 ? 50 : x-50;
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
  dc->DrawEllipse (0,0,100,100);

  dc->SetBrush(wxBLACK_BRUSH);
  dc->DrawEllipse (40+40*sin(dtor(angle)),40-40*cos(dtor(angle)),20,20);
  
  wxString f;
  f.sprintf ("%f", a->getCurrentFrame());
  dc->SetFont (myFont);
  float x,y;
  GetTextExtent (f.Data(), &x, &y);
  dc->DrawText (f.Data(), 50-(x/2), 50 -(y/2));
  
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


  myPanel = new wxPanel(this);
  myPlayButton = new wxButton (myPanel, (wxFunction) wxAnimator::ourPlayCB, "Play");
  myRewindButton = new wxButton (myPanel, (wxFunction) wxAnimator::ourRewindCB, "Rewind");
  myStopButton = new wxButton (myPanel, (wxFunction) wxAnimator::ourStopCB, "Stop");
  
  myPanel->NewLine();
  myDialBox = new dialCanvas(myPanel);
  
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
     
    case wxViewManager::WORLD_CHANGED: {
      //
      // Collect all animation objects in the new world.
      //  
      if (myAnimationList != NULL)
        deleteList(myAnimationList);

      if (!getViewManager()->getWorld())
        break; // NULL world
    
      myAnimationList = new List<Animation3D*>;
      Collector3DFor<Animation3D> animCollector;
      animCollector.execute(getViewManager()->getWorld());
      for (animCollector.first(); !animCollector.isDone(); animCollector.next())
        myAnimationList->append(animCollector.getObject());
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

void wxAnimator::ourPlayCB (wxButton& b, wxCommandEvent&)
{
  wxAnimator* a = (wxAnimator *) b.GetGrandParent();
  a->play();
}

void wxAnimator::ourRewindCB (wxButton& b, wxCommandEvent&)
{
  wxAnimator* a = (wxAnimator *) b.GetGrandParent();
  a->rewind();
}

void wxAnimator::ourStopCB (wxButton& b, wxCommandEvent&)
{
  wxAnimator* a = (wxAnimator *) b.GetGrandParent();
  a->stop();
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
