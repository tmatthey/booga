/*
 * $RCSfile: Nurbs3D.C,v $ 
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
 *  $Id: Nurbs3D.C,v 1.14 1996/09/12 13:51:22 amann Exp $
 * -----------------------------------------------------------------------------
 */
 

#include <math.h>

#include "booga/base/Report.h"
#include "booga/object/Grid3D.h"
#include "booga/object/Triangle3D.h"
#include "booga/object/Cylinder3D.h"
#include "booga/object/Shared3D.h"
#include "booga/nurbs/Nurbs3D.h"
#include "booga/nurbs/Nurbs3DEvaluator.h"
#include "booga/nurbs/DynamicMatrix.h"

#include "booga/nurbs/Nurbs3DKnots.h"        // Class Nurbs3DKnots
#include "booga/nurbs/Nurbs3DPoints.h"       // Class Nurbs3DPoints
#include "booga/nurbs/Nurbs3DWeights.h"      // Class Nurbs3DWeights
#include "booga/nurbs/Nurbs3DAttr.h"         // Class Nurbs3DAttr & Nurbs3DPathAttr

/***********************************************************
  Constants
***********************************************************/

/***********************************************************
  Static data
***********************************************************/

//______________________________________________________________________ Nurbs3D

implementRTTI(Nurbs3D, Primitive3D);

/***   Nurbs3D : Constructor   ****************************/
//                                                        //
//  Initialize from scratch.                              //
//                                                        //
/**********************************************************/

Nurbs3D::Nurbs3D (void)
{
  myKnotsU = NULL;
  myKnotsV = NULL;
  myPoints = NULL;
  myWeights = NULL;
  myType = Nurbs3DTypes::None;
  myEvaluation = Nurbs3DTypes::BasisFuns;
  myInterpolation = Nurbs3DTypes::ChordLength;
  myDiameter = 1.0;
  myDecomposition = NULL;
}

/***   Nurbs3D : Construct an exemplar   ******************/
//                                                        //
//  An exemplar is initialized for the namespace.         //
//                                                        //
/**********************************************************/

Nurbs3D::Nurbs3D (Exemplar exemplar)
  : Primitive3D (exemplar)
{
  myKnotsU = NULL;
  myKnotsV = NULL;
  myPoints = NULL;
  myWeights = NULL;
  myType = Nurbs3DTypes::None;
  myEvaluation = Nurbs3DTypes::BasisFuns;
  myInterpolation = Nurbs3DTypes::ChordLength;
  myDiameter = 1.0;
  myDecomposition = NULL;
}

/***   Nurbs3D : Constructor   ****************************/
//                                                        //
//  Initialize curve from given data.                     //
//                                                        //
/**********************************************************/

Nurbs3D::Nurbs3D (Nurbs3DKnots *adoptKtsU, Nurbs3DPoints *adoptPts, Nurbs3DWeights *adoptWts)
{
  myKnotsU = adoptKtsU;
  myKnotsV = NULL;
  myPoints = adoptPts;
  myWeights = adoptWts;
  myType = Nurbs3DTypes::Curve;         // Set type to curve
  myEvaluation = Nurbs3DTypes::BasisFuns;
  myInterpolation = Nurbs3DTypes::ChordLength;
  myDiameter = 1.0;
  myDecomposition = NULL;
  if (!isDataCorrect())                 // Check input data
    reset ();                           // Reset if faulty
}

/***   Nurbs3D : Constructor   ****************************/
//                                                        //
//  Initialize surface from given data.                   //
//                                                        //
/**********************************************************/

Nurbs3D::Nurbs3D (Nurbs3DKnots *adoptKtsU, Nurbs3DKnots *adoptKtsV, Nurbs3DPoints *adoptPts, Nurbs3DWeights *adoptWts)
{
  myKnotsU = adoptKtsU;
  myKnotsV = adoptKtsV;
  myPoints = adoptPts;
  myWeights = adoptWts;
  myType = Nurbs3DTypes::Surface;       // Set type to surface
  myEvaluation = Nurbs3DTypes::BasisFuns;
  myInterpolation = Nurbs3DTypes::ChordLength;
  myDiameter = 1.0;
  myDecomposition = NULL;
  if (!isDataCorrect())                 // Check input data
    reset ();                           // Reset if faulty
}

/***   Nurbs3D : Copy constructor   ***********************/
//                                                        //
//  Initialize a copy from given NURBS element.           //
//                                                        //
/**********************************************************/

