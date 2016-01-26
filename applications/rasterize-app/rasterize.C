/*
 * $RCSfile: rasterize.C,v $ 
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
 *  $Id: rasterize.C,v 1.32 1996/09/13 08:06:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef HAVE_OPENGL

#include <GL/glut.h>

#include "booga/base/ReportConfigurationHandler.h"

#include "booga/object/Primitive2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Texture2D.h"
#include "booga/object/Texture2DContext.h"

#include "booga/component/BSDL2DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Collector2DFor.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/Picker2D.h"
#include "booga/component/Rasterizer.h"
#include "booga/component/PSWriter2D.h"
#include "booga/component/ConfigurationHandlers.h"

#include "booga/glwrapper/GLTexture.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLUtilities.h"
#include "booga/glwrapper/GLRasterizer.h"

//_____________________________________________________________________ Globals

enum Output { PIXI, POSTSCRIPT, GL };

RCString in, out;                 // Input and output filenames.
GLRasterizer* rasterizer = NULL;
World2D* world           = NULL;
GLRasterizer::RenderingQuality renderingQuality = GLRasterizer::FLAT;
GLRasterizer::RenderingQuality motionQuality    = GLRasterizer::FLAT;

enum AppMode { PAN_ZOOM = 1, PICK = 2, RAYPAINT = 3 };
AppMode appMode = PAN_ZOOM;

enum MovingMode { NO_BUTTON_DOWN, LEFT_BUTTON_DOWN, MIDDLE_BUTTON_DOWN };
MovingMode movingMode = NO_BUTTON_DOWN;

static int oldX, oldY;

const int FLAT          = 1;
const int BOUNDING_BOX  = 2;

const int SAVE_FRAMEBUFFER  = 1;

//__________________________________________________________________ Initialiser
 
static void initRendering(int argc, char* argv[]);
static void readWorld();
static void saveFramebufferToFile();
static void pickObject(int x, int y);
static void raytrace(int fromX, int fromY, int toX, int toY, 
                     const Path2D* selectedObj = NULL);
static void raytraceObject(int x, int y);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, Output& output);
static void usage(const RCString& name);

//____________________________________________________________________ Callbacks

static void displayCallback();
static void reshapeCallback(int width, int height);
static void keyboardCallback(unsigned char key, int x, int y);
static void mouseCallback(int button, int state, int x, int y);
static void motionCallback(int x, int y);
static void appModeCallback(int value);
static void mainMenuCallback(int value);
static void renderingQualityCallback(int value);
static void motionQualityCallback(int value);
static void toolsCallback(int value);
static void optionsCallback(int value);
static void frameRateCallback(int value);
static void timeInBackbufferCallback(int value);

//__________________________________________________________________ Applikation

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  Output output = GL;
  parseCmdLine(argc, argv, in, out, output);

  if (output == PIXI || output == POSTSCRIPT) {
    initBSDLParserGlobalNS();
    initBSDLParser2DNS();

    BSDL2DParser parser;
    World2D* world2D = new World2D;
    parser.setFilename(in);
    parser.execute(world2D);
    
    if (output == PIXI) {
      Rasterizer rasterizer;
      World2D* result = rasterizer.execute(world2D);

      PixiWriter writer(out);
      writer.execute(result);
      
      delete result;
    }
    else if (output == POSTSCRIPT) {
      PSWriter2D writer(out);
      writer.execute(world2D);
    }
    
    delete world2D;

    return 0;
  }
  
  rasterizer = new GLRasterizer;
  rasterizer->generateWorld(false);

  readWorld();
 
  // 
  //  Start displaying of scene.
  // -----------------------------------------------------------

  initRendering(argc, argv); 
  glutMainLoop();

  return 0;
}

void initRendering(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(rasterizer->getCamera()->getViewing()->getResolutionX(), 
		   rasterizer->getCamera()->getViewing()->getResolutionY());
  glutCreateWindow("Rasterizer");

  rasterizer->setRenderingQuality(renderingQuality);

  //
  // Setup menus.
  // 

  int applicationMode = glutCreateMenu(appModeCallback);
  glutAddMenuEntry("Pan/Zoom", PAN_ZOOM);
  glutAddMenuEntry("Pick", PICK);
  glutAddMenuEntry("Raypaint", RAYPAINT);

  int renderingQuality = glutCreateMenu(renderingQualityCallback);
  glutAddMenuEntry("Flat", FLAT);
  glutAddMenuEntry("Bounding Box", BOUNDING_BOX);

  int motionQuality = glutCreateMenu(motionQualityCallback);
  glutAddMenuEntry("Flat", FLAT);
  glutAddMenuEntry("Bounding Box", BOUNDING_BOX);
  
  // 
  // Setup TOOLS Menu
  //

  int tools = glutCreateMenu(toolsCallback);
  glutAddMenuEntry("Save framebuffer", SAVE_FRAMEBUFFER);

  // 
  // Setup OPTIONS Menu
  //

  int frameRate = glutCreateMenu(frameRateCallback);
  glutAddMenuEntry(" 1", 1);
  glutAddMenuEntry(" 5", 5);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("15", 15);
  glutAddMenuEntry("20", 20);
  glutAddMenuEntry("25", 25);
  glutAddMenuEntry("30", 30);
  glutAddMenuEntry("Fastest", 10000);

  int timeInBackbuffer = glutCreateMenu(timeInBackbufferCallback);
  glutAddMenuEntry("0.0", 0);
  glutAddMenuEntry("0.1", 1);
  glutAddMenuEntry("0.5", 5);
  glutAddMenuEntry("1.0", 10);
  glutAddMenuEntry("1.5", 15);
  glutAddMenuEntry("2.0", 20);
  glutAddMenuEntry("3.0", 30);
  glutAddMenuEntry("5.0", 50);
  glutAddMenuEntry("as long as necessary", 10000);

  int options = glutCreateMenu(optionsCallback);
  glutAddSubMenu("Frames/sec", frameRate);
  glutAddSubMenu("Time spent in backbuffer", timeInBackbuffer);

  // 
  // Setup MAIN Menu
  //

  glutCreateMenu(mainMenuCallback);
  glutAddSubMenu("Application mode", applicationMode);
  glutAddSubMenu("Rendering quality", renderingQuality);
  glutAddSubMenu("Motion quality", motionQuality);
  glutAddSubMenu("Tools", tools);
  glutAddSubMenu("Options", options);
  glutAddMenuEntry("Quit", 666);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
  //
  // Install callbacks.
  //
  glutReshapeFunc(reshapeCallback);
  glutDisplayFunc(displayCallback);
  glutKeyboardFunc(keyboardCallback);
  glutMouseFunc(mouseCallback);
  glutMotionFunc(motionCallback);
}

void readWorld()
{
  if (world != NULL) delete world;
  world = new World2D;

  Makeable::removeNamespaces();
  initGLBSDLParserGlobalNS();
  initGLBSDLParser2DNS();

  //
  // Check file first: LINT!!!
  //   Not done yet....
  
  BSDL2DParser parser;
  parser.setFilename(in);
  parser.execute(world);

  //
  // Collect all cameras in the world.
  //  
  Collector2DFor<Camera2D> camCollector;
  camCollector.execute(world);
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
    Report::error("scene contains no active camera");
    exit(1);
  }

  rasterizer->adoptCamera(camera);
}

void saveFramebufferToFile()
{
  static int currentFrame = 1;

  AbstractPixmap* pixi = GLUtilities::createPixmapFromFramebuffer();
  if (out == "")
    out = "Noname";
  RCString filename = out;
  char tmp[256];
  sprintf(tmp,".%d.pixi", currentFrame++);
  filename += tmp;

  if (pixi->save(filename))
    std::cerr << "Pixi " << filename << " created." << std::flush << std::endl;
  
  delete pixi;  
}

void pickObject(int x, int y)
{
  Picker2D picker;
 
  picker.setCamera(rasterizer->getCamera()); 
  picker.setPickOrigin(x, rasterizer->getCamera()->getViewing()->getResolutionY()-y);
  picker.execute(world);
    
  //
  // Got a hit?
  //
  if (picker.getPath() != NULL) {
    //
    // Draw bounding rectangle around the selected object.
    //
    GLRasterizer::RenderingQuality currentQuality = rasterizer->getRenderingQuality();
    const Path2D* path = picker.getPath();

    glPushMatrix();
      path->last(); path->prev();
      if (!path->isDone() && !path->getTransform().isIdentity()) {
        static float m[16] = { 1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1
                             };
        const TransMatrix2D& trans = path->getTransform().getTransMatrix();
        m[0]  = trans(0, 0); m[1]  = trans(0, 1); 
        m[4]  = trans(1, 0); m[5]  = trans(1, 1); 
        m[12] = trans(2, 0); m[13] = trans(2, 1); 
        glMultMatrixf(m);
      }

      //
      // Select the color of the bounding box.
      //
      glDisable(GL_COLOR_MATERIAL);
      glDisable(GL_LIGHTING);
      Color bgColor = rasterizer->getCamera()->getBackground();
      if ((bgColor[0] + bgColor[1] + bgColor[2])/3.0 > .5)
        glColor3f (0, 0, 0);
      else
        glColor3f (1, 1, 1);
      glDrawBuffer(GL_FRONT);
 
      //
      // Draw the object in bounding box mode!
      //
      rasterizer->setRenderingQuality(GLRasterizer::BOUNDING_BOX);
      rasterizer->drawBounds(picker.getPath()->getLastObject()); 
    glPopMatrix();
    glFlush();
    rasterizer->setRenderingQuality(currentQuality);


    //
    // Print the whole path to std::cerr.
    //
    std::cerr << "World";
    for (picker.getPath()->first(); !picker.getPath()->isDone(); picker.getPath()->next()) 
      std::cerr << "->" << typeid(picker.getPath()->getObject()).name();
    std::cerr << std::endl;
  }
}  

void raytrace(int fromX, int fromY, int toX, int toY, const Path2D* selectedObj)
{
  //
  // Setup the texturing context.
  //
  Texture2DContext context;
  Viewing2D* viewing = rasterizer->getCamera()->getViewing();
  context.setWorld(world);
  Color defaultColor = Color::getDefault();

  Ray2D ray(Vector2D(0,0));
  const Path2D* path = NULL;
  Real maxDistance = 0.4 * viewing->getWindowSize().x() / viewing->getResolutionX();

  //
  // init OpenGL viewing:
  //
  glDrawBuffer(GL_FRONT);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, viewing->getResolutionX(), 
             0, viewing->getResolutionY());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  GLfloat pixel[3];
  GLfloat background[3] = { 
          rasterizer->getCamera()->getBackground().getRed(),
          rasterizer->getCamera()->getBackground().getGreen(),
          rasterizer->getCamera()->getBackground().getBlue()
          };
  
  //
  // Start raytracing.
  //
  for (int x = fromX; x <= toX; x++) {
    for (int y = fromY; y <= toY; y++) {
      //
      // Clipping...
      //
      if (x < 0 || x >= viewing->getResolutionX() ||
          y < 0 || viewing->getResolutionY()-y >= viewing->getResolutionY()) {
        continue;
      }  

      ray.reset();
      viewing->computeRayThrough(x, viewing->getResolutionY()-y, ray);

      if (!world->getObjects()->intersect(ray)) {
        //
        // No HIT. Draw the background color.
        //
        glRasterPos2i(x, viewing->getResolutionY()-y);
        glDrawPixels(1, 1, GL_RGB, GL_FLOAT, background);
      }
      else if (ray.getBestHitDistance() > maxDistance) {
        //
        // HIT, but too far away from the object. Don't do anything.
        //
      }
      else if (((path = ray.getPath()) != NULL)  &&
               (selectedObj == NULL || (*path) == (*selectedObj))) {
        //
        // HIT. Compute the texture color of the pixel and display it on 
        // the screen.
        //
        context.setOCS2WCS(path->getLastTransform());
        context.setPositionWCS(ray.getHitPoint());
        context.setColor(defaultColor);

        GLTexture::setTexturingType(GLTexture::BOOGA);
        Texture2D::texturing(context, path);
        GLTexture::setTexturingType(GLTexture::GL);

        pixel[0] = context.getColor().getRed();
        pixel[1] = context.getColor().getGreen();
        pixel[2] = context.getColor().getBlue();
        glRasterPos2i(x, viewing->getResolutionY()-y);
        glDrawPixels(1, 1, GL_RGB, GL_FLOAT, pixel);
      }
    }
  }
  
  glFlush();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void raytraceObject(int x, int y)
{
  Picker2D picker;
 
  picker.setCamera(rasterizer->getCamera()); 
  picker.setPickOrigin(x, rasterizer->getCamera()->getViewing()->getResolutionY()-y);
  picker.execute(world);
    
  //
  // Got a hit?
  //
  if (picker.getPath() != NULL) {
    //
    // Compute the bounding rectangle of the selected object in screen coordinates.
    //
    const Path2D* path = picker.getPath();
    BoundingRect br = path->getLastObject()->getBounds();
    const Viewing2D* viewing = rasterizer->getCamera()->getViewing();

    //
    // Step 1: Compute the bounding box with all transformations applied.
    //
    path->last(); path->prev();
    if (!path->isDone())
      br.transform(path->getTransform().getTransMatrix());

    //
    // Step 2: Compute screen coordinates.
    //
    Vector2D min = viewing->transformWorld2Screen(br.getMin());
    Vector2D max   = viewing->transformWorld2Screen(br.getMax());

    //
    // Step 3: Trace the object.
    //
    raytrace(int(min.x()), viewing->getResolutionY()-int(max.y()),
             int(max.x()), viewing->getResolutionY()-int(min.y()),
             path);
  }
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out, Output& output)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>5) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;  
  if ((cur < argc-1) && !strcmp(argv[cur],"-t")) {
    RCString type(argv[++cur]);
    if (type == "pixi")
      output = PIXI;
    else if (type == "ps")
      output = POSTSCRIPT;
    else if (type == "gl")
      output = GL;
    else {
      usage(argv[0]);
      exit(0);
    }
    cur++;
  }
  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
  std::cerr << "Usage: " << name << " [-t type] [in-file [out-file]]\n";
  std::cerr << " where:\n";
  std::cerr << "  type     : (optional) ( pixi | ps | gl )\n";
  std::cerr << "  in-file  : (optional) filename of input\n";
  std::cerr << "  out-file : (optional) filename of output\n";
}

//__________________________________________________________ Animation utilities

static void pan(Real dx, Real dy)
{
  Viewing2D* viewing = rasterizer->getCamera()->getViewing();

  viewing->setWindow(viewing->getWindowOrigin()+
                       Vector2D(-dx/viewing->getResolutionX()*viewing->getWindowSize().x(), 
                                 dy/viewing->getResolutionY()*viewing->getWindowSize().y()),
                     viewing->getWindowSize());
}

static void zoom(Real /* dx */, Real dy)
{
  Viewing2D* viewing = rasterizer->getCamera()->getViewing();

  viewing->setWindow(viewing->getWindowOrigin(),
                     Vector2D(viewing->getWindowSize().x() +
                                dy/viewing->getResolutionX()*viewing->getWindowSize().x(),
                              viewing->getWindowSize().y() +
                                dy/viewing->getResolutionY()*viewing->getWindowSize().y()));
}

