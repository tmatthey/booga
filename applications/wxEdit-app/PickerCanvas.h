/*
 * $RCSfile: PickerCanvas.h,v $
 *
 * Copyright (C) 1995-96, Bernhard Buhlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: PickerCanvas.h,v 1.4 1996/08/01 12:00:30 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PickerCanvas_H
#define _PickerCanvas_H

#include "booga/component/Picker3D.h"
#include "booga/wxwrapper/wxView3D.h"

//_____________________________________________________________________ PickerCanvas

class PickerCanvas : public wxView3D {
declareRTTI(PickerCanvas);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PickerCanvas (wxWindow *frame, int x=-1, int y=-1, int w=100, int h=100);
  // PickerCanvas();                         // Use default version.
private:
  PickerCanvas(const PickerCanvas&);             // No copies.

public:
  // virtual ~PickerCanvas();                // Use default version.

private:
  PickerCanvas& operator=(const PickerCanvas&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PickerCanvas
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void loadWorld(const RCString& filename);
  void renderPicker();
  void inspectPickedObject();
  void movePickedObject(int x, int y);
  void rotatePickedObject(int alpha);
  void pick(int x, int y);
  void interpolateCamera (Camera3D *cam);
  void cut();
  void copy();
  void paste();
	
  void adoptAuxilaryWorld(World3D *a);
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxView3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void OnEvent(wxMouseEvent& event);
  void OnPaint();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Componeht<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Picker3D myPicker;
  Picker3D toolPicker;
  World3D *toolWorld;
  World3D *auxilaryWorld;
  Object3D *clipBoard;
};

//______________________________________________________________________ INLINES

#endif // _PickerCanvas_H