Nurbs3D::Nurbs3D (const Nurbs3D &nrb)
  :Primitive3D(nrb)
{
  myKnotsU = NULL;
  myKnotsV = NULL;
  myPoints = NULL;
  myWeights = NULL;
  myDecomposition = NULL;
  *this = nrb;
}

/***   ~Nurbs3D : Destructor   ****************************/
//                                                        //
//  Clean up data structures.                             //
//                                                        //
/**********************************************************/

Nurbs3D::~Nurbs3D (void)
{
  if (myKnotsU != NULL)
    delete myKnotsU;
  if (myKnotsV != NULL)
    delete myKnotsV;
  if (myPoints != NULL)
    delete myPoints;
  if (myWeights != NULL)
    delete myWeights;
  if (myDecomposition != NULL)
    delete myDecomposition;
}

/***   operator= : Assignment   ***************************/
//                                                        //
//  Assign data from given NURBS element.                 //
//                                                        //
/**********************************************************/

Nurbs3D& Nurbs3D::operator= (const Nurbs3D &nrb)
{
  reset ();

  myType = nrb.myType;
  myEvaluation = nrb.myEvaluation;
  myInterpolation = nrb.myInterpolation;
  myDiameter = nrb.myDiameter;
  if (myType == Nurbs3DTypes::Curve)
  {
    myKnotsU = nrb.myKnotsU->copy ();
    myPoints = nrb.myPoints->copy ();
    myWeights = nrb.myWeights->copy ();
  }
  else if (myType == Nurbs3DTypes::Surface)
  {
    myKnotsU = nrb.myKnotsU->copy ();
    myKnotsV = nrb.myKnotsV->copy ();
    myPoints = nrb.myPoints->copy ();
    myWeights = nrb.myWeights->copy ();
  }

  return *this;
}

/***   createDecomposition : Create decomposition   *******/
//                                                        //
//  Create a decomposition of this object and return      //
//  it as a list of triangles.                            //
//                                                        //
/**********************************************************/

