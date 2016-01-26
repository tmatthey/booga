/*
 * GSBwxConetreeView.C 
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
 *  $Id: GSBwxConetreeView.C,v 1.9 1997/04/17 09:39:02 habegger Exp $
 * -----------------------------------------------------------------------------
 */


//#include "GSBViewManager.h"

#include "GSBwxConetreeView.h"
#include "GSBConetreeNode.h"
#include "GSBConetreeNode3D.h"
#include "GSBNodeTools.h"
#include "GSBGLRenderer.h"
#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Picker3D.h"
#include "booga/component/Collector3DFor.h"

// icon for canvas frame:
#include "icontree2.xpm"

#define GSB_CONETREE_PREFS        5
#define GSB_CONETREE_CLOSE        99

//_____________________________________________________________________ GSBwxConetreeView

implementRTTI(GSBwxConetreeView, GSBView);


GSBwxConetreeView::GSBwxConetreeView(World3D* world, RCString& IDStr)
: GSBView(world, IDStr),
  myTree(NULL),
  myPickedObject(NULL),
  myPivotObject(NULL),
  myXPos(0), myYPos(0),
  myTreeRenderingQuality(GLRenderer::SOLID_GOURAUD),
  myTreeMotionQuality(GLRenderer::BOUNDING_BOX),
  myLayoutBorder(20),
  myLayoutDistanceToParents(100),
  myLayoutVertical(false),
  deletionPending(NULL)
{
  myRenderer =  new GSBGLRenderer;
  myRenderer->generateWorld(false);
  myRenderer->setFrameRate(30);
  
  myLayouter = new GSBConetreeLayouter;
}


GSBwxConetreeView::~GSBwxConetreeView()
{
  if (!(myFrame == deletionPending)) {
    delete myFrame;
  }
  
  // remove node data
  GSBNodeTools nodeDeinstaller(myViewID);
  nodeDeinstaller.setActionType(GSBNodeTools::REMOVE_NODES);
  nodeDeinstaller.execute(myWorld);
  
  // remove tree data
  delete myLayouter;
  delete myRenderer;
  delete myTree;
}


void GSBwxConetreeView::init()
{
  GSBNodeTools nodeInstaller(myViewID);
  nodeInstaller.setActionType(GSBNodeTools::INSTALL_NODES);
  GSBConetreeNode* proto = new GSBConetreeNode(myViewID);
  proto->setHeight(30);
  nodeInstaller.adoptNodePrototype(proto);
  nodeInstaller.execute(myWorld);
  
  createGUI();
  update(GSBViewManager::REPAINT);
}


void GSBwxConetreeView::createGUI()
{
  // create frame widget:
  myFrame = new wxManagedFrame(this, 0, "Conetree View", -1, -1, 500, 500);
  RCString name = "Conetree: " + 
    RCString(wxFileNameFromPath((char*) myViewManager->getFilename().chars()));
  myFrame->SetIcon(new wxIcon(icontree2_xpm));
  myFrame->SetTitle((char*) name.chars());
  myFrame->Show(True);
  
  // create menu:
  wxMenu* myViewMenu = new wxMenu;

  myViewMenu->Append(GSB_CONETREE_PREFS, "&Preferences\tCtrl+P",
    "Set preferences");
  myViewMenu->Append(GSB_CONETREE_CLOSE, "&Close\tCtrl+C", 
    "Close this window");

  // create menubar:  
  wxMenuBar* myMenuBar = new wxMenuBar;
  myMenuBar->Append(myViewMenu,"&View");
  myFrame->SetMenuBar(myMenuBar);
  
  // create canvas:
  myCanvas = new wxManagedCanvas(this, myFrame, -1, -1, 500, 500);
}


void GSBwxConetreeView::layout()
{
  // adjust settings for layouter:
  myLayouter->setViewID(myViewID);
  myLayouter->setDistanceToParents(myLayoutDistanceToParents);
  myLayouter->setBorder(myLayoutBorder);
  
  adoptTree(myLayouter->execute(myWorld));
}


void GSBwxConetreeView::adoptTree(World3D* newWorld)
{
  if (newWorld == NULL) {
    Report::error("[GSBwxConetreeView::adoptTree] NULL world passed!");
  }
  
  if (newWorld == myTree)
    return;       // nothing to be done
    
//  Camera3D* foundCam = (Camera3D*) myRenderer->getCamera();
  delete myTree;
  myTree = newWorld;
//  if (foundCam) {
//    // use old camera
//    myRenderer->adoptCamera(foundCam);
//  } else {
    updateViewing();
//  }
}


void GSBwxConetreeView::rotateAroundLookp(Real theta, Real phi)
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


void GSBwxConetreeView::moveCamera(Real dx, Real dy)
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


