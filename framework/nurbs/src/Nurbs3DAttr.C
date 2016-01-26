/*
 * Nurbs3DAttr.C
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
 *  $Id: Nurbs3DAttr.C,v 1.6 1996/02/16 13:37:47 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/nurbs/Nurbs3DAttr.h"

#include "booga/nurbs/Nurbs3D.h"           // Class Nurbs3D and related
#include "booga/nurbs/NurbsCompound3D.h"   // Class NurbsCompound3D
#include "booga/nurbs/NurbsData3D.h"       // Class NurbsData3D

//__________________________________________________________________ Nurbs3DAttr

implementRTTI(Nurbs3DAttr, ObjectAttr);

//______________________________________________________________ Nurbs3DDataAttr

implementRTTI(Nurbs3DDataAttr, ObjectAttr);

//______________________________________________________________ Nurbs3DPathAttr

implementRTTI(Nurbs3DPathAttr, ObjectAttr);

//____________________________________________________________ Nurbs3DAttrUKnots

implementRTTI(Nurbs3DAttrUKnots, Nurbs3DAttr);

Makeable* Nurbs3DAttrUKnots::make (RCString &errMsg,
				   const List<Value*> *parameters) const
{
  Nurbs3DAttrUKnots *retval = new Nurbs3DAttrUKnots (*this);

  KnotArray *iknots = new KnotArray (parameters->count()-1);
  
  getParameter (1, Real, degree);
   
  for (int i = 1; i < parameters->count(); i++) 
  {
    getParameter (i+1, Real, knot);
    iknots->set (i-1, knot);
  }

  retval->myKnots = new Nurbs3DKnots ((int) degree, iknots);
  return retval;
}

void Nurbs3DAttrUKnots::setAttribute (Nurbs3D* nurbs)
{
  if (myKnots != NULL)
    nurbs->adoptKnotsU (myKnots->copy());
}

//____________________________________________________________ Nurbs3DAttrVKnots

implementRTTI(Nurbs3DAttrVKnots, Nurbs3DAttr);

Makeable* Nurbs3DAttrVKnots::make (RCString &errMsg,
				   const List<Value*> *parameters) const
{
  Nurbs3DAttrVKnots *retval = new Nurbs3DAttrVKnots (*this);

  KnotArray *iknots = new KnotArray (parameters->count()-1);
  
  getParameter (1, Real, degree);
  
  for (int i = 1; i < parameters->count(); i++) 
  {
    getParameter (i+1, Real, knot);
    iknots->set (i-1, knot);
  }

  retval->myKnots = new Nurbs3DKnots ((int) degree, iknots);
  return retval;
}

void Nurbs3DAttrVKnots::setAttribute(Nurbs3D* nurbs)
{
  if (nurbs->getType() != Nurbs3DTypes::Surface)
  {
    Report::recoverable ("[Nurbs3DAttrVKnots::setAttribute] vknots are only set for surfaces!");
    return;
  }
  if (myKnots != NULL)
    nurbs->adoptKnotsV (myKnots->copy());
}

//___________________________________________________________ Nurbs3DAttrVectors

implementRTTI(Nurbs3DAttrVectors, Nurbs3DAttr);

Makeable* Nurbs3DAttrVectors::make (RCString &errMsg,
				    const List<Value*> *parameters) const
{
  Nurbs3DAttrVectors *retval = new Nurbs3DAttrVectors (*this);

  getParameter (1, Real, uct);          // Get number of points in u-direction
  if (uct == parameters->count()-1)     // Initialize points for curve
  {
    PtArray1D *pts = new PtArray1D ((int) uct);

    int count = 2;
    for (int u = 0; u < uct; u++)
    {
      getParameter (count++, Vector3D, vector);
      pts->set (u, vector);
    }
    retval->myVectors = new Nurbs3DPoints (pts);
  }
  else                                  // Initialize points for surface
  {
    getParameter (2, Real, vct);        // Get number of points in v-direction
    if (uct*vct != parameters->count()-2)
    {
      errMsg = "wrong number of control points specified";
      delete retval;
      return NULL;
    }
  
    PtArray2D *pts = new PtArray2D ((int) uct, (int) vct);
 
    int count = 3;
    for (int u = 0; u < uct; u++) 
    {
      for (int v = 0; v < vct; v++) 
      {
	getParameter (count++, Vector3D, vector);
	pts->set (u, v, vector);
      }
    }
    retval->myVectors = new Nurbs3DPoints (pts);
  }

  return retval;
}

void Nurbs3DAttrVectors::setAttribute(Nurbs3D* nurbs)
{
  if (myVectors != NULL)
  {
    nurbs->adoptPoints (myVectors->copy());
  }
}

//___________________________________________________________ Nurbs3DAttrWeights

implementRTTI(Nurbs3DAttrWeights, Nurbs3DAttr);

Makeable* Nurbs3DAttrWeights::make (RCString &errMsg,
				    const List<Value*> *parameters) const
{
  Nurbs3DAttrWeights *retval = new Nurbs3DAttrWeights (*this);
 
  getParameter (1, Real, uct);          // Get number of weights in u-direction
  if (uct == parameters->count()-1)     // Initialize for curve
  {
    WtArray1D *wts = new WtArray1D ((int) uct);

    int count = 2;
    for (int u = 0; u < uct; u++)
    {
      getParameter (count++, Real, weight);
      wts->set (u, weight);
    }
    retval->myWeights = new Nurbs3DWeights (wts);
  }
  else                                  // Initialize for surface
  {
    getParameter (2, Real, vct);
    if (uct*vct != parameters->count()-2)
    {
      errMsg = "wrong number of weights specified";
      delete retval;
      return NULL;
    }
  
    WtArray2D *wts = new WtArray2D ((int) uct, (int) vct);

    int count = 3;
    for (int u = 0; u < uct; u++) 
    {
      for (int v = 0; v < vct; v++) 
      {
	getParameter (count++, Real, weight);
	wts->set (u, v, weight);
      }
    }
    retval->myWeights = new Nurbs3DWeights (wts);
  }

  return retval;
}

void Nurbs3DAttrWeights::setAttribute (Nurbs3D* nurbs)
{
  if (myWeights != NULL)
    nurbs->adoptWeights (myWeights->copy());
}

//___________________________________________________ NrbElementAttrEvaluation

implementRTTI(Nurbs3DAttrEvaluation, Nurbs3DAttr);

Makeable* Nurbs3DAttrEvaluation::make (RCString &errMsg,
				       const List<Value*> *parameters) const
{
  Nurbs3DTypes::EEvaluation etype;

  checkParameterNumber (1);
 
  getParameter (1, RCString, stype);
  if (stype == "basisfuns")
    etype = Nurbs3DTypes::BasisFuns;
  else if (stype == "cornercut")
    etype = Nurbs3DTypes::CornerCut;
  else if (stype == "deboor")
    etype = Nurbs3DTypes::DeBoor;
  else
  {
    errMsg = "unknown evaluation type";
    return NULL;
  }

  Nurbs3DAttrEvaluation *retval = new Nurbs3DAttrEvaluation (*this);
  retval->myType = etype;
  return retval;
}

void Nurbs3DAttrEvaluation::setAttribute (Nurbs3D* nurbs)
{
  nurbs->setEvaluation (myType);
}

//________________________________________________________ NrbElementAttrDiameter

implementRTTI(Nurbs3DAttrDiameter, Nurbs3DAttr);

Makeable* Nurbs3DAttrDiameter::make (RCString &errMsg,
				     const List<Value*> *parameters) const
{
  checkParameterNumber (1);
 
  getParameter (1, Real, diameter);
  Nurbs3DAttrDiameter *retval = new Nurbs3DAttrDiameter (*this);
  retval->myDiameter = diameter;
  return retval;
}

void Nurbs3DAttrDiameter::setAttribute (Nurbs3D* nurbs)
{
  nurbs->setDiameter (myDiameter);
}

//_________________________________________________________ Nurbs3DAttrDataPoints

implementRTTI(Nurbs3DAttrDataPoints, Nurbs3DDataAttr);

Makeable* Nurbs3DAttrDataPoints::make (RCString &errMsg,
				       const List<Value*> *parameters) const
{
  Nurbs3DAttrDataPoints *retval = new Nurbs3DAttrDataPoints (*this);

  getParameter (1, Real, uct);          // Get number of points in u-direction
  if (uct == parameters->count()-1)     // Initialize points for curve
  {
    PtArray1D *pts = new PtArray1D ((int) uct);

    int count = 2;
    for (int u = 0; u < uct; u++)
    {
      getParameter (count++, Vector3D, vector);
      pts->set (u, vector);
    }
    retval->myCurveData = pts;
  }
  else                                  // Initialize points for surface
  {
    getParameter (2, Real, vct);        // Get number of points in v-direction
    if (uct*vct != parameters->count()-2)
    {
      errMsg = "wrong number of control points specified";
      delete retval;
      return NULL;
    }
  
    PtArray2D *pts = new PtArray2D ((int) uct, (int) vct);
 
    int count = 3;
    for (int u = 0; u < uct; u++) 
    {
      for (int v = 0; v < vct; v++) 
      {
	getParameter (count++, Vector3D, vector);
	pts->set (u, v, vector);
      }
    }
    retval->mySurfaceData = pts;
  }

  return retval;
}

void Nurbs3DAttrDataPoints::setAttribute (NurbsData3D* nurbs)
{
  if (myCurveData != NULL)
    nurbs->adoptCurveData (new PtArray1D(*myCurveData));
  else if (mySurfaceData != NULL)
    nurbs->adoptSurfaceData (new PtArray2D(*mySurfaceData));
}

//___________________________________________________________ Nurbs3DAttrSection

implementRTTI(Nurbs3DAttrSection, Nurbs3DPathAttr);

Makeable* Nurbs3DAttrSection::make (RCString&, const List<Value*>*) const
{
  return new Nurbs3DAttrSection (*this);
}

int Nurbs3DAttrSection::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3D *attr = dynamic_cast (Nurbs3D, specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3D object knows how to handle this

    delete attr;
    return 1;
  }

  return ((Nurbs3DAttr*)this)->setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

void Nurbs3DAttrSection::setAttribute (NurbsCompound3D* nurbs)
{
  if (mySectionCurve != NULL)
    nurbs->adoptSectionCurve (new Nurbs3D(*mySectionCurve));
}

void Nurbs3DAttrSection::adoptCurve (Nurbs3D *curve)
{
  if (mySectionCurve != NULL)
    delete mySectionCurve;
  mySectionCurve = curve;
}

//_____________________________________________________________ Nurbs3DAttrPath

implementRTTI(Nurbs3DAttrPath, Nurbs3DPathAttr);

Makeable* Nurbs3DAttrPath::make (RCString&, const List<Value*>*) const
{
  return new Nurbs3DAttrPath (*this);
}

int Nurbs3DAttrPath::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3D *attr = dynamic_cast (Nurbs3D, specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3D object knows how to handle this

    delete attr;
    return 1;
  }

  return ((Nurbs3DAttr*)this)->setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

void Nurbs3DAttrPath::setAttribute (NurbsCompound3D* nurbs)
{
  if (myPathCurve != NULL)
    nurbs->adoptPathCurve (new Nurbs3D(*myPathCurve));
}

void Nurbs3DAttrPath::adoptCurve (Nurbs3D *curve)
{
  if (myPathCurve != NULL)
    delete myPathCurve;
  myPathCurve = curve;
}

