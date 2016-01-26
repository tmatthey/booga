/*
 * $RCSfile: DBBrowser.C,v $
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
 *  $Id: DBBrowser.C,v 1.4 1997/02/20 09:41:56 matthey Exp $
 * -----------------------------------------------------------------------------
 */

//__________________________________________________________________ BOOGA Includes

#include "booga/object/PointLight.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"

#include "booga/component/Collector3DFor.h"
#include "booga/component/CollectShared3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/SetStandardView3D.h"

#include "booga/persistence/PRef.h"
#include "booga/persistence/Transaction.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/Prototype.h"
#include "booga/persistence/PBinary.h"
#include "booga/persistence/FileBase.h"
#include "booga/persistence/TransientBase.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBStore.h"
#include "booga/graphicsdb/GraphicsDataBase.h"
#include "booga/graphicsdb/ImportBSDL3.h"
#include "booga/graphicsdb/GDBExport.h"

#include "booga/glwrapper/GLBSDLParserInit.h"
 
#include "booga/wxwrapper/wxView3DPreferences.h"
#include "booga/wxwrapper/wxPickCommand.h"



#include "DBBrowser.h"
#include "PickCommand.h"
#include <wxstring.h>
#include <wx.h>

//__________________________________________________________________ Menu items

enum fileItems {VIEW_PREFERENCES=10, FILE_ADD_SHARED, EDIT_APPLY_CHANGES, EDIT_SELECTION, TEXTURE_SELECTOR, OBJECT_FACTORY, ALIGN_TOOL};

DBBrowser::DBBrowser(wxFrame *frame, char *title, int x, int y):
  wxFrame(frame, title, x, y, -1, -1)
{
  myManager = new wxViewManager;
  myCurrentShared= -1;
  myPrefs           = NULL;
  myEditSelection   = NULL;
  myObjectFactory   = NULL;
  myTextureSelector = NULL;
  myAlignSelection  = NULL;

  myPersistentManager = new PersistentManager(1000);

  myPersistentManager->registerPrototype(new GraphicsDataBase(aPrototype));
  myPersistentManager->registerPrototype(new GDBDataType(aPrototype));
  myPersistentManager->registerPrototype(new GDBRepType(aPrototype));
  myPersistentManager->registerPrototype(new GDBData(aPrototype));
  myPersistentManager->registerPrototype(new PBinary(aPrototype));
  myPersistentManager->registerPrototype(new GDBOperation(aPrototype));
  myPersistentManager->registerPrototype(new GDBExport(aPrototype));
  myPersistentManager->registerPrototype(new ImportBSDL3(aPrototype));
//  myPersistenceManager.registerPrototype(new PRCString(aPrototype));

  myTransientBase = new TransientBase;
  myDB = new FileBase("/home/fcg/Scenes/GraphicsBase/");

  createGUI();
}

void DBBrowser::createGUI()
{
  panel = new wxPanel (this, 0,0,300,400);
// the menu:
  wxMenu *file_menu = new wxMenu;
  file_menu->Append(wxID_CLOSE, "&Close...\tAlt+W");

  wxMenu *edit_menu = new wxMenu;
  edit_menu->Append(EDIT_APPLY_CHANGES, "Apply Changes...");
  edit_menu->Append(FILE_ADD_SHARED, "Add to World");

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

  Transaction t;
  t.begin();
  PRef<GraphicsDataBase> gdb(POId(1,2));
  GDBDataType* gdbBsdl3 = gdb->getDataType("Object3D");
  ostrstream os;
  for (int i=0; i<gdbBsdl3->getExtent().count(); i++) { 
    ostrstream os;
    os << gdbBsdl3->getExtent().getKey(i) << "." << gdbBsdl3->getExtent().getData(i).getPOId();       
    RCString mys(os);
    myListBox->Append((char *)mys.chars(), (char *)this);
    myPoidList.append(gdbBsdl3->getExtent().getData(i).getPOId());
  }
  t.commit();
//
//  myListBox->SetSelection (0);
//  if (sharedList.count()) {
//    createNewWorld(sharedList.item(0));
//    myCurrentShared = 0;
//  }
  SetSize (800, 500);
}
  
void DBBrowser::widgetCallbackFunction(wxObject* widget, wxCommandEvent& event)
{
  if (widget == myListBox) {
    createNewWorld (RCString(myListBox->GetString(event.commandInt)), myPoidList.item(event.commandInt));
  }
}

Bool DBBrowser::OnClose(void)
{
//    delete this;
  Show(FALSE);
  return FALSE;
}

