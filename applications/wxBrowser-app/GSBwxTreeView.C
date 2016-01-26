/*
 * GSBwxTreeView.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
 *                     Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: GSBwxTreeView.C,v 1.17 1997/04/22 13:39:39 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "GSBwxTreeView.h"

#include "booga/object/Camera2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/List2D.h"
#include "booga/object/Path2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/BSDL2DWriter.h"
#include "booga/component/Picker2D.h"
#include "booga/component/CollectShared3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/PSWriter2D.h"
#include "booga/component/SingleFileStore.h"
#include "GSBNodeTools.h"

// icon for canvas frame:
#include "icontree2.xpm"

#define GSB_TREE_CLOSE           99
#define GSB_TREE_SOURCE          4
#define GSB_TREE_SHARED          5
#define GSB_TREE_PREFS           6
#define GSB_TREE_PRUNE           7
#define GSB_TREE_FIT             8
#define GSB_TREE_CONETREE        9
#define GSB_TREE_POSTSCRIPT      10
#define GSB_TREE_BSDL2           11

char *TreeMotionQualityStrings[] = { "Boundingbox", "Flat" };
const TreeMotionQualityCount = 2;

char *TreeLayoutStrings[] = { "From left to right", "Top down" };
const TreeLayoutCount = 2;

//_____________________________________________________________________ GSBwxTreeView

implementRTTI(GSBwxTreeView, GSBView);


GSBwxTreeView::GSBwxTreeView(World3D* world, RCString& IDStr)
: GSBView(world, IDStr),
  myTree(NULL),
  mySharedWorld(NULL),
  myPickingWorld(NULL),
  myXPos(0), 
  myYPos(0),
  myDisplayMode(NORMAL),
  myMarkedObject(NULL),
  myPickingCanvasSize(100),
  myTreeRenderingQuality(GLRasterizer::FLAT),
  myTreeMotionQuality(GLRasterizer::BOUNDING_BOX),
  myPickingRenderingQuality(GLRenderer::SOLID_GOURAUD),
  myPickingMotionQuality(GLRenderer::BOUNDING_BOX),
  myLayoutBorder(20),
  myLayoutDistanceToParents(100),
  myLayoutVertical(false),
  deletionPending(NULL)
{
  myRasterizer = new GLRasterizer;
  myRasterizer->generateWorld(false);
  myRasterizer->setFrameRate(30);

  myRenderer =  new GLRenderer;
  myRenderer->generateWorld(false);
  myRenderer->setFrameRate(30);
  
  myLayouter = new GSBTreeLayouter;
}


GSBwxTreeView::~GSBwxTreeView()
{
cout << "Destruktor von GSBwxTreeView() aufgerufen." << endl << flush;
  if (!(myFrame == deletionPending)) {
    delete myFrame;
  }

  // remove node data
  GSBNodeTools nodeDeinstaller(myViewID);
  nodeDeinstaller.setActionType(GSBNodeTools::REMOVE_NODES);
  nodeDeinstaller.execute(myWorld);
  
  // remove tree data
  delete myLayouter;
  delete myRasterizer;
  delete myTree;
  delete mySharedWorld;
  delete myPrefs;
}


void GSBwxTreeView::createGUI()
{
  // create frame widget:
  myFrame = new wxManagedFrame(this, (wxFrame*) NULL, "", -1, -1, 500, 500);
  RCString name = "Main View: " + 
        RCString(wxFileNameFromPath((char*) myViewManager->getFilename().chars()));
  myFrame->SetIcon(new wxIcon(icontree2_xpm));
  myFrame->SetTitle((char*) name.chars());
  myFrame->Show(true);
  
  // create view menu:
  myViewMenu = new wxMenu;
  myViewMenu->Append(GSB_TREE_PREFS, "P&references\tCtrl+P", 
    "Set preferences");
  myViewMenu->AppendSeparator();
  myViewMenu->Append(GSB_TREE_POSTSCRIPT, "S&ave Tree as Postscript\tCtrl+S",
    "Save tree as a postscript file");
  myViewMenu->Append(GSB_TREE_BSDL2, "S&ave Tree as BSDL2\tCtrl+B",
    "Save tree as a bsdl2 file");
  myViewMenu->AppendSeparator();
  myViewMenu->Append(GSB_TREE_CLOSE, "&Close\tCtrl+C", "Close this window");
  
  // create edit menu:
  myEditMenu = new wxMenu;
  myEditMenu->Append(GSB_TREE_FIT,   "&Fit Tree To Screen\tF",
    "Fits the tree to the size of the window");
  myEditMenu->Append(GSB_TREE_PRUNE, "&Prune Node (Toggle)\tP",
    "Toggle pruning of marked node");
    
  // create menu bar:
  myMenuBar = new wxMenuBar;
  myMenuBar->Append(myViewMenu, "&View");
  myMenuBar->Append(myEditMenu, "&Edit");
  myFrame->SetMenuBar(myMenuBar);

  // create canvas:
  myCanvas = new wxManagedCanvas(this, myFrame, -1, -1, 500, 500, wxRETAINED);
  if (mySharedWorld) {
    myPickingCanvas = new wxManagedCanvas(this, myFrame, -1, -1, 100, 100, wxRETAINED);
    myPickingCanvas->GLClear();
  }
  else
    myPickingCanvas = NULL;
  
  // create preferences:
  myPrefs = new wxManagedDialogBox(this, 0, "Preferences");
  myLayoutChoice = new wxManagedChoice(this, myPrefs, "Tree layout: ", -1, 
    -1, -1, -1, TreeLayoutCount, TreeLayoutStrings);
  myPrefs->NewLine();
  myTreeMotionQualityChoice = new wxManagedChoice(this, myPrefs, 
    "Tree motion quality: ", -1, -1, -1, -1, TreeMotionQualityCount, TreeMotionQualityStrings);
    
  myPrefs->NewLine();
  myLayoutBorderSlider = new wxManagedSlider(this, myPrefs,
    "Border around tree nodes:", 20, 5, 60, 300);
  myPrefs->NewLine();
  myLayoutDistanceToParentsSlider = new wxManagedSlider(this, myPrefs, 
    "Distance to parent node:", 50, 10, 120, 300);
  myPrefs->NewLine();
  myPickingCanvasSizeSlider = new wxManagedSlider(this, myPrefs,
    "Size of Picking Canvas:", 100, 25, 500, 300);
    
  myPrefs->NewLine();
  myApplyButton = new wxManagedButton(this, myPrefs, "Apply");
  myCloseButton = new wxManagedButton(this, myPrefs, "Close");
  myPrefs->Fit();
  myPrefs->Center(wxBOTH);
  
  // create saver:
}


void GSBwxTreeView::init()
{
  // add data to all objects in my world:
  GSBNodeTools nodeInstaller(myViewID);
  nodeInstaller.setActionType(GSBNodeTools::INSTALL_NODES);
  GSBTreeNode* proto = new GSBTreeNode(myViewID);
  proto->setHeight(30);
  proto->setBorder(20);
  nodeInstaller.adoptNodePrototype(proto);
  nodeInstaller.execute(myWorld);
  
  // set label of root object:
  RCString label("World 3D");
  proto = 
    dynamic_cast(GSBTreeNode, GSBNodeTools::getNode(myWorld->getObjects(), myViewID));
  if (proto != NULL)        // this test shouldn't be necessary (?)
    proto->setLabel(label);
  
  CollectShared3D sharedCollector;
  sharedCollector.setSortCollection(true);
  sharedCollector.execute(myWorld);
  

  if (sharedCollector.first(), !sharedCollector.isDone()) {
    mySharedWorld = new World3D;    

    for(sharedCollector.first(); !sharedCollector.isDone(); sharedCollector.next()) {
      mySharedWorld->getObjects()->adoptObject(sharedCollector.getCurrent()->copy());
    }
    proto = new GSBTreeNode(myViewID);
    proto->setHeight(30);
    proto->setBorder(20);
    nodeInstaller.adoptNodePrototype(proto);
    nodeInstaller.execute(mySharedWorld);
  
    // set label of root shared object:
    label = "Shared objects";
    proto =
      dynamic_cast(GSBTreeNode, GSBNodeTools::getNode(mySharedWorld->getObjects(), myViewID));
    if (proto != NULL) {      // this test shouldn't be necessary (?)
      Text2D text(label);
      text.computeBounds();
      proto->setWidth((text.getBounds().getMax() - text.getBounds().getMin()).x());
      proto->setLabel(label);
    }
  }

  // Create the GUI:
  createGUI();
  
  // update display:
  update(GSBViewManager::REPAINT);
}


void GSBwxTreeView::update(GSBViewManager::NotifyEvent event)
{
  switch(event) {
    case GSBViewManager::REPAINT :
      layout();
      myCanvas->OnPaint();
      break;
    case GSBViewManager::ICONIZE :
      myFrame->Show(false);
      break;
    case GSBViewManager::UNICONIZE :
      myFrame->Show(true);
      break;
    case GSBViewManager::PICKING :
      layout();
      myCanvas->OnPaint();
      myMarkedObject = myViewManager->getPickedObject();
      showPicking(myMarkedObject);
      break;
    case GSBViewManager::PRUNING :
      layout();
      myCanvas->OnPaint();
      break;
    case GSBViewManager::SUBJECT_KILLED : 
      // view manager is being destroyed
      delete this;
    default :
      break;
  }
}


void GSBwxTreeView::pan(Real dx, Real dy)
{
  Viewing2D* viewing = myRasterizer->getCamera()->getViewing();
  viewing->setWindow((viewing->getWindowOrigin() + Vector2D(-dx, dy)),
                      viewing->getWindowSize());
}


void GSBwxTreeView::zoom(Real /* dx */, Real dy)
{
  Viewing2D* viewing = myRasterizer->getCamera()->getViewing();

  viewing->setWindow(viewing->getWindowOrigin(),
                     Vector2D(viewing->getWindowSize().x() + dy,
                              viewing->getWindowSize().y() + dy));
}


