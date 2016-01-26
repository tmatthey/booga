/*
 * $RCSfile: InspectSelectionCommand.C,v $
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
 *  $Id: InspectSelectionCommand.C,v 1.3 1997/02/20 09:42:03 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Viewing3D.h"
#include "InspectSelectionCommand.h"
#include "InspectCommand.h"

//_____________________________________________________________________ InspectSelectionCommand

implementRTTI(InspectSelectionCommand, wxViewCommand);


InspectSelectionCommand::InspectSelectionCommand(wxView3D *v) : wxViewCommand(v)
{}

void InspectSelectionCommand::execute()
{
  Aggregate3D *selection = getView()->getViewManager()->getSelection();
  
  if (!selection)
    return;
  
  if (selection->countSubobject() > 1) {
    Report::warning("[InspectSelectionCommand::execute]: more than one object in selection. COmmand not executed");
    return;
  }
  
  Object3D *obj = selection->getSubobject(0); // get only object in selection
      
  Camera3D *myCam = new Camera3D();

  myCam->getViewing()->setView (obj->getBounds().getMin(), obj->getBounds().getMax());
//  myCam->getViewing()->setLookat (bbmid);
  interpolateCamera (myCam);
  // getView()->adoptMotionCommand(new InspectCommand(getView()));
  getView()->adoptMouseCommand(new InspectCommand(getView()));

}

void InspectSelectionCommand::interpolateCamera (Camera3D *newc)
{
  Vector3D oldeye = getView()->getRenderer()->getCamera()->getViewing()->getEye();
  Vector3D oldlookat = getView()->getRenderer()->getCamera()->getViewing()->getLookat();
  
  Vector3D neweye = newc->getViewing()->getEye();
  Vector3D newlookat = newc->getViewing()->getLookat();
  ostrstream os;
  os << "[InspectSelectionCommand::interpolateCamera]:oldeye= " << oldeye;
  os << " oldlookp = " << oldlookat << " neweye= " << neweye << " newlookat = " << newlookat;
  Report::warning (os);
  
  Vector3D deye = neweye - oldeye;
  Vector3D dlookat = newlookat - oldlookat;

  Real intervall = 100.0;
  Real frames = 20;

  for (Real i=1; i<=intervall; i+=intervall /(Real)frames) {
    Real value = log (i) / log (intervall);
    Vector3D ceye = oldeye + value*deye;
    Vector3D clookat = oldlookat + value*dlookat;
    getView()->getRenderer()->getCamera()->getViewing()->setEye(ceye); 
    getView()->getRenderer()->getCamera()->getViewing()->setLookat(clookat); 
//    getView()->getRenderer()->getCamera()->getViewing()->setFov(cfov); 
    getView()->useMotionQuality();

    getView()->OnPaint();
  }
  getView()->getRenderer()->getCamera()->getViewing()->setEye(neweye); 
  getView()->getRenderer()->getCamera()->getViewing()->setLookat(newlookat); 
//  getView()->getRenderer()->getCamera()->getViewing()->setFov(newfov);  
}
