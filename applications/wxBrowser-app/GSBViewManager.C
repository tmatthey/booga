/*
 * GSBViewManager.C 
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
 *  $Id: GSBViewManager.C,v 1.7 1997/04/17 09:39:00 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBViewManager.h"
#include "GSBNodeManager.h"
#include "GSBView.h"
#include "GSBNodeTools.h"


//_____________________________________________________________________ GSBViewManager


GSBViewManager::GSBViewManager(World3D* world) 
: myViewList(0),
  myViewCounter(0),
  myWorld(world),
  myIconizedFlag(false),
  myNotifyFlag(false), 
  myFilename(""),
  myPickedObject(NULL)
{}


GSBViewManager::~GSBViewManager()
{
  ListItr<GSBView*> observerList(myViewList);
  for (observerList.first(); !observerList.isDone(); observerList.next()) {
    GSBView* aView = observerList.curItem();
    cout << "[GSBViewManager] Vernichte View " << typeid(aView).name() << endl << flush;
  }
  notify(SUBJECT_KILLED);
}


long GSBViewManager::attach(GSBView* theView)
{
  if (theView == NULL) 
    return 0;

  if (myNotifyFlag)
    Report::error("[GSBViewManager::attach] No attaching possible now!");

  myViewList.append(theView);
  
  // init view:
  theView->setViewID(++myViewCounter);
  theView->setViewManager(this);
  return theView->getViewID();
}


void GSBViewManager::detach(long viewID)
{
  if (myNotifyFlag)
    Report::error("[GSBViewManager::detach] No detaching possible now!");
    
  ListItr<GSBView*> observerList(myViewList);
  
  // looking for desired view (algo. can be improved...)
  for (long index = 0;!observerList.isDone(); observerList.next(), index++) {
    if (observerList.curItem()->getViewID() == viewID) {
      myViewList.remove(index);
      break;
    }
  }
}


void GSBViewManager::notify(NotifyEvent event)
{
  bool oldNotifyState = myNotifyFlag;
  
  myNotifyFlag = true;
  ListItr<GSBView*> observerList(myViewList);
  for (;!observerList.isDone(); observerList.next()) {
    observerList.curItem()->update(event);
  }
  
  myNotifyFlag = oldNotifyState;
}


GSBView* GSBViewManager::getView(long viewID)
{
  ListItr<GSBView*> observerList(myViewList);
  for (;!observerList.isDone(); observerList.next()) {
    if (observerList.curItem()->getViewID() == viewID) 
      return observerList.curItem();
  }
  return (GSBView *) 0;
}


bool GSBViewManager::isUsedID(long viewID)
{
  return (getView(viewID) ? true : false);
}


void GSBViewManager::setFilename(RCString filename)
{
  myFilename = filename;
  notify(FILENAME);
}


void GSBViewManager::setIconized(bool iconize)
{
  if (myIconizedFlag = iconize) 
    notify(ICONIZE);
  else
    notify(UNICONIZE);
}


void GSBViewManager::picking(Object3D* obj)
{
  Report::debug(RCString("[GSBViewManager::picking] Object ") + typeid(obj).name() +  
    (myPickedObject == obj ? RCString(" deselected") : RCString(" selected")));
  if (myPickedObject == obj) {
    myPickedObject = (Object3D*) NULL; // deselection
    GSBNodeTools::getNodeManager(obj)->setMarked(false);
  }
  else {
    if (myPickedObject != NULL) {
      GSBNodeTools::getNodeManager(myPickedObject)->setMarked(false);
    }
    myPickedObject = obj;
    GSBNodeTools::getNodeManager(obj)->setMarked(true);
  }
  notify(PICKING);
}


void GSBViewManager::pruning(Object3D* obj)
{

  GSBNodeManager* aManager = dynamic_cast(GSBNodeManager, GSBNodeTools::getNodeManager(obj));
  if (aManager != NULL) {
    aManager->setPruned(aManager->isPruned() ? false : true);
    Report::debug(RCString("[GSBViewManager::pruning] Object ") + typeid(obj).name() +  
    (aManager->isPruned() ? RCString(" pruned") : RCString(" unpruned")));
  }
  notify(PRUNING);
}


bool GSBViewManager::isAttached(const RCString& id) const
{
  ListItr<GSBView*> observerList(myViewList);
  for (;!observerList.isDone(); observerList.next()) {
    if (observerList.curItem()->getViewIDStr() == id) 
      return true;
  }
  return false;
}
