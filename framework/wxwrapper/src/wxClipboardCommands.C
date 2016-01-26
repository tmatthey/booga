/*
 * $RCSfile: wxClipboardCommands.C,v $
 *
 * Copyright (C) 1996, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: wxClipboardCommands.C,v 1.4 1998/05/22 07:59:47 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/List3D.h"
#include "booga/object/Shared3D.h"

#include "booga/wxwrapper/wxClipboardCommands.h"
#include "wx.h"
//#include "wb_cmdlg.h"

//_____________________________________________________________________ wxClipboardCommands

implementRTTI(wxCutCommand, wxViewCommand);

wxCutCommand::wxCutCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxCutCommand::execute()
{
  std::stringstream os;
  os << "[wxCutCommand::execute]:";
  Report::warning(os);
  
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return; // no selection!

  // remove selection from world:
  for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
    Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													

    if (getView()->getViewManager()->getWorld()->getObjects()->orphanObject(obj)) {
      os << "[wxCutCommand::execute]:" << typeid(obj).name() << " removed!";
      Path3D p;
      p.append(getView()->getViewManager()->getWorld()->getObjects());
      getView()->getViewManager()->getWorld()->getObjects()->recomputeBounds(p);
    }  
  }
  getView()->getViewManager()->clearSelection();
}

implementRTTI(wxCopyCommand, wxViewCommand);

wxCopyCommand::wxCopyCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxCopyCommand::execute()
{
  std::stringstream os;
  os << "[wxCopyCommand::execute]:";
  Report::warning(os);
  
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return; // no selection!
    
  getView()->getViewManager()->adoptClipboard((Aggregate3D *)selection->copy());  // 
//  getView()->getViewManager()->clearSelection();
  
//  Transform3D myTrans = getView()->getViewManager()->getClipboard()->getTransform();
//  TransMatrix3D t;		
//  getView()->getViewManager()->getClipboard()->addTransform (t.makeTranslate (Vector3D(.5,.5,0)));

//  os << "[wxCopyCommand::execute]:" << typeid(obj).name() << " copied!";
}

implementRTTI(wxPasteCommand, wxViewCommand);

wxPasteCommand::wxPasteCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxPasteCommand::execute()
{
  std::stringstream os;
  os << "[wxPasteCommand::execute]:";
  Report::warning(os);
  
  Aggregate3D *selection = getView()->getViewManager()->getClipboard();
  
  if (!selection)
    return; // no selection!
  for (long i=0; i<getView()->getViewManager()->getClipboard()->countSubobject(); i++) {
    Object3D *obj = getView()->getViewManager()->getClipboard()->getSubobject(i);													

    Object3D *copy = obj->copy();
    // we should paste the new object just in front of the current camera
    
    // we translate the object a little bit...
    BoundingBox bb = obj->getBounds();
    Real dx = (bb.getMax() - bb.getMin())[0]; 
    Real dy = (bb.getMax() - bb.getMin())[1]; 
    
    Transform3D myTrans = getView()->getViewManager()->getClipboard()->getTransform();
    TransMatrix3D t;		
    copy->addTransform (t.makeTranslate (Vector3D(dx,dy,0)));

    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(copy);
    Path3D p;
    p.append(getView()->getViewManager()->getWorld()->getObjects());
    p.append(copy);
    getView()->getViewManager()->getWorld()->getObjects()->recomputeBounds(p);
    getView()->getViewManager()->addToSelection(copy);
  }
//  getView()->getViewManager()->notify (wxViewManager::WORLD_CHANGED, NULL);
}

implementRTTI(wxGroupCommand, wxViewCommand);

wxGroupCommand::wxGroupCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxGroupCommand::execute()
{
  std::stringstream os;
  os << "[wxGroupCommand::execute]:";
  Report::warning(os);
  
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return; // no selection!
  
  if (selection->countSubobject() <= 1) {
    Report::warning("[wxGroupCommand::execute]: Cannot group 1 object only...");
    return;
  }
  
  List3D *theList = new List3D;
  
//  char *name = wxGetTextFromUser ("Name of new Shared3D:", "Input Name", "newShared");

  for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {

    Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													
 
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(obj);
    
    theList->adoptObject(obj); 
  }
  theList->computeBounds();
  
//  if (strlen(name)) {
//    Shared3D *theShared = new Shared3D (theList, Name(name));
//    theShared->setTypeName(Name(name));
//    theShared->computeBounds();
//    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(theShared); 
//  } else 
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(theList); 
  getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
  getView()->getViewManager()->setSelection(theList);
  getView()->getViewManager()->notify (wxViewManager::WORLD_CHANGED, NULL);
}

implementRTTI(wxUnGroupCommand, wxViewCommand);

wxUnGroupCommand::wxUnGroupCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxUnGroupCommand::execute()
{
  std::stringstream os;
  os << "[wxUnGroupCommand::execute]:";
  Report::warning(os);
  
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return; // no selection!
  
  if (selection->countSubobject() > 1) {
    Report::warning("[wxGroupCommand::execute]: Cannot ungroup more than one object...");
    return;
  }
  
  Aggregate3D *theList = dynamic_cast(Aggregate3D, getView()->getViewManager()->getSelection()->getSubobject(0));

  if (theList) {
    getView()->getViewManager()->clearSelection();
    
    getView()->getViewManager()->getWorld()->getObjects()->orphanObject(theList);
          
    for (long i=theList->countSubobject()-1; i>=0; i--) {
      Object3D *obj = theList->getSubobject(i);
      theList->orphanObject(theList->getSubobject(i));													
 
      getView()->getViewManager()->getWorld()->getObjects()->adoptObject(obj);
      obj->addTransform(theList->getTransform());
      obj->computeBounds();
      getView()->getViewManager()->addToSelection(obj);
    }
    delete theList;
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
  }
//  getView()->getViewManager()->notify (wxViewManager::WORLD_CHANGED, NULL);
}

implementRTTI(wxCreateSharedCommand, wxViewCommand);

wxCreateSharedCommand::wxCreateSharedCommand (wxView3D *v) : wxViewCommand(v)
{}

void wxCreateSharedCommand::execute()
{
  std::stringstream os;
  os << "[wxCreateSharedCommand::execute]:";
  Report::warning(os);
  
  Shared3D *theShared = NULL; // we store the new shared here
  
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return; // no selection!
  
  if (selection->countSubobject() == 0) {
    // nothing selected!
    Report::warning("[wxCreateSharedCommand::execute]: Nothing selected!");
    return;
  }
  
  // we get the new name of the shared
  char *name="";
  while (!strlen(name))
    name = wxGetTextFromUser ("Name of new Shared3D:", "Input Name", "newShared");
  
  if (selection->countSubobject() == 1) {
    // only one object in selection
    Report::warning("[wxCreateSharedCommand::execute]: Creating shared form one object!");
    Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(0);	
    theShared = new Shared3D (obj, Name(name));
    theShared->setTypeName(Name(name));
  }
  
  if (selection->countSubobject() > 1) {
    // we have more than one objects in selection, so create a list out of'em
    List3D *theList = new List3D;
  
    for (long i=0; i<getView()->getViewManager()->getSelection()->countSubobject(); i++) {
      Object3D *obj = getView()->getViewManager()->getSelection()->getSubobject(i);													
 
      getView()->getViewManager()->getWorld()->getObjects()->orphanObject(obj);
    
      theList->adoptObject(obj); 
    }
    theList->computeBounds();
  
    theShared = new Shared3D (theList, Name(name));
    theShared->setTypeName(Name(name));
  } 
  
  if(theShared) {
    // finalize if successful:
    theShared->computeBounds();
    getView()->getViewManager()->getWorld()->getObjects()->adoptObject(theShared);    
    getView()->getViewManager()->getWorld()->getObjects()->computeBounds();
    getView()->getViewManager()->setSelection(theShared);
    getView()->getViewManager()->notify (wxViewManager::WORLD_CHANGED, NULL);
    Report::warning("[wxCreateSharedCommand::execute] successful!");
  }
}
