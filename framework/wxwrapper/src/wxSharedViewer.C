/*
 * $RCSfile: wxSharedViewer.C,v $
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
 *  $Id: wxSharedViewer.C,v 1.12 1998/05/01 07:11:21 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

//__________________________________________________________________ BOOGA Includes

#include "booga/object/PointLight.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"

#include "booga/component/Collector3DFor.h"
#include "booga/component/CollectShared3D.h"
 
#include "booga/wxwrapper/wxSharedViewer.h"
#include "booga/wxwrapper/wxView3DPreferences.h"
#include <wxstring.h>
#include <wx.h>

//__________________________________________________________________ Menu items

enum fileItems {VIEW_PREFERENCES=10, FILE_ADD_SHARED};

wxSharedViewer::wxSharedViewer(wxFrame *frame, char *title, int x, int y):
  wxFrame(frame, title, x, y, -1, -1)
{
  myManager = new wxViewManager;
  myCurrentShared= -1;
  myPrefs = NULL;
  createGUI();
  
//  panel->Fit();

//  Fit();
}

void wxSharedViewer::createGUI()
{
  panel = new wxPanel (this, 0,0,300,400);
// the menu:
  wxMenu *file_menu = new wxMenu;
  file_menu->Append(FILE_ADD_SHARED, "Add to World");
  file_menu->Append(wxID_CLOSE, "&Close...\tAlt+W");

  wxMenu *view_menu = new wxMenu;
  view_menu->Append(VIEW_PREFERENCES, "&Preferences...\tAlt+P");

//  wxMenu *shared_menu = new wxMenu;
//  view_menu->Append(SHARED_GOTO, "&Goto Shared...\tAlt+G");

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
  menu_bar->Append(view_menu, "&View");
//  menu_bar->Append(shared_menu, "&View");
  SetMenuBar(menu_bar);

// ListBox for Shareds
  myListBox = new wxManagedListBox(this, panel, "", wxSINGLE, 0, 0, 200, 400);

  canvas = new wxView3D(this, 200, 0, 400, 400,0);
  
  myManager->attach (canvas);
  
// adding elements

  myListBox->SetSelection (0);
  if (sharedList.count())
    createNewWorld(sharedList.item(0));
  Fit();
}
  
void wxSharedViewer::widgetCallbackFunction(wxObject* widget, wxCommandEvent& event)
{
  if (widget == myListBox) {
    createNewWorld (getShared(event.commandInt));
  }
}

Bool wxSharedViewer::OnClose(void)
{
//    delete this;
  Show(FALSE);
  return FALSE;
}

void wxSharedViewer::OnSize(int w, int h)
{
//  cerr << "on size: " << w << "  " << h << "\n";
  
//  SetSize (w,h);
        
  if (panel && canvas) {
    panel->SetSize (0,0,200, h);
    myListBox->SetSize (0,0,200,h);
    canvas->SetSize (200,0, w-200, h);
  }
}

void wxSharedViewer::OnMenuCommand(int id)
{
  switch (id) {
  case wxID_CLOSE: {
    OnClose();
    break;
  }
  
  case FILE_ADD_SHARED: {
    Object3D *obj = sharedList.item(myListBox->GetSelection())->copy();
    
    getViewManager()->getWorld()->getObjects()->adoptObject(obj);
    getViewManager()->addToSelection(obj);
    break;
  }
  
  case VIEW_PREFERENCES: {
    if (!myPrefs)
      myPrefs = new wxView3DPreferences(canvas);
    myPrefs->execute();    
    break;	  
  }
  }
}

void wxSharedViewer::addShared (Shared3D *sh)
{
  sharedList.append (sh);
  RCString mys = sh->getTypeName();
  myListBox->Append((char *)mys.chars(), (char *)this);
}

void wxSharedViewer::createNewWorld (Shared3D *obj)
{
  // first orphan old objects from world:
  if (myManager->getWorld())
    for (long i=0; i<myObjectList.countSubobject(); i++) 
      myManager->getWorld()->getObjects()->orphanObject(myObjectList.getSubobject(i));
  // empty my aggregate3D
  for (;myObjectList.countSubobject();) 
   myObjectList.orphanObject(myObjectList.getSubobject(0));

  // setup new world with all objects contained in the shared:  
  
  World3D *newWorld = new World3D;

  // Vector3D bbmid = obj->getBounds().getMin() + (obj->getBounds().getMax() - obj->getBounds().getMin())/2;

  Camera3D *myCam = new Camera3D();
  myCam->setBackground (Color (.5,.5,.5));
    
  int w,h;
  canvas->GetSize (&w,&h);
  myCam->getViewing()->setResolution (w,h);

  myCam->getViewing()->setView (obj->getBounds().getMin(), obj->getBounds().getMax());
//  myCam->getViewing()->setLookat (bbmid);
  newWorld->getObjects()->adoptObject (myCam);

  //  Shared3D *myCopy = (Shared3D *) obj->copy();
//    myCopy->computeBounds();

  ostrstream os;
  os << "[wxSharedViewer::createNewWorld]: countSubobject() = " << obj->countSubobject();
  Report::warning(os);
    
  Aggregate3D *a = dynamic_cast (Aggregate3D, obj->getSubobject(0));
  if (a) {
    for (long i=0; i<a->countSubobject(); i++) {
      myObjectList.adoptObject (a->getSubobject(i));
      newWorld->getObjects()->adoptObject(a->getSubobject(i));
    }
    ostrstream os;
    os << "[wxSharedViewer::createNewWorld]: a->countSubobject() = " << a->countSubobject();
    Report::warning(os);
  } else {
    ostrstream os;
    os << "[wxSharedViewer::createNewWorld]: only one subobject!";
    if (obj->countSubobject() == 1) {
      myObjectList.adoptObject (obj->getSubobject(0));
      newWorld->getObjects()->adoptObject(obj->getSubobject(0));
    }
  }  
            
        
//    newWorld->getObjects()->adoptObject (myCopy);
    
    // four lightsources to have a proper lighting
    
  PointLight *myPointLight = new PointLight(.6);
  myPointLight->setPosition (Vector3D (-40,0,10));
  myPointLight->setColor (Color (1,1,1));
  newWorld->getObjects()->adoptObject (myPointLight);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (Vector3D (40,0,10));
  myPointLight->setColor (Color (1,1,1));
  newWorld->getObjects()->adoptObject (myPointLight);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (Vector3D (0,40,10));
  myPointLight->setColor (Color (1,1,1));
  newWorld->getObjects()->adoptObject (myPointLight);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (Vector3D (0,-40,10));
  myPointLight->setColor (Color (1,1,1));
  newWorld->getObjects()->adoptObject (myPointLight);
  newWorld->getObjects()->computeBounds();
  myManager->adoptWorld(newWorld);
  myManager->notify(wxViewManager::REPAINT, NULL);
}

void wxSharedViewer::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
{
  switch (event) {
    case wxViewManager::WORLD_NEW:  
    case wxViewManager::WORLD_CHANGED: {
        if (!getViewManager()->getWorld())
          break; // NULL World detected

        sharedList.removeAll();
        myListBox->Clear();
        CollectShared3D collector;
        collector.execute(getViewManager()->getWorld());

        for (collector.first(); !collector.isDone(); collector.next()) {
		Shared3D *myShared = (Shared3D*)collector.getCurrent();
  		addShared (myShared);
        }
        myListBox->SetSelection(0);
        canvas->OnPaint();
      } 
      break;

    case wxViewManager::CAMERAS_CHANGED:
    case wxViewManager::REPAINT:
    case wxViewManager::CLIPBOARD_CHANGED:
    case wxViewManager::SELECTION_CHANGED:
    case wxViewManager::LIGHTS_CHANGED:

      break;
  }
}
