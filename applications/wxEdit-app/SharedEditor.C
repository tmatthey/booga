/*
 * $RCSfile: SharedEditor.C,v $
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
 *  $Id: SharedEditor.C,v 1.2 1997/02/20 09:42:09 matthey Exp $
 * -----------------------------------------------------------------------------
 */

//__________________________________________________________________ BOOGA Includes

#include "booga/object/PointLight.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"

#include "booga/component/Collector3DFor.h"
#include "booga/component/CollectShared3D.h"
 
#include "booga/wxwrapper/wxView3DPreferences.h"
#include "booga/wxwrapper/wxPickCommand.h"

#include "SharedEditor.h"
#include "PickCommand.h"
#include <wxstring.h>
#ifndef max
#define max(a,b)               ( ((a) > (b)) ? (a) : (b) )
#endif
//#include <wx.h>

//__________________________________________________________________ Menu items

enum fileItems {VIEW_PREFERENCES=10, FILE_ADD_SHARED, EDIT_APPLY_CHANGES, EDIT_SELECTION, TEXTURE_SELECTOR, OBJECT_FACTORY, ALIGN_TOOL};

SharedEditor::SharedEditor(wxFrame *frame, char *title, int x, int y):
  wxFrame(frame, title, x, y, -1, -1)
{
  myManager = new wxViewManager;
  myCurrentShared= -1;
  myPrefs           = NULL;
  myEditSelection   = NULL;
  myObjectFactory   = NULL;
  myTextureSelector = NULL;
  myAlignSelection  = NULL;
  myObjectList      = NULL;
  createGUI();
}

void SharedEditor::createGUI()
{
  panel = new wxPanel (this, 0,0,300,400);
// the menu:
  wxMenu *file_menu = new wxMenu;
  file_menu->Append(FILE_ADD_SHARED, "Add to World");
  file_menu->Append(wxID_CLOSE, "&Close...\tAlt+W");

  wxMenu *edit_menu = new wxMenu;
  edit_menu->Append(EDIT_APPLY_CHANGES, "Apply Changes...");

  wxMenu *tools_menu = new wxMenu;
  tools_menu->Append(TEXTURE_SELECTOR, "Texture Selection");
  tools_menu->Append(OBJECT_FACTORY, "Object Factory");
  tools_menu->Append(EDIT_SELECTION, "Edit Selection...");
  tools_menu->Append(ALIGN_TOOL, "Align Selection...");
  
  wxMenu *view_menu = new wxMenu;
  view_menu->Append(VIEW_PREFERENCES, "&Preferences...\tAlt+P");

//  wxMenu *shared_menu = new wxMenu;
//  view_menu->Append(SHARED_GOTO, "&Goto Shared...\tAlt+G");

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
  menu_bar->Append(edit_menu, "&Edit");
  menu_bar->Append(view_menu, "&View");
  menu_bar->Append(tools_menu, "&Tools");
//  menu_bar->Append(shared_menu, "&View");
  SetMenuBar(menu_bar);

// ListBox for Shareds
  myListBox = new wxManagedListBox(this, panel, "", wxSINGLE, 0, 50, 200, 400);

  myCanvas = new wxView3D(this, 200, 50, 400, 400,0);
  // myCanvas->adoptPickCommand(new wxPickCommand(myCanvas));
  // myCanvas->adoptMenuCommand(new SelectCommand(myCanvas));
  myCanvas->adoptMouseCommand(new wxPickCommand(myCanvas));
  myCanvas->adoptMouseCommand(new SelectCommand(myCanvas));
  
  myManager->attach (myCanvas);
  
  myToolBar = new ToolbarCommand (myCanvas, this, 0,0,400,50);
  
// adding elements

  myListBox->SetSelection (0);
  if (sharedList.count()) {
    createNewWorld(sharedList.item(0));
    myCurrentShared = 0;
  }
  SetSize (800, 500);
}
  
