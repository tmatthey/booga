/*
 * wxBrowser.C 
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
 *  $Id: wxBrowser.C,v 1.14 1997/04/17 09:39:15 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/Parser3D.h"
#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLConstantTexture2D.h"
#include "booga/glwrapper/GLPhong.h"

#include "GSBNodeTools.h"
#include "GSBViewManager.h"
#include "GSBwxTreeView.h"
#include "GSBwxConetreeView.h"
#include "GSBwxFlythroughView.h"
#include "GSBConetreeNode3D.h"
#include "wxBrowser.h"

GSBwxAppFrame* GSBMainframe = 0;

World3D* parseFile(const RCString&);
void     listboxCallback(wxListBox&, wxCommandEvent&);
void     parseCmdLine(int argc, char* argv[]);
void     readWorld(char* filename);
void     openWindow(int index);


// define different view types:
RCString viewTypes[] =
		{ "TREE", "CONETREE", "SOURCE", "FLYTHROUGH" };
#define TREE_VIEW	0
#define CONETREE_VIEW	1
#define SOURCE_VIEW	2
#define FLYTHROUGH_VIEW 3

// IDs of menu entries:
#define GSB_MENU_FILE_OPEN          1
#define GSB_MENU_FILE_CLOSE         2
#define GSB_MENU_FILE_SAVE          21
#define GSB_MENU_FILE_SAVEAS        22
#define GSB_MENU_FILE_QUIT          3

#define GSB_MENU_WINDOW_TREE        100
#define GSB_MENU_WINDOW_CONETREE    101
#define GSB_MENU_WINDOW_SOURCE      102
#define GSB_MENU_WINDOW_FLYTHROUGH  103


//_____________________________________________________________________ myApp


// Initialize the whole application and call method OnInit:

GSBApp myApp;
static RCString bsdlPath = ".";
static RCString bsdlFilename = "";

IMPLEMENT_WXWIN_MAIN

// main program equivalent:
wxFrame* GSBApp::OnInit()
{
  Report::setDebug(true);
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  Configuration::setOption(Name("Statistic.OutputStream"),Name("cerr"));

  GSBMainframe = new GSBwxAppFrame(0, "wxBrowser", 50, 50, 300, 200);
  GSBMainframe->CreateStatusLine();
  
 // Create file menu:
  wxMenu* fileMenu = new wxMenu;
  fileMenu->Append(GSB_MENU_FILE_OPEN, "&Open...\tCtrl+O", 
    "Open a file containing BOOGA-scene descriptions");
  fileMenu->Append(GSB_MENU_FILE_CLOSE,"&Close..\tCtrl+C",
    "Close a loaded scene");				 
  fileMenu->AppendSeparator();
  fileMenu->Append(GSB_MENU_FILE_SAVE, "&Save...\tCtrl+S",
    "Save file");
  fileMenu->Append(GSB_MENU_FILE_SAVEAS, "Save &As...",
    "Save file under a new name");
  fileMenu->AppendSeparator();
  fileMenu->Append(GSB_MENU_FILE_QUIT, "E&xit\tCtrl+X",
    "Quit program");
  fileMenu->Enable(GSB_MENU_FILE_SAVE, false);
  fileMenu->Enable(GSB_MENU_FILE_SAVEAS, false);
  
  // Create window menu:
  wxMenu* windowMenu = new wxMenu;
  windowMenu->Append(GSB_MENU_WINDOW_TREE, "Hierarchy of &Objects",
    "Show structure of loaded scene as a two-dimensional tree");
  windowMenu->Append(GSB_MENU_WINDOW_CONETREE, "&Conetree",
		"Show structure of loaded scene as a three-dimensional tree");
  windowMenu->Append(GSB_MENU_WINDOW_FLYTHROUGH, "&Flythrough",
    "Show flythrough view");
  windowMenu->Append(GSB_MENU_WINDOW_SOURCE, "Source &code\t",
    "Show source code of loaded BSDL-scene");
  
  windowMenu->Enable(GSB_MENU_WINDOW_TREE, true);
  windowMenu->Enable(GSB_MENU_WINDOW_SOURCE, false);

  // Create menubar:
  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(fileMenu, "&File");
  menuBar->Append(windowMenu, "&Window");
  GSBMainframe->SetMenuBar(menuBar);
  
  GSBwxPanel* panel = new GSBwxPanel(GSBMainframe);
  panel->SetHorizontalSpacing(1);
  panel->SetLabelPosition(wxVERTICAL);
  wxListBox* listbox = new wxListBox(panel, (wxFunction) listboxCallback, "", wxSINGLE, -1, -1, -1, -1);
  listbox->SetLabel("Loaded BOOGA scenes:");
  GSBMainframe->panel = panel;
  GSBMainframe->listbox = listbox;
  panel->Fit();
  GSBMainframe->Show(true);
  parseCmdLine(argc, argv);
  if (bsdlFilename != "") {
    readWorld((char *) bsdlFilename.chars());
  } else {
    bsdlPath = ".";
  }
  GLConstantTexture2D* texture2D = new GLConstantTexture2D(Color(.0, .0, 1));
  GSBNode2D::adoptSharedTexture(texture2D);
  
  GLPhong* texture3D = new GLPhong;
//  texture3D->setDiffuse(Color(.1, .6, .1));
//  texture3D->setSpecular(Color(.1, .6, .2));
  texture3D->setDiffuse(Color(.9, .9, .9));
  texture3D->setSpecular(Color(.1, .1, .1));
  GSBConetreeNode3D::adoptNodeTexture(texture3D);

  texture3D = new GLPhong;
  texture3D->setDiffuse(Color(.05, .05, .05));
  texture3D->setSpecular(Color(.05, .05, .05));
  GSBConetreeNode3D::adoptTextTexture(texture3D);
  
  texture3D = new GLPhong;
  texture3D->setDiffuse(Color(.0, .0, .9));
  texture3D->setSpecular(Color(.05, .05, .1));
  GSBConetreeNode3D::adoptSharedTexture(texture3D);
  
  texture3D = new GLPhong;
  texture3D->setDiffuse(Color(.9, .0, .0));
  texture3D->setSpecular(Color(.1, .05, .05));
  GSBConetreeNode3D::adoptPickedTexture(texture3D);
  
  return GSBMainframe;
}



//_____________________________________________________________________ GSBwxAppFrame


GSBwxAppFrame::GSBwxAppFrame(wxFrame* frame, char* title, int x, int y, int w, int h) :
  wxFrame(frame, title, x, y, w, h)
{}


void GSBwxAppFrame::OnMenuCommand(int id)
{
  switch (id) {
    case GSB_MENU_FILE_OPEN :
      {
        bsdlFilename = wxFileSelector("Open bsdl file", (char *) bsdlPath.chars(), 0, 0, "*.bsdl3");
        readWorld((char *) bsdlFilename.chars());
        break;
      }

    case GSB_MENU_FILE_CLOSE :
      if (GSBMainframe->listbox->GetSelection() > -1) {
        GSBViewManager* aManager = (GSBViewManager *) GSBMainframe->listbox->
                GetClientData(GSBMainframe->listbox->GetSelection());
        World3D* world = aManager->getWorld();
        delete aManager;
        delete world;
        GSBMainframe->listbox->Delete(GSBMainframe->listbox->GetSelection());
      }
      break;
      
    case GSB_MENU_FILE_QUIT :
      delete this;
      break;
	 
    case GSB_MENU_WINDOW_CONETREE :
      openWindow(CONETREE_VIEW);
      break;
		  
    case GSB_MENU_WINDOW_TREE :
      openWindow(TREE_VIEW);
      break;
      
    case GSB_MENU_WINDOW_FLYTHROUGH :
      openWindow(FLYTHROUGH_VIEW);
      break;
  }
}


void GSBwxAppFrame::OnSize(int w, int h)
{
  int width, height;
  GetClientSize(&width, &height);
  GSBMainframe->panel->SetSize(0, 0, w, h);

}


Bool GSBwxAppFrame::OnClose()
{
  Show(false);
  return true;
}



//_____________________________________________________________________ GSBwxPanel


void GSBwxPanel::OnSize(int, int)
{
  int width, height;
  GetClientSize(&width, &height);
  GSBMainframe->listbox->SetSize(0,0,width, height);
  GSBMainframe->listbox->Fit();
  GSBMainframe->listbox->Centre(wxHORIZONTAL);
  int x, y;
  GSBMainframe->listbox->GetPosition(&x, &y);
  GetPosition(&x, &y);
}


void GSBwxPanel::OnEvent(wxMouseEvent& event)
{
  if (event.ButtonDClick(1)) {
    cout << GSBMainframe->listbox->GetSelection() << " selected." << endl;
  } else {
    wxPanel::OnEvent(event);
  }
}


void GSBwxPanel::OnDefaultAction(wxItem* item)
{
  static bool isIconized = false;
  GSBViewManager* aManager = (GSBViewManager *) GSBMainframe->listbox->
        GetClientData(GSBMainframe->listbox->GetSelection());
  isIconized = isIconized ? false : true;
  aManager->setIconized(isIconized);
  wxPanel::OnDefaultAction(item);
}



//_____________________________________________________________________ functions


void parseCmdLine(int argc, char* argv[])
{
  if (argc >= 2) 
    bsdlFilename = argv[argc-1];
}


World3D* parseFile(const RCString& file2load)
{
  if (wxFileExists(file2load.chars())) {
    World3D* aWorld = new World3D;
    Makeable::removeNamespaces();
    initGLBSDLParserGlobalNS();
    initGLBSDLParser3DNS();

    Parser3D parser;
    parser.setFilename(file2load);
    parser.execute(aWorld);
    return aWorld;
  }
  return 0;
}


void listboxCallback(wxListBox&, wxCommandEvent& event)
{
  cout << "Es wurde Element " << event.commandString << " gewählt.\n";
}


void readWorld(char *filename)
{
  if (wxFileExists(filename)) {
    World3D *world = parseFile(filename);
    world->getObjects()->computeBounds();
    
    // attach a node manager to each object in the world:
    GSBNodeTools nodeManager;
    nodeManager.setActionType(GSBNodeTools::INSTALL_MANAGERS);
    nodeManager.execute(world);
    
    // set path for loading files in future
    bsdlPath = wxPathOnly(filename);
    if (bsdlPath.isEmpty()) {
      bsdlPath = ".";
    }
    
    GSBViewManager *aManager = new GSBViewManager(world);
    aManager->setFilename(filename);
    GSBMainframe->listbox->Append(wxFileNameFromPath(filename), (char *) aManager);
//    GSBwxConetreeView* tree = new GSBwxConetreeView(world, viewTypes[CONETREE_VIEW]);
    GSBwxTreeView* tree = new GSBwxTreeView(world, viewTypes[TREE_VIEW]);
    aManager->attach(tree);
    tree->init();
  } else {
    RCString msg = RCString ("Error while loading ") + filename;
    wxMessageBox ((char*) msg.chars(), "Error");
  }
}


void openWindow(int index)
{
  if (GSBMainframe->listbox->GetSelection() > -1) { // anything selected?
    GSBViewManager* aManager = (GSBViewManager *) 
                GSBMainframe->listbox->GetClientData(GSBMainframe->listbox->GetSelection());
				
    if (aManager == NULL) // just for the unprobable case that sth went wrong
      return;
		
    if (aManager->isAttached(viewTypes[index])) // view already open
      return;

    GSBView* tree(NULL);
    switch(index) {
      case CONETREE_VIEW : 
        tree = new GSBwxConetreeView(aManager->getWorld(), viewTypes[index]);
        break;
      case TREE_VIEW : 
        tree = new GSBwxTreeView(aManager->getWorld(), viewTypes[index]);
        break;
      case FLYTHROUGH_VIEW :
        tree = new GSBwxFlythroughView(aManager->getWorld(), viewTypes[index]);
        break;
      default :
        break;
    }
    if (tree) {
      aManager->attach(tree);
      tree->init();
    }
  }
}
