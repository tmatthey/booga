/*
 * $RCSfile: ToolBar.h,v $
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
 *  $Id: ToolBar.h,v 1.1 1996/10/11 14:58:03 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ToolbarCommand_H
#define _ToolbarCommand_H

#include "booga/object/Camera3D.h"
#include "booga/wxwrapper/wxViewCommand.h"
#include "wx_tbar.h"

//_____________________________________________________________________ ToolbarCommand

class ToolbarCommand : public wxViewCommand, public wxToolBar {
declareRTTI(ToolbarCommand);
// enable RTTI support
public:
  enum ToolIndex {
	SELECT_TOOL,
	GRAVITY_TOOL,
	MOVE_HORIZONTAL_TOOL,
	MOVE_VERTICAL_TOOL
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ToolbarCommand(wxView3D *v, wxFrame *f, int x, int y, int w, int h);                         // Use default version.
//private:
//  ToolbarCommand(const ToolbarCommand&);             // No copies.

public:
  // virtual ~ToolbarCommand();                // Use default version.

private:
  ToolbarCommand& operator=(const ToolbarCommand&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class ToolbarCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void createGUI();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxViewCommand
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void execute();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class wxToolBar
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Bool OnLeftClick(int index, Bool toggleDown);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
};

//______________________________________________________________________ INLINES

#endif // _ToolbarCommand_H

