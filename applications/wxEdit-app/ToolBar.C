/*
 * $RCSfile: ToolBar.C,v $
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
 *  $Id: ToolBar.C,v 1.3 1997/02/20 09:42:12 matthey Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Viewing3D.h"
#include "ToolBar.h"
#include "InspectCommand.h"
#include "PickCommand.h"
#include "GravityCommand.h"
#include "RotateCommand.h"

//_____________________________________________________________________ ToolbarCommand

implementRTTI(ToolbarCommand, wxViewCommand);

ToolbarCommand::ToolbarCommand(wxView3D *v, wxFrame *f, int x, int y, int w, int h) : wxViewCommand(v), wxToolBar(f, x, y, w, h, 0, wxVERTICAL, 1)
{
  wxBitmap *b = new wxBitmap();
  wxBitmap *c = new wxBitmap();
  
  SetMargins(2,2);
  
  if (b->LoadFile("/home/buhlmann/icons/select_off.gif", wxBITMAP_TYPE_GIF) &&
      c->LoadFile("/home/buhlmann/icons/select_on.gif", wxBITMAP_TYPE_GIF))
    AddTool (SELECT_TOOL, b,c,true);
  else {
    Report::warning("[ToolbarCommand::ToolbarCommand]: icon not found.");
    delete b;
    delete c;
  }
    
  b = new wxBitmap();
  c = new wxBitmap();
  if (b->LoadFile("/home/buhlmann/icons/gravity_off.gif", wxBITMAP_TYPE_GIF) &&
      c->LoadFile("/home/buhlmann/icons/gravity_on.gif", wxBITMAP_TYPE_GIF))
    AddTool (GRAVITY_TOOL, b,c,false);
  else {
    Report::warning("[ToolbarCommand::ToolbarCommand]: icon not found.");
    delete b;
    delete c;
  }
  
  b = new wxBitmap();
  c = new wxBitmap();
  if (b->LoadFile("/home/buhlmann/icons/horizontal_off.gif", wxBITMAP_TYPE_GIF) &&
      c->LoadFile("/home/buhlmann/icons/horizontal_on.gif", wxBITMAP_TYPE_GIF))
    AddTool (MOVE_HORIZONTAL_TOOL, b, c,true);
  else {
    Report::warning("[ToolbarCommand::ToolbarCommand]: icon not found.");
    delete b;
    delete c;
  }

  b = new wxBitmap();
  c = new wxBitmap();
  if(b->LoadFile("/home/buhlmann/icons/vertical_off.gif", wxBITMAP_TYPE_GIF) &&
     c->LoadFile("/home/buhlmann/icons/vertical_on.gif", wxBITMAP_TYPE_GIF))
       AddTool (MOVE_VERTICAL_TOOL, b, c,true);
  else {
    Report::warning("[ToolbarCommand::ToolbarCommand]: icon not found.");
    delete b;
    delete c;
  }

  Layout();
}

void ToolbarCommand::execute()
{

}

void ToolbarCommand::createGUI ()
{

  
}

Bool ToolbarCommand::OnLeftClick(int index, Bool)
{
  switch (index) {
    case SELECT_TOOL: {
      if (GetToolState(SELECT_TOOL))
        break;
      RotateCommand *c = new RotateCommand(getView());
      getView()->getViewManager()->attach(c);
      // getView()->adoptPickCommand (c);
      getView()->adoptMouseCommand (c);
      ToggleTool (SELECT_TOOL, true);
      ToggleTool (MOVE_HORIZONTAL_TOOL, false);
      ToggleTool (MOVE_VERTICAL_TOOL, false);
      break;
    }
    
    case MOVE_HORIZONTAL_TOOL: {
      // getView()->adoptPickCommand (new MoveHorizontalCommand(getView()));
      getView()->adoptMouseCommand (new MoveHorizontalCommand(getView()));
      ToggleTool (MOVE_HORIZONTAL_TOOL, true);
      ToggleTool (MOVE_VERTICAL_TOOL, false);
      ToggleTool (SELECT_TOOL, false);
      break;
    }
    
    case MOVE_VERTICAL_TOOL: {
      // getView()->adoptPickCommand (new MoveVerticalCommand(getView()));
      getView()->adoptMouseCommand (new MoveVerticalCommand(getView()));
      ToggleTool (MOVE_VERTICAL_TOOL, true);
      ToggleTool (MOVE_HORIZONTAL_TOOL, false);
      ToggleTool (SELECT_TOOL, false);
      break;
    }
      
    case GRAVITY_TOOL: {
      GravityCommand c(getView());
      c.execute();
    }
  }
  return true;
}  