Object3D* Nurbs3D::createDecomposition (void) const
{
  if (myDecomposition == NULL) 
  {
    Grid3D *decomp = new Grid3D;
    float  precision = getPrecision ();

    if (!isDataCorrect())
    {
      Report::warning ("[Nurbs3D::createDecomposition] data of NURBS not setup correctly!");
      return decomp;
    }

    if (myType == Nurbs3DTypes::Curve)
    {
      register int x;
      int        uc;
      Real       u, uMin, uMax, uInt;
      Vector3D   p1, p2;
      Nurbs3D    *newNurbs = new Nurbs3D (*this);

      newNurbs->getRangeU (uMin, uMax);	// Get knot vector ranges
      //n = newNurbs->myPoints->getCountU ();

      uc = (int) rint (100 * precision) + 1;
      uInt = (uMax - uMin) / (100 * precision);

      Cylinder3D *newCylinder = new Cylinder3D (myDiameter, Vector3D(0, 0, 0), Vector3D(1, 1, 1));
      newCylinder->setPrecision (getPrecision());

      Nurbs3DEvaluator eval (newNurbs);
      p2 = newNurbs->getPoint (0);
      for (x = 1, u = uMin+uInt; x < uc; x++, u += uInt)      // Calculate points
      {
	p1 = p2;
	p2 = eval.evaluate (u);
	newCylinder->setEnd (p2);
	newCylinder->setStart (p1);
	decomp->adoptObject(newCylinder);
      }
      delete newCylinder;

      // Set resolution of grid
      int size = (int)ceil(pow(decomp->countSubobject(),1.0/3.0));
      decomp->setResolution(size, size, size);
      
      // Cache only affects logical constness
      Nurbs3D* This = (Nurbs3D*)this;
      This->myDecomposition = new Shared3D(decomp);
      This->myDecomposition->computeBounds();
    }
    else if (myType == Nurbs3DTypes::Surface)
    {
      register int x, y;
      int      n, m, uc, vc;
      Real     u, v, uMin, uMax, vMin, vMax;
      Real     uLen = 0.0, vLen = 0.0, uInt, vInt;
      Vector3D p1, n1, p2, n2, p3, n3, p4, n4;
      Nurbs3D  *newNurbs = new Nurbs3D (*this);

      newNurbs->getRangeU (uMin, uMax);	// Get knot vector ranges
      newNurbs->getRangeV (vMin, vMax);
      n = newNurbs->getCtrlCountU ();   // Get control counts
      m = newNurbs->getCtrlCountV ();

      uc = (int) rint (100 * precision) + 1;        // Calculate number of points
      vc = (int) rint (100 * precision) + 1;
      uInt = (uMax - uMin) / (100 * precision);     // Calculate initial interval length
      vInt = (vMax - vMin) / (100 * precision);

      for (y = 0; y < m; y++)		// Calculate polygon length in u
      {
	p2 = newNurbs->getPoint (0, y);
	for (x = 1; x < n; x++)
        {
	  p1 = p2;
	  p2 = newNurbs->getPoint (x, y);
	  uLen += (p2 - p1).length ();
	}
      }
      uLen /= m;                          // Get average control polygon length
      for (x = 0; x < n; x++)		// Calculate polygon length in v
      {
	p2 = newNurbs->getPoint (x, 0);
	for (y = 1; y < m; y++)
	{
	  p1 = p2;
	  p2 = newNurbs->getPoint (x, y);
	  vLen += (p2 - p1).length ();
	}
      }
      vLen /= n;                          // Get average control polygon length

      if (uLen > vLen)                    // Adjust interval length to get "square" patches
      {
	vInt *= uLen / vLen;
	vc = (int) rint ((vMax - vMin) / vInt);
	vInt = (vMax - vMin) / vc++;
      }
      else
      {
	uInt *= vLen / uLen;
	uc = (int) rint ((uMax - uMin) / uInt);
	uInt = (uMax - uMin) / uc++;
      }

      Vector3D tu, tv;
      PtArray2D *pts = new PtArray2D (uc, vc), *nls = new PtArray2D (uc, vc);

      newNurbs->testDegeneration ();             // Test for degenerated edges

      Nurbs3DEvaluator eval (newNurbs);
      for (x = 0, u = uMin; x < uc; x++, u += uInt)      // Calculate points and normals
	for (y = 0, v = vMin; y < vc; y++, v += vInt)
	  eval.tangents (u, v, (*pts)[x][y], tu, tv, (*nls)[x][y]);

      for (x = 0; x < uc-1; x++)		// Calculate triangles
      {
	for (y = 0; y < vc-1; y++)
        {
	  p1 = pts->get (x, y); n1 = nls->get (x, y);
	  p2 = pts->get (x+1, y); n2 = nls->get (x+1, y);
	  p3 = pts->get (x, y+1); n3 = nls->get (x, y+1);
	  p4 = pts->get (x+1, y+1); n4 = nls->get (x+1, y+1);
	  if (p2 == p3)                      // Got degenerate points
	    continue;
	  if (p1 != p2 && p1 != p3)
	    decomp->adoptObject (new Triangle3D(p1, n1, p2, n2, p3, n3));
	  if (p4 != p3 && p4 != p2)
	    decomp->adoptObject (new Triangle3D(p4, n4, p3, n3, p2, n2)); 
	}
      }
      delete pts;
      delete nls;

      // Set resolution of grid
      int size = (int)ceil(pow(decomp->countSubobject(),1.0/3.0));
      decomp->setResolution(size, size, size);
      
      // Cache only affects logical constness
      Nurbs3D* This = (Nurbs3D*)this;
      This->myDecomposition = new Shared3D(decomp);
      This->myDecomposition->computeBounds();
    }
    else {
      decomp->computeBounds();
      return decomp;
    }
  }
  return myDecomposition->copy();
}

/***   normal : Calculate normal   ************************/
//                                                        //
//  Calculate the normal to the given point.              //
//                                                        //
/**********************************************************/

Vector3D Nurbs3D::normal (const Vector3D&) const
{
  return Vector3D(0,0,1); // !!!!!!! TO DO !!!!!!!
}

/***   make : Make a new NURBS   **************************/
//                                                        //
//  A new NURBS is created from the data specified by     //
//  "parameters". Actually all the work is done via       //
//  the class Nurbs3DAttr.                                //
//                                                        //
/**********************************************************/

Makeable* Nurbs3D::make (RCString &errMsg, const List<Value*> *parameters) const
{
  Nurbs3DTypes::EObject etype;

  checkParameterNumber (1);
  getParameter (1, RCString, stype);
  if (stype == "curve")
    etype = Nurbs3DTypes::Curve;
  else if (stype == "surface")
    etype = Nurbs3DTypes::Surface;
  else
  {
    errMsg = "unknown object type";
    return NULL;
  }

  Nurbs3D *newNurbs3D = new Nurbs3D (*this);
  newNurbs3D->setType (etype);
  return newNurbs3D;
}

