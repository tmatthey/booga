/*
 * $RCSfile: wxWalkThroughCommand.h,v $
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
 *  $Id: wxWalkThroughCommand.h,v 1.1 1996/09/27 11:48:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxWalkThroughCommand_H
#define _wxWalkThroughCommand_H

#include "booga/base/Timer.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "wx_timer.h"


class wxWalkThroughCommand; // forward declaration

class WalkThroughTimer : public wxTimer
{
  public:
    WalkThroughTimer (wxWalkThroughCommand *c);
    void Notify(void);
  private: 
    wxWalkThroughCommand* mywxWalkThroughCommand;
};

//_____________________________________________________________________ wxWalkThroughCommand

class wxWalkThroughCommand : public wxViewCommand {
//declareRTTI(wxWalkThroughCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxWalkThroughCommand(wxView3D *v);                        // Use default version.
private:
//  wxWalkThroughCommand(const wxWalkThroughCommand&);             // No copies.

public:
  // virtual ~wxWalkThroughCommand();                // Use default version.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxWalkThroughCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void doMotion();

private:
//  wxWalkThroughCommand& operator=(const wxWalkThroughCommand&);  // No assignments.
  void moveCamera(Real dx, Real dy);
  void turnHead (Real theat, Real phi);

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
  WalkThroughTimer *myWalkThroughTimer;
  Timer myTimer;
};

//______________________________________________________________________ INLINES

#endif // _wxWalkThroughCommand_H

