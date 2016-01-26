/*
 * wxAnimator.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: wxAnimator.h,v 1.3 1996/08/30 15:39:06 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxAnimator_H
#define _wxAnimator_H

#include "booga/animation/Animation3D.h"
#include "booga/wxwrapper/wxBOOGAView.h"

#include "wx.h"
#include "wx_timer.h"

//_____________________________________________________________________ wxAnimator

class wxAnimator;

class wxAnimationTimer : public wxTimer
{
  public:
    wxAnimationTimer (wxAnimator *a);
    void Notify(void);
  private: 
    wxAnimator* myAnimator;
};

class wxAnimator : public wxBOOGAView, public wxFrame {
//declareRTTI(wxAnimator);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxAnimator();
  wxAnimator(wxFrame* parent, int x=-1, int y=-1, int width=-1, int height=-1);
  // wxAnimator();                         // Use default version.
private:
  wxAnimator(const wxAnimator&);             // No copies.

public:
  // virtual ~wxAnimator();                // Use default version.

private:
  wxAnimator& operator=(const wxAnimator&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxAnimator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
// Callbacks:

  void doFrame(Real f);
  void nextFrame();
  void previousFrame();
  void stop();
  void play();
  void rewind();
    
    
  Real getFrameStep() { return myFrameStep; };
  void setFrameStep(Real s);
  Real getCurrentFrame() { return myCurrentFrame; };
  void setCurrentFrame(Real s);


  
  static void ourPlayCB (wxButton& b, wxCommandEvent& event);
  static void ourRewindCB (wxButton& b, wxCommandEvent& event);
  static void ourStopCB (wxButton& b, wxCommandEvent& event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxFrame
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  int OnClose();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<Animation3D*>* myAnimationList;
  Real myCurrentFrame;
  Real myLastFrame;
  Real myFrameStep;
  
  wxPanel* myPanel;
  wxButton* myPlayButton;
  wxButton* myRewindButton;
  wxButton* myStopButton;

  wxCanvas *myDialBox;
  wxTimer *myTimer;
};

inline void wxAnimator::setFrameStep (Real s) 
{
  myFrameStep = s;
}

inline void wxAnimator::setCurrentFrame (Real s) 
{
  myCurrentFrame = s;
}

//______________________________________________________________________ INLINES

#endif // _wxAnimator_H