void DBBrowser::OnSize(int w, int h)
{
//  cerr << "on size: " << w << "  " << h << "\n";
  
//  SetSize (w,h);
        
  if (panel && myCanvas) {
    panel->SetSize (0,0,200, h);
    myListBox->SetSize (0,50,200,h-50);
    myCanvas->SetSize (200,50, w-200, h-50);
  }
}

void DBBrowser::OnMenuCommand(int id)
{
  switch (id) {
  case wxID_CLOSE: {
    OnClose();
    break;
  }
  
  case FILE_ADD_SHARED: {
    Aggregate3D *a = myManager->getSelection();
    if (a->countSubobject() > 0) {
    for (long j=0; j<a->countSubobject(); j++) {
      Object3D *obj = a->getSubobject(j)->copy();
        getViewManager()->getWorld()->getObjects()->adoptObject(obj);
        getViewManager()->addToSelection(obj);       
      }
    }
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
   
  case VIEW_PREFERENCES: {
    if (!myPrefs)
      myPrefs = new wxView3DPreferences(myCanvas);
    myPrefs->execute();    
    break;	  
  }
  }
}

void DBBrowser::createNewWorld (RCString objectName, POId oid)
{
  World3D *newWorld = new World3D;
  Transaction t;
  t.begin();
//  POId poid(1,oid);
  PRef<GraphicsDataBase> gdb(POId(1,2));
    
  GDBOperation* op = gdb->getOperation("Exporter");
  GDBExport *exporter = dynamic_cast(GDBExport, op);
  if (exporter == NULL) {
     Report::error("[DBBrowser::createNewWorld]: GDBOperation 'Exporter' not found");
     exit(1);
  }
  exporter->execute(oid, POID_NULL);
  BSDL3DParser parser;
  parser.setFilename(exporter->getFilename());
  t.commit();
  // remove all namespaces
  Makeable::removeNamespaces();

  // init parser again
  initGLBSDLParserGlobalNS();
  initGLBSDLParser3DNS();

  parser.execute(newWorld);

  newWorld->getObjects()->computeBounds();

  // now we have to patch the world: 
  // there may be several cases to watch out:
  //   1. it's a scene -> no action, just set Xres and Yres in camera
  //   2. it's a shared -> create an instance of the shared, configure
  //      an appropriate lighting and setup a godd view.
  //   3. it's a texture -> ...?

  //
  // If there is no instance of an object create one and insert it into the world3D
  // 
  if (newWorld->getObjects()->countSubobject() == 0) {
    RCString errmsg;
    Makeable* makeable = Makeable::make(errmsg, 
                         ScopedName(Name(RCString("3D")), Name(objectName)), 
                         new List<Value*>());
    if (makeable == NULL) { // some objs as textures still havn't got oid in name definition
      makeable = Makeable::make(errmsg, 
                 ScopedName(Name(RCString("3D")), Name(objectName)), 
                 new List<Value*>()); // try without oid
      if (makeable == NULL) {
        ostrstream msg;
        msg << "DBBrowser::createNewWorld] object " 
            << objectName << " not found after parsing";
        Report::recoverable(msg);
        return;
      }
    }
    Object3D *obj = dynamic_cast(Object3D, makeable);
    if (obj == NULL) {
      Texture3D *texture = dynamic_cast(Texture3D, makeable);
      if (texture == NULL) {
        ostrstream msg;
        msg << "DBBrowser::createNewWorld] cannot handle object type " 
            << typeid(makeable).name();
        Report::recoverable(msg);
        return;
      } else {
        Sphere3D *sphere = new Sphere3D(1.0,Vector3D(0.,0.,0.));
        sphere->setSpecifier(errmsg, makeable);
        newWorld->getObjects()->adoptObject(sphere);
      }
    }
    else {
      newWorld->getObjects()->adoptObject(obj->copy());
    }
    newWorld->getObjects()->computeBounds();
  }

  // let's check if there are some camreas around...
  // Collect all cameras in the newWorld.
  //  
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(newWorld);
  
  if (camCollector.count() > 0) {
    // we do have a camera...
    // we should set the resolution to the canvas size
  
  } else {
    // get resolution:
    int w,h;
    myCanvas->GetSize (&w,&h);
    
    SetStandardView3D mySet;
    mySet.setResolution(w,h);
    mySet.execute(newWorld);
  }
  myManager->adoptWorld(newWorld);
  
  myManager->notify(wxViewManager::REPAINT, NULL);
}

void DBBrowser::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
{
  switch (event) {
    case wxViewManager::WORLD_NEW:  
    case wxViewManager::WORLD_CHANGED: 
      break;

    case wxViewManager::CAMERAS_CHANGED:
    case wxViewManager::REPAINT:
      break;
    default:
      break;
  }
}
