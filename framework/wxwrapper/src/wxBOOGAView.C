/*
 * wxBOOGAView.C 
 *
 * Copyright (C) 1995, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: wxBOOGAView.C,v 1.3 1996/10/11 14:55:21 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/wxwrapper/wxBOOGAView.h"

//_____________________________________________________________________ wxBOOGAView

implementRTTIBase(wxBOOGAView);

wxBOOGAView::wxBOOGAView()
{
  myViewManager = NULL;
}

wxBOOGAView::~wxBOOGAView()
{
  if (myViewManager)
    myViewManager->detach(this);
}

void wxBOOGAView::setViewManager(wxViewManager* theManager)
{
  myViewManager = theManager;
  update (wxViewManager::WORLD_CHANGED, (Object3D *)theManager->getWorld());
}