void SharedEditor::widgetCallbackFunction(wxObject* widget, wxCommandEvent& event)
{
  if (widget == myListBox) {
    createNewWorld (getShared(event.commandInt));
    myCurrentShared = event.commandInt;
  }
}

Bool SharedEditor::OnClose(void)
{
//    delete this;
  Show(FALSE);
  return FALSE;
}

void SharedEditor::OnSize(int w, int h)
{
//  cerr << "on size: " << w << "  " << h << "\n";
  
//  SetSize (w,h);
        
  if (panel && myCanvas) {
    panel->SetSize (0,0,200, h);
    myListBox->SetSize (0,50,200,h-50);
    myCanvas->SetSize (200,50, w-200, h-50);
  }
}

void SharedEditor::OnMenuCommand(int id)
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
  
  case EDIT_SELECTION: {
    if (!myEditSelection) {
      myEditSelection = new EditSelection ();
      myManager->attach (myEditSelection);
    } else
      myEditSelection->Show(true);
  break;
  }
  case ALIGN_TOOL: {
    if (!myAlignSelection) {
      myAlignSelection = new AlignTool ();
      myManager->attach (myAlignSelection);
    } else
      myAlignSelection->Show(true);
  break;
  }
  
  case OBJECT_FACTORY: {
    if (!myObjectFactory) {
      myObjectFactory = new ObjectFactory ();
      myManager->attach (myObjectFactory);
    } else
      myObjectFactory->Show(true);
  break;
  }
  
  case TEXTURE_SELECTOR: {
    if (!myTextureSelector) {
      myTextureSelector = new TextureSelector ();
      myManager->attach (myTextureSelector);
    } else
      myTextureSelector->Show(true);
  break;
  }
  
  case EDIT_APPLY_CHANGES: {
      // remove temporary objects from temporary world
      myManager->getWorld()->getObjects()->orphanObject(myObjectList);
      // check if any objects are left int the temporary world
      if (myManager->getWorld()->getObjects()->countSubobject() == 0) {
        ostrstream os;
        os << "[SharedEditor::OnMenu]: No objects left in world! try to delete the shared";
        Report::warning(os);  
        myManager->getWorld()->getObjects()->adoptObject(myObjectList);
        myManager->getWorld()->getObjects()->computeBounds();
        break;
      }
     
      // we orphan all objects from selected shared:
      if (myCurrentShared < 0) {
        Report::warning ("[SharedEditor::OnMenuCommand]No shared selected???");
        break;
      }
        
      Shared3D *obj = sharedList.item(myCurrentShared);

      if (myManager->getWorld()->getObjects()->countSubobject() > 1) {
        // we have to create a new aggregate!
        List3D *theList = new List3D;
        
        for (long i=0;i<myManager->getWorld()->getObjects()->countSubobject();i++) 
          theList->adoptObject (myManager->getWorld()->getObjects()->getSubobject(i)->copy());
      
        obj->adoptObject(theList);
        ostrstream os;
        os << "[SharedEditor::OnMenu]: List3D added to shared!";
        Report::warning(os);
      } else {
        // we only have one object left in world
        obj->adoptObject(myManager->getWorld()->getObjects()->getSubobject(0)->copy());   
        ostrstream os;
        os << "[SharedEditor::OnMenu]: only one subobject added!";
        Report::warning(os);
      }  
    
      // we add all temporary objects again...
      myManager->getWorld()->getObjects()->adoptObject(myObjectList);
      myManager->getWorld()->getObjects()->computeBounds();

      obj->computeBounds();
      
      getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
      break;
    }
   
  case VIEW_PREFERENCES: {
    if (!myPrefs)
      myPrefs = new wxView3DPreferences(myCanvas);
    myPrefs->execute();    
    break;	  
  }
  }
}

void SharedEditor::addShared (Shared3D *sh)
{
  sharedList.append (sh);
  RCString mys = sh->getTypeName();
  myListBox->Append((char *)mys.chars(), (char *)this);
}

