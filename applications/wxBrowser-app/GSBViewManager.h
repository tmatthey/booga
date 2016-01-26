/*
 * GSBViewManager.h
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
 *  $Id: GSBViewManager.h,v 1.6 1997/04/08 11:05:10 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBViewManager_H
#define _GSBViewManager_H

//#include "booga/object/Object3D.h"
#include "booga/object/World3D.h"

// forward declaration of class GSBView (observer-class):
class GSBView;


//_____________________________________________________________________ GSBViewManager

class GSBViewManager {
public:
  enum NotifyEvent {
        PICKING        = 0,
        PRUNING,
        ICONIZE,
        UNICONIZE,
        FILENAME,
        REPAINT,
        SUBJECT_KILLED,
        UPDATEALL      = 9
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBViewManager(World3D* world);
private:
  GSBViewManager(const GSBViewManager&);             // No copies.

public:
  virtual ~GSBViewManager(); 

private:
  GSBViewManager& operator=(const GSBViewManager&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBViewManager
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // interface according to 'Observer Pattern':
  long		attach(GSBView* theView);
  void		detach(long viewID);
private:
  void		notify(NotifyEvent event);

public:
  GSBView*	getView(long viewID);
  bool		isUsedID(long viewID);
  bool		isAttached(const RCString& id) const;
  
  // Interface for Observers:
  // inquire about state of the subject GSBViewManager
  World3D*    getWorld()    { return myWorld; }; 
  RCString    getFilename() { return myFilename; };
  bool        getIconized() const { return myIconizedFlag; };
  Object3D*   getPickedObject() const { return myPickedObject; };

  // change state of GSBViewManager:
  void        picking(Object3D* obj);
  void        pruning(Object3D* obj);
  void        setFilename(RCString name);
  void        setIconized(bool iconize);

  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<GSBView*>  myViewList;
  long            myViewCounter;
  
  // data members describing state of GSBViewManager
  World3D*        myWorld;
  bool            myIconizedFlag;
  bool            myNotifyFlag;
  RCString        myFilename;
  Object3D*       myPickedObject;
};

//______________________________________________________________________ INLINES

#endif // _GSBViewManager_H
