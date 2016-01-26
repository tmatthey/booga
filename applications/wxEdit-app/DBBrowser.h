/*
 * $RCSfile: DBBrowser.h,v $
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
 *  $Id: DBBrowser.h,v 1.1 1996/12/19 15:47:16 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _DBBrowser_H
#define _DBBrowser_H
#include "booga/object/List3D.h"

#include "booga/persistence/POId.h"

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

class PersistentManager;
class TransientBase;
class FileBase;

class DBBrowser: public wxFrame, public wxBOOGAView, public wxDialogDirector
{ 
public:
  DBBrowser(wxFrame *frame, char *title, int x, int y);
  void OnMenuCommand(int id);
  //  void OnSize(int w, int h);
  Bool OnClose(void);
  void OnSize(int w, int h);
  void createNewWorld (RCString name, POId oid);

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
  List<POId>            myPoidList;
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
  PersistentManager    *myPersistentManager;
  TransientBase        *myTransientBase;
  FileBase             *myDB;
};

#endif // _DBBrowser_H

