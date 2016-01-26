/*
 * $RCSfile: picker.C,v $
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
 *  $Id: picker.C,v 1.15 1996/09/13 08:05:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef HAVE_OPENGL

#include <GL/glut.h>

#include "booga/base/ReportConfigurationHandler.h"

#include "booga/object/Viewing3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/World3D.h"

#include "booga/component/Parser3D.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/Picker3D.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/BSDL3DWriter.h"
#include "booga/component/SingleFileStore.h"

#include "booga/glwrapper/GLMatte.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLRenderer.h"

//_____________________________________________________________________ Globals

RCString filename;
GLRenderer* renderer     = NULL;
World3D*    world        = NULL;
Object3D*   pickedObject = NULL;
Texture3D*  savedTexture = NULL;

//__________________________________________________________________ Initialiser
 
static void initParser();
static void initRendering(int argc, char* argv[]);
static void readWorld();
static void parseCmdLine(int argc, char* argv[]);
static void usage(const RCString& name);

//____________________________________________________________________ Callbacks

static void displayCallback();
static void reshapeCallback(int width, int height);
static void keyboardCallback(unsigned char key, int x, int y);
static void mouseCallback(int button, int state, int x, int y);

//__________________________________________________________________ Applikation

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  parseCmdLine(argc, argv);

  renderer = new GLRenderer;
  renderer->generateWorld(false);
  
  readWorld();
 
  // 
  //  Start displaying of scene.
  // -----------------------------------------------------------

  initRendering(argc, argv); 
  glutMainLoop();

  return 0;
}

void initParser() 
{
  initGLBSDLParserGlobalNS();
  initGLBSDLParser3DNS();
}

void initRendering(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(renderer->getCamera()->getViewing()->getResolutionX(), 
		   renderer->getCamera()->getViewing()->getResolutionY());
  glutCreateWindow("Picker");

  renderer->setRenderingQuality(GLRenderer::SOLID_FLAT);

  //
  // Install callbacks.
  //
  glutReshapeFunc(reshapeCallback);
  glutDisplayFunc(displayCallback);
  glutKeyboardFunc(keyboardCallback);
  glutMouseFunc(mouseCallback);
}

void readWorld()
{
  if (world != NULL) 
    delete world;
    
  world = new World3D;

  pickedObject = NULL;
  if (savedTexture != NULL) {
    delete savedTexture;
    savedTexture = NULL;
  }
  
  Makeable::removeNamespaces();
  initParser();

  Parser3D parser;
  parser.setFilename(filename);
  parser.execute(world);

  //
  // Collect all cameras in the world.
  //  
  Collector3DFor<Camera3D> camCollector;
  camCollector.execute(world);
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
    Report::error("scene contains no active camera");
    exit(1);
  }

  renderer->adoptCamera(camera);
}

void parseCmdLine(int argc, char* argv[])
{
  if (argc >= 2 && !strcmp(argv[1], "-h")) {
    usage(argv[0]);
    exit(0);
  }
    
  if (argc >= 2) 
    filename = argv[argc-1];
}

void usage(const RCString& name)
{
  cerr << "Usage: " << name << " [in-file]\n";
  cerr << " where:\n";
  cerr << "  in-file  : (optional) filename of input\n";
}

//____________________________________________________________________ Callbacks

void displayCallback()
{
  glDrawBuffer(GL_BACK);

  renderer->execute(world);
    
  GLint drawBuffer;
  glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
  if (drawBuffer == GL_BACK)
    GLUtilities::swapBuffers();
}

void reshapeCallback(int width, int height)
{
  renderer->getCamera()->getViewing()->setResolution(width, height);
  glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int, int)
{
  switch (key) {
  case 27:    // ESC and 'q' will quit.
  case 'q':   
    exit(1); 
    break;
  case 'r':
    readWorld();
    glutReshapeWindow(renderer->getCamera()->getViewing()->getResolutionX(),
		    renderer->getCamera()->getViewing()->getResolutionY());
    break;
  }
  
  glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y)
{
  Picker3D picker;
 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    //
    // Restore texture of the object from the last hit.
    //
    if (pickedObject != NULL) {
      delete pickedObject->orphanTexture();
      if (savedTexture != NULL)
        pickedObject->appendTexture(savedTexture);
      pickedObject = NULL;
      savedTexture = NULL;
    }

    picker.setCamera(renderer->getCamera()); 
    picker.setPickOrigin(x, renderer->getCamera()->getViewing()->getResolutionY()-y);
    picker.execute(world);
    
    //
    // Got a hit?
    //
    if (picker.getPath() != NULL) {
      
      //
      // Alter texture of the current hit.
      //
      pickedObject = picker.getPath()->getLastObject();
      savedTexture = pickedObject->orphanTexture();
           
      GLMatte* red = new GLMatte;
      red->setDiffuse(Color(1,0,0));
      red->setAmbient(Color(.5,0,0));
      pickedObject->appendTexture(red);

      //
      // Draw bounding box around the slected object.
      //
      GLRenderer::RenderingQuality currentQuality = renderer->getRenderingQuality();
      glPushMatrix();
        static float m[16];
        convert(picker.getPath()->getLastTransform().getTransMatrix(), m);
        glMultMatrixf(m);
        static GLfloat bboxColor[4] = { 1. , 1., 1., 1. };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bboxColor);

        //
        // Draw the object in bounding box mode!
        //
        renderer->setRenderingQuality(GLRenderer::BOUNDING_BOX);
        renderer->drawBounds(pickedObject); 
      glPopMatrix();
      glFlush();
      renderer->setRenderingQuality(currentQuality);

      //
      // Print the whole path to cerr.
      //
      cerr << "World";
      for (picker.getPath()->first(); !picker.getPath()->isDone(); picker.getPath()->next()) 
        cerr << "->" << typeid(picker.getPath()->getObject()).name();
      cerr << endl;

      SingleFileStore docuStore = SingleFileStore();

      World3D* world3D = new World3D();

      world3D->getObjects()->adoptObject((picker.getPath()->getLastObject())->copy());

      BSDL3DWriter writer(docuStore);
      writer.execute(world3D);
      
      delete world3D;
    }
  }
  //
  // For any up mouse click exept the one performed with the left mouse button, 
  // redisplay the whole scene.
  //
  else if (button != GLUT_LEFT_BUTTON && state == GLUT_UP) {
    glutPostRedisplay();
  }
}

#else // HAVE_OPENGL -----------------------------------------------------------

#include <stream.h>

int main ()
{
  cerr << "\nThis application needs the OpenGL graphics package.\n" 
       << "When compiling this application your site was \n"
       << "configured not to use OpenGL.\n\n";
}

#endif // HAVE_OPENGL