//____________________________________________________________________ Callbacks


void displayCallback()
{
  glDrawBuffer(GL_BACK);

  rasterizer->execute(world);
    
  GLint drawBuffer;
  glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
  if (drawBuffer == GL_BACK)
    GLUtilities::swapBuffers();
}

void reshapeCallback(int width, int height)
{
  rasterizer->getCamera()->getViewing()->setResolution(width, height);
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
      glutReshapeWindow(rasterizer->getCamera()->getViewing()->getResolutionX(),
                        rasterizer->getCamera()->getViewing()->getResolutionY());
      glutPostRedisplay();
     break;

    case ' ':   // Reset lookat.
      rasterizer->getCamera()->getViewing()->setWindow(
            Vector2D(0, 0),
            Vector2D(rasterizer->getCamera()->getViewing()->getResolutionX(),
                     rasterizer->getCamera()->getViewing()->getResolutionY()));
      glutPostRedisplay();
      break; 

    case 's':
      saveFramebufferToFile();
      break;

    case 'h':
    case '?':
      std::cerr << "Summary of keyboard commands:" << std::endl
           << "  q, ESC :  Quit." << std::endl
           << "  r      :  Reread the scene description file." << std::endl
           << "  SPACE  :  Reset view." << std::endl
           << "  s      :  Save contents of the file buffer." << std::endl
           << "  h, ?   :  This message." << std::endl;
      break;
  }
}

