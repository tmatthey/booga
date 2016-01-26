/*
 * $RCSFile: $
 *
 * Copyright (C) 1995, Bernhard Bühlmann <buhlmann@iam.unibe.ch>
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
 *  $Id: TextureSelector.C,v 1.2 1997/02/20 09:42:10 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Sphere3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Torus3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Texture3DList.h"
#include "booga/component/CollectTexture3D.h"
#include "TextureSelector.h"
#include <wxstring.h>
//_____________________________________________________________________ TextureSelector

implementRTTI(TextureSelector, wxBOOGAView);

TextureSelector::TextureSelector() : wxDialogBox (NULL, "TextureSelector")
{
  createGUI();
}

void TextureSelector::createGUI()
{
  myListBox = new wxManagedListBox(this, this, "Textures:", wxSINGLE, -1, -1, 250, 100);
  NewLine();
  myAdd = new wxManagedButton (this, this, "Append Texture to Selection");
  mySet = new wxManagedButton (this, this, "Set to Selection");
  Fit();
  Show(true);
}
  
void TextureSelector::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget == myAdd) {
    if (getViewManager()->getSelection()) {
      if (myListBox->GetSelection()<0)
        return; // invalid selection
      Aggregate3D *a = getViewManager()->getSelection();
      Texture3D *t = myTextureList.item(myListBox->GetSelection());
      for (long i=0; i<a->countSubobject(); i++) 
        a->getSubobject(i)->appendTexture(t->copy());
      getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
    }
  }   
  if (widget == mySet) {
    if (getViewManager()->getSelection()) {
      if (myListBox->GetSelection()<0)
        return; // invalid selection
      Aggregate3D *a = getViewManager()->getSelection();
      Texture3D *t = myTextureList.item(myListBox->GetSelection());
      for (long i=0; i<a->countSubobject(); i++) {
        Texture3D* tmpTex = a->getSubobject(i)->orphanTexture();
        a->getSubobject(i)->appendTexture(t->copy());
        if (tmpTex)
          delete tmpTex;
      }
      getViewManager()->notify(wxViewManager::WORLD_CHANGED, NULL);
    }   
  }
}

void TextureSelector::update(wxViewManager::NotifyEvent event, Object3D* )
{
  switch (event) {
    case wxViewManager::SELECTION_CHANGED:
      if (getViewManager()->getSelection()->countSubobject()>0) {
        mySet->Enable(true); 
        myAdd->Enable(true); 
      } else {
        mySet->Enable(false);       
        myAdd->Enable(false);
      }
      break;
   
   case wxViewManager::WORLD_NEW: {
     // erase old texture list:
     
     for (;myTextureList.count();)
       myTextureList.remove (0);
     
     myListBox->Clear();

     CollectTexture3D myCollector;
     
     myCollector.execute (getViewManager()->getWorld());
     
     for (myCollector.first(); !myCollector.isDone(); myCollector.next()) {
       Texture3D *t = myCollector.getCurrent();
       myTextureList.append(t);
       RCString s = t->getName();
//       s.sprintf ("Texture %d", myTextureList.count());
       myListBox->Append((char *)s.chars(), NULL);
     }
   
     break;
   }
   default:
     break;
  } 
}
