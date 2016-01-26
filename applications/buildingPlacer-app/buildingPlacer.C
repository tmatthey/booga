/*
 * $RCSfile: bsdlWriter.C,v $ 
 *
 * Copyright (C) 1997, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: bsdlWriter.C,v 1.5 1996/11/28 13:50:32 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "CollectBuilding.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/building/Building.h"
//#include "booga/component/Collector3DFor.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/BSDL3DWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/MultiFileStore.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], char& mode, 
                         RCString& in, RCString& out);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  
  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  RCString in, out;
  char mode = ' ';

  parseCmdLine(argc, argv, mode, in, out);

  //
  // Read scene
  //
  World3D* world3D = new World3D;
  Ray3D* ray;
  List<Vector3D> tmp;
  Parser3D parser;
  parser.setFilename(in);
  parser.execute(world3D);
  
  CollectBuilding buildingCollector;
  buildingCollector.execute(world3D);

  cerr << "Number of buildings found:  " << buildingCollector.count() << endl;

  for (buildingCollector.first(); !buildingCollector.isDone(); buildingCollector.next())
    buildingCollector.getCurrent()->turnOff();

  world3D->getObjects()->computeBounds();

  //
  // Print world
  //
  // PrintWorld3D printer(cout);
  // printer.apply(world3D);  
   

  Real z;
  Building* building;
  long count = 0;
  Vector3D a(0,0,10+world3D->getObjects()->getBounds().getMax().z());
  Vector3D b(0,0,-1);
  Vector3D c;
  
  for (buildingCollector.first(); !buildingCollector.isDone(); buildingCollector.next()){
    building = buildingCollector.getCurrent();
    tmp = building->getVertices();
    z = 0;
    for(long j=0;j<tmp.count();j++){
      c = tmp.item(j)*(building->getTransform().getTransMatrix());
      ray = Ray3DFactory::createRay(a+Vector3D(c.x(),c.y(),0),b);
      if (world3D->getObjects()->intersect(*ray) && (j == 0 || c.z() - ray->getHitPoint().z() > z))
        z = c.z()-ray->getHitPoint().z();
      delete ray;       
    }
    if (!equal(z,0,.001)){
      building->addTransform(TransMatrix3D::makeTranslate(0,0,-z));
      count++;
    }    
  }
  cerr << "Number of buildings placed: " << count << endl;
  
  
  for (buildingCollector.first(); !buildingCollector.isDone(); buildingCollector.next())
    buildingCollector.getCurrent()->turnOn();
      
  //
  // Write BSDL format.
  //

  DocumentStore* docuStore = NULL;
  if (mode == 'm') {
    docuStore = new MultiFileStore(out);
  } else {
    docuStore = new SingleFileStore(out);
  }

  BSDL3DWriter writer(*docuStore);
  writer.execute(world3D);

  delete world3D;

  return 0;
}

void parseCmdLine(int argc, char* argv[], char& mode, RCString& in, RCString& out)
{
  int next = 1;
  mode = ' ';
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc == 1) {
    usage(argv[0]);
    exit(0);
  }

  if (!strcmp(argv[1], "-m")) {
    mode = 'm';
    next++;
  }

  if (next >= argc) return;
  in = argv[next];
  next++;

  if (next >= argc) return;
  out = argv[next];
  next++;
}

void usage(const RCString& name)
{
    cerr << "Usage: " << name << " [-m] [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  -m             : (optional) multiple file output\n";
    cerr << "                    One file per shared object or material\n";
    cerr << "  in-file        : (optional) filename of input\n";
    cerr << "  out-file       : (optional) filename of output\n";
}