void mouseCallback(int button, int state, int x, int y)
{
  static int startX, startY;

  //
  // Left mouse button down.
  //
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (appMode == PAN_ZOOM) {
      rasterizer->setRenderingQuality(motionQuality);
      oldX = x;
      oldY = y;
    }
    else if (appMode == PICK) {
      pickObject(x, y);
    }
    else if (appMode == RAYPAINT)
      raytraceObject(x, y);
      
    movingMode = LEFT_BUTTON_DOWN;
  } 

  //
  // Left mouse button up.
  //
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    if (appMode == PAN_ZOOM) {
      rasterizer->setRenderingQuality(renderingQuality);
      glutPostRedisplay();
    }

    movingMode = NO_BUTTON_DOWN;
  } 

  //
  // Middle mouse button down.
  //
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    if (appMode == PAN_ZOOM) {
      rasterizer->setRenderingQuality(motionQuality);
      oldX = x;
      oldY = y;
    }
    else if (appMode == RAYPAINT) {
      startX = x;
      startY = y;
    }
    
    movingMode = MIDDLE_BUTTON_DOWN;
  } 

  //
  // Middle mouse button up.
  //
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    if (appMode == PAN_ZOOM) {
      rasterizer->setRenderingQuality(renderingQuality);
      glutPostRedisplay();
    }
    else if (appMode == RAYPAINT)
      raytrace(min(x, startX), min(y, startY),
               max(x, startX), max(y, startY));
               
    movingMode = NO_BUTTON_DOWN;
  }
}

