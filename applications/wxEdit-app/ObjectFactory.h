/*
 * $RCSFile: $
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: ObjectFactory.h,v 1.1 1996/10/11 14:57:34 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ObjectFactory_H
#define _ObjectFactory_H

#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxManagedChoice.h"
#include "booga/wxwrapper/wxManagedButton.h"
#include "booga/wxwrapper/wxManagedText.h"

#include <wx.h>

//_____________________________________________________________________ ObjectFactory

class ObjectFactory : public wxBOOGAView, public wxDialogDirector, public wxDialogBox {
declareRTTI(ObjectFactory);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ObjectFactory();                         // Use default version.
private:
  ObjectFactory(const ObjectFactory&);             // No copies.

public:
  // virtual ~ObjectFactory();                // Use default version.

private:
  ObjectFactory& operator=(const ObjectFactory&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ObjectFactory
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:


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
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  wxManagedChoice *myChoice;
  wxManagedButton *myButton;
  wxManagedText   *mySizeText;
  Real            mySize;
};

//______________________________________________________________________ INLINES

#endif // _ObjectFactory_H