void GSBwxTreeView::pickObject(int x, int y)
{
  Picker2D picker;      
  picker.setCamera(myRasterizer->getCamera()); 
  picker.setPickOrigin(x, myRasterizer->getCamera()->getViewing()->getResolutionY()-y-1);
  picker.execute(myTree);
  if (picker.getPath() != NULL) {
    GSBNode2D* aNode;
    for (picker.getPath()->last(); !picker.getPath()->isDone(); picker.getPath()->prev()) {
      aNode = dynamic_cast(GSBNode2D, picker.getPath()->getObject());
      if (aNode) {
        if (aNode->getRepresentWho() == NULL) {
          // something's fishy .. get out
          break;
        }
//        GSBNodeManager* pickedManager = GSBNodeTools::getNodeManager(aNode->getRepresentWho());
//        if (myMarkedObject != aNode->getRepresentWho()) {
//          if (myMarkedObject)
//            GSBNodeTools::getNodeManager(myMarkedObject)->setMarked(false);
//          pickedManager->setMarked(true);
//          myMarkedObject = aNode->getRepresentWho();
//        } else {
//          pickedManager->setMarked(false);
//          myMarkedObject = (Object3D*) NULL;
//        }
        
        // Something got picked. Make sure the view gets updated.
        // ==> notify view manager
        myViewManager->picking(aNode->getRepresentWho());
        break;
      }
    }
  }
}


