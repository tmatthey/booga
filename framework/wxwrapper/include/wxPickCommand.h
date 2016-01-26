/*
 * $RCSfile: wxPickCommand.h,v $
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
 *  $Id: wxPickCommand.h,v 1.1 1996/09/27 11:48:43 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxPickCommand_H
#define _wxPickCommand_H

#include "booga/component/Picker3D.h"
#include "booga/wxwrapper/wxViewCommand.h"

//_____________________________________________________________________ wxPickCommand

class wxPickCommand : public wxViewCommand {
  //  declareRTTI(wxPickCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxPickCommand(wxView3D *v);                         // Use default version.
private:
//  wxPickCommand(const wxPickCommand&);             // No copies.

public:
  // virtual ~wxPickCommand();                // Use default version.

private:
  wxPickCommand& operator=(const wxPickCommand&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxPickCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void moveObjectHorizontal();
  void moveObjectVertical();
  void rotateObject();

  void enableGravity();
  void disableGravity();
  bool isGravityEnabled();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Object3D *myOldObject;
  bool myMovingFlag;
  bool myGravityFlag;
  Vector3D myOldHitPoint;
  Picker3D *myPicker;
  int myOldx, myOldy;
  
};

//______________________________________________________________________ INLINES

#endif // _wxPickCommand_H

