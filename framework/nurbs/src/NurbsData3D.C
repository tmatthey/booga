/*
 * NurbsData3D.C 
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
 *  $Id: NurbsData3D.C,v 1.2 1996/02/09 08:31:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/nurbs/NurbsData3D.h"

//__________________________________________________________________ NurbsData3D

implementRTTI (NurbsData3D, Nurbs3D);

NurbsData3D::NurbsData3D (void)
  : Nurbs3D ()
{
  myCurveData = NULL;
  mySurfaceData = NULL;
  myChangedFlag = false;
}

NurbsData3D::NurbsData3D (Exemplar exemplar)
  : Nurbs3D (exemplar)
{
  myCurveData = NULL;
  mySurfaceData = NULL;
  myChangedFlag = false;
}

NurbsData3D::NurbsData3D (PtArray1D *adoptCurveData)
  : Nurbs3D ()
{
  myCurveData = adoptCurveData;
  mySurfaceData = NULL;
  myChangedFlag = true;
}

NurbsData3D::NurbsData3D (PtArray2D *adoptSurfaceData)
  : Nurbs3D ()
{
  myCurveData = NULL;
  mySurfaceData = adoptSurfaceData;
  myChangedFlag = true;
}

NurbsData3D::~NurbsData3D (void)
{
  if (myCurveData != NULL)
    delete myCurveData;
  if (mySurfaceData != NULL)
    delete mySurfaceData;
}

void NurbsData3D::adoptCurveData (PtArray1D *curveData)
{
  if (curveData == NULL)
    return;
  if (myCurveData != NULL)
    delete myCurveData;
  myCurveData = curveData;
  myChangedFlag = true;
}

PtArray1D* NurbsData3D::copyCurveData (void) const
{
  if (myCurveData != NULL)
    return new PtArray1D (*myCurveData);
  return NULL;
}

PtArray1D* NurbsData3D::orphanCurveData (void)
{
  PtArray1D *retData = myCurveData;

  myCurveData = NULL;
  myChangedFlag = true;
  return retData;
}

void NurbsData3D::adoptSurfaceData (PtArray2D *surfaceData)
{
  if (surfaceData == NULL)
    return;
  if (mySurfaceData != NULL)
    delete mySurfaceData;
  mySurfaceData = surfaceData;
  myChangedFlag = true;
}

PtArray2D* NurbsData3D::copySurfaceData (void) const
{
  if (mySurfaceData != NULL)
    return new PtArray2D (*mySurfaceData);
  return NULL;
}

PtArray2D* NurbsData3D::orphanSurfaceData (void)
{
  PtArray2D *retData = mySurfaceData;

  mySurfaceData = NULL;
  myChangedFlag = true;
  return retData;
}