void GSBwxTreeView::showPicking(Object3D* obj)
{
  if (myPickingCanvas) {
    myPickingCanvas->GLClear();
  }
  
  Shared3D* shobj = dynamic_cast(Shared3D, obj);
  // is the picked object shared?
  if (shobj == NULL) 
    return;

  delete myPickingWorld;
  
  myPickingWorld = new World3D;
  myPickingWorld->getObjects()->adoptObject(shobj->copy());
  myPickingWorld->getObjects()->computeBounds();
  
  // delete all existing cameras
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(myPickingWorld);
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    delete camCollector.getObject();
                  
  // delete all existing light sources
  Collector3DFor<LightSource> lightCollector;
  lightCollector.execute(myPickingWorld);
  for (lightCollector.first(); !lightCollector.isDone(); lightCollector.next())
    delete lightCollector.getObject();
                  
  // add new camera
  Camera3D* cam = new Camera3D;
  cam->setBackground(Color(.6,.6,.6));
  Vector3D ll(myPickingWorld->getObjects()->getBounds().getMin());
  Vector3D ur(myPickingWorld->getObjects()->getBounds().getMax());
                
  cam->getViewing()->setEye(ur-ll-Vector3D(-20,0,0));
  int width, height;
  myPickingCanvas->GetSize(&width, &height);
  cam->getViewing()->setResolution(width, height);
  cam->getViewing()->setView(ll, ur);
  cam->getViewing()->setLookat((ur + ll)/2);
                
  myRenderer->adoptCamera(cam);
                
  // set up lighting (four light sources)
  float scale = sqrt(((ur - ll).x() * (ur - ll).x())/4 + 
                ((ur - ll).y() * (ur - ll).y())/4) * 2;
  PointLight *light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(1, 1, 0));
  light->setColor(Color(1,1,1));
  myPickingWorld->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(-1, 1, 0));
  light->setColor(Color(1,1,1));
  myPickingWorld->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(-1, -1, 0));
  light->setColor(Color(1,1,1));
  myPickingWorld->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(1, -1, 0));
  light->setColor(Color(1,1,1));
  myPickingWorld->getObjects()->adoptObject(light);             
                
  myPickingWorld->getObjects()->computeBounds();
  myPickingCanvas->OnPaint();
}


