/*
 * $RCSfile: GLRasterizer.C,v $
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
 *  $Id: GLRasterizer.C,v 1.18 1996/09/13 08:04:25 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <stdio.h>

#ifdef HAVE_OPENGL
# include <GL/gl.h>
#endif

#include "booga/base/TransMatrix3D.h"
#include "booga/base/AbstractPixmap.h"

#include "booga/object/Point2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/object/Camera2D.h"

#include "booga/component/Collector2DFor.h"

#include "booga/glwrapper/GLTraversal2D.h"
#include "booga/glwrapper/GLBBTraversal2D.h"
#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLRasterizer.h"

//__________________________________________________________________ GLRasterizer

implementRTTI(GLRasterizer, Operation2D);

GLRasterizer::GLRasterizer()
{
  myCamera = NULL;
  myHasAdoptedCamera = false;
  myGenerateWorld = true;
  myRenderingQuality = FLAT;
  adoptTraversal(new GLTraversal2D);
}

GLRasterizer::~GLRasterizer()
{
  if (myCamera != NULL)
    delete myCamera;
}

void GLRasterizer::adoptCamera(Camera2D* camera)
{
  if (camera == NULL) {
    Report::warning("[GLRasterizer::adoptCamera] NULL pointer passed");
    return;
  }
    
  if (myCamera != NULL && myCamera != camera)
    delete myCamera;

  myCamera = camera; 
  myHasAdoptedCamera = true;
}

void GLRasterizer::deleteCamera()
{
  if (myCamera != NULL) {
    delete myCamera;
    myCamera = NULL;
  }
  myHasAdoptedCamera = false;
}

void GLRasterizer::setRenderingQuality(RenderingQuality quality)
{
  GLAbstractTraversal2D* newTraversal = NULL;
  if (myRenderingQuality == BOUNDING_BOX && quality != BOUNDING_BOX)
    newTraversal = new GLTraversal2D;
  else if (myRenderingQuality != BOUNDING_BOX && quality == BOUNDING_BOX)
    newTraversal = new GLBBTraversal2D;
    
  if (newTraversal != NULL) {
    newTraversal->setMaxTimeInBackbuffer(getMaxTimeInBackbuffer());
    newTraversal->setFrameRate(getFrameRate());
    adoptTraversal(newTraversal);
  }

  myRenderingQuality = quality;
}

Real GLRasterizer::getMaxTimeInBackbuffer() const
{
  return dynamic_cast<GLAbstractTraversal2D*>(getTraversal())->getMaxTimeInBackbuffer();
}

void GLRasterizer::setMaxTimeInBackbuffer(Real maxTimeInBackbuffer)
{
  dynamic_cast<GLAbstractTraversal2D*>(getTraversal())->setMaxTimeInBackbuffer(maxTimeInBackbuffer);
}

int GLRasterizer::getFrameRate() const
{
  return dynamic_cast<GLAbstractTraversal2D*>(getTraversal())->getFrameRate();
}

void GLRasterizer::setFrameRate(int frameRate)
{
  dynamic_cast<GLAbstractTraversal2D*>(getTraversal())->setFrameRate(frameRate);
}

bool GLRasterizer::preprocessing()
{
  if (!Operation2D::preprocessing())
    return false;
    
  if (!myHasAdoptedCamera) {
    //
    // Collect all cameras in the world.
    //  
    Collector2DFor<Camera2D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        if (myCamera != NULL)
          delete myCamera;
        myCamera = camCollector.createTransformedObject(); 
    }
  }

  if (myCamera == NULL) {
    Report::recoverable("[GLRasterizer::preprocessing] no camera available");
    return false;
  }
    
  setupDisplay();

  return true;
}

bool GLRasterizer::postprocessing()
{
#ifdef HAVE_OPENGL
  glFlush();
#endif // HAVE_OPENGL 
  if (myGenerateWorld == true) {
    getResult()->getObjects()->adoptObject(
        new Pixmap2D(GLUtilities::createPixmapFromFramebuffer()));
    getResult()->getObjects()->computeBounds();
  }

  return Operation2D::postprocessing();
}

void GLRasterizer::setupDisplay()
{
  //
  // Clear display.
  //
  Color bgColor = getCamera()->getBackground();
#ifdef HAVE_OPENGL
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
  glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

  glClear(GL_COLOR_BUFFER_BIT);

  //
  // Setup viewing parameters and light sources of the GL rendering engine.
  //
  GLdouble left    = getCamera()->getViewing()->getWindowOrigin().x();
  GLdouble right   = left + getCamera()->getViewing()->getWindowSize().x();
  GLdouble bottom  = getCamera()->getViewing()->getWindowOrigin().y();
  GLdouble top     = bottom + getCamera()->getViewing()->getWindowSize().y();
                   
  glViewport(0, 0, (GLint)getCamera()->getViewing()->getResolutionX(), 
                   (GLint)getCamera()->getViewing()->getResolutionY());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(left, right, bottom, top, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  //
  // Setup rendering quality.
  //
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  glShadeModel(GL_FLAT);

  if (myRenderingQuality == BOUNDING_BOX) {
    if ((bgColor[0] + bgColor[1] + bgColor[2])/3.0 > .5)
      glColor3f (0, 0, 0);
    else
      glColor3f (1, 1, 1);
  }
#endif // HAVE_OPENGL 
}

void GLRasterizer::drawBounds(Object2D* object)
{
#ifdef HAVE_OPENGL

  Vector2D from = object->getBounds().getMin();
  Vector2D to   = object->getBounds().getMax();

  glBegin(GL_LINE_LOOP);
    glVertex2f(from.x(), from.y());
    glVertex2f(to.x(), from.y());
    glVertex2f(to.x(), to.y());
    glVertex2f(from.x(), to.y());
  glEnd();

#endif // HAVE_OPENGL 
}

Traversal::Result GLRasterizer::visit(Point2D* point)
{
#ifdef HAVE_OPENGL

  glBegin(GL_POINTS);
    glVertex2f(point->getPosition().x(), point->getPosition().y());
  glEnd();

#endif // HAVE_OPENGL

  return Traversal::CONTINUE;
}

Traversal::Result GLRasterizer::visit(Line2D* line)
{
#ifdef HAVE_OPENGL
 
  glBegin(GL_LINE_STRIP);
    glVertex2f(line->getFrom().x(), line->getFrom().y());
    glVertex2f(line->getTo().x(),   line->getTo().y());
  glEnd();
          
#endif // HAVE_OPENGL

  return Traversal::CONTINUE;
}

Traversal::Result GLRasterizer::visit(Pixmap2D* pixmap)
{
#ifdef HAVE_OPENGL

  //
  // Pixmaps may be scaled, rotated, etc. The implementation below is very, very
  // simple and transformations applied to pixmaps may lead to rendering artefacts.
  // SORRY.
  //
  const AbstractPixmap* pm = pixmap->getPixmap();
  
  // A Pixmap2D may have no pixmap attached to it!
  if (pm != NULL) {
    GLfloat pixel[3];
  
    for (long y=0; y<pm->getResolutionY(); y++) {
      for (long x=0; x<pm->getResolutionX(); x++) {
        //
        // Drawing a pixmap may take a very long time!!!
        //
        if (GLUtilities::isEventPending())
          return Traversal::CONTINUE;
        
        pm->setPosition(x, y);
        pm->getColor(pixel[0], pixel[1], pixel[2]);
        glRasterPos2i(x, y);
        glDrawPixels(1, 1, GL_RGB, GL_FLOAT, pixel);
      }  
    }
  }
  
#endif // HAVE_OPENGL
  
  return Traversal::CONTINUE;
}

Traversal::Result GLRasterizer::dispatch(Makeable* obj)
{
  tryConcrete(Point2D,  obj);
  tryConcrete(Line2D,   obj);
  tryConcrete(Pixmap2D, obj);
  
  //
  // Create decomposition for unknown objects.
  //
  return Traversal::UNKNOWN;
}

