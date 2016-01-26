/*
 * $RCSfile: MPIraytrace.C,v $
 *
 * Copyright (C) 1996, Bernhard Buhlmann <buhlmann@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: MPIraytrace.C,v 1.4 1998/05/22 07:07:39 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */


// MPIch: mpirun -p4pg pg4 MPIraytrace

extern "C" {
#include <mpi.h>
}

#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"
#include "booga/base/Report.h"

#include "booga/object/Path3D.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/JPEGWriter.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/Collector3DFor.h"
 
#include "booga/animation/Animation3D.h"

#include "MPIRaytracer.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out,
                         bool& ppm, bool& jpeg, 
                         int& samplingRate, bool& print, bool& show, 
			 Real& startframe, int& number, Real& frameStep, int& counter, int& pipe);
int numtask;
int taskid;


int main(int argc, char* argv[])
{
  extern char* form(const char * ...);
  bool ppm   = false;
  bool jpeg  = false;
  bool show  = false;
  bool print = false;
  int pipe         = 0;
  Real startframe  = 0;  // starframe of the animation
  int number       = 1;  // # of frames to raytrace
  Real frameStep   = 1;  // framestep of the animation
  int counter      = 0;  // startvalue of counter of the frames for the filename
  double t, t2;

  MPI_Init (&argc,&argv);
  MPI_Comm_size (MPI_COMM_WORLD, &numtask);
  MPI_Comm_rank (MPI_COMM_WORLD, &taskid);

  

  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  RCString in, out, filename;
  int samplingRate = 0;
  List<Animation3D*>* listAnimation = NULL;
  List<Path3D*>* listAnimationPath = NULL;

  parseCmdLine(argc, argv, in, out, ppm, jpeg, samplingRate, print, show,
	       startframe, number, frameStep, counter, pipe);

  // Do some tests

  if (show){
    if(numtask < 3){
      Report::error("at least 3 process needed");
      MPI_Finalize();
      exit(1);
    }
  }
  else {
    if(numtask < 2){
      Report::error("at least 2 process needed");
      MPI_Finalize();
      exit(1);
    }
  }

  //
  // Read scene
  //
  World3D* world3D = new World3D;
  Parser3D parser;
  parser.setFilename(in);
  
  setExecTime(parser.execute(world3D), "MPIraytrace: 1: Parsing");
  MPI_Barrier(MPI_COMM_WORLD);
 
  if (taskid == 0){
    t = MPI_Wtime();
    cerr << "Animationparameters :" << endl;
    cerr << " startframe       : " << startframe << endl;
    cerr << " number of frames : " << number << endl;
    cerr << " framestep        : " << frameStep << endl;
    cerr << " counter          : " << counter << endl;
  }
    
  //
  // Print scene
  //
  if (print && taskid == 0) {
    PrintWorld3D printer(cerr);
    printer.execute(world3D);
  }
  
  //
  // Collect all animation objects in the world.
  //  
  if (listAnimation != NULL)
    delete listAnimation;
    
  listAnimation = new List<Animation3D*>;
  listAnimationPath = new List<Path3D*>;
  Collector3DFor<Animation3D> animCollector;
  animCollector.execute(world3D);
  
  for (animCollector.first(); !animCollector.isDone(); animCollector.next()){
    listAnimation->append(animCollector.getObject());
    listAnimationPath->append(animCollector.getPath());
  }
  Real frame = startframe;

  //
  // Process scene
  //

  World2D* world2D;


  
  for (long i = counter; i < number + counter; i++) {
    if (taskid == 0)
      cerr << "Current frame : " << frame << " (" << i << ")." << endl;
 
    for (long j=0; j<listAnimation->count(); j++){
      if(listAnimation->item(j)->frame(frame))
	listAnimation->item(j)->resetBounds(*listAnimationPath->item(j));
    }
    
    world3D->getObjects()->computeBoundsLazy();
 
    MPIRaytracer* ourRaytracer = new MPIRaytracer(numtask, taskid, show, number, pipe, argc, argv);

    if (samplingRate > 0) {
      OversamplingAntialiaser antialiasing;
      antialiasing.setRenderer(ourRaytracer);
      antialiasing.setSamplingRate(samplingRate);
      setExecTime(world2D=antialiasing.execute(world3D), "MPIraytrace: 2: Rendering");
    }
    else {
      setExecTime(world2D=ourRaytracer->execute(world3D), "MPIraytrace: 2: Rendering");
    }

    if (taskid == 0) {
      //
      // Write image(s)
      //
      
      filename = out;
      if (number > 1 && !out.isEmpty())
	filename += form(".%04d", i);

      if (ppm) {
	if (!filename.isEmpty())
	  filename += form(".ppm");
	PPMWriter writer(filename);
	setExecTime(writer.execute(world2D), "MPIraytrace: 3: Writing output");
      } 
      else if (jpeg) {
	if (!filename.isEmpty())
	  filename += form(".jpg");
	JPEGWriter writer(filename);
	setExecTime(writer.execute(world2D), "MPIraytrace: 3: Writing output");
      } 
      else {
	if (!filename.isEmpty())
	  filename += form(".pixi");
	PixiWriter writer(filename);
	setExecTime(writer.execute(world2D), "MPIraytrace: 3: Writing output");
      }
    }
    delete ourRaytracer;
    delete world2D;
    frame += frameStep;

    //
    // Write out statistics
    //
  
    MPI_Barrier(MPI_COMM_WORLD);
    if (taskid == 0) {
      Statistic::print();
      t2 =  MPI_Wtime();
      cerr << "Wall clock: " << t2 - t << " seconds.\n";
      t = t2;
    }
    
  }

  delete world3D;
  delete listAnimation;
  delete listAnimationPath;
    
  MPI_Finalize();
  
  return 0;
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out,
                  bool& ppm, bool& jpeg, 
                  int& samplingRate, bool& print, bool& show,
		  Real& startframe, int& number, Real& frameStep, int& counter, int& pipe)
{
  if ((argc == 2 && !strcmp(argv[1], "-h"))) {
    if (taskid == 0)
      usage(argv[0]);
    MPI_Finalize();
    exit(0);
  }
  
  int cur = 1;
    
  while (cur<argc && argv[cur][0]=='-') {
    if (!strcmp(argv[cur],"--oversampling")) {
      samplingRate = atoi(argv[++cur]);
      cur++;
    }
    
    if (!strcmp(argv[cur],"--print"))
      print = true;

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
    if (!strcmp(argv[cur],"--show")) {
      show = true;
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
      if (number <= 0)
	number = 1;
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
 
    if (!strcmp(argv[cur],"--pipe")) {
      pipe = atoi(argv[++cur]);
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
    cerr << "Usage: " << name << " [--oversampling rate] [--print]  [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  --oversampling : (optional) oversampling rate for antialiasing\n";
    cerr << "                              (default: no antialiasing performed)\n";
    cerr << "  --ppm          : (optional) output as PPM\n";    
    cerr << "  --jpeg         : (optional) output as JPEG\n";
    cerr << "  --print        : (optional) print scene for debugging purpose\n";
    cerr << "  --show         : (optional) display output\n";
    cerr << "  --start startframe    : (optional) start frame of the animation\n";
    cerr << "  --number number       : (optional) number of frames\n";
    cerr << "  --framestep framestep : (optional) framestep of the animation\n";
    cerr << "  --counter startnumber : (optional) startnumber of the counter for the output";
    cerr << "  --pipe number  : (optional)  size of the pipe\n";
    cerr << "  in-file        : (optional) filename of input\n";
    cerr << "  out-file       : (optional) filename of output\n";
}

