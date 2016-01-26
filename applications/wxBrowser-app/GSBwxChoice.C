/*
 * GSBwxChoice.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBwxChoice.C,v 1.4 1997/04/08 11:05:17 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "GSBwxChoice.h"

//_____________________________________________________________________ GSBwxChoice

implementRTTI(GSBwxChoice, wxChoice);
GSBwxChoice::GSBwxChoice(GSBwxDialogDirector* director, wxPanel* parent, char* label,
  int x, int y, int width, int height, int n, char* choices[], long style, char* name)
: wxChoice(parent, (wxFunction) GSBwxChoiceCallback, label, x, y, width, height,
  n, choices, style, name)
{
  if ((myDirector = director) == NULL)
    Report::error("[GSBwxChoice::GSBwxChoice] NULL DialogDirector passed!");
}


// define choice callback function:
void GSBwxChoiceCallback(wxObject* object, wxCommandEvent& event)
{
  // dirty...
  GSBwxChoice* choice = (GSBwxChoice*) object;
  
  choice->getDirector()->widgetCallbackFunction(choice, event);
}



