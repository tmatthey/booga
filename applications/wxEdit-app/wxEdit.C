/*
 * $RCSfile: wxEdit.C,v $
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
 *  $Id: wxEdit.C,v 1.13 1997/02/20 09:17:42 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "DBBrowser.h"
 
#include <iostream>
#include "booga/base/ConfigurationHandler.h"
#include "booga/base/Timer.h"
#include "booga/base/ListUtilities.h"

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/BezierPatch3D.h"

#include "booga/texture/PolygonMapper.h"
#include "booga/texture/PolygonMapperAttr.h"

#include "booga/component/BSDLParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/BSDLWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/RayshadeWriter.h"
#include "booga/component/Parser3D.h"

#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLUtilities.h"

#include "booga/wxwrapper/wxCameraEditor.h"
#include "booga/wxwrapper/wxViewManager.h"
#include "booga/wxwrapper/wxView3DPreferences.h"
#include "booga/wxwrapper/wxWalkThroughCommand.h"
#include "booga/wxwrapper/wxClipboardCommands.h"
#include "booga/wxwrapper/wxBOOGAView.h"
#include "booga/wxwrapper/wxPickCommand.h"

#include "SharedEditor.h"
#include "InspectCommand.h"
#include "GravityCommand.h"
#include "PickCommand.h"
#include "wxAnimator.h"
#include "GLPolygonMapper.h"
#include "InspectSelectionCommand.h"
#include "ToolBar.h"
#include "EditSelection.h"
#include "ObjectFactory.h"
#include "TextureSelector.h"
#include "AlignTool.h"
#include "AdaptiveTraceCommand.h"

#include "wx.h"

#include "wxstring.h"
#include "wx_doc.h"
//#include "wx_timer.h"


// A macro needed for some compilers (AIX) that need 'main' to be defined
// in the application itself.
IMPLEMENT_WXWIN_MAIN

// our ViewManager

wxViewManager ourViewManager;

wxAnimator*      ourAnimator        = NULL;
SharedEditor*    ourSharedEditor    = NULL;
DBBrowser*       ourDBBrowser       = NULL;
EditSelection*   ourEditSelection   = NULL;
ObjectFactory*   ourObjectFactory   = NULL;
TextureSelector* ourTextureSelector = NULL;
AlignTool*       ourAlignTool       = NULL;
wxCameraEditor*  ourCameraEditor    = NULL;

wxFileHistory myFileHistory;
RCString filename;
RCString theLastPath;

//__________________________________________________________________ Defines

//class Console: public wxFrame
//{
//public:
//  Console (wxFrame *frame, char *title, int x, int y);
//  ~Console();
//  OnClose() { return TRUE;};
//  wxTextWindow *myConsoleWindow;
//  ostream *myOs;
//};

class wxEditFrame: public wxFrame, public wxBOOGAView
{ 
public:
  wxEditFrame(wxFrame *frame, char *title, int x, int y, int w, int h);
  ~wxEditFrame();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxFrame
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:  
  int OnClose() { return (TRUE);}
  void OnSize (int w, int h);
  void OnMenuCommand(int id);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxBOOGAView
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public: 
  void update(wxViewManager::NotifyEvent event, Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxEditFrame
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

  wxView3D* getView() { return myCanvas; };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  wxView3D            *myCanvas;
  ToolbarCommand      *myToolBar;
  wxView3DPreferences *myPrefs;
  wxMenu *myFileMenu, *myEditMenu, *myViewMenu, *myToolMenu, *myPickMenu, *myHelpMenu; 
};

// Define a new application type
class wxEditApp: public wxApp
{ 
public:
  wxFrame *OnInit(void);
  void loadWorld (const RCString& filename);
  wxEditFrame *frame;

};

//__________________________________________________________________ Globals


enum fileItems {
  FILE_RELOAD=1,
  FILE_SAVE,
  FILE_SAVEAS,
  FILE_SAVE_RAYSHADE,
  FILE_SAVE_RAYSHADE_ANIM,
  FILE_QUIT
};

enum MenuItems {
  VIEW_PREFERENCES=10, 
  VIEW_INSPECT,
  VIEW_WALKTHROUGH,
  VIEW_ADAPTIVETRACE,
  VIEW_SCREENSHOT,
  VIEW_CAMERAS,
  EDIT_CUT,
  EDIT_COPY,
  EDIT_PASTE,
  EDIT_GROUP,
  EDIT_UNGROUP,
  EDIT_CREATE_SHARED,
  ANIMATOR,
  TOOL_ANIMATION_CONTROL,
  TOOL_SHARED_VIEWER,
  TOOL_INSPECT_SELECTION,
  TOOL_RAYPAINT,
  TOOL_GRAVITY,
  TOOL_REORDER_GRAVITY,
  TOOL_EDIT_SELECTION,
  TOOL_OBJECT_FACTORY,
  TOOL_TEXTURE_SELECTOR,
  TOOL_ALIGN,
  TOOL_DBBROWSER,
  PICK_GRAVITY,
  PICK_STANDARD,
  ST_STATISTICS,
  HELP_ABOUT
};

// This statement initializes the whole application and calls OnInit
wxEditApp myApplication;

// `Main program' equivalent, creating windows and returning main app frame
wxFrame *wxEditApp::OnInit(void)
{


  if (argc > 1)
    filename = wxApp::argv[1];
  else
    filename = "";

  // ---- Read world ----
  loadWorld(filename);

  // Create the main frame window
  frame = new wxEditFrame(NULL, "wxEdit", 50, 50, 400, 400);

  ourViewManager.attach (frame);
  frame->SetSize (frame->getView()->getRenderer()->getCamera()->getViewing()->getResolutionX(), 
                  frame->getView()->getRenderer()->getCamera()->getViewing()->getResolutionY());	

//  ourViewManager.notify (wxViewManager::SELECTION_CHANGED, NULL);
//  ourViewManager.notify (wxViewManager::CLIPBOARD_CHANGED, NULL);  

  // set path for next load dialogue
  theLastPath = RCString(wxPathOnly ((char *)filename.chars()));
  if (theLastPath.isEmpty())  // empty path!
    theLastPath = RCString("."); // default is current directory

  return frame;
}

wxEditFrame::wxEditFrame(wxFrame *pframe, char *title, int x, int y, int w, int h):
  wxFrame(pframe, title, x, y, w, h)
{
  // Make a menubar
  myFileMenu= new wxMenu;
  myFileMenu->Append(wxID_OPEN, "&Open...\tAlt+O");
  myFileMenu->Append(FILE_RELOAD, "&Reload...\tAlt+R");
  myFileMenu->Append(FILE_SAVEAS, "&Save as BSDL...\tAlt+S");
  myFileMenu->Append(FILE_SAVE_RAYSHADE, "&Save as Rayshade...\tAlt+R");
//  myFileMenu->Append(FILE_SAVE_RAYSHADE_ANIM, "&Save as Rayshade animation...");
  myFileMenu->Append(FILE_QUIT, "E&xit");
  // ---- Attach wxFileHistory ----
  myFileHistory.FileHistoryUseMenu(myFileMenu);

  myEditMenu= new wxMenu;
  myEditMenu->Append(EDIT_CUT, "Cut\tCtrl+X");
  myEditMenu->Append(EDIT_COPY, "Copy\tCtrl+C");
  myEditMenu->Append(EDIT_PASTE, "Paste\tCtrl+V");
  myEditMenu->Append(EDIT_GROUP, "Group");
  myEditMenu->Append(EDIT_UNGROUP, "Ungroup");
  myEditMenu->Append(EDIT_CREATE_SHARED, "Create Shared");
	
  myViewMenu = new wxMenu;
  myViewMenu->Append(VIEW_PREFERENCES, "&Preferences...\tAlt+P");
  myViewMenu->Append(VIEW_INSPECT, "&Inspect Mode");
  myViewMenu->Append(VIEW_WALKTHROUGH, "&WalkThrough Mode");
  myViewMenu->Append(VIEW_ADAPTIVETRACE, "Raypaint\tCtrl+R");
  myViewMenu->Append(ANIMATOR, "Animation Control","Animation Control"); 
  myViewMenu->Append(VIEW_SCREENSHOT, "Screenshot\tCtrl+S","Animation Control"); 

  myToolMenu = new wxMenu;
//  myToolMenu->Append(ST_STATISTICS, "Statistics","Display Statistics"); 
  myToolMenu->Append(VIEW_CAMERAS, "&Camera Editor\tAlt+C");
  myToolMenu->Append(TOOL_INSPECT_SELECTION, "Inspect Selection...\tAlt+I", "Edit material.");
  myToolMenu->Append(TOOL_GRAVITY, "Apply Gravity to Selection\tAlt+G", "Gravity");
  myToolMenu->Append(TOOL_REORDER_GRAVITY, "Reorder Gravity in World", "Gravity");
  myToolMenu->Append(TOOL_SHARED_VIEWER, "Edit Shared Objects...", "Raypaint");
  myToolMenu->Append(TOOL_EDIT_SELECTION, "Edit Selection","Edit Selection"); 
  myToolMenu->Append(TOOL_OBJECT_FACTORY, "Object Factory","Edit Selection"); 
  myToolMenu->Append(TOOL_TEXTURE_SELECTOR, "Texture Factory","Edit Selection"); 
  myToolMenu->Append(TOOL_ANIMATION_CONTROL, "Animation Control","Edit Selection"); 
  myToolMenu->Append(TOOL_ALIGN, "Align Selection...","Edit Selection"); 
  myToolMenu->Append(TOOL_DBBROWSER, "DB Browser...","DB Browser"); 

  myPickMenu = new wxMenu;
//  myToolMenu->Append(ST_STATISTICS, "Statistics","Display Statistics"); 
  myPickMenu->Append(PICK_GRAVITY, "&Gravity Picker");
  myPickMenu->Append(PICK_STANDARD, "&Standard Picker");

  myHelpMenu = new wxMenu;
  myHelpMenu->Append(HELP_ABOUT, "About...","About ..."); 

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(myFileMenu, "&File");
  menu_bar->Append(myEditMenu, "&Edit");
  menu_bar->Append(myViewMenu, "&View");
  menu_bar->Append(myToolMenu, "&Tools");
  menu_bar->Append(myPickMenu, "&Pickers");
  menu_bar->Append(myHelpMenu, "&Help");

  SetMenuBar(menu_bar);
  
  myCanvas = new wxView3D(this, 0, 0, 400, 400);
  // myCanvas->adoptMenuCommand (new SelectCommand (myCanvas));
  myCanvas->adoptMouseCommand (new SelectCommand (myCanvas));
  ourViewManager.attach (myCanvas);

  myToolBar = new ToolbarCommand (myCanvas, this, 0,0,400,50);

  myPrefs = NULL;
  SetSize (400, 400);

  // Show the frame
  Show(TRUE);
}

wxEditFrame::~wxEditFrame ()
{
  delete myCanvas;
}

// Intercept size commands
void wxEditFrame::OnSize(int w, int h)
{
  if (myToolBar)
    myToolBar->SetSize (0,0,w,50);
  if (myCanvas)
    myCanvas->SetSize (0,50,w,h-50);
}

// Intercept menu commands
void wxEditFrame::OnMenuCommand(int id)
{
  switch (id) {
    case FILE_QUIT: 
      if (OnClose())
        delete this;
      break;

    case wxID_OPEN: {
      wxBeginBusyCursor();
      char *the_filename = wxFileSelector ("Open bsdl file", wxString(theLastPath.chars()), NULL, NULL, "*.bsdl3");
      if (the_filename  && wxFileExists(the_filename)) {
        filename = RCString(the_filename);
        theLastPath = RCString(wxPathOnly (the_filename));
        myApplication.loadWorld (the_filename);
        SetSize (getView()->getRenderer()->getCamera()->getViewing()->getResolutionX(), 
                 getView()->getRenderer()->getCamera()->getViewing()->getResolutionY());	

        myFileHistory.AddFileToHistory(the_filename);

      }
      wxEndBusyCursor();
      break;
    }			     
  
    case FILE_SAVEAS: {
      char *filename;
      if ((filename = wxFileSelector ("Save BSDL-file as", NULL, NULL, NULL,   "*.bsdl3"))) {
        wxBeginBusyCursor();
        // we have to adjust camera #1 to the current camera in the canvas
        Collector3DFor<Camera3D> camCollector;
        camCollector.execute(ourViewManager.getWorld());
        camCollector.first();
        Camera3D *myCam = camCollector.getObject();    

        myCam->adoptViewing(getView()->getRenderer()->getCamera()->getViewing()->copy());
        
        
        SingleFileStore store(filename);
        BSDLWriter writer(store);
        writer.execute(ourViewManager.getWorld());
        wxEndBusyCursor();
      }
      break;
    }
    case FILE_SAVE_RAYSHADE: {
      char *filename;
      if ((filename = wxFileSelector ("Save Camera file as", NULL, NULL, NULL, "*.ray"))) {
        wxBeginBusyCursor();
        Camera3D *oldCam = (Camera3D *)getView()->getRenderer()->getCamera()->copy();
        RayshadeWriter writer(filename); //, oldCam);
        writer.adoptCamera (oldCam);
        writer.execute(ourViewManager.getWorld());
        wxEndBusyCursor();
        break;
      }
    }
	
    case FILE_RELOAD: {
      if (!wxFileExists(filename.chars()))
        break; // no valid file!

      wxBeginBusyCursor();
      Camera3D *oldCam = (Camera3D *)getView()->getRenderer()->getCamera()->copy();
      myApplication.loadWorld(filename);
      getView()->getRenderer()->adoptCamera (oldCam);
      wxEndBusyCursor();
      OnPaint();
      break;
    }			     
		

    case wxID_FILE1:
    case wxID_FILE2:
    case wxID_FILE3:  
    case wxID_FILE4:
    case wxID_FILE5:
    case wxID_FILE6:
    case wxID_FILE7:  
    case wxID_FILE8:
    case wxID_FILE9: {
      filename = RCString(myFileHistory.GetHistoryFile(id-wxID_FILE1));
      wxBeginBusyCursor();
      myApplication.loadWorld(filename);
      SetSize (getView()->getRenderer()->getCamera()->getViewing()->getResolutionX(), 
      getView()->getRenderer()->getCamera()->getViewing()->getResolutionY());
      wxEndBusyCursor();
      break;
    }  
    
    case TOOL_INSPECT_SELECTION: {
      InspectSelectionCommand c(getView());
      c.execute();
      break;
      }
    
    case TOOL_GRAVITY: {
      GravityCommand c(getView());
      c.execute();
      break;
      }
      
    case TOOL_REORDER_GRAVITY: {
      ReorderGravityCommand c(getView());
      c.execute();
      break;
      }
      
    case VIEW_PREFERENCES: 
      if (!myPrefs)
        myPrefs = new wxView3DPreferences (getView());
      myPrefs->Show(TRUE);
      break;

    case VIEW_INSPECT:
      // getView()->adoptMotionCommand (new InspectCommand (getView()));
      getView()->adoptMouseCommand (new InspectCommand (getView()));
      break;
      
    case VIEW_WALKTHROUGH:
      // getView()->adoptMotionCommand (new wxWalkThroughCommand (getView()));
      getView()->adoptMouseCommand (new wxWalkThroughCommand (getView()));
      break;

    case VIEW_ADAPTIVETRACE: {
      AdaptiveTraceCommand *c = new AdaptiveTraceCommand (getView());
      // getView()->adoptMotionCommand (c);
      getView()->adoptMouseCommand (c);
      c->execute();
      break;
    }

    case PICK_GRAVITY:
      // getView()->adoptPickCommand (new PickCommand (getView()));
      getView()->adoptMouseCommand (new PickCommand (getView()));
      break;

      
    case PICK_STANDARD:
      // getView()->adoptPickCommand (new wxPickCommand (getView()));
      getView()->adoptMouseCommand (new wxPickCommand (getView()));
      break;
      
    case EDIT_CUT: {
      wxCutCommand cut(getView());
      cut.execute();
      getView()->OnPaint();
      break;
      }
   
    case EDIT_COPY: {
      wxCopyCommand copy(getView());
      copy.execute();
      break;
      }
   
    case EDIT_PASTE: { 
      wxPasteCommand paste(getView());
      paste.execute();
      getView()->OnPaint();
      break;
      }
      
    case EDIT_GROUP: { 
      wxGroupCommand c(getView());
      c.execute();
      break;
      }
      
    case EDIT_UNGROUP: { 
      wxUnGroupCommand c(getView());
      c.execute();
      break;
      }
      
    case EDIT_CREATE_SHARED: { 
      wxCreateSharedCommand c(getView());
      c.execute();
      break;
      }

    case VIEW_CAMERAS: {
      if (ourCameraEditor)
        ourCameraEditor->Show(TRUE);
      else {
        ourCameraEditor = new wxCameraEditor (getView(), this);
        ourViewManager.attach (ourCameraEditor);
        ourCameraEditor->Show(TRUE);
      }
	}
	break;

    case TOOL_EDIT_SELECTION: {
      if (!ourEditSelection) {
        ourEditSelection = new EditSelection ();
        ourViewManager.attach (ourEditSelection);
      } else 
        ourEditSelection->Show(true);
	}
	break;

    case TOOL_OBJECT_FACTORY: {
      if (!ourObjectFactory) {
        ourObjectFactory = new ObjectFactory ();
        ourViewManager.attach (ourObjectFactory);
      } else 
        ourObjectFactory->Show(true);
	}
	break;
	
    case TOOL_TEXTURE_SELECTOR: {
      if (!ourTextureSelector) {
        ourTextureSelector = new TextureSelector ();
        ourViewManager.attach (ourTextureSelector);
      } else 
        ourTextureSelector->Show(true);
	}
	break;

    case TOOL_ANIMATION_CONTROL: {
      if (!ourAnimator) {
        ourAnimator = new wxAnimator (NULL,200,200);
        ourViewManager.attach (ourAnimator);
        ourAnimator->Show(true);
      } else 
        ourAnimator->Show(true);
	}
	break;

    case TOOL_SHARED_VIEWER: {
      if (!ourSharedEditor) {
        ourSharedEditor = new SharedEditor (NULL, "Shareds", 200, 200);
        ourViewManager.attach (ourSharedEditor);
        ourSharedEditor->Show(true);
      } else 
        ourSharedEditor->Show(true);
    }
    break;

    case TOOL_DBBROWSER: {
      if (!ourDBBrowser) {
        ourDBBrowser = new DBBrowser (NULL, "DBBrowser", 200, 200);
        ourViewManager.attach (ourDBBrowser);
        ourDBBrowser->Show(true);
      } else 
        ourDBBrowser->Show(true);
    }
    break;

    case TOOL_ALIGN: {
      //if (!ourAlignTool) {
        ourAlignTool = new AlignTool ();
        ourViewManager.attach (ourAlignTool);
        ourAlignTool->Show(true);
      //} else 
//        ourAlignTool->Show(true);
    }
    break;
  
    case VIEW_SCREENSHOT: {
      static int currentFrame = 1;

      AbstractPixmap* pixi = GLUtilities::createPixmapFromFramebuffer();
      RCString filename = "frame";
      filename += form(".%d.pixi", currentFrame++);

      if (pixi->save(filename)) {
        ostrstream os;
        os << "Pixi " << filename << " created";
        Report::hint(os);
      }
  
      delete pixi;
      break;  
    }

  case HELP_ABOUT: {
    (void)wxMessageBox("wxWindows BOOGA demo\nAuthor: Bernhard Bühlmann buhlmann@iam.unibe.ch\nIAM (c) 1995",
		       "About wxBOOGA", wxOK|wxCENTRE);
    break;
  }
  }
}

void wxEditApp::loadWorld (const RCString& filename)
{


  World3D *newWorld = new World3D;

  // remove all namespaces
  Makeable::removeNamespaces();

  // init parser again
  initGLBSDLParserGlobalNS();
  initGLBSDLParser3DNS();

  unregisterParserAttribute("3D", ambient, polygonmapper);
  unregisterParserAttribute("3D", reflectivity, polygonmapper);
  unregisterParserAttribute("3D", specular, polygonmapper);
  unregisterParserAttribute("3D", specpow, polygonmapper);
  unregisterParserExemplar("3D", polygonmapper);

  registerParserExemplar("3D", polygonmapper, GLPolygonMapper);
  registerParserAttribute("3D", ambient, polygonmapper, PolygonMapperAttrAmbient);
  registerParserAttribute("3D", specular, polygonmapper, PolygonMapperAttrSpecular);
  registerParserAttribute("3D", specpow, polygonmapper, PolygonMapperAttrSpecPow);
  registerParserAttribute("3D", reflectivity, polygonmapper, PolygonMapperAttrReflectivity);


  Parser3D parser;
  parser.setFilename(filename);
  parser.execute(newWorld);

  ourViewManager.adoptWorld(newWorld);
 
}

void wxEditFrame::update(wxViewManager::NotifyEvent event, Object3D* /* obj */)
{
  switch (event) {
    case wxViewManager::CAMERAS_CHANGED:
      break;
      
    case wxViewManager::WORLD_CHANGED: 
      break;
      
    case wxViewManager::REPAINT:
      break;
    
    case wxViewManager::SELECTION_CHANGED:
      if (getViewManager()->getSelection()) {
        if (getViewManager()->getSelection()->countSubobject()) {
          myEditMenu->Enable (EDIT_CUT, true);
          myEditMenu->Enable (EDIT_COPY, true);
          myToolMenu->Enable (TOOL_INSPECT_SELECTION, true);
          myToolMenu->Enable (TOOL_GRAVITY, true);
          myEditMenu->Enable (EDIT_CREATE_SHARED, true);
          if(getViewManager()->getSelection()->countSubobject() > 1) {
            myEditMenu->Enable (EDIT_GROUP, true);
            myEditMenu->Enable (EDIT_UNGROUP, false);
          } else {
            myEditMenu->Enable (EDIT_GROUP, false);
            myEditMenu->Enable (EDIT_UNGROUP, true);
          } 
        } else {
          myEditMenu->Enable (EDIT_CUT, false);
          myEditMenu->Enable (EDIT_COPY, false);
          myToolMenu->Enable (TOOL_INSPECT_SELECTION, false);
          myToolMenu->Enable (TOOL_GRAVITY, false);
          myEditMenu->Enable (EDIT_CREATE_SHARED, false);
          myEditMenu->Enable (EDIT_GROUP, false);
          myEditMenu->Enable (EDIT_UNGROUP, false);
        }
        if (getViewManager()->getClipboard()) {
          myEditMenu->Enable (EDIT_PASTE, true);
        } else {
          myEditMenu->Enable (EDIT_PASTE, false);
        }
      }               
      break;
      
    case wxViewManager::CLIPBOARD_CHANGED:
      if (getViewManager()->getClipboard()) {
        myEditMenu->Enable (EDIT_PASTE, true);
      } else {
        myEditMenu->Enable (EDIT_PASTE, true);
      }               
      break;
      
    default: 
      break;
  }
}
