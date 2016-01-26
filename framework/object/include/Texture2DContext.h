/*
 * $RCSfile: Texture2DContext.h,v $
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
 *  $Id: Texture2DContext.h,v 1.5 1996/08/30 12:21:25 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Texture2DContext_H
#define _Texture2DContext_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector2D.h"
#include "booga/base/Color.h"
#include "booga/base/List.h"
#include "booga/object/Transform2D.h"

class World2D;
class Object2D;

//_____________________________________________________________ Texture2DContext

class Texture2DContext {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Texture2DContext();
  // Texture2DContext(const Texture3DContext&);             // Use default version.

public:
  // ~Texture2DContext();                                   // Use default version.

public:
  // Texture2DContext& operator=(const Texture3DContext&);  // Use default version.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// World, Object
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const World2D* getWorld() const;
  void setWorld(World2D* world);

  const Object2D* getObject() const;
  void setObject(Object2D* object);

private:
  World2D* myWorld;
  Object2D* myObject;                                 // in OCS !

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Texturing, Lightning
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const Color& getColor() const;
  void setColor(const Color& color);

private:
  Color myColor;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Position and normal in different coordinate systems
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  //
  // WCS: World Coordinate System (OCS and applied modelling transformations)
  // OCS: Object Coordinate System
  // TCS: Texture Coordinate System (OCS and applied texture transformations)
  //
  void setOCS2WCS(const Transform2D& transform);
  const Transform2D& getOCS2WCS() const;

  void setOCS2TCS(const Transform2D& transform);
  const Transform2D& getOCS2TCS() const;

  const Vector2D& getPositionWCS() const;
  const Vector2D& getPositionOCS() const;
  const Vector2D& getPositionTCS() const;
  void setPositionWCS(const Vector2D& position);
  void setPositionOCS(const Vector2D& position);
  void setPositionTCS(const Vector2D& position);

private:
  // Transformations.
  Transform2D myOCS2WCS;
  Transform2D myOCS2TCS;
  
  // World coordinate system.
  Vector2D myPositionWCS;

  // Object coordinate system. (Cached)
  Vector2D myPositionOCS;

  // Texture coordinate system. (Cached)
  Vector2D myPositionTCS;

  // Cache handling.
  bool myIsPositionOCSValid;
  bool myIsPositionTCSValid;
};

//______________________________________________________________________ INLINES

inline const World2D* Texture2DContext::getWorld() const
{
  return myWorld;
}

inline void Texture2DContext::setWorld(World2D* world)
{
  myWorld = world;
}

inline const Object2D* Texture2DContext::getObject() const
{
  return myObject;
}

inline void Texture2DContext::setObject(Object2D* object)
{
  myObject = object;
}

inline const Color& Texture2DContext::getColor() const
{
  return myColor;
}

inline void Texture2DContext::setColor(const Color& color)
{
  myColor = color;
}

inline const Transform2D& Texture2DContext::getOCS2WCS() const
{
  return myOCS2WCS;
}

inline const Transform2D& Texture2DContext::getOCS2TCS() const
{
  return myOCS2TCS;
}

#endif // _Texture2DContext_H
