/*
 * NurbsCompound3D.C 
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
 *  $Id: NurbsCompound3D.C,v 1.2 1996/02/09 08:30:46 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/nurbs/NurbsCompound3D.h"

//______________________________________________________________ NurbsCompound3D

implementRTTI (NurbsCompound3D, Nurbs3D);

NurbsCompound3D::NurbsCompound3D (void)
  : Nurbs3D ()
{
  mySectionCurve = NULL;
  myPathCurve = NULL;
  myChangedFlag = false;
}

NurbsCompound3D::NurbsCompound3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  mySectionCurve = NULL;
  myPathCurve = NULL;
  myChangedFlag = false;
}

NurbsCompound3D::NurbsCompound3D (Nurbs3D *adoptSection, Nurbs3D *adoptPath)
  : Nurbs3D ()
{
  mySectionCurve = adoptSection;
  myPathCurve = adoptPath;
  myChangedFlag = true;
}

NurbsCompound3D::~NurbsCompound3D (void)
{
  if (mySectionCurve != NULL)
    delete mySectionCurve;
  if (myPathCurve != NULL)
    delete myPathCurve;
}

void NurbsCompound3D::adoptSectionCurve (Nurbs3D *sectionCurve)
{
  if (sectionCurve == NULL || sectionCurve->getType() != Nurbs3DTypes::Curve)
    return;
  if (mySectionCurve != NULL)
    delete mySectionCurve;
  mySectionCurve = sectionCurve;
  myChangedFlag = true;
}

Nurbs3D* NurbsCompound3D::copySectionCurve (void) const
{
  if (mySectionCurve != NULL)
    return new Nurbs3D (*mySectionCurve);
  return NULL;
}

Nurbs3D* NurbsCompound3D::orphanSectionCurve (void)
{
  Nurbs3D *retNurbs = mySectionCurve;

  mySectionCurve = NULL;
  myChangedFlag = true;
  return retNurbs;
}

void NurbsCompound3D::adoptPathCurve (Nurbs3D *pathCurve)
{
  if (pathCurve == NULL || pathCurve->getType() != Nurbs3DTypes::Curve)
    return;
  if (myPathCurve != NULL)
    delete myPathCurve;
  myPathCurve = pathCurve;
  myChangedFlag = true;
}

Nurbs3D* NurbsCompound3D::copyPathCurve (void) const
{
  if (myPathCurve != NULL)
    return new Nurbs3D (*myPathCurve);
  return NULL;
}

Nurbs3D* NurbsCompound3D::orphanPathCurve (void)
{
  Nurbs3D *retNurbs = myPathCurve;

  myPathCurve = NULL;
  myChangedFlag = true;
  return retNurbs;
}
