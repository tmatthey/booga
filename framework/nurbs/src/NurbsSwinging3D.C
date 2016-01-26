/*
 * $RCSfile: NurbsSwinging3D.C,v $
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
 *  $Id: NurbsSwinging3D.C,v 1.8 1996/09/12 13:51:45 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/NurbsSwinging3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//______________________________________________________________ NurbsSwinging3D

implementRTTI (NurbsSwinging3D, NurbsCompound3D);

NurbsSwinging3D::NurbsSwinging3D (void)
  : NurbsCompound3D ()
{
}

NurbsSwinging3D::NurbsSwinging3D (Exemplar exemplar)
  : NurbsCompound3D (exemplar)
{
}

NurbsSwinging3D::NurbsSwinging3D (Nurbs3D *adoptSection, Nurbs3D *adoptPath)
  : NurbsCompound3D (adoptSection, adoptPath)
{}

NurbsSwinging3D::NurbsSwinging3D (const NurbsSwinging3D &nrb)
  : NurbsCompound3D ()
{
  *this = nrb;
}

NurbsSwinging3D& NurbsSwinging3D::operator= (const NurbsSwinging3D &nrb)
{
  reset ();

  setEvaluation (nrb.getEvaluation());
  if (nrb.mySectionCurve != NULL || nrb.myPathCurve != NULL) // something to copy
  {
    setChanged (true);
    if (nrb.mySectionCurve != NULL)
      adoptSectionCurve (nrb.copySectionCurve());
    if (nrb.myPathCurve != NULL)
      adoptPathCurve (nrb.copyPathCurve());
  }

  return *this;
}

void NurbsSwinging3D::rebuild (void)
{
  if (isChanged())        // Rebuild only if necessary
  {
    if (mySectionCurve == NULL || myPathCurve == NULL)
    {
      Report::warning ("[NurbsSwingping3D::rebuild] object not complete");
      return;
    }
    Nurbs3D *swungSurface = new Nurbs3D (*mySectionCurve);

    Nurbs3DCreator creator (swungSurface);   // Initialize creator
    creator.swing (myPathCurve);             // Create swung surface
    swungSurface = creator.orphanNurbs ();

    setType (Nurbs3DTypes::Surface);    // Set correct type
    adoptKnotsU (swungSurface->orphanKnotsU());
    adoptKnotsV (swungSurface->orphanKnotsV());
    adoptPoints (swungSurface->orphanPoints());
    adoptWeights (swungSurface->orphanWeights());
    delete swungSurface;            // Clean up
    setChanged (false);             // Flag that I'm done
  }
}

Object3D* NurbsSwinging3D::createDecomposition (void) const
{
  if (isChanged())
    ((NurbsSwinging3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsSwinging3D::doComputeBounds (void)
{
  if (mySectionCurve != NULL && myPathCurve != NULL)
  {
    rebuild ();
    Nurbs3D::doComputeBounds ();
  }
}

Makeable* NurbsSwinging3D::make (RCString &, const List<Value*> *) const
{
  return new NurbsSwinging3D (*this);
}

/***   setSpecifier : Set a specifier   *******************/
//                                                        //
//  If the specifier is a Nurbs3DAttr, the attribute      //
//  is set. Else Object3D is left to handle it on it's    //
//  own.                                                  //
//                                                        //
/**********************************************************/

int NurbsSwinging3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3DPathAttr *attr = dynamic_cast (Nurbs3DPathAttr, specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3DPathAttr object knows how to handle this

    delete attr;
    return 1;
  }

  return NurbsCompound3D::setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

Object3D* NurbsSwinging3D::copy (void) const
{
  return new NurbsSwinging3D (*this);
}

