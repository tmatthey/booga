/*
 * $RCSfile: wxFlythrough.C,v $ 
 *
 * Copyright (C) 1994-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxFlythrough.C,v 1.13 1996/08/30 15:39:13 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <iostream>

#include "booga/base/ReportConfigurationHandler.h"
#include "booga/object/Camera3D.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/VRMLParser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/wxwrapper/wxView3D.h"
#include "booga/wxwrapper/wxView3DPreferences.h"

#include <wx.h>

//__________________________________________________________________ Initialiser
 
static void initParser();
static void readWorld(const RCString& filename);
static void parseCmdLine(int argc, char* argv[]);
static void usage(const RCString& name);

//__________________________________________________________________ Callbacks

// Define a new application type
class wxFlythroughApp: public wxApp
{ 
public:
  wxFrame *OnInit(void);
};

class wxFlythroughFrame: public wxFrame
{ 
public:
  wxFlythroughFrame(int w, int h);
  ~wxFlythroughFrame();
  wxFlythroughFrame(wxFrame *frame, char *title, int x, int y, int w, int h);
  void OnMenuCommand(int id);
  void OnSize(int w, int h);
  Bool OnClose(void) { return TRUE; }
private:
  wxView3D* myCanvas;
};

//__________________________________________________________________ Defines

RCString filename;

wxViewManager ourViewManager;
wxView3DPreferences* ourPrefs = NULL;

enum fileItems { FILE_QUIT, FILE_RELOAD };
enum viewItems { VIEW_PREFERENCES = 1000};

// This statement initializes the whole application and calls OnInit
wxFlythroughApp wxFlythroughApp;

// A macro needed for some compilers (AIX) that need 'main' to be defined
// in the application itself.
IMPLEMENT_WXWIN_MAIN

// `Main program' equivalent, creating windows and returning main app frame
wxFrame *wxFlythroughApp::OnInit(void)
{
  // Create the main frame window
  parseCmdLine(wxApp::argc, wxApp::argv);

// ---- Read world ----
  readWorld(filename);
  return new wxFlythroughFrame(NULL, "wxBooga Sample", 0, 0, 400, 400);
}

wxFlythroughFrame::wxFlythroughFrame(wxFrame *pframe, char *title, int x, int y, int w, int h):
  wxFrame(pframe, title, x, y, w, h)
{
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  file_menu->Append(FILE_RELOAD, "Reload...\tAlt+R");
  file_menu->Append(FILE_QUIT, "E&xit\tCtrl+X");

  wxMenu *view_menu = new wxMenu;

  view_menu->Append(VIEW_PREFERENCES, "Preferences...\tAlt+P");

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
  menu_bar->Append(view_menu, "&View");

  SetMenuBar(menu_bar);
				    
  myCanvas = new wxView3D(this, x, y, w, h,0);
  
  ourViewManager.attach(myCanvas); // attach to View Manager
  
  Show(TRUE); // Show the frame
}

wxFlythroughFrame::~wxFlythroughFrame ()
{
  delete myCanvas;
}

// Intercept size commands
void wxFlythroughFrame::OnSize(int w, int h)
{
  myCanvas->SetSize (0,0, w, h);
}

// Intercept menu commands
void wxFlythroughFrame::OnMenuCommand(int id)
{
  switch (id) {
    case VIEW_PREFERENCES: 
      if (!ourPrefs)
        ourPrefs = new wxView3DPreferences(myCanvas);
      ourPrefs->Show(TRUE);
      break;
    
    case FILE_RELOAD: {
      wxBeginBusyCursor();
      Camera3D *oldCam = (Camera3D *) myCanvas->getRenderer()->getCamera()->copy();
      readWorld (filename);
      myCanvas->getRenderer()->adoptCamera (oldCam);
      myCanvas->OnPaint();
      wxEndBusyCursor();
      break;
	}
		
    case FILE_QUIT:
      if (OnClose())
        delete this;
      break;
  }
}

void usage(const RCString& name)
{
  cerr << "Usage: " << name << " [in-file]\n";
  cerr << " where:\n";
  cerr << "  in-file  : (optional) filename of input\n";
}

void parseCmdLine(int argc, char* argv[])
{
  if (argc >= 2 && !strcmp(argv[1], "-h")) {
    usage(argv[0]);
    exit(0);
  }
    
  if (argc >= 2) 
    filename = argv[argc-1];
}

void initParser() 
{
  initGLBSDLParserGlobalNS();
  initGLBSDLParser3DNS();
}

static void readWorld(const RCString& filename)
{
  World3D* world = new World3D;

  Makeable::removeNamespaces();
  initParser();
  
  Parser3D parser;
  parser.setFilename(filename);
  parser.execute(world);

  ourViewManager.adoptWorld(world);
}



