/*
 * $RCSfile: raytrace.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: raytrace.C,v 1.10 1996/08/01 12:01:07 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"
#include "booga/object/Path3D.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/PNGWriter.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/JPEGWriter.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/Collector3DFor.h"
 
#include "booga/animation/Animation3D.h"
 
static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, 
                         int& samplingRate, bool& print,
                         Real& startframe, int& number, 
                         Real& frameStep, int& counter, 
                         bool& ppm, bool& jpeg, bool& png);
 
 
int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  Configuration::setOption(Name("Statistic.OutputStream"),Name("cerr"));
  
  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  RCString in, out, filename;
  int samplingRate = 0;
  bool print = false;
  Real startframe  = 0;  // starframe of the animation
  int number       = 1;  // # of frames to raytrace
  Real frameStep   = 1;  // framestep of the animation
  int counter      = 0;  // startvalue of counter of the frames for the filename
  bool ppm = false;
  bool png = false;
  bool jpeg = false;
  
  List<Animation3D*>* listAnimation = NULL;
  List<Path3D*>* listAnimationPath = NULL;
  parseCmdLine(argc, argv, in, out, samplingRate, print, 
               startframe, number, frameStep, counter, ppm, jpeg, png );
  //
  // Read scene
  //

  World3D* world3D = new World3D;
  Parser3D parser;
  parser.setFilename(in);
  
  setExecTime(parser.execute(world3D), "raytrace: 1: Parsing");
  
  //
  // Print scene
  //
  if (print) {
    PrintWorld3D printer(std::cerr);
    printer.execute(world3D);
  }
  
  //
  // Process scene
  //
  World2D* world2D;
  
  //
  // Collect all animation objects in the world.
  //  
  if (listAnimation != NULL)
    delete listAnimation;

  if (listAnimationPath != NULL)
    delete listAnimationPath;
    
  listAnimation = new List<Animation3D*>;
  listAnimationPath = new List<Path3D*>;
  Collector3DFor<Animation3D> animCollector;
  animCollector.execute(world3D);
  
  for (animCollector.first(); !animCollector.isDone(); animCollector.next()){
    listAnimation->append(animCollector.getObject());
    listAnimationPath->append(animCollector.getPath());
  }
  
  Real frame = startframe;
  
  std::cerr << "Animationparameters :" << std::endl;
  std::cerr << " startframe       : " << startframe << std::endl;
  std::cerr << " number of frames : " << number << std::endl;
  std::cerr << " framestep        : " << frameStep << std::endl;
  std::cerr << " counter          : " << counter << std::endl;
  
  for (long i = counter; i < number + counter; i++) {
    std::cerr << "Current frame : " << frame << " (" << i << ")." << std::endl;
 
    for (long j=0; j<listAnimation->count(); j++){
      if(listAnimation->item(j)->frame(frame))
	listAnimation->item(j)->resetBounds(*listAnimationPath->item(j));
    }

    world3D->getObjects()->computeBoundsLazy();
 
    if (samplingRate > 0){
      Raytracer raytrace;
      OversamplingAntialiaser antialiasing;
      antialiasing.setRenderer(&raytrace);
      antialiasing.setSamplingRate(samplingRate);
      setExecTime(world2D=antialiasing.execute(world3D), "raytrace: 2: Rendering");
    }
    else {
      Raytracer raytrace;
      setExecTime(world2D=raytrace.execute(world3D), "raytrace: 2: Rendering");
    }

    //
    // Write image(s)
    //
    
    filename = out;
    if (number > 1 && !out.isEmpty()){
      char tmp[256];
      sprintf(tmp,".%04d", static_cast<int>(i));
      filename += tmp;
    }

    if (ppm) {
      if (!out.isEmpty())
        filename += ".ppm";
      PPMWriter writer(filename);
      setExecTime(writer.execute(world2D), "raytrace: 3: Writing output");
    }
    if (png) {
      if (!out.isEmpty())
        filename += ".png";
      PNGWriter writer(filename);
      setExecTime(writer.execute(world2D), "raytrace: 3: Writing output");
    }
    else if (jpeg) {
      if (!out.isEmpty())
        filename += ".jpg";
      JPEGWriter writer(filename);
      setExecTime(writer.execute(world2D), "raytrace: 3: Writing output");
    }
    else {
      if (!out.isEmpty())
        filename += ".pixi";
      PixiWriter writer(filename);
      setExecTime(writer.execute(world2D), "raytrace: 3: Writing output");
    }
    
    frame += frameStep;
    delete world2D;
    //
    // Write out statistics
    //
    Statistic::print();
  }
 
  delete world3D;
  delete listAnimation;
  delete listAnimationPath;

  return 0;
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out, int& samplingRate,
                  bool& print, Real& startframe, int& number, Real& frameStep, int& counter,
		  bool& ppm, bool& jpeg, bool& png)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>13) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;
    
  while (cur<argc && argv[cur][0]=='-') {
 
    if (!strcmp(argv[cur],"--oversampling")) {
      samplingRate = atoi(argv[++cur]);
      cur++;
      continue;
    }
    
    if (!strcmp(argv[cur],"--print")){
      print = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--ppm")){
      ppm = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--png")){
      png = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--jpeg")){
      jpeg = true;
      cur++;
      continue;
    }
      
    if (!strcmp(argv[cur],"--start")) {
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
      frameStep = atof(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--counter")) {
      counter = atoi(argv[++cur]);
      cur++;
      continue;
    }
    
    break;

  }  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [--oversampling rate] [--print] [in-file [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  --oversampling        : (optional) oversampling rate for antialiasing\n";
    std::cerr << "                          (default: no antialiasing performed)\n";
    std::cerr << "  --print               : (optional) print scene for debugging purpose\n";
    std::cerr << "  --start startframe    : (optional) start frame of the animation\n";
    std::cerr << "  --number number       : (optional) number of frames\n";
    std::cerr << "  --framestep framestep : (optional) framestep of the animation\n";
    std::cerr << "  --counter startnumber : (optional) startnumber of the counter for the outputfiles\n";
    std::cerr << "  --ppm                 : (optional) output as PPM\n";
    std::cerr << "  --png                 : (optional) output as PNG\n";
    std::cerr << "  --jpeg                : (optional) output as JPEG\n";
    std::cerr << "  in-file               : (optional) filename of input\n";
    std::cerr << "  out-file              : (optional) filename of output\n";
}

