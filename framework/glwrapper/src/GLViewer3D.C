/*
 * $RCSfile: GLViewer3D.C,v $
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
 *  $Id: GLViewer3D.C,v 1.11 1997/09/19 07:14:09 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_OPENGL
# include <GL/glut.h>
#endif

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/glwrapper/GLRenderer.h"
#include "booga/glwrapper/GLViewer3D.h"
#include "booga/glwrapper/GLUtilities.h"

//___________________________________________________________________ GLViewer3D

implementRTTI(GLViewer3D, Operation3D);
implementInitStatics(GLViewer3D);

World3D* GLViewer3D::ourWorld;
GLRenderer* GLViewer3D::ourRenderer;
Arcball GLViewer3D::ourArcball;
GLViewer3D::MovingMode GLViewer3D::ourMovingMode = NO_BUTTON_DOWN;

void GLViewer3D::initClass()
{
  ourWorld = NULL;
  ourRenderer = new GLRenderer;
  ourRenderer->setRenderingQuality(GLRenderer::SOLID_FLAT);
  ourRenderer->setFrameRate(15);
  ourRenderer->setMaxTimeInBackbuffer(5.0);
  ourRenderer->generateWorld(false);
}

void GLViewer3D::setRenderingQuality(GLRenderer::RenderingQuality quality)
{
  ourRenderer->setRenderingQuality(quality);
}

void GLViewer3D::displayCallback()
{
#ifdef HAVE_OPENGL

  glDrawBuffer(GL_BACK);

  TransMatrix3D mat(ourArcball.value());
  ourWorld->getObjects()->setTransform(mat);
  ourRenderer->execute(ourWorld);
    
  GLint drawBuffer;
  glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
  if (drawBuffer == GL_BACK)
    GLUtilities::swapBuffers();

#endif
}

void GLViewer3D::keyboardCallback(unsigned char key, int, int)
{
  switch (key) {
  case 27:    // ESC and 'q' will quit.
  case 'q':   
    exit(1); 
    break;
  }
}

void GLViewer3D::mouseCallback(int button , int state , int /* x */ , int /* y */)
{
#ifdef HAVE_OPENGL
  //
  // Left mouse button down.
  //
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    ourRenderer->setRenderingQuality(GLRenderer::BOUNDING_BOX);
    ourArcball.beginDrag();

    ourMovingMode = LEFT_BUTTON_DOWN;
  } 

  //
  // Left mouse button up.
  //
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    ourRenderer->setRenderingQuality(GLRenderer::SOLID_FLAT);
    ourArcball.endDrag();
    glutPostRedisplay();

    ourMovingMode = NO_BUTTON_DOWN;
  } 

  //
  // Middle mouse button down.
  //
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    ourMovingMode = MIDDLE_BUTTON_DOWN;
  } 

  //  
  //   Middle mouse button up.
  //  
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    ourMovingMode = NO_BUTTON_DOWN;
  }
#endif // HAVE_OPENGL
}

void GLViewer3D::motionCallback(int x, int y)
{
  switch (ourMovingMode) {
  case LEFT_BUTTON_DOWN:
    ourArcball.mouse(2.0*x/ourRenderer->getCamera()->getViewing()->getResolutionX()-1.0, 
                     2.0*(ourRenderer->getCamera()->getViewing()->getResolutionY()-y)/ourRenderer->getCamera()->getViewing()->getResolutionY()-1.0);
    ourArcball.update();
#ifdef HAVE_OPENGL
    glutPostRedisplay();
#endif // HAVE_OPENGL
    break;
    
  case MIDDLE_BUTTON_DOWN:
#ifdef HAVE_OPENGL
    glutPostRedisplay();
#endif // HAVE_OPENGL
    break;
    
  case NO_BUTTON_DOWN:
    break;
 
  default:
    std::stringstream os;
    os << "[GLViewer3D::motionCallback] unknown moving mode " << (int)ourMovingMode;
    Report::recoverable(os);
  }
} 

void GLViewer3D::reshapeCallback(int width, int height)
{
  ourRenderer->getCamera()->getViewing()->setResolution(width, height);
#ifdef HAVE_OPENGL
  glutPostRedisplay();
#endif // HAVE_OPENGL
}

bool GLViewer3D::doExecute()
{
  ourWorld = getWorld();
  
  //
  // Collect all cameras in the world.
  //  
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(ourWorld);
  Camera3D* camera = NULL;

  //
  // Look for first camera in world, that is switched on.
  //
  for (camCollector.first(); !camCollector.isDone(); camCollector.next())
    if (camCollector.getObject()->isOn()) {
      camera = camCollector.createTransformedObject(); 
      break;
    }

  if (camera == NULL) {
    Report::recoverable("[GLViewer3D::doExecute] scene contains no active camera");
    return false;
  }

  ourRenderer->adoptCamera(camera);
  const BoundingBox& bb = getWorld()->getObjects()->getBounds();
  ourArcball.place((bb.getMax() + bb.getMin())/2, 0.75);

#ifdef HAVE_OPENGL
  //
  // Setup window.
  //
  int argc = 0;
  char* argv0 = "dummy argument";
  
  glutInit(&argc, &argv0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(ourRenderer->getCamera()->getViewing()->getResolutionX(), 
		   ourRenderer->getCamera()->getViewing()->getResolutionY());

  glutCreateWindow("BOOGA 3D Viewer");

  //
  // Install callbacks.
  //
  glutDisplayFunc(GLViewer3D::displayCallback);
  glutKeyboardFunc(GLViewer3D::keyboardCallback);
  glutMouseFunc(GLViewer3D::mouseCallback);
  glutMotionFunc(GLViewer3D::motionCallback);
  glutReshapeFunc(GLViewer3D::reshapeCallback);

  glutMainLoop();
#endif

  return true;
}
