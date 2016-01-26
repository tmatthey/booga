/*
 * $RCSfile: InspectSelectionCommand.h,v $
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
 *  $Id: InspectSelectionCommand.h,v 1.1 1996/09/27 15:07:51 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InspectSelectionCommand_H
#define _InspectSelectionCommand_H

#include "booga/object/Camera3D.h"
#include "booga/wxwrapper/wxViewCommand.h"

//_____________________________________________________________________ InspectSelectionCommand

class InspectSelectionCommand : public wxViewCommand {
declareRTTI(InspectSelectionCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InspectSelectionCommand(wxView3D *v);                         // Use default version.
//private:
//  InspectSelectionCommand(const InspectSelectionCommand&);             // No copies.

public:
  // virtual ~InspectSelectionCommand();                // Use default version.

private:
  InspectSelectionCommand& operator=(const InspectSelectionCommand&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class InspectSelectionCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  void interpolateCamera (Camera3D *newc);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

};

//______________________________________________________________________ INLINES

#endif // _InspectSelectionCommand_H