/***   setSpecifier : Set a specifier   *******************/
//                                                        //
//  If the specifier is a Nurbs3DAttr, the attribute      //
//  is set. Else Object3D is left to handle it on it's    //
//  own.                                                  //
//                                                        //
/**********************************************************/

int Nurbs3D::setSpecifier (RCString &errMsg, Makeable *specifier)
{
  Nurbs3DAttr *attr = dynamic_cast<Nurbs3DAttr*>(specifier);
  if (attr)
  {
    attr->setAttribute (this);         // The Nurbs3DAttr object knows how to handle this

    delete attr;
    return 1;
  }

  return Primitive3D::setSpecifier (errMsg, specifier);     // Let popa do the rest...
}

/*
 * setAttribute : Set an attribute
 *
 * Used to set an attribute of a Nurbs3DPathAttr object.
 */

void Nurbs3D::setAttribute (Nurbs3DPathAttr *attr)
{
  if (attr != NULL)
    attr->adoptCurve (new Nurbs3D(*this));
}

/***   doComputeBounds : Compute bounding box   ***********/
//                                                        //
//  Computes the bounding box of the NURBS by expanding   //
//  "myBounds" by all control points.                     //
//                                                        //
/**********************************************************/

void Nurbs3D::doComputeBounds (void)
{
  register int i, j;
  int n, m;

  if (myType == Nurbs3DTypes::Curve)
  {
    n = myPoints->getCountU ();
    for (i = 0; i < n; i++)
      myBounds.expand (myPoints->get(i));
  }
  else if (myType == Nurbs3DTypes::Surface)
  {
    n = myPoints->getCountU ();
    m = myPoints->getCountV ();
    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
	myBounds.expand (myPoints->get(i, j));
  }
}

/***   doIntersect : Intersection routine   ***************/
//                                                        //
//                                                        //
//                                                        //
/**********************************************************/

bool Nurbs3D::doIntersect(Ray3D& ray)
{
  if (myDecomposition == NULL)
    delete Nurbs3D::createDecomposition();

  return myDecomposition->intersect(ray);
}

/***   initialize : Reset data   **************************/
//                                                        //
//  All data is reset.                                    //
//                                                        //
/**********************************************************/

void Nurbs3D::reset (void)
{
  if (myKnotsU != NULL)
  {
    delete myKnotsU;
    myKnotsU = NULL;
  }
  if (myKnotsV != NULL)
  {
    delete myKnotsV;
    myKnotsV = NULL;
  }
  if (myPoints != NULL)
  {
    delete myPoints;
    myPoints = NULL;
  }
  if (myWeights != NULL)
  {
    delete myWeights;
    myWeights = NULL;
  }
  myType = Nurbs3DTypes::None;
  myEvaluation = Nurbs3DTypes::BasisFuns;
  if (myDecomposition != NULL)         // Delete the decomposition
  {
    delete myDecomposition;
    myDecomposition = NULL;
  }
}

/***   initialize : Initialize curve   ********************/
//                                                        //
//  The NURBS element is initialized as curve.            //
//                                                        //
/**********************************************************/

void Nurbs3D::adoptParameters (Nurbs3DKnots *knotsU, Nurbs3DPoints *points, Nurbs3DWeights *weights)
{
  reset ();
  myKnotsU = knotsU;
  myPoints = points;
  myWeights = weights;
  myType = Nurbs3DTypes::Curve;

  if (!isDataCorrect())                // Check input data
    reset ();                          // Reset if faulty
}

/***   initialize : Initialize surface   ******************/
//                                                        //
//  The NURBS element is initialized as surface.          //
//                                                        //
/**********************************************************/

void Nurbs3D::adoptParameters (Nurbs3DKnots *knotsU, Nurbs3DKnots *knotsV, Nurbs3DPoints *points, 
			       Nurbs3DWeights *weights)
{
  reset ();
  myKnotsU = knotsU;
  myKnotsV = knotsV;
  myPoints = points;
  myWeights = weights;
  myType = Nurbs3DTypes::Surface;

  if (!isDataCorrect())                // Check input data
    reset ();                          // Reset if faulty
}