void motionCallback(int x, int y)
{
  if (appMode != PAN_ZOOM)
    return;

  switch (movingMode) {
  case LEFT_BUTTON_DOWN:
    pan(x-oldX, y-oldY);
    glutPostRedisplay();
    break;
    
  case MIDDLE_BUTTON_DOWN:
    zoom(x-oldX, y-oldY);
    glutPostRedisplay();
    break;
    
  case NO_BUTTON_DOWN:
    break;
  }

  oldX = x;
  oldY = y;
}

void mainMenuCallback(int value)
{
  if (value == 666) {
    delete world;
    delete rasterizer;
    exit(0);
  }
}

void renderingQualityCallback(int value)
{
  switch (value) {
  case FLAT:
    renderingQuality = GLRasterizer::FLAT;
    rasterizer->setRenderingQuality(renderingQuality);
    break;

 case BOUNDING_BOX:
    renderingQuality = GLRasterizer::BOUNDING_BOX;
    rasterizer->setRenderingQuality(renderingQuality);
    break;
  }
}

void motionQualityCallback(int value)
{
  switch (value) {
  case FLAT:
    motionQuality = GLRasterizer::FLAT;
    break;

 case BOUNDING_BOX:
    motionQuality = GLRasterizer::BOUNDING_BOX;
    break;
  }
}

void appModeCallback(int value)
{
  switch (value) {
  case PAN_ZOOM:
    appMode = PAN_ZOOM;
    break;
    
  case PICK:
    appMode = PICK;
    break;
    
  case RAYPAINT:
    appMode = RAYPAINT;
    break;
  }
}

void toolsCallback(int value)
{
  switch (value) {
  case SAVE_FRAMEBUFFER:
    saveFramebufferToFile();
    break;
  }
}

void optionsCallback(int /* value */)
{
}

void frameRateCallback(int value)
{
  rasterizer->setFrameRate(value);
}

void timeInBackbufferCallback(int value)
{
  rasterizer->setMaxTimeInBackbuffer(value / 10.);
}

#else // HAVE_OPENGL -----------------------------------------------------------

#include <iostream>

int main ()
{
  std::cerr << "\nThis application needs the OpenGL graphics package.\n" 
       << "When compiling this application your site was \n"
       << "configured not to use OpenGL.\n\n";
}

#endif // HAVE_OPENGL

