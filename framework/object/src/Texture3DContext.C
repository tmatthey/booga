/*
 * $RCSfile: Texture3DContext.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Texture3DContext.C,v 1.17 1996/12/04 08:54:20 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Texture3DContext.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"

//_____________________________________________________________ Texture3DContext

Texture3DContext::Texture3DContext()
{
  myWorld  = NULL;
  myObject = NULL;
  myAmbientLightSources  = NULL;
  myDirectedLightSources = NULL;

  myIncidenceRay             = NULL;
  myIsCreatedIncidenceRay    = false;
  myIsIncidencePositionValid = true;

  myIsPositionOCSValid = false;
  myIsNormalOCSValid   = false;
  myIsPositionTCSValid = false;
  myIsNormalTCSValid   = false;
}

Texture3DContext::Texture3DContext(const Texture3DContext& context)
{
  myWorld  = context.myWorld;
  myObject = context.myObject;
  myAmbientLightSources  = context.myAmbientLightSources;
  myDirectedLightSources = context.myDirectedLightSources;
  myColor = context.myColor;
  myIllumination = context.myIllumination;
  myLightDirection = context.myLightDirection;
  myLightDistance = context.myLightDistance;
  myIncidencePosition = context.myIncidencePosition;
  myIsIncidencePositionValid = context.myIsIncidencePositionValid;
  myIsCreatedIncidenceRay = false;        // We didn't create the ray here!
  myIncidenceRay = context.myIncidenceRay;
  myOCS2WCS = context.myOCS2WCS;
  myOCS2TCS = context.myOCS2TCS;
  myPositionWCS = context.myPositionWCS;
  myNormalWCS = context.myNormalWCS;
  myPositionOCS = context.myPositionOCS;
  myNormalOCS = context.myNormalOCS;
  myPositionTCS = context.myPositionTCS;
  myNormalTCS = context.myNormalTCS;
  myIsPositionOCSValid = context.myIsPositionOCSValid;
  myIsNormalOCSValid = context.myIsNormalOCSValid;
  myIsPositionTCSValid = context.myIsPositionTCSValid;
  myIsNormalTCSValid = context.myIsNormalTCSValid;
}

Texture3DContext::~Texture3DContext()
{
  if (myIsCreatedIncidenceRay)
    // Const cast: If ray is created by this class, it may
    //             be deleted by this class.
    delete (Ray3D*) myIncidenceRay;
}

const Vector3D& Texture3DContext::getIncidencePosition() const
{
  // Logical constness: 
  // handling of cache does not affect constness of object
  Texture3DContext* This = (Texture3DContext*) this;
  // Extract incidence position from ray, if position is invalid
  if (!myIsIncidencePositionValid && myIncidenceRay != NULL) {
    This->myIncidencePosition = myIncidenceRay->getOrigin();
    This->myIsIncidencePositionValid = true;
  }
  
  return myIncidencePosition;
}

void Texture3DContext::setIncidencePosition(const Vector3D& position)
{
  myIncidencePosition = position;
  myIsIncidencePositionValid = true;
  
  if (myIsCreatedIncidenceRay)
    // Const cast: If ray is created by this class, it may
    //             be deleted by this class.
    delete (Ray3D*) myIncidenceRay;
  myIncidenceRay = NULL;
}

const Ray3D* Texture3DContext::getIncidenceRay() const
{
  // Logical constness: 
  // handling of cache does not affect constness of object
  Texture3DContext* This = (Texture3DContext*) this;

  if (myIncidenceRay == NULL) {
    This->myIncidenceRay = Ray3DFactory::createRayTo(getIncidencePosition(), getPositionWCS());
    This->myIsCreatedIncidenceRay = true;
  }
  
  return myIncidenceRay;
}

void Texture3DContext::setIncidenceRay(const Ray3D* ray)
{
  // If myIncidenceRay is cached, delete it.
  if (ray != NULL && myIsCreatedIncidenceRay)
    // Const cast: If ray is created by this class, it may
    //             be deleted by this class.
    delete (Ray3D*) myIncidenceRay;
  
  // Set new incidence ray. This invalidates prior incidence position.
  myIncidenceRay = ray;
  myIsCreatedIncidenceRay    = false;
  myIsIncidencePositionValid = false;
}

void Texture3DContext::setOCS2WCS(const Transform3D& transform)
{
  myIsPositionOCSValid = false;
  myIsNormalOCSValid   = false;
  
  myOCS2WCS = transform;
}

void Texture3DContext::setOCS2TCS(const Transform3D& transform)
{
  myIsPositionTCSValid = false;
  myIsNormalTCSValid   = false;
  
  myOCS2TCS = transform;
}

const Vector3D& Texture3DContext::getPositionWCS() const
{
  return myPositionWCS;
}

const Vector3D& Texture3DContext::getPositionOCS() const
{
  if (!myIsPositionOCSValid) {
    ((Texture3DContext*)this)->myPositionOCS = myOCS2WCS.invTransformAsPoint(myPositionWCS);
    ((Texture3DContext*)this)->myIsPositionOCSValid = true;
  }

  return myPositionOCS;
}

const Vector3D& Texture3DContext::getPositionTCS() const
{
  if (!myIsPositionTCSValid) {
    ((Texture3DContext*)this)->myPositionTCS = myOCS2TCS.invTransformAsPoint(getPositionOCS());
    ((Texture3DContext*)this)->myIsPositionTCSValid = true;
  }
  
  return myPositionTCS;
}

void Texture3DContext::setPositionWCS(const Vector3D& position)
{
  myPositionWCS = position;

  myIsPositionOCSValid = false;
  myIsPositionTCSValid = false;
}

void Texture3DContext::setPositionOCS(const Vector3D& position)
{
  myIsPositionOCSValid = true;
  myIsPositionTCSValid = false;
  myPositionOCS = position;
  myPositionWCS = myOCS2WCS.transformAsPoint(myPositionOCS);
}

void Texture3DContext::setPositionTCS(const Vector3D& position)
{
  myPositionTCS = position;
  myIsPositionTCSValid = true;

  myPositionOCS = myOCS2TCS.transformAsPoint(myPositionTCS);
  myIsPositionOCSValid = true;
  myPositionWCS = myOCS2WCS.transformAsPoint(myPositionOCS);
}

const Vector3D& Texture3DContext::getNormalWCS() const
{
  return myNormalWCS;
}

const Vector3D& Texture3DContext::getNormalOCS() const
{
  if (!myIsNormalOCSValid) {
    ((Texture3DContext*)this)->myNormalOCS = myOCS2WCS.invTransformAsNormal(myNormalWCS);
    ((Texture3DContext*)this)->myIsNormalOCSValid = true;
  }

  return myNormalOCS;
}

const Vector3D& Texture3DContext::getNormalTCS() const
{
  if (!myIsNormalTCSValid) {
    ((Texture3DContext*)this)->myNormalTCS = myOCS2TCS.invTransformAsNormal(getNormalOCS());
    ((Texture3DContext*)this)->myIsNormalTCSValid = true;
  }

  return myNormalTCS;
}

void Texture3DContext::setNormalWCS(const Vector3D& normal)
{
  myNormalWCS = normal;
  myIsNormalOCSValid = false;
  myIsNormalTCSValid = false;
}

void Texture3DContext::setNormalOCS(const Vector3D& normal)
{
  myNormalOCS = normal;
  myIsNormalOCSValid = true;

  myNormalWCS = myOCS2WCS.transformAsNormal(myNormalOCS);
  myIsNormalTCSValid = false;
}

void Texture3DContext::setNormalTCS(const Vector3D& normal)
{
  myNormalTCS = normal;
  myIsNormalTCSValid = true;

  myPositionOCS = myOCS2TCS.transformAsNormal(myNormalTCS);
  myIsNormalOCSValid = true;
  myNormalWCS = myOCS2WCS.transformAsNormal(myNormalOCS);
}