/***   transpose : Transpose element's data   *************/
//                                                        //
//  This function transposes the given element. u- and    //
//  v-data is swapped.                                    //
//                                                        //
/**********************************************************/

void Nurbs3D::transpose (void)
{
  Nurbs3DKnots *temp;

  temp = myKnotsU;                     // Transpose knot vectors
  myKnotsU = myKnotsV;
  myKnotsV = temp;
  myPoints->transpose ();              // Transpose control points
  myWeights->transpose ();             // Transpose weights
}

/***   getDegreeU : Get u-degree   ************************/
//                                                        //
//  The degree of the curve in u-direction is returned.   //
//                                                        //
/**********************************************************/

int Nurbs3D::getDegreeU (void) const
{
  if (myKnotsU != NULL)
    return myKnotsU->getDegree ();
  return 0;
}

/***   getDegreeV : Get u-degree   ************************/
//                                                        //
//  The degree of the curve in u-direction is returned.   //
//                                                        //
/**********************************************************/

int Nurbs3D::getDegreeV (void) const
{
  if (myKnotsV != NULL)
    return myKnotsV->getDegree ();
  return 0;
}

/***   GetKnotCountU : Get u-knot count   *****************/
//                                                        //
//  The number of knots in u-direction is returned.       //
//                                                        //
/**********************************************************/

int Nurbs3D::getKnotCountU (void) const
{
  if (myKnotsU != NULL)
    return myKnotsU->getCount ();
  return 0;
}

/***   GetKnotCountV : Get v-knot count   *****************/
//                                                        //
//  The number of knots in v-direction is returned.       //
//                                                        //
/**********************************************************/

int Nurbs3D::getKnotCountV (void) const
{
  if (myKnotsV != NULL)
    return myKnotsV->getCount ();
  return 0;
}

/***   getCtrlCountU : Get u-control count   **************/
//                                                        //
//  The number of control point in u-direction is         //
//  returned.                                             //
//                                                        //
/**********************************************************/

int Nurbs3D::getCtrlCountU (void) const
{
  if (myPoints != NULL)
    return myPoints->getCountU ();
  return 0;
}

/***   getCtrlCountV : Get v-control count   **************/
//                                                        //
//  The number of control point in v-direction is         //
//  returned.                                             //
//                                                        //
/**********************************************************/

int Nurbs3D::getCtrlCountV (void) const
{
  if (myPoints != NULL)
    return myPoints->getCountV ();
  return 0;
}

/***   getRangeU : Get range of u-curve   *****************/
//                                                        //
//  The range of the u-knot vector is returned.           //
//                                                        //
/**********************************************************/

void Nurbs3D::getRangeU (Real &first, Real &last) const
{
  if (myType != Nurbs3DTypes::Curve && myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3D::getRangeU] needs a valid object");
    return;
  }

  first = myKnotsU->getFirstKnot ();
  last = myKnotsU->getLastKnot ();
}

/***   getRangeV : Get range of v-curve   *****************/
//                                                        //
//  The range of the v-knot vector is returned.           //
//                                                        //
/**********************************************************/

void Nurbs3D::getRangeV (Real &first, Real &last) const
{
  if (myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3D::getRangeV] needs a surface to evaluate v-knot vector");
    return;
  }

  first = myKnotsV->getFirstKnot ();
  last = myKnotsV->getLastKnot ();
}

/***   getKnotU : Return u-knot   *************************/
//                                                        //
//  The desired u-knot value is returned.                 //
//                                                        //
/**********************************************************/

Real Nurbs3D::getKnotU (int i) const
{
  if (myKnotsU == NULL)
  {
    Report::warning ("[Nurbs3D::getPoint] needs a u-knot vector");
    return 0.0;
  }

  return myKnotsU->get (i);
}

/***   getKnotV : Return v-knot   *************************/
//                                                        //
//  The desired v-knot value is returned.                 //
//                                                        //
/**********************************************************/

Real Nurbs3D::getKnotV (int i) const
{
  if (myKnotsV == NULL)
  {
    Report::warning ("[Nurbs3D::getPoint] needs a v-knot vector");
    return 0.0;
  }

  return myKnotsV->get (i);
}

/***   getPoint : Return point   **************************/
//                                                        //
//  The desired control point is returned.                //
//                                                        //
/**********************************************************/

Vector3D Nurbs3D::getPoint (int i) const
{
  if (myType != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3D::getPoint] needs a curve");
    return Vector3D ();
  }

  return myPoints->get (i);
}

