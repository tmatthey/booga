/*
 * $RCSfile: NurbsRevolution3D.C,v $
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
 *  $Id: NurbsRevolution3D.C,v 1.8 1996/09/12 13:51:35 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/nurbs/NurbsRevolution3D.h"
#include "booga/nurbs/Nurbs3DCreator.h"

#include "booga/nurbs/Nurbs3DAttr.h"      // Class Nurbs3DPathAttr

//____________________________________________________________ NurbsRevolution3D

implementRTTI (NurbsRevolution3D, NurbsCompound3D);

NurbsRevolution3D::NurbsRevolution3D (void)
  : NurbsCompound3D ()
{
}

NurbsRevolution3D::NurbsRevolution3D (Exemplar exemplar)
  : NurbsCompound3D (exemplar)
{
}

NurbsRevolution3D::NurbsRevolution3D (Nurbs3D *adoptSection)
  : NurbsCompound3D ()
{
  adoptSectionCurve (adoptSection);
}

NurbsRevolution3D::NurbsRevolution3D (const NurbsRevolution3D &nrb)
  : NurbsCompound3D ()
{
  *this = nrb;
}

NurbsRevolution3D& NurbsRevolution3D::operator= (const NurbsRevolution3D &nrb)
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

void NurbsRevolution3D::rebuild (void)
{
  if (isChanged())        // Revolve only if necessary
  {
    if (mySectionCurve == NULL)
    {
      Report::warning ("[NurbsRevolution3D::rebuild] object not complete");
      return;
    }

    Nurbs3D *revolved = new Nurbs3D (*mySectionCurve);

    Nurbs3DCreator create (revolved);   // Initialize creator
    create.surfaceOfRevolution ();      // Create surface of revolution
    revolved = create.orphanNurbs ();

    setType (Nurbs3DTypes::Surface);    // Set correct type
    adoptKnotsU (revolved->orphanKnotsU());
    adoptKnotsV (revolved->orphanKnotsV());
    adoptPoints (revolved->orphanPoints());
    adoptWeights (revolved->orphanWeights());
    delete revolved;            // Clean up
    setChanged (false);         // Flag that I'm done
  }
}

Object3D* NurbsRevolution3D::createDecomposition (void) const
{
  if (isChanged())
    ((NurbsRevolution3D*)this)->rebuild ();
  return Nurbs3D::createDecomposition ();
}

void NurbsRevolution3D::doComputeBounds (void)
{
  if (mySectionCurve != NULL)
  {
    register int i;
    int n = mySectionCurve->getCtrlCountU ();

    for (i = 0; i < n; i++)
    {
      myBounds.expand (mySectionCurve->getPoint(i).x(),
		       mySectionCurve->getPoint(i).x(),
		       mySectionCurve->getPoint(i).z());
      myBounds.expand (-mySectionCurve->getPoint(i).x(),
		       -mySectionCurve->getPoint(i).x(),
		       mySectionCurve->getPoint(i).z());
    }
  }
}

Makeable* NurbsRevolution3D::make (RCString &, const List<Value*> *) const
{
  return new NurbsRevolution3D (*this);
}

/***   setSpecifier : Set a specifier   *******************/
//                                                        //
//  If the specifier is a Nurbs3DAttr, the attribute      //
//  is set. Else Object3D is left to handle it on it's    //
//  own.                                                  //
//                                                        //
/**********************************************************/

int NurbsRevolution3D::setSpecifier (RCString &errMsg, Makeable *specifier)
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

Object3D* NurbsRevolution3D::copy (void) const
{
  return new NurbsRevolution3D (*this);
}


