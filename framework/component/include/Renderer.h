/*
 * $RCSfile: Renderer.h,v $
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: Renderer.h,v 1.15 1996/09/13 08:06:15 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Renderer_H
#define _Renderer_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/List.h"
#include "booga/component/Operation3DTo2D.h"

class Camera3D;
class AmbientLight;
class DirectedLight;

//_____________________________________________________________________ Renderer

class Renderer : public Operation3DTo2D {
declareRTTI(Renderer);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Renderer();
private:
  Renderer(const Renderer&);  // No copies.
  
public:
  virtual ~Renderer();

private:
  Renderer& operator=(const Renderer&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Renderer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera3D* camera);
  // Set camera to use for rendering
  void deleteCamera();
  const Camera3D* getCamera() const;

  // Handling of light sources to use for rendering
  // Ambient lights :
  void adoptAmbientLightSources(List<AmbientLight*>* lightSources);
  void deleteAmbientLightSources();
  const List<AmbientLight*>* getAmbientLightSources() const;

  // Directed lights :
  void adoptDirectedLightSources(List<DirectedLight*>* lightSources);
  void deleteDirectedLightSources();
  const List<DirectedLight*>* getDirectedLightSources() const;
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  // Collects all the light sources (ambient and directed) and the cameras
  // available in the world. If the world contains no light source and/or 
  // camera the rendering process is aborted.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Camera3D* myCamera; 
  bool myHasAdoptedCamera;
  
  List<AmbientLight*>* myAmbientLightSources;
  bool myHasAdoptedAmbientLightSources;

  List<DirectedLight*>* myDirectedLightSources;
  bool myHasAdoptedDirectedLightSources;
};

//______________________________________________________________________ INLINES

inline const Camera3D* Renderer::getCamera() const
{
  return myCamera;
}

inline const List<AmbientLight*>* Renderer::getAmbientLightSources() const
{
  return myAmbientLightSources;
}

inline const List<DirectedLight*>* Renderer::getDirectedLightSources() const
{
  return myDirectedLightSources;
}

#endif // _Renderer_H
