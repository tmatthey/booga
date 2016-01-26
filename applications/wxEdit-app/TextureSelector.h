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
 *  $Id: TextureSelector.h,v 1.1 1996/10/11 14:57:58 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TextureSelector_H
#define _TextureSelector_H

#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxManagedListBox.h"
#include "booga/wxwrapper/wxManagedButton.h"

#include <wx.h>

//_____________________________________________________________________ TextureSelector

class TextureSelector : public wxBOOGAView, public wxDialogDirector, public wxDialogBox {
declareRTTI(TextureSelector);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TextureSelector();                         // Use default version.
private:
  TextureSelector(const TextureSelector&);             // No copies.

public:
  // virtual ~TextureSelector();                // Use default version.

private:
  TextureSelector& operator=(const TextureSelector&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TextureSelector
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
  wxManagedListBox *myListBox;
  wxManagedButton  *myAdd;
  wxManagedButton  *mySet;
  List<Texture3D*> myTextureList;
};

//______________________________________________________________________ INLINES

#endif // _TextureSelector_H

