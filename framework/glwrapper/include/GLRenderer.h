/*
 * $RCSfile: GLRenderer.h,v $ 
 *
 * Copyright (C) 1994-96, Bernhard Buehlmann <buhlmann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: GLRenderer.h,v 1.25 1998/05/20 13:01:54 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLRenderer_H
#define _GLRenderer_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Renderer.h"

class LightSource;
class Triangle3D;
class TriangleList3D;
class Polygon3D;
class Text3D;
class Box3D;
class Sphere3D;
class Cylinder3D;
class Cone3D;
class Torus3D;
class Line3D;
class LevelOfDetail3D;
class Point3D;

//___________________________________________________________________ GLRenderer

class GLRenderer : public Renderer {
declareRTTI(GLRenderer);
// enable RTTI support

public:
enum RenderingQuality {
  BOUNDING_BOX         = 1,
  WIREFRAME            = 2,
  WIREFRAME_FLAT       = 3,
  WIREFRAME_GOURAUD    = 4,
  SOLID_FLAT           = 5,
  SOLID_GOURAUD        = 6,
  SOLID_GOURAUD_TRANSP = 7
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLRenderer();
private:
  GLRenderer(const GLRenderer&);             // No copies.

public:
  // virtual ~GLRenderer();                  // Use default version.

private:
  GLRenderer& operator=(const GLRenderer&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLRenderer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void generateWorld(bool enable);
  // Indicates if the call to execute() creates a new world object.
  //
  // The GLRenderer will always display the scene in the framebuffer. If 
  // this option is enable (default behaviour), the content of the 
  // framebuffer is copied to a pixmap, the pixmap is added to a new
  // world object and the world is returned as a result of the call to 
  // the GLRenderer::execute() method.

  RenderingQuality getRenderingQuality() const;
  void setRenderingQuality(RenderingQuality quality);
  
  Real getMaxTimeInBackbuffer() const;
  void setMaxTimeInBackbuffer(Real maxTimeInBackbuffer);
  // Rendering in back buffer mode is much faster then using the front 
  // buffer. For interactive applications, one has to give visual feedback 
  // to the user as soon as possible. For large scenes rendered into the 
  // back buffer this is not possible, so we have to be able to limit the 
  // rendering time in back buffer mode and switch automatically to the 
  // front buffer to conclude the rendering of the scene when the maximum 
  // back buffer time is exceeded.

  int getFrameRate() const;
  void setFrameRate(int frameRate);
  // For interactive applications a high frame rate is essential. But 
  // for (very) large scenes the frame rate is always too low, even if  
  // a fast rendering hardware is in use. As a consequence the rendering 
  // process has to be interupted if a request (event) from the user is 
  // pending. However, it makes no sense to interupt too quickly. 
  // The setFrameRate method allows to limit the frame rate to a maximal 
  // value. 
  // This option has no influence, if the total rendering time of the scene 
  // is not longer than (1./'frameRate') seconds.

  void setCheckPendingEvents (bool check);
  bool doCheckPendingEvents () const;
  // controls wheter events from the windowing system should be checked
  
  void displayStatistics() const;
  // Display some statistical information concerning the rendering process
  // (number of primitives rendered, ...) on the screen.
  long getTriangleCount() const; 

public:
  void drawBounds(Object3D* object);
  // Draw the bounding box of a single object.
  
private:
  void installLightSources();

private:
  Traversal::Result visit(LightSource* light);
  Traversal::Result visit(Triangle3D* triangle);
  Traversal::Result visit(TriangleList3D* list);
  Traversal::Result visit(Polygon3D* polygon);
  Traversal::Result visit(Text3D* text);
  Traversal::Result visit(Box3D* box);
  Traversal::Result visit(Sphere3D* sphere);
  Traversal::Result visit(Cylinder3D* cylinder);
  Traversal::Result visit(Cone3D* cone);
  Traversal::Result visit(Torus3D* torus);
  Traversal::Result visit(Line3D* line);
  Traversal::Result visit(Point3D* line);
  Traversal::Result visit(LevelOfDetail3D* lod);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool postprocessing();
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool myGenerateWorld; 
  // Indicates if the call to execute() creates a new world object.
  
  RenderingQuality myRenderingQuality;
  long myTriangleCount;
};

//______________________________________________________________________ INLINES

inline void GLRenderer::generateWorld(bool enable)
{
  myGenerateWorld = enable;
}

inline GLRenderer::RenderingQuality GLRenderer::getRenderingQuality() const
{
  return myRenderingQuality;
}
inline long GLRenderer::getTriangleCount() const
{
  return myTriangleCount;
}
#endif // _GLRenderer_H

