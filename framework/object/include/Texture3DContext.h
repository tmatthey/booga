/*
 * $RCSfile: Texture3DContext.h,v $
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
 *  $Id: Texture3DContext.h,v 1.19 1996/12/04 08:54:21 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Texture3DContext_H
#define _Texture3DContext_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"
#include "booga/base/Color.h"
#include "booga/base/List.h"
#include "booga/object/Transform3D.h"

class World3D;
class Object3D;
class AmbientLight;
class DirectedLight;
class Ray3D;

//_____________________________________________________________ Texture3DContext

class Texture3DContext {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Texture3DContext();
  Texture3DContext(const Texture3DContext& context);  

public:
  ~Texture3DContext();

private:
  Texture3DContext& operator=(const Texture3DContext&); // No assignment.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// World, Object, Lights
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const World3D* getWorld() const;
  void setWorld(const World3D* world);

  const List<AmbientLight*>* getAmbientLightSources() const;
  void setAmbientLightSources(const List<AmbientLight*>* lightSources);

  const List<DirectedLight*>* getDirectedLightSources() const;
  void setDirectedLightSources(const List<DirectedLight*>* lightSources);

  const Object3D* getObject() const;
  void setObject(const Object3D* object);

private:
  const World3D* myWorld;
  const Object3D* myObject;                                 // in OCS !
  const List<AmbientLight*>* myAmbientLightSources;         // in WCS !
  const List<DirectedLight*>* myDirectedLightSources;       // in WCS !

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Texturing, Lightning
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getColor() const;
  void setColor(const Color& color);

  const Color& getIllumination() const;
  void setIllumination(const Color& color);

  const Vector3D& getLightDirection() const;
  void setLightDirection(const Vector3D& direction);

  Real getLightDistance() const;
  void setLightDistance(Real dist);


private:
  Color myColor;
  Color myIllumination;
  Vector3D myLightDirection; // Vector from Object to Light
  Real myLightDistance;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Incidence position in world coordinate systems
//
// When a ray is set explicitely, this is supposed to invalidate
// a implicitley (during initialization) or explicitely set
// incidence position.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Vector3D& getIncidencePosition() const;
  void setIncidencePosition(const Vector3D& position);

private:
  Vector3D myIncidencePosition;    // We look from this position (WCS)
  bool myIsIncidencePositionValid; // Extract from ray if invalid. 
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Incident ray in world coordinate systems
//
// When no ray is set, a ray will be created during a call to 
// getIncidenceRay(). This ray is cached for subsequent calls.
// This cache will be invalid, if incidencePosition is set 
// explicitely. 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Ray3D* getIncidenceRay() const; 
  void setIncidenceRay(const Ray3D* ray);
   
private:
  const Ray3D* myIncidenceRay;
  bool myIsCreatedIncidenceRay;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Hit position and normal in different coordinate systems
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  //
  // WCS: World Coordinate System (OCS and applied modelling transformations)
  // OCS: Object Coordinate System
  // TCS: Texture Coordinate System (OCS and applied texture transformations)
  //
  void setOCS2WCS(const Transform3D& transform);
  const Transform3D& getOCS2WCS() const;

  void setOCS2TCS(const Transform3D& transform);
  const Transform3D& getOCS2TCS() const;

  const Vector3D& getPositionWCS() const;
  const Vector3D& getPositionOCS() const;
  const Vector3D& getPositionTCS() const;
  void setPositionWCS(const Vector3D& position);
  void setPositionOCS(const Vector3D& position);
  void setPositionTCS(const Vector3D& position);

  const Vector3D& getNormalWCS() const;
  const Vector3D& getNormalOCS() const;
  const Vector3D& getNormalTCS() const;
  void setNormalWCS(const Vector3D& normal);
  void setNormalOCS(const Vector3D& normal);
  void setNormalTCS(const Vector3D& normal);
  
private:
  // Transformations.
  Transform3D myOCS2WCS;
  Transform3D myOCS2TCS;
  
  // World coordinate system.
  Vector3D myPositionWCS;
  Vector3D myNormalWCS;

  // Object coordinate system. (Cached)
  Vector3D myPositionOCS;
  Vector3D myNormalOCS;

  // Texture coordinate system. (Cached)
  Vector3D myPositionTCS;
  Vector3D myNormalTCS;

  // Cache handling.
  bool myIsPositionOCSValid;
  bool myIsNormalOCSValid;
  bool myIsPositionTCSValid;
  bool myIsNormalTCSValid;
};

//______________________________________________________________________ INLINES

inline const World3D* Texture3DContext::getWorld() const
{
  return myWorld;
}

inline void Texture3DContext::setWorld(const World3D* world)
{
  myWorld = world;
}

inline const List<AmbientLight*>* Texture3DContext::getAmbientLightSources() const
{
  return myAmbientLightSources;
}

inline void Texture3DContext::setAmbientLightSources(const List<AmbientLight*>* lightSources)
{
  myAmbientLightSources = lightSources;
}

inline const List<DirectedLight*>* Texture3DContext::getDirectedLightSources() const
{
  return myDirectedLightSources;
}

inline void Texture3DContext::setDirectedLightSources(const List<DirectedLight*>* lightSources)
{
  myDirectedLightSources = lightSources;
}

inline const Object3D* Texture3DContext::getObject() const
{
  return myObject;
}

inline void Texture3DContext::setObject(const Object3D* object)
{
  myObject = object;
}

inline const Color& Texture3DContext::getColor() const
{
  return myColor;
}

inline void Texture3DContext::setColor(const Color& color)
{
  myColor = color;
}

inline const Color& Texture3DContext::getIllumination() const
{
  return myIllumination;
}

inline void Texture3DContext::setIllumination(const Color& color)
{
  myIllumination = color;
}
  
inline const Vector3D& Texture3DContext::getLightDirection() const
{
  return myLightDirection;
}

inline void Texture3DContext::setLightDirection(const Vector3D& direction)
{
  myLightDirection = direction;
}

inline Real Texture3DContext::getLightDistance() const
{
  return myLightDistance;
}

inline void Texture3DContext::setLightDistance(Real dist)
{
  myLightDistance = dist;
}

inline const Transform3D& Texture3DContext::getOCS2WCS() const
{
  return myOCS2WCS;
}

inline const Transform3D& Texture3DContext::getOCS2TCS() const
{
  return myOCS2TCS;
}

#endif // _Texture3DContext_H
