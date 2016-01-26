/*
 * $RCSfile: wxSelectCommand.C,v $
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
 *  $Id: wxSelectCommand.C,v 1.1 1998/05/15 09:19:13 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Object3D.h"
#include "booga/object/Disc3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Viewing3D.h"
#include "booga/wxwrapper/wxSelectCommand.h"

//_____________________________________________________________________ wxSelectCommand

implementRTTI(wxSelectCommand, wxViewCommand);

wxSelectCommand::wxSelectCommand (wxView3D *v) : wxViewCommand (v)
{
}

void wxSelectCommand::execute()
{
  // we store the current mouse position
  float x, y;
  getView()->getMouseEvent().Position(&x,&y);
  Picker3D myPicker;
  
  if (getView()->getMouseEvent().ButtonDown() && getView()->getMouseEvent().ShiftDown()) {
    // user wants to add or remove an object to or from the selection
    
    // setup picker:
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    if (myPicker.getPath() != NULL) {
      // select second object in path:
      myPicker.getPath()->first(); myPicker.getPath()->next();
      getView()->getViewManager()->addToSelection(myPicker.getPath()->getObject());
    }
  } else if (getView()->getMouseEvent().ButtonDown()) { 
    myPicker.setCamera(getView()->getRenderer()->getCamera()); 
    myPicker.setPickOrigin((int)x, (int)(getView()->getRenderer()->getCamera()->getViewing()->getResolutionY()-(int)y-1));
    myPicker.execute(getView()->getViewManager()->getWorld());

    if (myPicker.getPath() != NULL) {
      // select second object in path
      myPicker.getPath()->first(); myPicker.getPath()->next();
      if (!getView()->getViewManager()->isSelected(myPicker.getPath()->getObject())) 
        getView()->getViewManager()->setSelection(myPicker.getPath()->getObject());
    } else {
      getView()->getViewManager()->clearSelection();
    }    
  }
}


