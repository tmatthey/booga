/*
 * $RCSfile: EditSelection.h,v $
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
 *  $Id: EditSelection.h,v 1.1 1996/10/11 14:57:18 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _EditSelection_H
#define _EditSelection_H

#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedDialogBox.h"
#include "booga/wxwrapper/wxManagedText.h"
#include "booga/wxwrapper/wxManagedButton.h"

//_____________________________________________________________________ EditSelection

class EditSelection : public wxBOOGAView, public wxDialogDirector, public wxDialogBox {
declareRTTI(EditSelection);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  EditSelection();                         // Use default version.
private:
  EditSelection(const EditSelection&);             // No copies.

public:
  ~EditSelection();                

private:
  EditSelection& operator=(const EditSelection&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class EditSelection
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void updateGUI();
  
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
  wxManagedText         *myText;
  List<wxManagedText*>  myValueList;
  wxManagedButton       *myApplyButton;
};

//______________________________________________________________________ INLINES

#endif // _EditSelection_H

