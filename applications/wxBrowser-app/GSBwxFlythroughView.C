/*
 * GSBwxFlythroughView.C 
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
 *  $Id: GSBwxFlythroughView.C,v 1.4 1997/04/17 09:39:04 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#include "GSBwxFlythroughView.h"

#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/AmbientLight.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/Picker3D.h"
#include "GSBNodeTools.h"
#include "GSBGLRenderer.h"
#include "PathFinder.h"

// icon for canvas frame:
#include "icontree2.xpm"

#define GSB_FLYTHROUGH_CLOSE          99
#define GSB_FLYTHROUGH_PREFS          1
#define GSB_FLYTHROUGH_PRUNE          2

char *MotionQualityStrings[] = { "Boundingbox", "Flat" };
const MotionQualityCount = 2;

//_____________________________________________________________________ GSBwxFlythroughView

implementRTTI(GSBwxFlythroughView, GSBView);

GSBwxFlythroughView::GSBwxFlythroughView(World3D* world, RCString& IDStr)
: GSBView(world, IDStr),
  myPickedObject(0),
  myXPos(0), 
  myYPos(0),
  myMarkedObject(NULL),
  myRenderingQuality(GLRenderer::SOLID_GOURAUD),
  myMotionQuality(GLRenderer::BOUNDING_BOX),
  deletionPending(NULL)
{
  myRenderer =  new GSBGLRenderer;
  myRenderer->generateWorld(false);
  myRenderer->setFrameRate(30);
//  myRenderer->adoptTraversal(new GSBGLTraversal3D);
}


GSBwxFlythroughView::~GSBwxFlythroughView()
{
cout << "Destruktor von GSBwxFlythroughView() aufgerufen." << endl << flush;
  if (!(myFrame == deletionPending)) {
    delete myFrame;
  }

  // remove node data
  GSBNodeTools nodeDeinstaller(myViewID);
  nodeDeinstaller.setActionType(GSBNodeTools::REMOVE_NODES);
  nodeDeinstaller.execute(myWorld);
  
  // remove tree data
  delete myPrefs;
}


void GSBwxFlythroughView::createGUI()
{
  // create frame widget:
  myFrame = new wxManagedFrame(this, (wxFrame*) NULL, "", -1, -1, 500, 500);
  RCString name = "GSBwxFlythrough: " + 
        RCString(wxFileNameFromPath((char*) myViewManager->getFilename().chars()));
  myFrame->SetIcon(new wxIcon(icontree2_xpm));
  myFrame->SetTitle((char*) name.chars());
  myFrame->Show(true);
  
  // create view menu:
  myViewMenu = new wxMenu;
  myViewMenu->Append(GSB_FLYTHROUGH_PREFS, "P&references\tCtrl+P", 
    "Set preferences");
  myViewMenu->Append(GSB_FLYTHROUGH_CLOSE, "&Close\tCtrl+C", "Close this window");
  
  // create edit menu:
  myEditMenu = new wxMenu;
  myEditMenu->Append(GSB_FLYTHROUGH_PRUNE, "&Prune Node\tP",
    "Toggle pruning of marked node");
    
  // create menu bar:
  myMenuBar = new wxMenuBar;
  myMenuBar->Append(myViewMenu, "&View");
  myMenuBar->Append(myEditMenu, "&Edit");
  myFrame->SetMenuBar(myMenuBar);

  // create canvas:
  myCanvas = new wxManagedCanvas(this, myFrame, -1, -1, 500, 500, wxRETAINED);
  
  // create preferences:
  myPrefs = new wxManagedDialogBox(this, 0, "Preferences GSBwxFlythrough");
  myMotionQualityChoice = new wxManagedChoice(this, myPrefs, 
    "Tree motion quality: ", -1, -1, -1, -1, MotionQualityCount, MotionQualityStrings);
    
  myPrefs->NewLine();
    
  myPrefs->NewLine();
  myApplyButton = new wxManagedButton(this, myPrefs, "Apply");
  myCloseButton = new wxManagedButton(this, myPrefs, "Close");
  myPrefs->Fit();
}


void GSBwxFlythroughView::init()
{
  createGUI();
  adoptWorld(myWorld);
  
  // update display:
  update(GSBViewManager::REPAINT);
}


void GSBwxFlythroughView::update(GSBViewManager::NotifyEvent event)
{
  switch(event) {
    case GSBViewManager::REPAINT :
      myCanvas->OnPaint();
      break;
    case GSBViewManager::ICONIZE :
      myFrame->Show(false);
      break;
    case GSBViewManager::UNICONIZE :
      myFrame->Show(true);
      break;
    case GSBViewManager::PICKING : {
//      myPickedObject = myViewManager->getPickedObject();
//      PathFinder find;
//      find.findObject(myPickedObject, myWorld);
//      if (find.getPath())
//        cout << "FOUND PATH" << endl << flush;
//      else
//        cout << "NOTHING FOUND" << endl << flush;
      myCanvas->OnPaint();
      break;
    }
    case GSBViewManager::PRUNING :
      myCanvas->OnPaint();
      break;
    case GSBViewManager::SUBJECT_KILLED : 
      // view manager is being destroyed
      delete this;
    default :
      break;
  }
}


//void GSBwxFlythroughView::pickObject(int x, int y)
//{
//  Picker2D picker;	
//  picker.setCamera(myRasterizer->getCamera()); 
//  picker.setPickOrigin(x, myRasterizer->getCamera()->getViewing()->getResolutionY()-y-1);
//  picker.apply(myTree);
//  if (picker.getPath() != NULL) {
//    GSBNode2D* aNode;
//    for (picker.getPath()->last(); !picker.getPath()->isDone(); picker.getPath()->prev()) {
//      aNode = dynamic_cast(GSBNode2D, picker.getPath()->getObject());
//      if (aNode) {
//        if (aNode->getRepresentWho() == NULL) {
//          // something's fishy .. get out
//          break;
//        }
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
//			
//        // Something got picked. Make sure the view gets updated.
//        // ==> notify view manager
//        myViewManager->picking(aNode->getRepresentWho());
//        break;
//      }
//    }
//  }
//}


void GSBwxFlythroughView::moveCamera(Real dx, Real dy)
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


void GSBwxFlythroughView::rotateAroundLookp(Real theta, Real phi)
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


//void GSBwxFlythroughView::pruneNode()
//{
//  if (myMarkedObject != NULL) {
//    GSBNodeTools::getNodeManager(myMarkedObject)->setPruned(
//        GSBNodeTools::getNodeManager(myMarkedObject)->isPruned() ? false : true);
//    update(GSBViewManager::REPAINT);
//  }
//}


void GSBwxFlythroughView::widgetCallbackFunction(wxObject* widget, wxCommandEvent& )
{
  if (widget == myApplyButton) {
    update(GSBViewManager::REPAINT);
  } else
  
  if (widget == myCloseButton) {
    myPrefs->Show(false);
  } else
  
  if (widget == myMotionQualityChoice) {
   myMotionQuality = 
     (GLRenderer::RenderingQuality) (((wxManagedChoice*) widget)->GetSelection() + 1);
  }
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnChar(wxObject* widget, wxKeyEvent& )
{
  if (widget == myCanvas) {
//    if ((event.keyCode == 'p') || (event.keyCode == 'P')) {
//      pruneNode();
//    } else
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnClose(wxObject* widget)
{
  if (widget == myFrame) {
    deletionPending = myFrame;

    // detach from view manager
    myViewManager->detach(myViewID);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnEvent(wxObject* widget, wxMouseEvent& event)
{
  if (widget == myCanvas) {
    float x, y;
    event.Position(&x, &y);

    if (x > -1 && y > -1 && event.Dragging() && event.RightIsDown()) {
      moveCamera(x - myXPos, y - myYPos);
      myRenderer->setRenderingQuality(myMotionQuality);
      myCanvas->OnPaint();
    } else
      
    if (x > -1 && y > -1 && event.Dragging() && event.MiddleIsDown()) {
      myRenderer->setRenderingQuality(myMotionQuality);
      rotateAroundLookp(x - myXPos, y - myYPos);
      myCanvas->OnPaint();
    } else 
      
    if (x > -1 && y > -1 && event.LeftIsDown()) {
//      pickObject(x,y);
    } else
    
    if (event.LeftUp() || event.MiddleUp() || event.RightUp()) {
      myRenderer->setRenderingQuality(myRenderingQuality);
      myCanvas->OnPaint();
    }
    myXPos = x;
    myYPos = y; 
  }
  return wxDialogDirector::NO_DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnSize(wxObject* widget, int width, int height)
{
  if (widget == myFrame) {
    if ((width == -1) && (height == -1)) 
      myFrame->GetSize(&width, &height);
    myCanvas->SetSize(0, 0, width, height);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  } else if (widget == myCanvas) {
    myRenderer->getCamera()->getViewing()->setResolution(width, height);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnMenuCommand(wxObject* widget, int id)
{
  if (widget == myFrame) {
    switch (id) {
      case GSB_FLYTHROUGH_CLOSE :
        // detach from view manager
        myViewManager->detach(myViewID);
        delete this;
      case GSB_FLYTHROUGH_PRUNE :
//        pruneNode();
        break;
      case GSB_FLYTHROUGH_PREFS :
        myPrefs->Show(true);
        break;
    }
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxFlythroughView::widgetOnPaint(wxObject* widget)
{
  if (widget == myCanvas) {
cout << "ONPAINT CALLED" << endl << flush;
    myRenderer->execute(myWorld);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION; 
}


void GSBwxFlythroughView::adoptWorld(World3D* world)
{
  //
  // Collect all cameras in the world.
  //  
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(world);
  Camera3D* camera = NULL;

  //
  // Look for first camera in world, that is switched on.
  //
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    if (camCollector.getObject()->isOn()) {
      camera = camCollector.createTransformedObject(); 
      break;
    }

  if (camera == NULL) {
    Report::error("scene contains no active camera");
    exit(1);
  }

  myRenderer->adoptCamera(camera);

  //
  // Collect all directed light sources in the world.
  //  
  Collector3DFor<DirectedLight> directedCollector;
  directedCollector.execute(world);
  List<DirectedLight*>* directed = new List<DirectedLight*>;

  for (directedCollector.first(); !directedCollector.isDone(); directedCollector.next())
    if (directedCollector.getObject()->isOn())
      directed->append(directedCollector.createTransformedObject());

  //
  // Collect all ambient light sources in the world.
  //  
  Collector3DFor<AmbientLight> ambientCollector;
  ambientCollector.execute(world);
  List<AmbientLight*>* ambient = new List<AmbientLight*>;

  for (ambientCollector.first(); !ambientCollector.isDone(); ambientCollector.next())
    if (ambientCollector.getObject()->isOn())
      ambient->append(ambientCollector.createTransformedObject());


  if (directed->count() + ambient->count() <= 0) {
    Report::error("scene contains no active light source");
    exit(1);
  }

  myRenderer->adoptDirectedLightSources(directed);
  myRenderer->adoptAmbientLightSources(ambient);
  int w, h;
  myCanvas->GetSize(&w,&h);
  myRenderer->getCamera()->getViewing()->setResolution(w,h);
}


void GSBwxFlythroughView::pickObject(int x, int y)
{
  Picker3D picker;
  picker.setCamera(myRenderer->getCamera()); 
  picker.setPickOrigin(x, myRenderer->getCamera()->getViewing()->getResolutionY()-y-1);
  picker.execute(myWorld);
  
  if (picker.getPath() != NULL) {
    myViewManager->picking(picker.getPath()->getObject());
  }
}
