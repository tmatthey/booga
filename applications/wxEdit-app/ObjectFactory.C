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
 *  $Id: ObjectFactory.C,v 1.2 1997/02/20 09:42:04 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Sphere3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Box3D.h"
#include "booga/object/Torus3D.h"
#include "booga/object/Cone3D.h"
#include "booga/object/Aggregate3D.h"
#include "ObjectFactory.h"

//_____________________________________________________________________ ObjectFactory

char *objectStrings[] = {
  "Sphere",
  "Box",
  "Cylinder",
  "Cone",
  "Torus"
};

const int objectCount = 5;


implementRTTI(ObjectFactory, wxBOOGAView);

ObjectFactory::ObjectFactory() : wxDialogBox (NULL, "ObjectFactory")
{
  mySize = 1.0;
  createGUI();
}

void ObjectFactory::createGUI()
{
  myChoice = new wxManagedChoice (this, this, "Object Type", -1,-1,-1,-1,
                                  objectCount, objectStrings);                                   
  myButton = new wxManagedButton (this, this, "Add");
  NewLine();
  mySizeText = new wxManagedText (this, this, "Object size:", "1.0");
  
  Fit();
  Show(true);
}
  
void ObjectFactory::widgetCallbackFunction(wxObject* widget, wxCommandEvent&)
{
  if (widget == mySizeText) {
    mySize = atof (mySizeText->GetValue());
  } else if (widget == myButton) {
    switch (myChoice->GetSelection()) {
      case 0: {
        Sphere3D *s = new Sphere3D (mySize, Vector3D(0,0,0));
        s->computeBounds();
        if (getViewManager()->getWorld()) {
          getViewManager()->getWorld()->getObjects()->adoptObject(s);
          getViewManager()->setSelection(s);
        }
        break;
      }
      case 1: {
        Box3D *b = new Box3D (Vector3D(-mySize,-mySize,-mySize), Vector3D(mySize,mySize,mySize));
        b->computeBounds();
        if (getViewManager()->getWorld()) {
          getViewManager()->getWorld()->getObjects()->adoptObject(b);
          getViewManager()->setSelection(b);
        }
        break;
      }
      case 2: {
        Cylinder3D *c = new Cylinder3D (mySize, Vector3D(0,0,-mySize), Vector3D(0,0,mySize));
        c->computeBounds();
        if (getViewManager()->getWorld()) {
          getViewManager()->getWorld()->getObjects()->adoptObject(c);
          getViewManager()->setSelection(c);
        }
        break;
      }
      case 3: {
        Cone3D *c = new Cone3D (mySize, Vector3D(0,0,-mySize), mySize/2, Vector3D(0,0,mySize));
        c->computeBounds();
        if (getViewManager()->getWorld()) {
          getViewManager()->getWorld()->getObjects()->adoptObject(c);
          getViewManager()->setSelection(c);
        }
        break;
      }
      case 4: {
        Torus3D *t = new Torus3D (mySize, mySize/5, Vector3D(0,0,0), Vector3D(0,0,1));
        t->computeBounds();
        if (getViewManager()->getWorld()) {
          getViewManager()->getWorld()->getObjects()->adoptObject(t);
          getViewManager()->setSelection(t);
        }
        break;
      }
      default:
        break;
    }
  }   
}


void ObjectFactory::update(wxViewManager::NotifyEvent , Object3D* )
{
}