void GSBwxTreeView::adoptTree(World2D* newWorld)
{
  if (newWorld == NULL)
    Report::error("[GSBwxTreeCanvas::adoptTree] NULL world passed!");

  if (newWorld == myTree)
    return;        // nothing to be done
      
  Camera2D* foundCam = (Camera2D*) myRasterizer->getCamera();

  delete myTree;
  myTree = newWorld;

  if (foundCam) {
    // use old camera
    myRasterizer->adoptCamera(foundCam);
  } else {
    updateViewing();
  }
}


void GSBwxTreeView::updateViewing()
{
  if (myTree == NULL)
    return;        // nothing to be done

  // make new camera
  Camera2D* cam = new Camera2D;
  Vector2D ll(myTree->getObjects()->getBounds().getMin());
  Vector2D ur(myTree->getObjects()->getBounds().getMax());
  cam->getViewing()->setWindow(ll,ur-ll);
  int w, h;
  myCanvas->GetSize(&w,&h);
  cam->getViewing()->setResolution(w, h);
  cam->setBackground(Color(.5,.5,.5));
  myRasterizer->adoptCamera(cam);
}


void GSBwxTreeView::bestFitToScreen()
{
  cout << "Trying BestFit.\n" << flush;
  
  if (myTree == NULL)
    return;       // nothing to be done
    
  // make a new camera
  Camera2D* cam = new Camera2D;
  
  Vector2D ll(myTree->getObjects()->getBounds().getMin());
  Vector2D ur(myTree->getObjects()->getBounds().getMax());
  
//  float resX = (ur - ll).x(),
//        resY = (ur - ll).y();
//
  int w, h;
  myCanvas->GetSize(&w,&h);
  Viewing2D* viewing = cam->getViewing();
  cam->setBackground(Color(.5,.5,.5));
//  
//  Vector2D oc;
//  if (w/h < resX/resY)
//    oc = ll + Vector2D(resX * w/h, resY);
//  else
//    oc = ll + Vector2D(resX, resY * h/w);
//  viewing->setWindow(viewing->getWindowOrigin(),
//                     viewing->getWindowSize());
//  viewing->setResolution((oc-ll).x(), (oc-ll).y());
  float c = w/(ur-ll).x();
  if (h/(ur-ll).y() > c) 
    c = h/(ur-ll).y();

  viewing->setResolution(w, h);
  viewing->setWindow(ll, 2*c*(ur-ll));
  
  myRasterizer->adoptCamera(cam);
  myCanvas->OnPaint();
}


