/*
 * $RCSfile: wxInspectCommand.h,v $
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
 *  $Id: wxInspectCommand.h,v 1.1 1996/09/27 11:48:41 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxInspectCommand_H
#define _wxInspectCommand_H

#include "booga/base/Timer.h"
#include "booga/wxwrapper/wxViewCommand.h"

#include "wx_timer.h"


class wxInspectCommand; // forward declaration

class wxInspectTimer : public wxTimer
{
  public:
    wxInspectTimer (wxInspectCommand *c);
    void Notify(void);
  private: 
    wxInspectCommand* mywxInspectCommand;
};

//_____________________________________________________________________ wxInspectCommand

class wxInspectCommand : public wxViewCommand {
  //  declareRTTI(wxInspectCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxInspectCommand(wxView3D *v);                        // Use default version.
private:
//  wxInspectCommand(const wxInspectCommand&);             // No copies.

public:
  ~wxInspectCommand();                

private:
//  wxInspectCommand& operator=(const wxInspectCommand&);  // No assignments.
  void moveCamera(Real dx, Real dy);
  void rotateAroundLookpoint (Real theat, Real phi);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxInspectCommand
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
  wxInspectTimer *mywxInspectTimer;
  Timer myTimer;
};

//______________________________________________________________________ INLINES

#endif // _wxInspectCommand_H