/***   getPoint : Return point   **************************/
//                                                        //
//  The desired control point is returned.                //
//                                                        //
/**********************************************************/

Vector3D Nurbs3D::getPoint (int u, int v) const
{
  if (myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3D::getPoint] needs a surface");
    return Vector3D ();
  }

  return myPoints->get (u, v);
}

/***   getWeight : Return weight   ************************/
//                                                        //
//  The weight associated to control point (i) is         //
//  returned.                                             //
//                                                        //
/**********************************************************/

Real Nurbs3D::getWeight (int i) const
{
  if (myType != Nurbs3DTypes::Curve)
  {
    Report::warning ("[Nurbs3D::getWeight] needs a curve");
    return 0.0;
  }

  return myWeights->get (i);
}

/***   getWeight : Return weight   ************************/
//                                                        //
//  The weight associated to control point (u, v) is      //
//  returned.                                             //
//                                                        //
/**********************************************************/

Real Nurbs3D::getWeight (int u, int v) const
{
  if (myType != Nurbs3DTypes::Surface)
  {
    Report::warning ("[Nurbs3D::getWeight] needs a surface");
    return 0.0;
  }

  return myWeights->get (u, v);
}

/***   isDataCorrect : Check data of element   ************/
//                                                        //
//  This function checks if all data is correct, i.e.     //
//  numbers of knots, points and weights are related      //
//  correctly.                                            //
//                                                        //
/**********************************************************/

bool Nurbs3D::isDataCorrect (void) const
{
  int du, dv, ku, kv, pu, pv, wu, wv;

  if (myType == Nurbs3DTypes::Curve)     // Check curve
  {
    du = myKnotsU->getDegree ();       // Get degrees
    ku = myKnotsU->getCount ();        // Get knot counts
    pu = myPoints->getCountU ();       // Get control point counts
    wu = myWeights->getCountU ();      // Get weight counts
    if (ku != du + pu - 1)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of knots and points in u-direction");
      return false;
    }
    if (pu != wu)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of points and weights in u-direction");
      return false;
    }
    return true;
  }
  if (myType == Nurbs3DTypes::Surface)   // Check surface
  {
    du = myKnotsU->getDegree ();       // Get degrees
    dv = myKnotsV->getDegree ();
    ku = myKnotsU->getCount ();        // Get knot counts
    kv = myKnotsV->getCount ();
    pu = myPoints->getCountU ();       // Get control point counts
    pv = myPoints->getCountV ();
    wu = myWeights->getCountU ();      // Get weight counts
    wv = myWeights->getCountV ();
    if (ku != du + pu - 1)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of knots and points in u-direction");
      return false;
    }
    if (pu != wu)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of points and weights in u-direction");
      return false;
    }
    if (kv != dv + pv - 1)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of knots and points in v-direction");
      return false;
    }
    if (pv != wv)
    {
      Report::warning ("[Nurbs3D::isDataCorrect] wrong number of points and weights in v-direction");
      return false;
    }
    return true;
  }
  return false;
}

/***   whatAmI : Return type of element   *****************/
//                                                        //
//  The type of the element is returned as a string.      //
//                                                        //
/**********************************************************/

const char* Nurbs3D::whatAmI (void)
{
  if (myType == Nurbs3DTypes::Curve)
    return "curve";
  else if (myType == Nurbs3DTypes::Surface)
    return "surface";
  return "";
}

/*
 * testDegeneration : Test for degenerate edges
 *
 * If all control points (4D) of one edge collapse to one point, 
 * the appropriate flag is set
 */

void Nurbs3D::testDegeneration (void)
{
  register int x;
  int n = myPoints->getCountU () - 1, m = myPoints->getCountV () - 1;

  myDegeneratedStartU = true;
  for (x = 0; myDegeneratedStartU && x < m; x++)
    if (myPoints->get(0, x) != myPoints->get(0, x+1))
      myDegeneratedStartU = false;
  myDegeneratedEndU = true;
  for (x = 0; myDegeneratedEndU && x < m; x++)
    if (myPoints->get(n, x) != myPoints->get(n, x+1))
      myDegeneratedEndU = false;
  myDegeneratedStartV = true;
  for (x = 0; myDegeneratedStartV && x < n; x++)
    if (myPoints->get(x, 0) != myPoints->get(x+1, 0))
      myDegeneratedStartV = false;
  myDegeneratedEndV = true;
  for (x = 0; myDegeneratedEndV && x < n; x++)
    if (myPoints->get(x, m) != myPoints->get(x+1, m))
      myDegeneratedEndV = false;

  if (myDegeneratedStartU || myDegeneratedEndU || myDegeneratedStartV || myDegeneratedEndV)
    myDegeneratedFlag = true;
}

