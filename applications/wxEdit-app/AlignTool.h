/*
 * $RCSfile: AlignTool.h,v $
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
 *  $Id: AlignTool.h,v 1.2 1996/10/31 08:35:31 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AlignTool_H
#define _AlignTool_H

#include "booga/object/List3D.h"
#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxManagedRadioBox.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxDialogDirector.h"

//_____________________________________________________________________ AlignTool

class AlignTool : public wxBOOGAView, public wxDialogDirector, public wxDialogBox {
declareRTTI(AlignTool);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AlignTool();                         // Use default version.
//private:
//  AlignTool(const AlignTool&);             // No copies.

public:
  ~AlignTool();                // Use default version.

private:
  AlignTool& operator=(const AlignTool&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AlignTool
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void execute();
  void attachObjects();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
   void update(wxViewManager::NotifyEvent event, Object3D* obj);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  void createGUI();
  
  void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  int OnClose();

private:
  Aggregate3D* createGrid (Vector3D origin, Vector3D x, Vector3D y, int count);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List3D            *myObjectList;
  wxManagedRadioBox *myRadioBox;
  wxManagedButton   *myApply;

};

//______________________________________________________________________ INLINES

#endif // _AlignTool_H

