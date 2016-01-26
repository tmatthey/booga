/*
 * GSBView.h
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
 *  $Id: GSBView.h,v 1.6 1997/04/08 11:05:08 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBView_H
#define _GSBView_H

#include "booga/object/World3D.h"

#include "GSBNode.h"
#include "GSBViewManager.h"

//_____________________________________________________________________ GSBView

class GSBView {
declareRTTI(GSBView);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBView(World3D* world, RCString& IDStr);
  
private:
  GSBView(const GSBView&);                   // No copies.

public:
  virtual ~GSBView() {};                     // Use default version.

private:
  GSBView&        operator=(const GSBView&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // setViewID() may be called by GSBViewManager ONLY.
  void            setViewID(long viewID) { myViewID = viewID; };
  long            getViewID() const { return myViewID; };
  
  const RCString& getViewIDStr() const { return myViewIDStr; }
  
  void            setViewManager(GSBViewManager* theManager);
  GSBViewManager* getViewManager() const;
  
  virtual void    update(GSBViewManager::NotifyEvent event) = 0;
    
  World3D*        getWorld() const { return myWorld; };
  
  virtual void    init() = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  World3D*	    myWorld;
  long            myViewID;
  RCString        myViewIDStr;
  GSBViewManager* myViewManager;
};

//______________________________________________________________________ INLINES

inline
void GSBView::setViewManager(GSBViewManager* theManager)
{
  myViewManager = theManager;
};


inline
GSBViewManager* GSBView::getViewManager() const
{
  return myViewManager;
}

#endif // _GSBView_H
