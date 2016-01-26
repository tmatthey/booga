/*
 * $RCSfile: NurbsSweeping3D.C,v $
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
 *  $Id: NurbsSweeping3D.C,v 1.8 1996/09/12 13:51:43 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/NurbsSweeping3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//______________________________________________________________ NurbsSweeping3D

implementRTTI (NurbsSweeping3D, Nurbs3D);

NurbsSweeping3D::NurbsSweeping3D (void)
  : NurbsCompound3D ()
{
}

NurbsSweeping3D::NurbsSweeping3D (Exemplar exemplar)
  : NurbsCompound3D (exemplar)
{
}

NurbsSweeping3D::NurbsSweeping3D (Nurbs3D *adoptSection, Nurbs3D *adoptPath)
  : NurbsCompound3D (adoptSection, adoptPath)
{}

NurbsSweeping3D::NurbsSweeping3D (const NurbsSweeping3D &nrb)
  : NurbsCompound3D ()
{
  *this = nrb;
}

NurbsSweeping3D& NurbsSweeping3D::operator= (const NurbsSweeping3D &nrb)
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

void NurbsSweeping3D::rebuild (void)
{
  if (isChanged())        // Rebuild only if necessary
  {
    if (mySectionCurve == NULL || myPathCurve == NULL)
    {
      Report::warning ("[NurbsSweeping3D::rebuild] object not complete");
      return;
    }
    Nurbs3D *sweptSurface = new Nurbs3D (*mySectionCurve);

    Nurbs3DCreator creator (sweptSurface);   // Initialize creator
    creator.sweep (myPathCurve);             // Create swept surface
    sweptSurface = creator.orphanNurbs ();

    setType (Nurbs3DTypes::Surface);    // Set correct type
    adoptKnotsU (sweptSurface->orphanKnotsU());
    adoptKnotsV (sweptSurface->orphanKnotsV());
    adoptPoints (sweptSurface->orphanPoints());
    adoptWeights (sweptSurface->orphanWeights());
    delete sweptSurface;            // Clean up
    setChanged (false);             // Flag that I'm done
  }
}

Object3D* NurbsSweeping3D::createDecomposition (void) const
{
  ((NurbsSweeping3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsSweeping3D::doComputeBounds (void)
{
  if (mySectionCurve != NULL && myPathCurve != NULL)
  {
    rebuild ();
    Nurbs3D::doComputeBounds ();
  }
}

Makeable* NurbsSweeping3D::make (RCString &, const List<Value*> *) const
{
  return new NurbsSweeping3D (*this);
}

/***   setSpecifier : Set a specifier   *******************/
//                                                        //
//  If the specifier is a Nurbs3DAttr, the attribute      //
//  is set. Else Object3D is left to handle it on it's    //
//  own.                                                  //
//                                                        //
/**********************************************************/

int NurbsSweeping3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3DPathAttr *attr = dynamic_cast<Nurbs3DPathAttr*>(specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3DPathAttr object knows how to handle this

    delete attr;
    return 1;
  }

  return NurbsCompound3D::setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

Object3D* NurbsSweeping3D::copy (void) const
{
  return new NurbsSweeping3D (*this);
}
