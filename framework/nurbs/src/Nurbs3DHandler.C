/*
 * Nurbs3DHandler.C 
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: Nurbs3DHandler.C,v 1.3 1996/01/12 16:06:22 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/Nurbs3DHandler.h"

#include "booga/nurbs/Nurbs3D.h"              // Class Nurbs3D

//_______________________________________________________________ Nurbs3DHandler

implementRTTIBase (Nurbs3DHandler);

Nurbs3DHandler::Nurbs3DHandler (void)
{
  myNurbs = NULL;
}

Nurbs3DHandler::Nurbs3DHandler (Nurbs3D *adoptNurbs)
{
  myNurbs = adoptNurbs;
}

Nurbs3DHandler::~Nurbs3DHandler (void)
{
  if (myNurbs != NULL)
    delete myNurbs;
}

void Nurbs3DHandler::adoptNurbs (Nurbs3D *nurbs)
{
  if (myNurbs != NULL)
  {
    delete myNurbs;
    myNurbs = NULL;
  }
  myNurbs = nurbs;
}

Nurbs3D* Nurbs3DHandler::copyNurbs (void) const
{
  return new Nurbs3D (*myNurbs);
}

Nurbs3D* Nurbs3DHandler::orphanNurbs (void)
{
  Nurbs3D *retNurbs = myNurbs;

  myNurbs = NULL;
  return retNurbs;
}
