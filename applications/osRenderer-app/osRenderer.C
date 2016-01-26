/*
 * $RCSfile: osRenderer.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: osRenderer.C,v 1.6 1998/01/07 16:48:12 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Compiling osRenderer on AIX 4.2 with Mesa-2.4 requires the Mesa libraries to 
// be shared, not static!!! The GLcontext in Mesa will not be set correctly!
//
//------------------------------------------------------------------------------
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#ifdef HAVE_OPENGL
#include <GL/gl.h>
#endif


#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"

#include "booga/animation/Animation3D.h"

#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/JPEGWriter.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/SetStandardView3D.h"
#include "booga/glwrapper/GLTraversal3D.h"
#include "booga/glwrapper/GLBBTraversal3D.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLRenderer.h"
#include "booga/glosmesa/osmesa.h"

class myGLRenderer : public GLRenderer {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();
  virtual bool postprocessing();

private:
  GLubyte *myBuffer;
  OSMesaContext myContext;
};

bool myGLRenderer::preprocessing()
{

  // Create an RGBA-mode context */
  myContext = OSMesaCreateContext( GL_RGBA, NULL );

  if (!myContext) {
    cerr << "invalid context: NULL\n";
    exit(1);
  }
  // get resolution of image and create a frame buffer

  int width  = getCamera()->getViewing()->getResolutionX();
  int height = getCamera()->getViewing()->getResolutionY();

  myBuffer = new GLubyte[width*height*4];

  // Bind the buffer to the context and make it current 
  OSMesaMakeCurrent(myContext, (void *) myBuffer, GL_UNSIGNED_BYTE, width, height);

  return GLRenderer::preprocessing();
}

bool myGLRenderer::postprocessing()
{
  if (!GLRenderer::postprocessing())
    return false;

  /* destroy the context */
  OSMesaDestroyContext(myContext);
  delete [] myBuffer;
  return true;
}


static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, 
                         Real& startframe, int& number, Real& framestep, int& counter,
                         bool& ppm, bool& jpeg,
                         int& samplingRate, bool& pal_large, bool& pal_small, bool& raytrace);

myGLRenderer ourGLRenderer;
Renderer* ourRenderer = NULL;

int main(int argc, char* argv[])
{
  ourRenderer = &ourGLRenderer;

  Configuration::setOption(Name("Statistic.OutputStream"),Name("cerr"));
    
  RCString in, out;
  int samplingRate = 0;

  Real startframe  = 0;  // starframe of the animation
  int number       = 1;  // # of frames to render
  Real frameStep   = 1;  // framestep of the animation
  int counter      = 0;  // startvalue of counter of the frames for the filename
  bool ppm   = false;
  bool jpeg  = true;
  bool print = false;
  bool pal_small   = false;
  bool pal_large   = false;
  bool raytrace = false;
  RCString filename;
  
  parseCmdLine(argc, argv, in, out, startframe, number, 
               frameStep, counter, ppm, jpeg, samplingRate, pal_large, pal_small, raytrace);

  // initialize the right textures

  if (!raytrace) {
    initGLBSDLParserGlobalNS();
    initGLBSDLParser3DNS();
  } else {
    initBSDLParserGlobalNS();
    initBSDLParser3DNS();
  }
  //
  // Read scene
  //
  World3D* world3D = new World3D;
  Parser3D parser;
  parser.setFilename(in);
  
  setExecTime(parser.execute(world3D), "raytrace: 1: Parsing");
 
  List<Animation3D*> listAnimation;
  Collector3DFor<Animation3D> animCollector;
  animCollector.execute(world3D);
 
  //
  // Setup renderer
  //
  ourGLRenderer.setCheckPendingEvents(false);
  ourGLRenderer.setMaxTimeInBackbuffer(2000);
  ourGLRenderer.setFrameRate(0);
  
  for (animCollector.first(); !animCollector.isDone(); animCollector.next())
    listAnimation.append(animCollector.getObject());
 
  Real frame = startframe;
  cerr << "Animationparameters :" << endl;
  cerr << " startframe       : " << startframe << endl;
  cerr << " number of frames : " << number << endl;
  cerr << " framestep        : " << frameStep << endl;
  cerr << " counter          : " << counter << endl;
  for (long i = counter; i < number + counter; i++) {
    cerr << "Current frame : " << frame << " (" << i << ")." << endl;
    for (long j=0; j<listAnimation.count(); j++)
      listAnimation.item(j)->frame(frame);
    
    world3D->getObjects()->computeBounds();
    
    //  
    //
    // Collect all cameras in the world3D.
    //  
    Collector3DFor<Camera3D> camCollector;
    camCollector.execute(world3D);

    //
    // Look for first camera in newWorld, that is switched on.
    //
    Path3D myPath;
    bool hasCamera = false;  
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        for (camCollector.getPath()->first(); !camCollector.getPath()->isDone(); camCollector.getPath()->next())
          myPath.append(camCollector.getPath()->getObject()); 
        hasCamera = true;
        break;
      }
  
    if (!hasCamera) {
      SetStandardView3D mySet;
      mySet.execute(world3D);
    } else {
      // myPath stores the path to the first camera in the scene.
      // we have to calculate the current transformation of the camera, 
      // since it may be animated.
  
     // calculate the current transformation of the camera
  
      Transform3D myTransform;
      myTransform.addTransform(myPath.getLastTransform());
      
//      for (myPath.first(); !myPath.isDone(); myPath.next())
//        myTransform.addTransform(myPath.getObject()->getTransform());
  
      // make a copy of this camera and modify it
  
      Camera3D *myCamera = dynamic_cast(Camera3D, myPath.getLastObject());
      Camera3D *copyCam = (Camera3D *) myCamera->copy();
 
      copyCam->getViewing()->setEye(myCamera->getViewing()->getEye()*myTransform.getTransMatrix());
      copyCam->getViewing()->setLookat(myCamera->getViewing()->getLookat()*myTransform.getTransMatrix());

      // set pal resoultion if necessary
  
      if (pal_large) {
        copyCam->getViewing()->setResolution(704,576);
      }
      if (pal_small) {
        copyCam->getViewing()->setResolution(352,288);
      }
      ourRenderer->adoptCamera(copyCam);
   }


    World2D* world2D;
  
    if (samplingRate > 0) {
      OversamplingAntialiaser antialiasing;
      antialiasing.setRenderer(ourRenderer);
      antialiasing.setSamplingRate(samplingRate);
      setExecTime(world2D=antialiasing.execute(world3D), "raytrace: 2: Rendering");
    } else
      setExecTime(world2D=ourRenderer->execute(world3D), "raytrace: 2: Rendering");

  //
  // Write image(s)
  //
  
  
  filename = out;
    if (number > 1 && !out.isEmpty()) {
       if (i < 10) 
         filename += form(".000%d", i);
       else if (i < 100) 
         filename += form(".00%d", i);
       else if (i < 1000) 
         filename += form(".0%d", i);
       else 
         filename += form(".0%d", i);
    }

    if (ppm) {
      if (!out.isEmpty())
        filename += form(".ppm");
      PPMWriter writer(filename);
      setExecTime(writer.execute(world2D), "osRenderer: 3: Writing output");
    } else if (jpeg) {
      if (!out.isEmpty())
        filename += form(".jpg");
      JPEGWriter writer(filename);
      setExecTime(writer.execute(world2D), "osRenderer: 3: Writing output");
    } else {
      Report::warning("no output specification!");
    }
/*
     else {
      if (!out.isEmpty())
        filename += form(".pixi");
      PixiWriter writer(filename);
      setExecTime(writer.execute(world2D), "osRenderer: 3: Writing output");
    }
*/    
    frame += frameStep;
    delete world2D;
   Statistic::print();
  }

  delete world3D;
  //
  // Write out statistics
  //

  return 0;
}