void Nurbs3D::adoptKnotsU (Nurbs3DKnots *kts)
{
  if (myKnotsU != NULL)
    delete myKnotsU;
  myKnotsU = kts;
}

void Nurbs3D::adoptKnotsV (Nurbs3DKnots *kts)
{
  if (myKnotsV != NULL)
    delete myKnotsV;
  myKnotsV = kts;
}

void Nurbs3D::adoptPoints (Nurbs3DPoints *pts)
{
  if (myPoints != NULL)
    delete myPoints;
  myPoints = pts;
}

void Nurbs3D::adoptWeights (Nurbs3DWeights *wts)
{
  if (myWeights != NULL)
    delete myWeights;
  myWeights = wts;
}

Nurbs3DKnots* Nurbs3D::copyKnotsU (void) const
{
  if (myKnotsU != NULL)
    return new Nurbs3DKnots (*myKnotsU);
  return NULL;
}

Nurbs3DKnots* Nurbs3D::copyKnotsV (void) const
{
  if (myKnotsV != NULL)
    return new Nurbs3DKnots (*myKnotsV);
  return NULL;
}

Nurbs3DPoints* Nurbs3D::copyPoints (void) const
{
  if (myPoints != NULL)
    return new Nurbs3DPoints (*myPoints);
  return NULL;
}

Nurbs3DWeights* Nurbs3D::copyWeights (void) const
{
  if (myWeights != NULL)
    return new Nurbs3DWeights (*myWeights);
  return NULL;
}

Nurbs3DKnots* Nurbs3D::orphanKnotsU (void)
{
  Nurbs3DKnots *oldKnots = myKnotsU;
  myKnotsU = NULL;
  return oldKnots;
}

Nurbs3DKnots* Nurbs3D::orphanKnotsV (void)
{
  Nurbs3DKnots *oldKnots = myKnotsV;
  myKnotsV = NULL;
  return oldKnots;
}

Nurbs3DPoints* Nurbs3D::orphanPoints (void)
{
  Nurbs3DPoints *oldPoints = myPoints;
  myPoints = NULL;
  return oldPoints;
}

Nurbs3DWeights* Nurbs3D::orphanWeights (void)
{
  Nurbs3DWeights *oldWeights = myWeights;
  myWeights = NULL;
  return oldWeights;
}

//__________________________________________________________________ was: INLINES

Nurbs3DTypes::EObject Nurbs3D::getType() const
{
  return myType;
}

void Nurbs3D::setType(Nurbs3DTypes::EObject type)
{
  myType = type;
}

Nurbs3DTypes::EEvaluation Nurbs3D::getEvaluation() const
{
  return myEvaluation;
}

void Nurbs3D::setEvaluation(Nurbs3DTypes::EEvaluation type)
{
  myEvaluation = type;
}

Nurbs3DTypes::EInterpolation Nurbs3D::getInterpolation() const
{
  return myInterpolation;
}

void Nurbs3D::setInterpolation(Nurbs3DTypes::EInterpolation type)
{
  myInterpolation = type;
}

Real Nurbs3D::getDiameter() const
{
  return myDiameter;
}

void Nurbs3D::setDiameter(Real diameter)
{
  myDiameter = diameter;
}

bool Nurbs3D::isDegenerated() const
{
  return myDegeneratedFlag;
}

bool Nurbs3D::isDegeneratedFirstRowU() const
{
  return myDegeneratedStartU;
}

bool Nurbs3D::isDegeneratedLastRowU() const
{
  return myDegeneratedEndU;
}

bool Nurbs3D::isDegeneratedFirstRowV() const
{
  return myDegeneratedStartV;
}

bool Nurbs3D::isDegeneratedLastRowV() const
{
  return myDegeneratedEndV;
}

/***   copy : Copy this object   **************************/
//                                                        //
//  Return a copy of this object.                         //
//                                                        //
/**********************************************************/

Object3D* Nurbs3D::copy() const
{
  return new Nurbs3D(*this);
}

