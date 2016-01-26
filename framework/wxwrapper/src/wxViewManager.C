/*
 * wxViewManager.C 
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
 *  $Id: wxViewManager.C,v 1.10 1998/05/20 13:04:20 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/List3D.h"

#include "booga/wxwrapper/wxViewManager.h"
#include "booga/wxwrapper/wxBOOGAView.h"


//_____________________________________________________________________ wxViewManager


wxViewManager::wxViewManager() 
: myViewList(0), myWorld(NULL), myClipboard(NULL)
{
  mySelection = new List3D;
  myAuxWorld = new World3D;
}



wxViewManager::~wxViewManager()
{
//clearSelection();
  delete mySelection;
  delete myAuxWorld;
//  cout << "[wxViewManager] Vernichte alle Views...\n";
//  cout << "[wxViewManager] Anzahl Views: " << myViewList.count() << endl;
//  for (; myViewList.count() > 0;) {
//    wxBOOGAView* tmp = myViewList.item(0);
//    myViewList.remove(0);
//    delete tmp;
//  }
//  cout << "[wxBOOGAViewManager] Done.\n";
}


void wxViewManager::attach(wxBOOGAView* theView)
{
  if (theView == NULL) 
    return;
  myViewList.append(theView);
  theView->setViewManager(this);
  // tell the view there's a new world.
  theView->update(WORLD_NEW, NULL);
  theView->update(SELECTION_CHANGED, NULL);
}

void wxViewManager::detach(wxBOOGAView* theView)
{
  for (long i=0;i<myViewList.count(); i++) {
    if (myViewList.item(i) == theView) {
      myViewList.remove(i);
      break;
    }
  }
  
//  ListItr<wxBOOGAView*> observerList(myViewList);
//  
//  // looking for desired view (algo. can be improved...)
//  for (long index = 0;!observerList.isDone(); observerList.next(), index++) {
//    if (observerList.curItem()->getViewID() == viewID) {
//      
//      break;
//    }
//  }
}

void wxViewManager::notify(NotifyEvent event, Object3D* obj)
{
  ListItr<wxBOOGAView*> observerList(myViewList);
  for (;!observerList.isDone(); observerList.next()) {
    observerList.curItem()->update(event, obj);
  }
}

void wxViewManager::adoptWorld(World3D *world)
{
  clearSelection(); // reset selection
  
  if (myWorld)
    delete myWorld;
  myWorld = world;
  notify(WORLD_NEW, NULL);
}

//void wxViewManager::setSelection(Object3D* o)
//{
//  mySelection = o;
//  notify (SELECTION_CHANGED, o);
//}
void wxViewManager::setSelection (Object3D *o) 
{
  if (o==NULL) {
    Report::warning ("[wxViewManager::setSelection] skipping NULL object");
    return;
  }

  if (mySelection == NULL)
    mySelection = new List3D; // allocating new list
  
  if (mySelection->countSubobject() > 0) // remove all objects
    for (long i=mySelection->countSubobject()-1; i>=0; i--) 
      mySelection->orphanObject(mySelection->getSubobject(i));

  mySelection->adoptObject(o);
  notify(SELECTION_CHANGED,o);
}

void wxViewManager::addToSelection (Object3D *o) 
{

  if (o==NULL) {
    Report::warning ("[wxViewManager::addToSelection] skipping NULL object");
    return;
  }
  
  if (mySelection == NULL)
    mySelection = new List3D; // allocating new list
  
  for (long i=0; i<mySelection->countSubobject(); i++) {
    if (mySelection->getSubobject(i) == o) { // same object..
      mySelection->orphanObject(o); // we remove it from selection  
      return;
    }
  }
  
  mySelection->adoptObject(o);
  notify(SELECTION_CHANGED,o);
}

bool wxViewManager::isSelected (Object3D *o)
{
  if (mySelection == NULL)
    return false;
  
  for (long i=0; i<mySelection->countSubobject(); i++) 
    if (mySelection->getSubobject(i) == o)  // same object..
      return true;  
  
  return false;
}

void wxViewManager::removeFromSelection(Object3D *o)
{
  if (mySelection == NULL)
    return;
  
  mySelection->orphanObject(o);
  notify(SELECTION_CHANGED,o);
}

void wxViewManager::clearSelection ()
{
  if (mySelection == NULL)
    return;
  
  for (; mySelection->countSubobject();) 
    mySelection->orphanObject(mySelection->getSubobject(0));

  notify(SELECTION_CHANGED,NULL);
}


void wxViewManager::adoptClipboard(Aggregate3D* a)
{
  if(myClipboard)
    delete myClipboard;
    
  myClipboard = a;
  notify (CLIPBOARD_CHANGED, a);
}

void wxViewManager::adoptAuxObject(Object3D *o)
{
  myAuxWorld->getObjects()->adoptObject(o);
}

Object3D *wxViewManager::orphanAuxObject(Object3D *o)
{
  if (myAuxWorld->getObjects()->orphanObject(o))
    return o;
  else
    return NULL;
}