void GSBwxConetreeView::updateViewing()
{
  if (myTree == NULL) {
    return;
  }
  // delete all existing cameras
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(myTree);
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    delete camCollector.getObject();
		  
  // delete all existing light sources
  Collector3DFor<LightSource> lightCollector;
  lightCollector.execute(myTree);
  for (lightCollector.first(); !lightCollector.isDone(); lightCollector.next())
    delete lightCollector.getObject();
		  
  // add new camera
  Camera3D* cam = new Camera3D;
  cam->setBackground(Color(.5,.5,.5));
  Vector3D ll(myTree->getObjects()->getBounds().getMin());
  Vector3D ur(myTree->getObjects()->getBounds().getMax());
		
  cam->getViewing()->setEye(ur-ll-Vector3D(-20,0,0));

  int w, h;
  myCanvas->GetSize(&w,&h);
  cam->getViewing()->setResolution(w, h);
  cam->getViewing()->setView(ll, ur);
  cam->getViewing()->setLookat((ur + ll)/2);
		
  myRenderer->adoptCamera(cam);
		
  // set up lighting (four light sources)
  float scale = sqrt(((ur - ll).x() * (ur - ll).x())/4 + 
                ((ur - ll).y() * (ur - ll).y())/4) * 2;
  PointLight *light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(1, 1, 0));
  light->setColor(Color(1,1,1));
  myTree->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(-1, 1, 0));
  light->setColor(Color(1,1,1));
  myTree->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(-1, -1, 0));
  light->setColor(Color(1,1,1));
  myTree->getObjects()->adoptObject(light);
    
  light = new PointLight(.6);
  light->setPosition((ll + ur)/2 + scale * Vector3D(1, -1, 0));
  light->setColor(Color(1,1,1));
  myTree->getObjects()->adoptObject(light);		
		
  myTree->getObjects()->computeBounds();
}


void GSBwxConetreeView::update(GSBViewManager::NotifyEvent event)
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
//      layout();
      myPickedObject = myViewManager->getPickedObject();
      myCanvas->OnPaint();
      break;
    case GSBViewManager::PRUNING :
      layout();
      myCanvas->OnPaint();
//		  myCanvas->markPickedObject(obj);
//		  myCanvas->OnPaint();
//		  myCanvas->OnSize();
	break;
    case GSBViewManager::SUBJECT_KILLED : // view manager is being destroyed
      delete this;
    default :
	break;
  }
}

