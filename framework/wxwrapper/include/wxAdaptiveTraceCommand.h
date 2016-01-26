/*
 * wxAdaptiveTraceCommand.h
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
 *  $Id: wxAdaptiveTraceCommand.h,v 1.1 1997/09/19 08:41:47 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxAdaptiveTraceCommand_H
#define _wxAdaptiveTraceCommand_H

#include "booga/base/Timer.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "booga/wxwrapper/wxAdaptiveTracer.h"

#include "wx_timer.h"


class wxAdaptiveTraceCommand; // forward declaration

class wxAdaptiveTraceTimer : public wxTimer
{
  public:
    wxAdaptiveTraceTimer (wxAdaptiveTraceCommand *c);
    void Notify(void);
  private: 
    wxAdaptiveTraceCommand* mywxAdaptiveTraceCommand;
};

//_____________________________________________________________________ wxAdaptiveTraceCommand

class wxAdaptiveTraceCommand : public wxViewCommand {
declareRTTI(wxAdaptiveTraceCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxAdaptiveTraceCommand(wxView3D *v);                        // Use default version.
private:
//  wxAdaptiveTraceCommand(const wxAdaptiveTraceCommand&);             // No copies.

public:
  ~wxAdaptiveTraceCommand();                // Use default version.

private:
//  wxAdaptiveTraceCommand& operator=(const wxAdaptiveTraceCommand&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxAdaptiveTraceCommand
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
  wxAdaptiveTraceTimer *mywxAdaptiveTraceTimer;
  wxAdaptiveTracer *myRenderer;
};

//______________________________________________________________________ INLINES

#endif // _wxAdaptiveTraceCommand_H

