/*
 * $RCSfile: GLViewer2D.C,v $
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
 *  $Id: GLViewer2D.C,v 1.8 1996/09/13 08:04:35 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/glut.h>
#endif

#include "booga/object/Camera2D.h"
#include "booga/component/Collector2DFor.h"
#include "booga/glwrapper/GLRasterizer.h"
#include "booga/glwrapper/GLViewer2D.h"

//___________________________________________________________________ GLViewer2D

implementRTTI(GLViewer2D, Operation2D);
implementInitStatics(GLViewer2D);

World2D* GLViewer2D::ourWorld;
GLRasterizer* GLViewer2D::ourRasterizer;
GLViewer2D::MovingMode GLViewer2D::ourMovingMode = GLViewer2D::NO_BUTTON_DOWN;
int GLViewer2D::ourOldX;
int GLViewer2D::ourOldY;

void GLViewer2D::initClass()
{
  ourWorld = NULL;
  ourRasterizer = new GLRasterizer;
  ourRasterizer->generateWorld(false);
}

void GLViewer2D::displayCallback()
{
#ifdef HAVE_OPENGL
  glDrawBuffer(GL_FRONT);
#endif

  ourRasterizer->execute(ourWorld);
}

void GLViewer2D::keyboardCallback(unsigned char key, int, int)
{
  switch (key) {
  case 27:    // ESC and 'q' will quit.
  case 'q':   
    exit(1); 
    break;
  }
}

void GLViewer2D::mouseCallback(int button, int state, int x, int y)
{
#ifdef HAVE_OPENGL

  //
  // Left mouse button down.
  //
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    ourRasterizer->setRenderingQuality(GLRasterizer::BOUNDING_BOX);
    ourOldX = x;
    ourOldY = y;
    ourMovingMode = LEFT_BUTTON_DOWN;
  } 

  //
  // Left mouse button up.
  //
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    ourRasterizer->setRenderingQuality(GLRasterizer::FLAT);
    glutPostRedisplay();
    ourMovingMode = NO_BUTTON_DOWN;
  } 

  //
  // Middle mouse button down.
  //
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    ourRasterizer->setRenderingQuality(GLRasterizer::BOUNDING_BOX);
    ourOldX = x;
    ourOldY = y;
    ourMovingMode = MIDDLE_BUTTON_DOWN;
  } 

  //
  // Middle mouse button up.
  //
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    ourRasterizer->setRenderingQuality(GLRasterizer::FLAT);
    glutPostRedisplay();
    ourMovingMode = NO_BUTTON_DOWN;
  }

#endif // HAVE_OPENGL

}

void GLViewer2D::motionCallback(int x, int y)
{

#ifdef HAVE_OPENGL

  switch (ourMovingMode) {
  case LEFT_BUTTON_DOWN:
    pan(x-ourOldX, y-ourOldY);
    glutPostRedisplay();
    break;
    
  case MIDDLE_BUTTON_DOWN:
    zoom(x-ourOldX, y-ourOldY);
    glutPostRedisplay();
    break;
    
  case NO_BUTTON_DOWN:
    break;
  }

  ourOldX = x;
  ourOldY = y;

#endif // HAVE_OPENGL

} 

void GLViewer2D::reshapeCallback(int width, int height)
{

#ifdef HAVE_OPENGL

  ourRasterizer->getCamera()->getViewing()->setResolution(width, height);
  glutPostRedisplay();

#endif // HAVE_OPENGL

}

void GLViewer2D::pan(Real dx, Real dy)
{
  Viewing2D* viewing = ourRasterizer->getCamera()->getViewing();

  viewing->setWindow(viewing->getWindowOrigin()+
                       Vector2D(-dx/viewing->getResolutionX()*viewing->getWindowSize().x(), 
                                 dy/viewing->getResolutionY()*viewing->getWindowSize().y()),
                     viewing->getWindowSize());
}

void GLViewer2D::zoom(Real /* dx */, Real dy)
{
  Viewing2D* viewing = ourRasterizer->getCamera()->getViewing();

  viewing->setWindow(viewing->getWindowOrigin(),
                     Vector2D(viewing->getWindowSize().x() +
                                dy/viewing->getResolutionX()*viewing->getWindowSize().x(),
                              viewing->getWindowSize().y() +
                                dy/viewing->getResolutionY()*viewing->getWindowSize().y()));
}

bool GLViewer2D::doExecute()
{
  ourWorld = getWorld();
  
  //
  // Collect all cameras in the world.
  //  
  Collector2DFor<Camera2D> camCollector;
  camCollector.execute(ourWorld);
  Camera2D* camera = NULL;

  //
  // Look for first camera in world, that is switched on.
  //
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    if (camCollector.getObject()->isOn()) {
      camera = camCollector.createTransformedObject(); 
      break;
    }

  if (camera == NULL) {
    Report::recoverable("[GLViewer2D::doExecute] scene contains no active camera");
    return false;
  }

  ourRasterizer->adoptCamera(camera);

#ifdef HAVE_OPENGL
  //
  // Setup window.
  //
  int argc = 1;
  char* argv0 = "dummy argument";
  
  glutInit(&argc, &argv0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(ourRasterizer->getCamera()->getViewing()->getResolutionX(), 
		   ourRasterizer->getCamera()->getViewing()->getResolutionY());

  glutCreateWindow("BOOGA 2D Viewer");

  //
  // Install callbacks.
  //
  glutDisplayFunc(GLViewer2D::displayCallback);
  glutKeyboardFunc(GLViewer2D::keyboardCallback);
  glutMouseFunc(GLViewer2D::mouseCallback);
  glutMotionFunc(GLViewer2D::motionCallback);
  glutReshapeFunc(GLViewer2D::reshapeCallback);

  glutMainLoop();
#endif

  return true;
}
