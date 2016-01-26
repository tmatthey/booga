/*
 * $RCSfile: RotateCommand.h,v $
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
 *  $Id: RotateCommand.h,v 1.1 1996/10/11 14:57:46 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _RotateCommand_H
#define _RotateCommand_H

#include "booga/object/List3D.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxManagedRadioBox.h"
#include "booga/wxwrapper/wxManagedButton.h"

class RotateCommand : public wxViewCommand , public wxDialogDirector , public wxDialogBox, public wxBOOGAView {
  declareRTTI(RotateCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RotateCommand(wxView3D *v);                         // Use default version.
private:
//  RotateCommand(const MoveVerticalCommand&);             // No copies.

public:
  ~RotateCommand();              

private:
  RotateCommand& operator=(const RotateCommand&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MoveHorizontalCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void rotateObject (Vector3D axis, Real angle);
  Vector3D getAxis() const { return myAxis; }
  void setAxis(Vector3D a);
  void attachObjects();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  void createGUI();
  
  void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogBox
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  Bool OnClose() { return FALSE;};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool              myMovingFlag;
  Vector3D          myAxis;
  List3D            *myObjectList;
  int               myOldx, myOldy;
  wxManagedRadioBox *myRadio;  
  wxManagedButton   *myPlusButton;
  wxManagedButton   *myMinusButton;
};

//______________________________________________________________________ INLINES

#endif // _RotateCommand_H

