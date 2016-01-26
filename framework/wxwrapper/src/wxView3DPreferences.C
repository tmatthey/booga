/*
 * $RCSfile: wxView3DPreferences.C,v $
 *
 * Copyright (C) 1995-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: wxView3DPreferences.C,v 1.6 1997/09/19 08:42:18 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/wxwrapper/wxView3DPreferences.h"
#include "booga/glwrapper/GLTraversal3D.h"

//____________________________________________________________ wxView3DPreferences

char *displayQualityStrings[] = {
  "Boundingbox",
  "Wireframe",
  "Wireframe flat",
  "Wireframe gouraud",
  "Solid flat",
  "Solid gouraud"
};

const int displayQualityCount = 6;

wxView3DPreferences::wxView3DPreferences (wxView3D *theCanvas) 
: wxDialogBox (theCanvas, "Preferences"), wxViewCommand (theCanvas)
{
  createGUI();
}

void wxView3DPreferences::createGUI()
{
  myRenderingQualityChoice = new wxManagedChoice (this, this, 
                                                  "Rendering quality",
                                                  -1,-1,-1,-1,
                                                  displayQualityCount,
                                                  displayQualityStrings);
                                                  
  myRenderingQualityChoice->SetSelection (getView()->getRenderingQuality()-1);
  NewLine();
  
  myMotionQualityChoice = new wxManagedChoice (this, this, 
                                               "Motion quality", -1,-1,-1,-1,
                                               displayQualityCount,
                                               displayQualityStrings);
                                               
  myMotionQualityChoice->SetSelection (getView()->getMotionQuality()-1);
  NewLine();	 

  myFrameRateSlider = new wxManagedSlider (this, this, 
                                           "Frame rate",10, 0, 30, 350, -1, -1,
                                           wxHORIZONTAL);
                                           
  myFrameRateSlider->SetValue(getView()->getRenderer()->getFrameRate());
  NewLine();

  myTimeInBackbufferSlider = new wxManagedSlider (this, this,
                                                  "Time in backbuffer",
                                                  10, 0, 
                                                  30, 350, 
                                                  -1, -1,
                                                  wxHORIZONTAL);

  myTimeInBackbufferSlider->SetValue((int)getView()->getRenderer()->getMaxTimeInBackbuffer());
  NewLine();

//  myCullingCheckBox = new wxManagedCheckBox (this, this, "Frustrum Culling");
//  NewLine();
//  GLTraversal3D *t = dynamic_cast (GLTraversal3D, getView()->getRenderer()->getTraversal());
//  if (t)
//    myCullingCheckBox->SetValue(t->frustrumCullingEnabled());
  myCloseButton = new wxManagedButton (this, this, "Close");

  Fit();
}

void wxView3DPreferences::initAll()
{
//  myMotionModeRadioBox->SetSelection(getView()->getMotionMode());
  myRenderingQualityChoice->SetSelection(getView()->getRenderingQuality());
  myMotionQualityChoice->SetSelection(getView()->getMotionQuality());
  myFrameRateSlider->SetValue(getView()->getRenderer()->getFrameRate());
  myTimeInBackbufferSlider->SetValue((int)getView()->getRenderer()->getMaxTimeInBackbuffer());
  
}

void wxView3DPreferences::execute()
{
  initAll();
  Show(TRUE);
}

void wxView3DPreferences::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
//  Report::warning ("wxView3DPreferences::widgetCallbackFunction..");

  if (widget == myCloseButton) {
    Show(false);
  } else if (widget == myTimeInBackbufferSlider) {
    getView()->getRenderer()->setMaxTimeInBackbuffer (((wxManagedSlider *)widget)->GetValue());
  } else if (widget == myFrameRateSlider) {
    getView()->getRenderer()->setFrameRate (((wxManagedSlider *)widget)->GetValue());
  } else if (widget == myMotionQualityChoice) {
    wxManagedChoice *c = (wxManagedChoice *) widget;
    getView()->changeMotionQuality((GLRenderer::RenderingQuality)(c->GetSelection()+1));
  } else if (widget == myRenderingQualityChoice) {
    wxManagedChoice *c = (wxManagedChoice *) widget;
    getView()->changeRenderingQuality((GLRenderer::RenderingQuality)(c->GetSelection()+1));
//  } else if (widget == myCullingCheckBox) {
//    wxManagedCheckBox *c = (wxManagedCheckBox *) widget;
//    GLTraversal3D *t = dynamic_cast (GLTraversal3D, getView()->getRenderer()->getTraversal());
//    if (t) {
//      if (c->GetValue())
//        t->enableFrustrumCulling();
//      else
//        t->disableFrustrumCulling();
//    }
  }
  
}
