/*
 * $RCSfile: EditSelection.C,v $
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: EditSelection.C,v 1.3 1997/02/20 09:41:58 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Aggregate3D.h"
#include "booga/object/PointLight.h"
#include "booga/base/Value.h"
#include "EditSelection.h"

//_____________________________________________________________________ EditSelection

implementRTTI(EditSelection, wxBOOGAView);

EditSelection::EditSelection() : wxDialogBox (NULL, "Edit Selection")
{
  createGUI();
  updateGUI();
}

EditSelection::~EditSelection()
{
}  

void EditSelection::update(wxViewManager::NotifyEvent event, Object3D*)
{
  switch (event) {
    case wxViewManager::SELECTION_CHANGED: {
      updateGUI();
    }
    default:
      break;
  }
}

void EditSelection::createGUI()
{
  myText   = new wxManagedText (this, this, "Object Type: ", "---");
  myApplyButton = new wxManagedButton (this, this, "Apply");
  Fit();
  Show(true);
}

void EditSelection::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
//  Report::warning("[EditSelection::widgetCallbackFunction]");
//  for (long i=0; i<myValueList.count(); i++) {
//    if (widget == myValueList.item(i)) {
  if (widget == myApplyButton) {
//    ostrstream os;
//    os << "[EditSelection::widgetCallbackFunction]: apply ";
//    Report::warning(os);
    List<Value*>* vlist = new List<Value*>;
    for (long i=0; i<myValueList.count(); i++) 
      vlist->append (new Value (myValueList.item(i)->GetValue()));

    Object3D *obj = getViewManager()->getSelection()->getSubobject(0);
    RCString err("EditSelection::apply");
    Makeable *copy = obj->make(err, vlist);
    Object3D *new_obj = dynamic_cast (Object3D,copy);
    if (new_obj) {
      // remove old object...
      getViewManager()->getWorld()->getObjects()->orphanObject(obj);
      getViewManager()->getWorld()->getObjects()->adoptObject(new_obj);
      new_obj->computeBounds();
      getViewManager()->getWorld()->getObjects()->computeBounds();
      
      // if it's a PointLight, we have to report it to ViewManager
      PointLight *p = dynamic_cast (PointLight, new_obj);    
      if (p)
        getViewManager()->notify(wxViewManager::LIGHTS_CHANGED, obj);
      getViewManager()->setSelection(new_obj);
    }
  }
}

void EditSelection::updateGUI()
{
  Aggregate3D *a = getViewManager()->getSelection();
  
  if (a == NULL) {
    myText->SetValue ("******");
    for (;myValueList.count();) {
      delete myValueList.item(0);
      myValueList.remove(0);
    }
    myApplyButton->Enable(false);
    Fit();
    return;
  }

  if (a->countSubobject() > 1) {
    myText->SetValue ("List3D");
    for (;myValueList.count();) {
      delete myValueList.item(0);
      myValueList.remove(0);
    }
    myApplyButton->Enable(false);
    SetSize(400,100);
    return;
  }

  if (a->countSubobject() == 1) {
    myApplyButton->Enable(true);
    Object3D *obj = a->getSubobject(0);
//    char *name = (char *)typeid(obj).name();
    List<Value*>* vlist = obj->createParameters();
    for (;myValueList.count();) {
      delete myValueList.item(0);
      myValueList.remove(0);
    }
    SetSize(400,100);

    for (long i=0; i<vlist->count(); i++) {
      RCString s;
      vlist->item(i)->toRCString(s);
//      Report::warning(s);
      char *string = new char[s.length()+1];
      strcpy (string, (char *)s.chars());
//      ostrstream os;
//      os << "[EditSelection::updateGUI]: " << s << " length = " << s.length();
//      os << "string = " << string;
//      Report::warning(os);
      wxManagedText *t = new wxManagedText(this, this, "Value: ", string, 10, 50 + 30*i);
      myValueList.append(t);
      NewLine();
    }
    SetSize(400,70 + 30 * vlist->count());
    myText->SetValue ((char *)obj->getKeyword().chars());
    return;
  }  
}
