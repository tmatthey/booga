/*
 * wxBOOGAView.h
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
 *  $Id: wxBOOGAView.h,v 1.3 1996/10/11 14:55:27 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxBOOGAView_H
#define _wxBOOGAView_H

#include "booga/object/World3D.h"

#include "booga/wxwrapper/wxViewManager.h"

//_____________________________________________________________________ wxBOOGAView

class wxBOOGAView {
  //  declareRTTI(wxBOOGAView);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxBOOGAView();
  
private:
//  wxBOOGAView(const wxBOOGAView&);				 

public:
  virtual ~wxBOOGAView();					 // Use default version.

private:
//  wxBOOGAView& operator=(const wxBOOGAView&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  
  void 		setViewManager(wxViewManager* theManager);
  wxViewManager* getViewManager() const;
  
  virtual void update(wxViewManager::NotifyEvent event, Object3D* obj) = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  wxViewManager* myViewManager;
};

//______________________________________________________________________ INLINES

inline
wxViewManager* wxBOOGAView::getViewManager() const
{
  return myViewManager;
}

#endif // _wxBOOGAView_H
