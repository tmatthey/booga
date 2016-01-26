/*
 * $RCSfile: GLRasterizer.h,v $ 
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
 *  $Id: GLRasterizer.h,v 1.8 1996/09/13 08:04:26 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLRasterizer_H
#define _GLRasterizer_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Operation2D.h"

class Point2D;
class Line2D;
class Pixmap2D;
class Camera2D;

//__________________________________________________________________ GLRasterizer

class GLRasterizer : public Operation2D {
declareRTTI(GLRasterizer);
// enable RTTI support

public:
enum RenderingQuality {
  BOUNDING_BOX  = 1,
  FLAT          = 2
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GLRasterizer();
private:
  GLRasterizer(const GLRasterizer&);             // No copies.

public:
  virtual ~GLRasterizer();

private:
  GLRasterizer& operator=(const GLRasterizer&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GLRasterizer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void adoptCamera(Camera2D* camera);
  // Set camera to use for rendering
  void deleteCamera();
  const Camera2D* getCamera() const;

  void generateWorld(bool enable);
  // Indicates if the call to execute() creates a new world object.
  //
  // The GLRasterizer will always display the scene in the framebuffer. If 
  // this option is enable (default behaviour), the content of the 
  // framebuffer is copied to a pixmap, the pixmap is added to a new
  // world object and the world is returned as a result of the call to 
  // the GLRasterizer::execute() method.

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

public:
  void drawBounds(Object2D* object);
  // Draw the bounding rectangle of a single object.

private:
  void setupDisplay();

private:
  Traversal::Result visit(Point2D* point);
  Traversal::Result visit(Line2D* line);
  Traversal::Result visit(Pixmap2D* pixmap);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Compnent<>
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
  Camera2D* myCamera;
  bool      myHasAdoptedCamera;

  bool myGenerateWorld; 
  // Indicates if the call to execute() creates a new world object.

  RenderingQuality myRenderingQuality;
};

//______________________________________________________________________ INLINES

inline const Camera2D* GLRasterizer::getCamera() const
{
  return myCamera;
}

inline void GLRasterizer::generateWorld(bool enable)
{
  myGenerateWorld = enable;
}

inline GLRasterizer::RenderingQuality GLRasterizer::getRenderingQuality() const
{
  return myRenderingQuality;
}

#endif // _GLRasterizer_H