void GSBwxTreeView::moveCamera(Real dx, Real dy)
{
  Viewing3D* viewing = myRenderer->getCamera()->getViewing();

  Vector3D eyep  = viewing->getEye();   
  Vector3D lookp = viewing->getLookat();        
  Vector3D up    = viewing->getUp();
  Vector3D direction = eyep - lookp;

  Vector3D dist = eyep-lookp;

  // Move left / right

  Vector3D left = up*(eyep-lookp);
  Vector3D l = -dx * left/left.length()*dist.length()*.005;
  

  // Move forward / backward

  Vector3D m = dy * direction.normalized() * dist.length() * .005;
  eyep += m - l; 
  lookp += m - l;

  viewing->setEye(eyep);
  viewing->setLookat(lookp);
}


void GSBwxTreeView::rotateAroundLookp(Real theta, Real phi)
{
  Viewing3D* viewing = myRenderer->getCamera()->getViewing();

  //
  // n: Direction to the observer.
  // v: Up direction.
  // u: To the right.
  //
  Vector3D n = viewing->getLookat() - viewing->getEye(); 
  n.normalize(); 

  Vector3D v = viewing->getUp() - (n^viewing->getUp())*n;  
  v.normalize(); 

  Vector3D u = n * v; 
  u.normalize();
  
  TransMatrix3D phi_rot;
  phi_rot.rotate(v, sin(dtor(-theta)), cos(dtor(-theta)));
  TransMatrix3D rot = phi_rot;
  rot.rotate(u*phi_rot, sin(dtor(-phi)), cos(dtor(-phi))); 
  
  TransMatrix3D rotateEye;
  rotateEye.translate(-viewing->getLookat());
  rotateEye *= rot;
  rotateEye.translate(viewing->getLookat());

  viewing->setEye(viewing->getEye() * rotateEye);
}


void GSBwxTreeView::layout()
{
  // adjust settings for layouter:
  myLayouter->setViewID(myViewID);
  myLayouter->setDistanceToParents(myLayoutDistanceToParents);
  myLayouter->setBorder(myLayoutBorder);
  myLayouter->setVertical(myLayoutVertical);
  
  if (myDisplayMode == SHARED)
    adoptTree(myLayouter->execute(mySharedWorld));
  else
    adoptTree(myLayouter->execute(myWorld));
}


void GSBwxTreeView::fitToScreen()
{
  cout << "fitToScreen.\n" << flush;
  updateViewing();
  myCanvas->OnPaint();
}


void GSBwxTreeView::pruneNode()
{
  if (myMarkedObject != NULL) {
    myViewManager->pruning(myMarkedObject);
  }
}


