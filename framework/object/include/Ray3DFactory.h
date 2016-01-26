/*
 * $RCSfile: Ray3DFactory.h,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: Ray3DFactory.h,v 1.5 1996/08/16 14:04:34 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Ray3DFactory_H
#define _Ray3DFactory_H

#include "booga/base/StaticInit.h"
#include "booga/base/Vector3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Texture3DContext.h"

//_________________________________________________________________ Ray3DFactory

class Ray3DFactory {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Ray3DFactory();                               // No constructor.

private:
  Ray3DFactory(const Ray3DFactory&);            // No copies.

public:
  virtual ~Ray3DFactory();                      // No destructor.

private:
  Ray3DFactory& operator=(const Ray3DFactory&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Ray3DFactory
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static Ray3D* createRay(const Vector3D& from, const Vector3D& dir);
  static Ray3D* createRayTo(const Vector3D& from, const Vector3D& to);

  static Ray3D* createSecondaryRay(const Vector3D& from, const Vector3D& dir, 
                                   const Ray3D* predecessor);
  static Ray3D* createSecondaryRayTo(const Vector3D& from, const Vector3D& to, 
                                     const Ray3D* predecessor);

  static Ray3D* createReflectedRay(const Texture3DContext& context, 
                                   Real factor);           // contribution 
  static Ray3D* createRefractedRay(const Texture3DContext& context,
                                   Real factor,            // contribution
                                   Real index);            // refraction index

  static long getNoOfPrimaryRays();
  static long getNoOfReflectedRays();
  static long getNoOfRefractedRays();

public:
  static void initClass(); 
  // do proper initialisation of static members
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static Real ourMinContribution;
  static int  ourMaxRayDepth;

private:
  // some statistics
  static long ourNoOfPrimaryRays;
  static long ourNoOfReflectedRays;
  static long ourNoOfRefractedRays;
};

//__________________________________________ ensure initialization of class Name

declareInitStatics(Ray3DFactory);

#endif // _Ray3DFactory_H

