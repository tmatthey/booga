/*
 * $RCSfile: Ray3DFactory.C,v $
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
 *  $Id: Ray3DFactory.C,v 1.12 1996/08/30 12:14:44 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/Texture3DContext.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"

//_________________________________________________________________ Ray3DFactory

implementInitStatics(Ray3DFactory);

Real Ray3DFactory::ourMinContribution;
int  Ray3DFactory::ourMaxRayDepth;
long Ray3DFactory::ourNoOfPrimaryRays;
long Ray3DFactory::ourNoOfReflectedRays;
long Ray3DFactory::ourNoOfRefractedRays;

void Ray3DFactory::initClass()
{
  Ray3DFactory::ourMinContribution   = 0.05;
  Ray3DFactory::ourMaxRayDepth       = 4;
  Ray3DFactory::ourNoOfPrimaryRays   = 0;
  Ray3DFactory::ourNoOfReflectedRays = 0;
  Ray3DFactory::ourNoOfRefractedRays = 0;
}

Ray3D* Ray3DFactory::createRay(const Vector3D& from, const Vector3D& dir)
{
  ourNoOfPrimaryRays++;
  return new Ray3D(from, dir);
}

Ray3D* Ray3DFactory::createRayTo(const Vector3D& from, const Vector3D& to)
{
  ourNoOfPrimaryRays++;
  return new Ray3D(from, to-from);
}

Ray3D* Ray3DFactory::createSecondaryRay(const Vector3D& from, const Vector3D& dir, 
                                        const Ray3D* predecessor)
{
  //
  // Ray depth limit reached?
  //
  if (predecessor->myDepth > ourMaxRayDepth)
    return NULL;

  ourNoOfPrimaryRays++;

  Ray3D* ray = new Ray3D(from, dir);
  ray->myDepth = predecessor->myDepth+1;

  return ray;
}                                        

Ray3D* Ray3DFactory::createSecondaryRayTo(const Vector3D& from, const Vector3D& to, 
                                          const Ray3D* predecessor)
{
  //
  // Ray depth limit reached?
  //
  if (predecessor->myDepth > ourMaxRayDepth)
    return NULL;

  ourNoOfPrimaryRays++;

  Ray3D* ray = new Ray3D(from, to-from);
  ray->myDepth = predecessor->myDepth+1;

  return ray;
}                                          

Ray3D* Ray3DFactory::createReflectedRay(const Texture3DContext& context, Real factor)
{
  const Ray3D* incRay = context.getIncidenceRay();
  
  if (incRay->myDepth > ourMaxRayDepth)
    return NULL;

  Real contribution = factor * incRay->myContribution;
  if (contribution < ourMinContribution)
    return NULL;

  //
  // using Heckbert's method to compute reflected ray direction
  // R = I + 2*c1*N, where
  //    I  = incident direction (unit)
  //    N  = plane normal (unit)
  //    c1 = cos (-I*N) (= cosAlpha)
  //
  Vector3D normal = context.getNormalWCS();
  Real cosAlpha = -incRay->myDirection^normal;

  if (cosAlpha < 0) {
    //
    // Hit the 'backside' of a surface -- flip the normal.
    //
    cosAlpha = -cosAlpha;
    normal = -normal;
  }

  Ray3D* ray = new Ray3D(context.getPositionWCS(), incRay->myDirection + 2*cosAlpha*normal);

  // Set new rays parameters
  ray->myContribution = contribution;
  ray->myDepth = incRay->myDepth + 1;
    
  ourNoOfReflectedRays++; 
    
  return ray;
}

Ray3D* Ray3DFactory::createRefractedRay(const Texture3DContext& context, Real factor, Real index)
{
  const Ray3D* incRay = context.getIncidenceRay();
  
  if (incRay->myDepth > ourMaxRayDepth)
    return NULL;

  Real contribution = factor * incRay->myContribution;
  if (contribution < ourMinContribution)
    return NULL;

  //
  // using Heckbert's method to compute refracted ray direction
  // T = n*I + (n*c1 - c2)*N, where
  //    I  = incident ray direction (unit)
  //    N  = plane normal (unit)
  //    n  = index of refraction
  //    c1 = cos(-I*N) (= cosAlpha)
  //    c2 = sqrt(1-n^2*(1-c1^2))
  //
  Vector3D normal = context.getNormalWCS();
  Real cosAlpha = -(incRay->myDirection^normal);

  if (cosAlpha < 0) {
    //
    // Hit the 'backside' of a surface -- flip the normal.
    //
    cosAlpha = -cosAlpha;
    normal = -normal;
  }
    
  Real c2 = 1-sqr(index)*(1-sqr(cosAlpha));

  if (c2 < EPSILON)
    //
    // Total internal reflection. Ignored. !!!!!!!!!!!!
    //
    return NULL; // <------
    
  Ray3D* ray = new Ray3D(context.getPositionWCS(), incRay->myDirection*index + (index*cosAlpha - sqrt(c2))*normal);

  // Set new rays parameters
  ray->myContribution = contribution;
  ray->myDepth = incRay->myDepth + 1;

  ourNoOfRefractedRays++; 
    
  return ray;
}

long Ray3DFactory::getNoOfPrimaryRays()   
{ 
  return ourNoOfPrimaryRays;   
}

long Ray3DFactory::getNoOfReflectedRays() 
{ 
  return ourNoOfReflectedRays; 
}

long Ray3DFactory::getNoOfRefractedRays() 
{ 
  return ourNoOfRefractedRays; 
}

