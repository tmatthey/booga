/*
 * $RCSfile: wxInspectSelectionCommand.h,v $
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
 *  $Id: wxInspectSelectionCommand.h,v 1.1 1997/09/19 08:41:57 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxInspectSelectionCommand_H
#define _wxInspectSelectionCommand_H

#include "booga/object/Camera3D.h"
#include "booga/wxwrapper/wxViewCommand.h"

//_____________________________________________________________________ wxInspectSelectionCommand

class wxInspectSelectionCommand : public wxViewCommand {
  declareRTTI(wxInspectSelectionCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxInspectSelectionCommand(wxView3D *v);                         // Use default version.
//private:
//  wxInspectSelectionCommand(const wxInspectSelectionCommand&);             // No copies.

public:
  // virtual ~wxInspectSelectionCommand();                // Use default version.

private:
  wxInspectSelectionCommand& operator=(const wxInspectSelectionCommand&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class wxInspectSelectionCommand
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

#endif // _wxInspectSelectionCommand_H

