/*
 * $RCSfile: wxView3DPreferences.h,v $
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
 *  $Id: wxView3DPreferences.h,v 1.4 1996/10/11 14:55:54 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifndef _wxView3DPreferences_h_
#define _wxView3DPreferences_h_
 
#include "booga/wxwrapper/wxView3D.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxManagedSlider.h"
#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedCheckBox.h"
#include <wx.h>

//_____________________________________________________________________ wxView3DPreferences

class wxView3DPreferences : public wxDialogBox, public wxViewCommand, public wxDialogDirector {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxView3DPreferences(const wxView3DPreferences&); // No copies.
public:
  wxView3DPreferences (wxView3D *v);

public:
  // ~wxView3DPreferences();                    // Use default version.

private:
  wxView3DPreferences& operator=(const wxView3DPreferences&); // No assignment

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class wxView3DPreferences
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void initAll ();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute ();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class GSBwxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void createGUI();
  
  virtual void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);
//  virtual ActionRequest widgetOnClose(wxObject* widget);
//  virtual ActionRequest widgetOnMenuCommand(wxObject* widget, int id);
//  virtual ActionRequest widgetOnEvent(wxObject* widget, wxMouseEvent& event);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

  wxManagedChoice   *myRenderingQualityChoice;
  wxManagedChoice   *myMotionQualityChoice;
  wxManagedSlider   *myFrameRateSlider;
  wxManagedSlider   *myTimeInBackbufferSlider;
  wxManagedCheckBox *myCullingCheckBox;
  wxManagedButton   *myCloseButton;
 
};
#endif

