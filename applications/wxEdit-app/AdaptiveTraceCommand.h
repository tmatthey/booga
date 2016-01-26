/*
 * AdaptiveTraceCommand.h
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
 *  $Id: AdaptiveTraceCommand.h,v 1.2 1996/12/06 13:52:41 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AdaptiveTraceCommand_H
#define _AdaptiveTraceCommand_H

#include "booga/base/Timer.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "AdaptiveTracer.h"

#include "wx_timer.h"


class AdaptiveTraceCommand; // forward declaration

class AdaptiveTraceTimer : public wxTimer
{
  public:
    AdaptiveTraceTimer (AdaptiveTraceCommand *c);
    void Notify(void);
  private: 
    AdaptiveTraceCommand* myAdaptiveTraceCommand;
};

//_____________________________________________________________________ AdaptiveTraceCommand

class AdaptiveTraceCommand : public wxViewCommand {
declareRTTI(AdaptiveTraceCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AdaptiveTraceCommand(wxView3D *v);                        // Use default version.
private:
//  AdaptiveTraceCommand(const AdaptiveTraceCommand&);             // No copies.

public:
  ~AdaptiveTraceCommand();                // Use default version.

private:
//  AdaptiveTraceCommand& operator=(const AdaptiveTraceCommand&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AdaptiveTraceCommand
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
  AdaptiveTraceTimer *myAdaptiveTraceTimer;
  AdaptiveTracer *myRenderer;
};

//______________________________________________________________________ INLINES

#endif // _AdaptiveTraceCommand_H

