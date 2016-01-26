/*
 * wxViewManager.h
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: wxViewManager.h,v 1.5 1998/05/20 13:04:21 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxViewManager_H
#define _wxViewManager_H

//#include "booga/object/Object3D.h"
#include "booga/object/World3D.h"

// forward declaration of class wxBOOGAView (observer-class):
class wxBOOGAView;


//_____________________________________________________________________ wxViewManager

class wxViewManager {
public:
  enum NotifyEvent {
	REPAINT,
	WORLD_NEW,
	WORLD_CHANGED,
	LIGHTS_CHANGED,
	CAMERAS_CHANGED,
	SELECTION_CHANGED,
	CLIPBOARD_CHANGED
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxViewManager();
private:
//  wxViewManager(const wxViewManager&);             // No copies.

public:
  virtual ~wxViewManager(); 

private:
//  wxViewManager& operator=(const wxViewManager&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxViewManager
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // interface according to 'Observer Pattern':
  void attach(wxBOOGAView* theView);
  void detach(wxBOOGAView* theView);
  void notify(NotifyEvent event, Object3D* obj);

  // manage world
  void adoptWorld (World3D *world);
  World3D* orphanWorld();
  World3D* getWorld() {return myWorld;};

  // manage auxilary world
/** 
  Returns a pointer to the auxialry world of the viemanager. 
  The auxilary world stores helper objects like construction planes, 
  modifiers, outlines.
  */
  const World3D *getAuxWorld() { return myAuxWorld;} ;
/**
  The auxilary world of the viemanager adopts object o. If any view displays 
  objects from the auxilary world, it must be notifed or refreshed by the user. 
  The object will be displayed on the next repaint of the view.
  */
  void adoptAuxObject(Object3D *o);
/**
  Orphan objects from the auxilary world of the view. If object o does not exist,
  a NULL pointer is returned.
  */
  Object3D *orphanAuxObject(Object3D *o);

  // manage selection
  Aggregate3D* getSelection() const { return mySelection; };
  void setSelection(Object3D *o);
  void addToSelection (Object3D *o);
  bool isSelected (Object3D *o);
  void removeFromSelection(Object3D *o);
  void clearSelection ();

  // manage clipboard
  Aggregate3D* getClipboard() const { return myClipboard; };
  void adoptClipboard (Aggregate3D *a);
  Aggregate3D* orphanClipboard();
        
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<wxBOOGAView*>	myViewList;
  
  // data members describing state of wxViewManager
  World3D*			myWorld;

  // auxilary world for helper objects
  World3D*			myAuxWorld;

  Aggregate3D*    mySelection;
  Aggregate3D*    myClipboard;
};

//______________________________________________________________________ INLINES

#endif // _wxViewManager_H
