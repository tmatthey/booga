/*
 * $RCSfile: SharedEditor.h,v $
 *
 * Copyright (C) 1995-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: SharedEditor.h,v 1.1 1996/10/11 14:57:52 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _SharedEditor_H
#define _SharedEditor_H
#include "booga/object/List3D.h"
#include "booga/wxwrapper/wxView3D.h"
#include "booga/wxwrapper/wxView3DPreferences.h"
#include "booga/wxwrapper/wxDialogDirector.h"
#include "booga/wxwrapper/wxManagedListBox.h"
#include "ToolBar.h"
#include "EditSelection.h"
#include "TextureSelector.h"
#include "ObjectFactory.h"
#include "AlignTool.h"
#include <wx.h>

class Shared3D; // forward declaration

class SharedEditor: public wxFrame, public wxBOOGAView, public wxDialogDirector
{ 
public:
  SharedEditor(wxFrame *frame, char *title, int x, int y);
  void OnMenuCommand(int id);
  //  void OnSize(int w, int h);
  Bool OnClose(void);
  void OnSize(int w, int h);
  void addShared (Shared3D *cam);
  Shared3D *getShared (int i);
  void createNewWorld (Shared3D *obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxDialogDirector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void createGUI();
  
  virtual void widgetCallbackFunction(wxObject* widget, wxCommandEvent& event);

private:
  List<Shared3D*>       sharedList;
  int                   myCurrentShared;
  wxView3D             *myCanvas;
  wxView3DPreferences  *myPrefs;
  wxManagedListBox     *myListBox;
  wxViewManager        *myManager;
  wxPanel              *panel;
  ToolbarCommand       *myToolBar;
  EditSelection        *myEditSelection;  
  TextureSelector      *myTextureSelector;  
  ObjectFactory        *myObjectFactory;  
  AlignTool            *myAlignSelection;  
  List3D               *myObjectList;
};


inline Shared3D* SharedEditor::getShared (int i)
{
  return sharedList.item(i);
}

#endif // _SharedEditor_H

