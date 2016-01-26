/*
 * $RCSfile: wxSelectCommand.h,v $
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
 *  $Id: wxSelectCommand.h,v 1.1 1998/05/15 09:19:15 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _wxSelectCommand_H
#define _wxSelectCommand_H

#include "booga/component/Picker3D.h"
#include "booga/wxwrapper/wxViewCommand.h"

//_____________________________________________________________________ wxSelectCommand

class wxSelectCommand : public wxViewCommand {
  declareRTTI(wxSelectCommand);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  wxSelectCommand(wxView3D *v);                         // Use default version.
private:
//  wxSelectCommand(const wxSelectCommand&);             // No copies.

public:
  // virtual ~wxSelectCommand();                // Use default version.

private:
  wxSelectCommand& operator=(const wxSelectCommand&);  // No assignments.

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

#endif // _wxSelectCommand_H

