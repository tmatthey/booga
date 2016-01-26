/*
 * $RCSfile: Nurbs3D.h,v $
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
 *  $Id: Nurbs3D.h,v 1.11 1996/09/13 08:05:06 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3D_H
#define _Nurbs3D_H

#include "booga/object/Primitive3D.h"
#include "booga/nurbs/Nurbs3DTypes.h"
#include "booga/nurbs/Nurbs3DKnots.h"
#include "booga/nurbs/Nurbs3DPoints.h"
#include "booga/nurbs/Nurbs3DWeights.h"

class Nurbs3DPathAttr;       // Forward declaration

//______________________________________________________________________ Nurbs3D
/*
 * Nurbs3D is the basic class for handling NURBS curves and surfaces.
 * A unified data structure is provided which is used by specialized classes
 * like Nurbs3DEvaluator (curve / surface interrogation), ...
 */ 

class Nurbs3D : public Primitive3D {
declareRTTI(Nurbs3D);
// enable RTTI support

  friend class Nurbs3DEvaluator;
  friend class Nurbs3DManipulator;
  friend class Nurbs3DCreator;

//   enum ENrbType { Curve, Surface };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Nurbs3D();
  Nurbs3D(Exemplar exemplar);
  Nurbs3D(Nurbs3DKnots *adoptKtsU, Nurbs3DPoints *adoptPts, Nurbs3DWeights *adoptWts);
  Nurbs3D(Nurbs3DKnots *adoptKtsU, Nurbs3DKnots *kntV, Nurbs3DPoints *adoptPts,
	   Nurbs3DWeights *adoptWts);
  Nurbs3D(const Nurbs3D& nrb);

public:
  virtual ~Nurbs3D();
  
public:
  Nurbs3D& operator=(const Nurbs3D &nrb);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Nurbs3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void reset();
  virtual void rebuild() {}

  virtual void adoptParameters(Nurbs3DKnots *knotsU, Nurbs3DPoints *points,
				Nurbs3DWeights *weights);
  virtual void adoptParameters(Nurbs3DKnots *knotsU, Nurbs3DKnots *knotsV,
				Nurbs3DPoints *points, Nurbs3DWeights *weights);

  virtual void transpose();                         // Transpose the data

  virtual int  getDegreeU() const;                  // Return degrees in u-direction
  virtual int  getDegreeV() const;                  // Return degrees in v-direction
  virtual int  getKnotCountU() const;               // Get number of u-knots
  virtual int  getKnotCountV() const;               // Get number of v-knots
  virtual int  getCtrlCountU() const;               // Get number of control points and weights in u-dir
  virtual int  getCtrlCountV() const;               // Get number of control points and weights in v-dir
  virtual void getRangeU(Real &first, Real &last) const;     // Get first and last u-knot
  virtual void getRangeV(Real &first, Real &last) const;     // Get first and last v-knot

  virtual Real     getKnotU(int i) const;               // Get desired knot of u-knot vector
  virtual Real     getKnotV(int i) const;               // Get desired knot of v-knot vector
  virtual Vector3D getPoint(int i) const;               // Get desired control point
  virtual Vector3D getPoint(int u, int v) const;        // Get desired control point
  virtual Real     getWeight(int i) const;              // Get desired weight
  virtual Real     getWeight(int u, int v) const;       // Get desired weight
  
  virtual void adoptKnotsU(Nurbs3DKnots *kts);
  virtual void adoptKnotsV(Nurbs3DKnots *kts);
  virtual void adoptPoints(Nurbs3DPoints *pts);
  virtual void adoptWeights(Nurbs3DWeights *wts);
  virtual Nurbs3DKnots   *copyKnotsU() const;
  virtual Nurbs3DKnots   *copyKnotsV() const;
  virtual Nurbs3DPoints  *copyPoints() const;
  virtual Nurbs3DWeights *copyWeights() const;
  virtual Nurbs3DKnots   *orphanKnotsU();
  virtual Nurbs3DKnots   *orphanKnotsV();
  virtual Nurbs3DPoints  *orphanPoints();
  virtual Nurbs3DWeights *orphanWeights();

  virtual Nurbs3DTypes::EObject getType() const;
  virtual void setType(Nurbs3DTypes::EObject type);
  virtual Nurbs3DTypes::EEvaluation getEvaluation() const;
  virtual void setEvaluation(Nurbs3DTypes::EEvaluation type);
  virtual Nurbs3DTypes::EInterpolation getInterpolation() const;
  virtual void setInterpolation(Nurbs3DTypes::EInterpolation type);
  virtual Real getDiameter() const;
  virtual void setDiameter(Real diameter);
  
  virtual bool isDataCorrect() const;    // Test data for correctness
  virtual const char *whatAmI();          // Return type of object(curve / surface) in string

  virtual void testDegeneration();
  virtual bool isDegenerated() const;
  virtual bool isDegeneratedFirstRowU() const;
  virtual bool isDegeneratedLastRowU() const;
  virtual bool isDegeneratedFirstRowV() const;
  virtual bool isDegeneratedLastRowV() const;

  virtual void setAttribute(Nurbs3DPathAttr *attr);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TPrimitive
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* createDecomposition() const;
  virtual Vector3D normal(const Vector3D& point) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class BOOGAObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual void doComputeBounds();
private:
  virtual bool doIntersect(Ray3D& ray);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString &errMsg, const List<Value*> *parameters) const;
  virtual int setSpecifier(RCString &errMsg, Makeable *specifier);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Nurbs3DKnots   *myKnotsU, *myKnotsV;    // Knot vectors
  Nurbs3DPoints  *myPoints;               // Control points
  Nurbs3DWeights *myWeights;              // Associated weights

  Nurbs3DTypes::EObject myType;                    // Type of object
  Nurbs3DTypes::EEvaluation myEvaluation;          // Type of evaluation
  Nurbs3DTypes::EInterpolation myInterpolation;    // Type of interpolation
  Real myDiameter;                                 // Diameter of curve

  bool myDegeneratedFlag;
  bool myDegeneratedStartU;
  bool myDegeneratedEndU;
  bool myDegeneratedStartV;
  bool myDegeneratedEndV;
  
  Object3D *myDecomposition;
  // The decomposition ist cached for each nurbs object.
};

#endif // _Nurbs3D_H

