/*
 * $RCSfile: NurbsInterpolation3D.C,v $
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
 *  $Id: NurbsInterpolation3D.C,v 1.6 1996/09/12 13:51:27 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/List3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/nurbs/NurbsInterpolation3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DDataAttr

//_________________________________________________________ NurbsInterpolation3D

implementRTTI (NurbsInterpolation3D, Nurbs3D);

NurbsInterpolation3D::NurbsInterpolation3D (void)
  : NurbsData3D ()
{
}

NurbsInterpolation3D::NurbsInterpolation3D (Exemplar exemplar)
  : NurbsData3D (exemplar)
{
}

NurbsInterpolation3D::NurbsInterpolation3D (PtArray1D *adoptCurveData)
  : NurbsData3D (adoptCurveData)
{
}

NurbsInterpolation3D::NurbsInterpolation3D (PtArray2D *adoptSurfaceData)
  : NurbsData3D (adoptSurfaceData)
{
}

NurbsInterpolation3D::NurbsInterpolation3D (const NurbsInterpolation3D &nrb)
  : NurbsData3D ()
{
  *this = nrb;
}

NurbsInterpolation3D& NurbsInterpolation3D::operator= (const NurbsInterpolation3D &nrb)
{
  reset ();

  setEvaluation (nrb.getEvaluation());
  if (nrb.myCurveData != NULL || nrb.mySurfaceData != NULL) // something to copy
  {
    setChanged (true);
    if (nrb.myCurveData != NULL)
      adoptCurveData (nrb.copyCurveData());
    else if (nrb.mySurfaceData != NULL)
      adoptSurfaceData (nrb.copySurfaceData());
  }

  return *this;
}

void NurbsInterpolation3D::rebuild (void)
{
  if (isChanged())        // Rebuild only if necessary
  {
    if (myCurveData == NULL && mySurfaceData == NULL)
    {
      Report::warning ("[NurbsInterpolation3D::rebuild] no data specified");
      return;
    }
    Nurbs3D *interpolated = new Nurbs3D;

    // Apply sensible degree ===>>> TO DO

    Nurbs3DCreator creator (interpolated);   // Initialize creator
    if (myCurveData != NULL)
      creator.interpolate (myCurveData);     // Create interpolated curve
    else
      creator.interpolate (mySurfaceData);   // Create interpolated surface
    interpolated = creator.orphanNurbs ();

    setType (interpolated->getType());       // Set correct type
    adoptKnotsU (interpolated->orphanKnotsU());
    adoptKnotsV (interpolated->orphanKnotsV());
    adoptPoints (interpolated->orphanPoints());
    adoptWeights (interpolated->orphanWeights());
    delete interpolated;            // Clean up
    setChanged (false);             // Flag that I'm done
  }
}

Object3D* NurbsInterpolation3D::createDecomposition (void) const
{
  ((NurbsInterpolation3D*)this)->rebuild ();
  List3D *decomp = new List3D;

  if (myCurveData != NULL)
  {
    for (int x = 0; x < myCurveData->getCount(); x++)
      decomp->adoptObject (new Sphere3D(3*getDiameter(), myCurveData->get(x)));
  }
  else if (mySurfaceData != NULL)
  {
    for (int x = 0; x < mySurfaceData->getCountU(); x++)
      for (int y = 0; y < mySurfaceData->getCountV(); y++)
      decomp->adoptObject (new Sphere3D(3*getDiameter(), mySurfaceData->get(x, y)));
  }
  decomp->adoptObject (Nurbs3D::createDecomposition());
  decomp->computeBounds();
  
  return decomp;
}

void NurbsInterpolation3D::doComputeBounds (void)
{
  if (myCurveData != NULL || mySurfaceData != NULL)
  {
    rebuild ();
    Nurbs3D::doComputeBounds ();
  }
}

Makeable* NurbsInterpolation3D::make (RCString&, const List<Value*> *) const
{
  return new NurbsInterpolation3D (*this);
}

/***   setSpecifier : Set a specifier   *******************/
//                                                        //
//  If the specifier is a Nurbs3DAttr, the attribute      //
//  is set. Else Object3D is left to handle it on it's    //
//  own.                                                  //
//                                                        //
/**********************************************************/

int NurbsInterpolation3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3DDataAttr *attr = dynamic_cast (Nurbs3DDataAttr, specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3DDataAttr object knows how to handle this

    delete attr;
    return 1;
  }

  return NurbsData3D::setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

Object3D* NurbsInterpolation3D::copy () const
{
  return new NurbsInterpolation3D (*this);
}
