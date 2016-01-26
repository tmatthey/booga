/*
 * $RCSfile: animationRemove.C,v $
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
 *  $Id: animationRemove.C,v 1.10 1996/08/01 12:01:07 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Texture3D.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/Collector3DFor.h"
#include "booga/component/BSDL3DWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/MultiFileStore.h"
 
#include "booga/animation/Animation3D.h"
 
static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, 
                         bool& print, char& mode, 
                         Real& startframe, int& number, 
                         Real& frameStep, int& counter);
 
 
int main(int argc, char* argv[])
{
  extern char* form(const char * ...);
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  Configuration::setOption(Name("Statistic.OutputStream"),Name("cerr"));
  
  //initBSDLParserGlobalNS();
  //initBSDLParser3DNS();
  
  RCString in, out, filename;
  bool print = false;
  char mode = ' ';
  Real startframe  = 0;  // starframe of the animation
  int number       = 1;  // # of frames to raytrace
  Real frameStep   = 1;  // framestep of the animation
  int counter      = 0;  // startvalue of counter of the frames for the filename
  
  Collector3DFor<Animation3D>* collector;

  parseCmdLine(argc, argv, in, out, print, mode,
               startframe, number, frameStep, counter);

  
  //
  // Process scene
  //
  World3D* animation;
  
  
  Real frame = startframe;

  cerr << "Animationparameters :" << endl;
  cerr << " startframe       : " << startframe << endl;
  cerr << " number of frames : " << number << endl;
  cerr << " framestep        : " << frameStep << endl;
  cerr << " counter          : " << counter << endl;
  
  for (long i = counter; i < number + counter; i++) {
    cerr << "Current frame : " << frame << " (" << i << ")." << endl;
 

    //
    // Read scene
    //
    animation = new World3D();
    Makeable::removeNamespaces();
    initBSDLParserGlobalNS();
    initBSDLParser3DNS();
    Parser3D* parser = new Parser3D();
    parser->setFilename(in);
    parser->execute(animation);
    delete parser;

    //
    // Print scene
    //
    if (print && counter == i) {
	PrintWorld3D printer(cerr);
	printer.execute(animation);
    }
    
    Object3D* parent;
    Animation3D* animObj;
    Object3D* stillObj;
    Aggregate3D* agg;
    Shared3D* shared;

    int l=0;
    int k=0;


    //for (collector->first(); !collector->isDone(); collector->next()){
    while(true){
	collector = new Collector3DFor<Animation3D>();
	collector->execute(animation);

	if(collector->count()< 1){
	    delete collector;
	    break;
	}
	for (collector->first(); !collector->isDone(); collector->next())
	    collector->getObject()->frame(frame);
	animation->getObjects()->computeBounds();
	collector->first();

	Path3D* path = collector->getPath();
	path->last();
	animObj = (Animation3D*)path->getObject();
	path->prev();
	parent = path->getObject();
	agg = (Aggregate3D*)parent;
	shared = (Shared3D*)parent;
	
	if(parent == NULL)
	    Report::error("zero pointer parent object");
	if(animObj == NULL)
	    Report::error("zero pointer animation object");
	
	
	
	//if(parent != NULL)
	//    cerr << l << " : parent    = " << parent->getKeyword() << endl;
	//if(animObj != NULL)
	//    cerr << l << " : animation = " << animObj->getKeyword() << endl;
	//if(agg != NULL)
	//    cerr << l << " : aggregate = " << agg->getKeyword() << endl;
	
	
	if(agg != NULL)
	    agg->orphanObject(animObj);
	
	if(animObj->getSubobject(0) != NULL){
	    stillObj = animObj->getSubobject(0)->copy();
	    stillObj->addTransform(animObj->getTransform());
	    if(animObj->getTexture() != NULL)
		stillObj->appendTexture(animObj->getTexture()->copy());
	    
	    if(agg != NULL){
		agg->adoptObject(stillObj);
		k++;
	    }
	    else if(shared != NULL){
		shared->adoptObject(stillObj);
		k++;
	    }
	    else
		delete stillObj;
	}
	delete animObj;
	l++;
	delete collector;
    }
    
    
    
    RCString filename = out;
    if (number > 1 && !out.isEmpty())
	filename += form(".%04d", i);
    
    DocumentStore* docuStore = NULL;
    if (mode == 'm') {
	docuStore = new MultiFileStore(filename);
    } else {
	docuStore = new SingleFileStore(filename);
    }
    
    BSDL3DWriter* writer = new BSDL3DWriter(*docuStore);
    writer->execute(animation);
    delete writer;
    delete animation;
    ostrstream os;
    os << "Found "<< l<< " animation object(s) and removed " << k;
    Report::hint(os);
    
    frame += frameStep;
    //
    // Write out statistics
    //
  }
  
  return 0;
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out,
                  bool& print, char& mode, Real& startframe, int& number, Real& frameStep, int& counter)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>13) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;
    
  while (cur<argc && argv[cur][0]=='-') {
 
    
    if (!strcmp(argv[cur],"-mt")){
      mode = 'm';
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--print")){
      print = true;
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
    cerr << "Usage: " << name << " [--oversampling rate] [--print] [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  --print               : (optional) print scene for debugging purpose\n";
    cerr << "  --start startframe    : (optional) start frame of the animation\n";
    cerr << "  --number number       : (optional) number of frames\n";
    cerr << "  --framestep framestep : (optional) framestep of the animation\n";
    cerr << "  --counter startnumber : (optional) startnumber of the counter for the outputfiles\n";
    cerr << "  in-file               : (optional) filename of input\n";
    cerr << "  out-file              : (optional) filename of output\n";
}