void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, 
                         Real& startframe, int& number, Real& framestep, int& counter,
                         bool& ppm, bool& jpeg,
                         int& samplingRate, bool& pal_large, bool& pal_small, bool& raytrace)
{
  if ((argc == 2 && !strcmp(argv[1], "-h"))) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;
    
  while (cur<argc && argv[cur][0]=='-') {
    if (!strcmp(argv[cur],"--oversampling")) {
      samplingRate = atoi(argv[++cur]);
      cur++;
    }
    
    if (!strcmp(argv[cur],"--startframe")) {
      startframe = atof(argv[++cur]);
      cur++;
      continue;
    }
  
    if (!strcmp(argv[cur],"--number")) {
      number = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--framestep")) {
      framestep = atof(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--counter")) {
      counter = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--pal_large")) {
      pal_large = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--pal_small")) {
      pal_small = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--ppm")) {
      ppm = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--jpeg")) {
      jpeg = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--quality")) {
      char *quality = argv[++cur];
      if (!strcmp(quality, "boundingbox")) 
	  ourGLRenderer.setRenderingQuality(GLRenderer::BOUNDING_BOX);
      else if (!strcmp(quality, "wireframe")) 
	  ourGLRenderer.setRenderingQuality(GLRenderer::WIREFRAME);
      else if (!strcmp(quality, "gouraud")) 
	  ourGLRenderer.setRenderingQuality(GLRenderer::SOLID_GOURAUD);
      else if (!strcmp(quality, "raytracing")) {
          ourRenderer = new Raytracer();
          raytrace = true;
      }
      cur++;
      continue;
    }
  }
  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
    cerr << "Usage: " << name << " [--oversampling rate] [--print] [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  --oversampling      : (optional) oversampling rate for antialiasing\n";
    cerr << "                              (default: no antialiasing performed)\n";
    cerr << "  --pal_large         : (optional) render scene with PAL resolution (704x576)\n";
    cerr << "  --pal_small         : (optional) render scene with 1/4 PAL resolution (352x288)\n";
    cerr << "  --ppm               : (optional) output as PPM\n";    
    cerr << "  --jpeg              : (optional) output as JPEG\n";
    cerr << "  --quality quality   : (optional) render scene with quality [boundingbox|wireframe|gouraud|raytracing]\n";
    cerr << "                        (default: gouraud)\n";
    cerr << "  --startframe number : (optional) start frame of the animation\n";
    cerr << "  --number number     : (optional) number of frames\n";
    cerr << "  --framestep number  : (optional) framestep of the animation\n";
    cerr << "  --counter number    : (optional) startnumber of the counter for the outputfiles\n";
    cerr << "  in-file             : (optional) filename of input\n";
    cerr << "  out-file            : (optional) filename of output\n";
}