void SharedEditor::createNewWorld (Shared3D *obj)
{
  // first orphan myObjectList from temporary world:
  if (myManager->getWorld()) {
    if (myManager->getWorld()->getObjects()->orphanObject(myObjectList));
      delete myObjectList;
  }

  myObjectList = new List3D;

  // setup new world with all objects contained in the shared:  
  
  World3D *newWorld = new World3D;



  ostrstream os;
  os << "[SharedEditor::createNewWorld]: countSubobject() = " << obj->countSubobject();
  Report::warning(os);
    
  Aggregate3D *a = dynamic_cast (Aggregate3D, obj->getSubobject(0));
  if (a) {
    // we create a copy of each object in the shared3d
    for (long i=0; i<a->countSubobject(); i++) {
      newWorld->getObjects()->adoptObject(a->getSubobject(i)->copy());
    }
    ostrstream os;
    os << "[SharedEditor::createNewWorld]: a->countSubobject() = " << a->countSubobject();
    Report::warning(os);
  } else {
    ostrstream os;
    os << "[SharedEditor::createNewWorld]: only one subobject!";
    if (obj->countSubobject() == 1) {
      newWorld->getObjects()->adoptObject(obj->getSubobject(0)->copy());
    }
  }  

  newWorld->getObjects()->computeBounds();

  // now we have to set a camera which shows all objects in shared

  Camera3D *myCam = new Camera3D();
  myCam->setBackground (Color (.5,.5,.5));
    
  int w,h;
  myCanvas->GetSize (&w,&h);
  myCam->getViewing()->setResolution (w,h);
  
  myCam->getViewing()->setView (newWorld->getObjects()->getBounds().getMin(),
                                newWorld->getObjects()->getBounds().getMax());

  myObjectList->adoptObject(myCam);
  
  // four lightsources to have a proper lighting
  
  
  Vector3D min = newWorld->getObjects()->getBounds().getMin();
  Vector3D max = newWorld->getObjects()->getBounds().getMax();
  Vector3D mid = min + ((max - min)/2.0);
  Vector3D diag = max - min;
  
  
  Real z = 2.0 * (max(diag[0], max(diag[1],diag[2])));
  Real theRadius = diag.length() / 7.0;
  Vector3D pos = Vector3D(max[0], max[1], z);
  pos = pos + (pos - mid);
  
  PointLight *myPointLight = new PointLight(.6);
  myPointLight->setPosition (pos);
  myPointLight->setRadius (theRadius);
 
  myPointLight->setColor (Color (1,1,1));
  myObjectList->adoptObject (myPointLight);

  pos = Vector3D(max[0], min[1], z);
  pos = pos + (pos - mid);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (pos);
  myPointLight->setRadius (theRadius);
  myPointLight->setColor (Color (1,1,1));
  myObjectList->adoptObject (myPointLight);


  pos = Vector3D(min[0], min[1], z);
  pos = pos + (pos - mid);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (pos);
  myPointLight->setRadius (theRadius);
  myPointLight->setColor (Color (1,1,1));
  myObjectList->adoptObject (myPointLight);
  
  pos = Vector3D(min[0], max[1], z);
  pos = pos + (pos - mid);
  myPointLight = new PointLight(.6);
  myPointLight->setPosition (pos);
  myPointLight->setRadius (theRadius);
  myPointLight->setColor (Color (1,1,1));
  myObjectList->adoptObject (myPointLight);

  myObjectList->computeBounds();
  
  newWorld->getObjects()->adoptObject(myObjectList);
  newWorld->getObjects()->computeBounds();
  
  myManager->adoptWorld(newWorld);
  
  myManager->notify(wxViewManager::REPAINT, NULL);
}

void SharedEditor::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
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
        if (sharedList.count())
          createNewWorld(sharedList.item(0));
        myCanvas->OnPaint();
      } 
      break;

    case wxViewManager::CAMERAS_CHANGED:
    case wxViewManager::REPAINT:
      break;
    default:
      break;
  }
}
