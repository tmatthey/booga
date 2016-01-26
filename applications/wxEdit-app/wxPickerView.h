/*
 * $RCSfile: wxPickerView.h,v $
 *
 * Copyright (C) 1995-96, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxPickerView.h,v 1.2 1996/09/27 15:08:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxPickerView_H
#define _wxPickerView_H

#include "booga/component/Picker3D.h"
#include "booga/wxwrapper/wxView3D.h"

//_____________________________________________________________________ wxPickerView

class wxPickerView : public wxView3D {
//declareRTTI(wxPickerView);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxPickerView (wxWindow *frame, int x=-1, int y=-1, int w=100, int h=100);
  // wxPickerView();                         // Use default version.
private:
//  wxPickerView(const wxPickerView&);             // No copies.

public:
  // virtual ~wxPickerView();                // Use default version.

private:
//  wxPickerView& operator=(const wxPickerView&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxPickerView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void loadWorld(const RCString& filename);
  void renderPicker();
  void inspectPickedObject();
  void movePickedObject(int x, int y);
  void rotatePickedObject(int alpha);
  void pick(int x, int y);
  void interpolateCamera (Camera3D *cam);
	
  void adoptAuxilaryWorld(World3D *a);
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxView3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void OnPaint();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//public:
//  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Picker3D    myPicker;
  Picker3D    toolPicker;
  World3D*    toolWorld;
  World3D*    auxilaryWorld;
  Object3D*   clipBoard;
};

//______________________________________________________________________ INLINES

#endif // _wxPickerView_H