void GSBwxConetreeView::widgetCallbackFunction(wxObject* , wxCommandEvent& )
{
/*  if (widget == myApplyButton) {
    update(GSBViewManager::REPAINT);
    myPickingCanvas->SetSize(0,0, myPickingCanvasSize, myPickingCanvasSize, 0);
    showPicking(myMarkedObject);
    myRenderer->getCamera()->getViewing()->setResolution(
      myPickingCanvasSize, myPickingCanvasSize);
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
*/
}


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnChar(wxObject* , wxKeyEvent& )
{
/*
  if (widget == myCanvas) {
    // <SPACE> pressed ==> show SHARED WORLD
    if (event.keyCode == WXK_SPACE) {
      myDisplayMode = (myDisplayMode == NORMAL) ? SHARED : NORMAL;
      update(GSBViewManager::REPAINT);
    } else
    
    // <p> or <P> pressed ==> PRUNING
    if ((event.keyCode == 'p') || (event.keyCode == 'P')) {
      pruneNode();
    } else
    
    // <f> or <F> pressed ==> FIT TO SCREEN
    if (event.keyCode == 'F') {
cout << "f pressed" << endl;    
      bestFitToScreen();  
    } else
    
    if (event.keyCode == 'O') {
cout << "F pressed" << endl;
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
*/
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnClose(wxObject* widget)
{
  if (widget == myFrame) {
    deletionPending = myFrame;
    // detach from view manager
    myViewManager->detach(myViewID);

    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnEvent(wxObject* widget, wxMouseEvent& event)
{
  if (widget == myCanvas) {
    float x, y;
    event.Position(&x, &y);

    if (x > -1 && y > -1 && event.Dragging() && event.RightIsDown()) {
      moveCamera(x - myXPos, y - myYPos);
      myRenderer->setRenderingQuality(myTreeMotionQuality);
      myCanvas->OnPaint();
    } else if (x > -1 && y > -1 && event.Dragging() && event.MiddleIsDown()) {
      myRenderer->setRenderingQuality(myTreeMotionQuality);
      rotateAroundLookp(x - myXPos, y - myYPos);
      myCanvas->OnPaint();
    } else if (x > -1 && y > -1 && event.Dragging() && event.LeftIsDown()) {
      if (myPivotObject) {
        rotateBranch(y - myYPos);
        myRenderer->setRenderingQuality(myTreeMotionQuality);
        myCanvas->OnPaint();
      }		  
    } else if (x > -1 && y > -1 && event.LeftIsDown()) {
      pickObject((int) x, (int) y);
    } else if (event.LeftUp() || event.MiddleUp() || event.RightUp()) {
      cout << "ONPAINT" << endl;
      myPivotObject = NULL;
      myRenderer->setRenderingQuality(myTreeRenderingQuality);
      myCanvas->OnPaint();
      cout << "ONPAINT FINISHED" << endl;
    }
    myXPos = x;
    myYPos = y;
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnSize(wxObject* widget, int width, int height)
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


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnMenuCommand(wxObject* widget, int id)
{
  if (widget == myFrame) {
    switch (id) {
      case GSB_CONETREE_CLOSE :
       // detach from view manager
        myViewManager->detach(myViewID);
        delete this;
    }
  }
  return wxDialogDirector::DEFAULT_ACTION;
}


wxDialogDirector::ActionRequest GSBwxConetreeView::widgetOnPaint(wxObject* widget)
{
  if (widget == myCanvas) {
    myRenderer->execute(myTree);
//    GLRenderer::RenderingQuality oldQuality = myRenderer->getRenderingQuality();
//    myRenderer->setRenderingQuality(GLRenderer::BOUNDING_BOX);
//    Transform3D lastTransform = picker.getPath()->getLastTransform();
//    static float m[16];
//    glPushMatrix();
//    convert(picker.getPath()->getLastTransform().getTransMatrix(), m);
//    glMultMatrixf(m);
//    glColor3f (1,1,1);
//    glDrawBuffer(GL_FRONT);
//    myRenderer->visit(myPickedObject); 
//    glPopMatrix();
//    glFlush();
//    myRenderer->setRenderingQuality(oldQuality);
    return wxDialogDirector::NO_DEFAULT_ACTION;
  }
  return wxDialogDirector::DEFAULT_ACTION; 
}


void GSBwxConetreeView::pickObject(int x, int y)
{
  Picker3D picker;	
  picker.setCamera(myRenderer->getCamera()); 
  picker.setPickOrigin(x, myRenderer->getCamera()->getViewing()->getResolutionY()-y-1);
  myTree->getObjects()->computeBounds();
  picker.execute(myTree);
  
  if (picker.getPath() != NULL) {
//    Path3D path(*picker.getPath());
    GSBConetreeNode3D* aNode;
    
    for (picker.getPath()->last(); !picker.getPath()->isDone(); picker.getPath()->prev()) {
//cout << typeid(picker.getPath()->getObject()).name() << "<-";
      aNode = dynamic_cast(GSBConetreeNode3D, picker.getPath()->getObject());
      if (aNode && aNode->getRepresentWho()) {
// next step: get pivot object:
        picker.getPath()->prev();
        picker.getPath()->prev();
        if (aNode->getRepresentWho()->countSubobject() > 0)
          picker.getPath()->prev();
        myPivotObject = picker.getPath()->getObject();
//cout << typeid(myPivotObject).name() << endl << flush;
//        delete myPivotObjectPath;
//        myPivotObjectPath = new Path3D(*picker.getPath());
        
	// Something got picked. Make sure the view gets updated.
	// ==> notify view manager
	myViewManager->picking(aNode->getRepresentWho());
    	break;
      }
    }
  }
}


void GSBwxConetreeView::rotateBranch(Real phi)
{
cout << "rotateBranch" << endl;
cout << typeid(myPivotObject).name() << endl << flush;
  if (myPickedObject == NULL)
    return;

cout << "Doing transformation" << endl;
  TransMatrix3D tm = TransMatrix3D::makeRotateY(-phi/180*M_PI);

  myPivotObject->setTransform(tm * myPivotObject->getTransform().getTransMatrix());
  
//  World3D* dummyworld = new World3D;
//  dummyworld->adoptObject(myPivotObject);
  
//  GSBNodeCollector nodeCollector;
//  PrintWorld3D printer;
//  printer.apply(dummyworld);
  
//  nodeCollector.apply(dummyworld);
//  for(nodeCollector.first(); !nodeCollector.isDone(); nodeCollector.next()) {
//    TransMatrix3D tm = nodeCollector.getObject()->getTransform().getTransMatrix();
//    nodeCollector.getObject()->setTransform(
//        tm * TransMatrix3D::makeRotateY(phi/180*M_PI));
//  }
//  myPivotObject->computeBounds();
//  dummyworld->orphanObject(myPivotObject);
//  delete dummyworld;
//  for(myPivotObjectPath->first();!myPivotObjectPath->isDone();myPivotObjectPath->next()) {
//    cout << typeid(myPivotObjectPath->getObject()).name() << "->";
//  }
//  cout << endl << flush;
//  myPivotObject->recomputeBounds(*myPivotObjectPath);
//  myTree->getObjects()->computeBounds();
}
