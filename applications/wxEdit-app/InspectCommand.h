/*
 * InspectCommand.h
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
 *  $Id: InspectCommand.h,v 1.1 1996/09/27 15:07:49 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InspectCommand_H
#define _InspectCommand_H

#include "booga/base/Timer.h"
#include "booga/wxwrapper/wxViewCommand.h"

#include "wx_timer.h"


class InspectCommand; // forward declaration

class InspectTimer : public wxTimer
{
  public:
    InspectTimer (InspectCommand *c);
    void Notify(void);
  private: 
    InspectCommand* myInspectCommand;
};

//_____________________________________________________________________ InspectCommand

class InspectCommand : public wxViewCommand {
//declareRTTI(InspectCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InspectCommand(wxView3D *v);                        // Use default version.
private:
//  InspectCommand(const InspectCommand&);             // No copies.

public:
  ~InspectCommand();                // Use default version.

private:
//  InspectCommand& operator=(const InspectCommand&);  // No assignments.
  void moveCamera(Real dx, Real dy);
  void rotateAroundLookpoint (Real theat, Real phi);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class InspectCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void doMotion();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BaseClass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  float oldX, oldY;  // remember old mouse position
  float myDx, myDy;      // for animated control
  InspectTimer *myInspectTimer;
  Timer myTimer;
};

//______________________________________________________________________ INLINES

#endif // _InspectCommand_H