void GSBwxTreeView::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget == myApplyButton) {
    update(GSBViewManager::REPAINT);
    if (myPickingCanvas) {
      myPickingCanvas->SetSize(0,0, myPickingCanvasSize, myPickingCanvasSize, 0);
      showPicking(myMarkedObject);
    }
//    myRenderer->getCamera()->getViewing()->setResolution(
//      myPickingCanvasSize, myPickingCanvasSize);
  } else
  
  if (widget == myCloseButton)
    myPrefs->Show(false);
  else
  
  if (widget == myLayoutBorderSlider)
    myLayoutBorder = ((wxManagedSlider *) widget)->GetValue();
  else
  
  if (widget == myLayoutDistanceToParentsSlider)
    myLayoutDistanceToParents = ((wxManagedSlider *) widget)->GetValue();
  else
  
  if (widget == myLayoutChoice)
    myLayoutVertical = myLayoutVertical ? false : true;
  else
  
  if (widget == myTreeMotionQualityChoice)
   myTreeMotionQuality = 
     (GLRasterizer::RenderingQuality) (((wxManagedChoice*) widget)->GetSelection() + 1);
  else
  
  if (widget == myPickingCanvasSizeSlider) 
    myPickingCanvasSize = ((wxManagedSlider *) widget)->GetValue();
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnChar(wxObject* widget, wxKeyEvent& event)
{
  if (widget == myCanvas) {
    // <SPACE> pressed ==> show SHARED WORLD
    cout << "keycode = " << event.keyCode << endl << flush;
    if (event.keyCode == WXK_SPACE) {
      if (mySharedWorld) {
        myDisplayMode = (myDisplayMode == NORMAL) ? SHARED : NORMAL;
        update(GSBViewManager::REPAINT);
      }
    } else
    
    // <p> or <P> pressed ==> PRUNING
    if ((event.keyCode == 'p') || (event.keyCode == 'P')) {
      pruneNode();
    } else
    
    // <f> or <F> pressed ==> FIT TO SCREEN
    if (event.keyCode == 'f') {
      bestFitToScreen();  
    } else
    
    if ((event.keyCode == 111) || (event.keyCode == 'G')) {
      fitToScreen();
    }

  } else
  
  if (widget == myPickingCanvas) {
    if ((event.keyCode == WXK_ADD) || (event.keyCode == WXK_SUBTRACT)) {
      if (event.keyCode == WXK_ADD)
        myPickingCanvasSize = (myPickingCanvasSize <= 475) 
                ? myPickingCanvasSize + 25 : myPickingCanvasSize;
      else
        myPickingCanvasSize = (myPickingCanvasSize > 25) 
                ? myPickingCanvasSize - 25 : myPickingCanvasSize;
      myPickingCanvas->SetSize(0,0, myPickingCanvasSize, myPickingCanvasSize, 0);
      myPickingCanvasSizeSlider->SetValue(myPickingCanvasSize);
      showPicking(myMarkedObject);
    }
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnClose(wxObject* widget)
{
  if (widget == myFrame) {
    deletionPending = myFrame;

    // detach from view manager
    myViewManager->detach(myViewID);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnEvent(wxObject* widget, wxMouseEvent& event)
{
  if (widget == myCanvas) {
    float x, y;
    event.Position(&x, &y);
    if (myXPos > -1 && myYPos > -1 && event.Dragging() && event.RightIsDown()) {
      myRasterizer->setRenderingQuality(myTreeMotionQuality);
      zoom(x - myXPos, y - myYPos);
      myRasterizer->setRenderingQuality(myTreeMotionQuality);
      myCanvas->OnPaint();
    } else if (myXPos > -1 && myYPos > -1 && event.Dragging() && event.MiddleIsDown()) {
      myRasterizer->setRenderingQuality(myTreeMotionQuality);
      pan(x - myXPos, y - myYPos);
      myCanvas->OnPaint();
    } else if (event.LeftUp() && !event.Dragging()) {
      pickObject((int) x, (int) y);
    } else if (event.MiddleUp() || event.RightUp()) {
      myRasterizer->setRenderingQuality(myTreeRenderingQuality);
      myCanvas->OnPaint();
    }
    myXPos = x;
    myYPos = y;
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  
  if (widget == myPickingCanvas) {
    if (myPickingWorld) {
      float x, y;
      event.Position(&x, &y);

      if (x > -1 && y > -1 && event.Dragging() && event.RightIsDown()) {
        moveCamera(x - myPickingXPos, y - myPickingYPos);
        myRenderer->setRenderingQuality(myPickingMotionQuality);
        myPickingCanvas->OnPaint();
      } else
      
      if (x > -1 && y > -1 && event.Dragging() && event.MiddleIsDown()) {
        myRenderer->setRenderingQuality(myPickingMotionQuality);
        rotateAroundLookp(x - myPickingXPos, y - myPickingYPos);
        myPickingCanvas->OnPaint();
      } else 
      
      if (event.MiddleUp() || event.RightUp()) {
        myRenderer->setRenderingQuality(myPickingRenderingQuality);
        myPickingCanvas->OnPaint();
      }
      myPickingXPos = x;
      myPickingYPos = y; 
    }
  }
  return wxDialogDirector::NO_DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnSize(wxObject* widget, int width, int height)
{
  if (widget == myFrame) {
    if ((width == -1) && (height == -1)) 
      myFrame->GetSize(&width, &height);
    myCanvas->SetSize(0, 0, width, height);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  } else if (widget == myCanvas) {
    myRasterizer->getCamera()->getViewing()->setResolution(width, height);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  } else if (widget == myPickingCanvas) {
    myRenderer->getCamera()->getViewing()->setResolution(
      myPickingCanvasSize, myPickingCanvasSize);
    cout << "OnSize called ..." << endl << flush;
    return wxDialogDirector::DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnMenuCommand(wxObject* widget, int id)
{
  if (widget == myFrame) {
    switch (id) {
      case GSB_TREE_CLOSE :
        // detach from view manager
        myViewManager->detach(myViewID);
        delete this;
        break;
      case GSB_TREE_FIT :
        fitToScreen();
        break;
      case GSB_TREE_PRUNE :
        pruneNode();
        break;
      case GSB_TREE_PREFS :
        myPrefs->Show(true);
        break;
      case GSB_TREE_POSTSCRIPT : {
        RCString filename = wxFileSelector("Save current tree view as postscript", 
          ".", 0, 0, "*.ps");
        if (!filename.isEmpty()) {
          int w,h;
          Vector2D from(myRasterizer->getCamera()->getViewing()->getWindowOrigin());
          Vector2D to(from + myRasterizer->getCamera()->getViewing()->getWindowSize());
          myCanvas->GetSize(&w,&h);
          Camera2D* cam = new Camera2D;
          cam->getViewing()->setWindow(Vector2D(0,0),Vector2D(w,h));
          cam->getViewing()->setResolution(w,h);
          Aggregate2D* agg = myTree->getObjects();
          long i;
          Vector2D scale(w/(to-from).x(),h/(to-from).y());
          for(i=0; i<agg->countSubobject(); i++){
             agg->getSubobject(i)->setTransform(TransMatrix2D::makeTranslate(-from));
             agg->getSubobject(i)->addTransform(TransMatrix2D::makeScale(scale));
          }

          PSWriter2D writer(filename);
          writer.adoptCamera(cam);
          writer.execute(myTree);

          for(i=0; i<agg->countSubobject(); i++)
             agg->getSubobject(i)->setTransform(TransMatrix2D());
          writer.deleteCamera();
        }
        break;
      }
      case GSB_TREE_BSDL2 : {
        RCString filename = wxFileSelector("Save current tree view as bsdl2", 
          ".", 0, 0, "*.bsdl2");
        if (!filename.isEmpty()) {
          DocumentStore* docuStore = new SingleFileStore(filename);
          BSDL2DWriter writer(*docuStore);
          int w,h;
          Vector2D from(myTree->getObjects()->getBounds().getMin());
          Vector2D to(myTree->getObjects()->getBounds().getMax());
          myCanvas->GetSize(&w,&h);
          Camera2D* cam = new Camera2D;
          cam->getViewing()->setWindow(Vector2D(0,0),Vector2D(w,h));
          cam->getViewing()->setResolution(w,h);
          myTree->getObjects()->adoptObject(cam);
          Aggregate2D* agg = myTree->getObjects();
          long i;
          Vector2D scale(w/(to-from).x(),h/(to-from).y());
          for(i=0; i<agg->countSubobject(); i++){
             agg->getSubobject(i)->setTransform(TransMatrix2D::makeTranslate(-from));
             agg->getSubobject(i)->addTransform(TransMatrix2D::makeScale(scale));
          }
          writer.execute(myTree);
          for(i=0; i<agg->countSubobject(); i++)
             agg->getSubobject(i)->setTransform(TransMatrix2D());
          myTree->getObjects()->orphanObject(cam);
        }
        break;
      }
    }
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxTreeView::widgetOnPaint(wxObject* widget)
{
  if (widget == myCanvas) {
    myRasterizer->execute(myTree);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  } else
  
  if (widget == myPickingCanvas) {
    myRenderer->execute(myPickingWorld);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  
  return wxDialogDirector::DEFAULT_ACTION; 
}

