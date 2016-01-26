/*
 * $RCSfile: 
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitnesms of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: graphicsdb.C,v 1.3 1997/01/30 10:10:25 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/BSDLWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/MultiFileStore.h"
#include "booga/component/Parser3D.h"
#include "booga/component/Raytracer.h"
#include "booga/component/ZBuffer.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/PPMWriter.h"
#include "booga/base/RCString.h"

#include "booga/persistence/PRef.h"
#include "booga/persistence/Transaction.h"
#include "booga/persistence/FileBase.h"
#include "booga/persistence/TransientBase.h"
#include "booga/persistence/Persistent.h"
#include "booga/persistence/PersistentManager.h"
#include "booga/persistence/Prototype.h"
#include "booga/persistence/PBinary.h"
#include "booga/graphicsdb/GraphicsDataBase.h"
#include "booga/graphicsdb/GDBDataType.h"
#include "booga/graphicsdb/GDBRepType.h"
#include "booga/graphicsdb/GDBData.h"
#include "booga/graphicsdb/GDBStore.h"
#include "booga/graphicsdb/GDBOperation.h"
#include "booga/graphicsdb/GDBConfiguration.h"
#include "booga/graphicsdb/GDBIconBuilderBSDL3.h"
#include "booga/graphicsdb/GDB3CanonicalViews.h"
// #include "booga/graphicsdb/RaytraceBSDL3.h"
// #include "booga/graphicsdb/WireframeBSDL3.h"
#include "booga/graphicsdb/ImportBSDL3.h"
#include "booga/graphicsdb/GDBExport.h"
// #include "booga/graphicsdb/GDBComputeContour.h"
// #include "booga/graphicsdb/GDBCompute3Icons.h"
// #include "GDBOperation.h"
static void usage(const RCString& name);

static void parseCmdLine(int argc, char* argv[], char& mode, 
                         unsigned long& oid, RCString& filename);
                         
int main(int argc, char* argv[]) {
  
  PersistentManager thePersistentManager(1000);

  thePersistentManager.registerPrototype(new GraphicsDataBase(aPrototype));
  thePersistentManager.registerPrototype(new GDBDataType(aPrototype));
  thePersistentManager.registerPrototype(new GDBRepType(aPrototype));
  thePersistentManager.registerPrototype(new GDBData(aPrototype));
  thePersistentManager.registerPrototype(new PBinary(aPrototype));
  thePersistentManager.registerPrototype(new GDBOperation(aPrototype));
  thePersistentManager.registerPrototype(new GDBExport(aPrototype));
  thePersistentManager.registerPrototype(new ImportBSDL3(aPrototype));
  thePersistentManager.registerPrototype(new GDBIconBuilderBSDL3(aPrototype));
  thePersistentManager.registerPrototype(new GDB3CanonicalViews(aPrototype));

//  thePersistentManager.registerPrototype(new PRCString(aPrototype));

  TransientBase theTransientBase;
//  FileBase aDB("/home/collison/tmp/testDB/");
  FileBase aDB((char*)"/home/fcg/Scenes/GraphicsBase/");

//  PRCString aprcs(aDB);
//  aprcs = "i wonder! is this really gonna work?\n";
//  cout << aprcs.find(RCString("wonder")) << " " << aprcs.getPOId() << " tataaa!!!\n";
//  aprcs.markChanged();

//  Transaction t1;
//  t1.begin();
//  GDBData* bla = new GDBData(aDB, "bla");
//  bla->setName("bla t1");
//  bla->markChanged();
//  Transaction t2;
//  t2.begin();
//  GDBData* bla2 = new GDBData(aDB, "bla2");
//  bla->setName("bla t2");
//  cout << bla->getName() << std::endl;
//  bla->markChanged();
//  t2.abort();
//  cout << bla->getName() << std::endl;
//  t1.commit();

//  Transaction t3;
//  t3.begin();
//  A* a = new A(aDB);
//  B* b = new B(aDB);
//  
//  a->myB = b;
//  b->myA = a;
//  a->markChanged();
//  b->markChanged();
//  cout << a->myB->myData;
//  t3.commit(); 
  
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  RCString interpol("Gouraud");
  if (!Configuration::setOption(Name("ZBuffer.TriangleInterpolator"), Name(interpol)))
    Report::error("Unknown Shader \"" + interpol + "\"");
   
  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  GDBStore gdbStore(aDB);
  RCString filename("");
  unsigned long oid;
  char mode = ' ';
  World3D *world3D = new World3D;
   
  parseCmdLine(argc, argv, mode, oid, filename);

  if (mode == 'I') {
    Transaction t;
    t.begin();

    if (aDB.lookupObject((char*)"GraphicsBase") != POID_NULL) {
      Report::error("GraphicsBase allready exists");
      return 1;
    }
    GraphicsDataBase* theGDB = new GraphicsDataBase(aDB);
    aDB.setObjectName((char*)"GraphicsBase",theGDB->getPOId());
    GDBDataType *gdbAnyData = new GDBDataType(aDB, "AnyData");
    GDBDataType *gdbTexture3D = new GDBDataType(aDB, "Texture3D");
    GDBDataType *gdbObject3D = new GDBDataType(aDB, "Object3D");
    GDBDataType *gdbScene3D = new GDBDataType(aDB, "Scene3D");
    GDBDataType *gdbImage = new GDBDataType(aDB, "Image");
    GDBDataType *gdbIcon = new GDBDataType(aDB, "Icon");
    gdbTexture3D->setBaseType(gdbAnyData);
    gdbObject3D->setBaseType(gdbAnyData);
    gdbScene3D->setBaseType(gdbAnyData);
    gdbImage->setBaseType(gdbAnyData);
    gdbIcon->setBaseType(gdbImage);
    theGDB->registerDataType(gdbAnyData);
    theGDB->registerDataType(gdbTexture3D);
    theGDB->registerDataType(gdbObject3D);
    theGDB->registerDataType(gdbScene3D);
    theGDB->registerDataType(gdbImage);
    theGDB->registerDataType(gdbIcon);
    
    GDBRepType *gdbAnyRep = new GDBRepType(aDB, "AnyRep", "any");
    GDBRepType *gdbBSDL = new GDBRepType(aDB, "BSDL", "bsdl");
    GDBRepType *gdbBSDL3 = new GDBRepType(aDB, "BSDL3", "bsdl3");
    GDBRepType *gdbBSDL2 = new GDBRepType(aDB, "BSDL2", "bsdl2");
    GDBRepType *gdbPPM = new GDBRepType(aDB, "PPM", "ppm");
    GDBRepType *gdbBOOGAWorld3D = new GDBRepType(aDB, "BOOGAWorld3D");
    GDBRepType *gdbBOOGAWorld2D = new GDBRepType(aDB, "BOOGAWorld2D");
    gdbBSDL->setSuperRepType(gdbAnyRep);
    gdbBSDL3->setSuperRepType(gdbBSDL);
    gdbBSDL2->setSuperRepType(gdbBSDL);
    gdbPPM->setSuperRepType(gdbAnyRep);
    gdbBOOGAWorld3D->setSuperRepType(gdbAnyRep);
    gdbBOOGAWorld2D->setSuperRepType(gdbAnyRep);
    theGDB->registerRepType(gdbAnyRep);
    theGDB->registerRepType(gdbBSDL);
    theGDB->registerRepType(gdbBSDL3);
    theGDB->registerRepType(gdbBSDL2);
    theGDB->registerRepType(gdbPPM);
    theGDB->registerRepType(gdbBOOGAWorld3D);
    theGDB->registerRepType(gdbBOOGAWorld2D);

    GDBExport* gdbExporter = new GDBExport(aDB, gdbAnyData, gdbBSDL3, NULL, NULL);
    ImportBSDL3* gdbImporter = new ImportBSDL3(aDB, NULL, NULL, gdbAnyData, gdbBSDL3);

    theGDB->registerOperation(gdbExporter);

    theGDB->registerOperation(gdbImporter);

    GDBIconBuilderBSDL3* gdbIconBuilder = 
       new GDBIconBuilderBSDL3(aDB, gdbAnyData, gdbBSDL3, gdbIcon, gdbPPM, 100, 100);
    GDBConfiguration defaultConfig;
    defaultConfig.setValue("Resolution", Vector2D(100,100));
    gdbIconBuilder->setDefaultConfiguration(defaultConfig);
    theGDB->registerOperation(gdbIconBuilder);

    GDB3CanonicalViews* gdb3Views = 
       new GDB3CanonicalViews(aDB, gdbObject3D, gdbBSDL3, NULL, NULL, 100, 100);
    GDBConfiguration defaultConfig2;
    defaultConfig2.setValue("Resolution", Vector2D(128,128));
    gdb3Views->setDefaultConfiguration(defaultConfig2);
    theGDB->registerOperation(gdb3Views);

    t.commit();
    return 0;
  }
  
  if (mode == 'g') {
    // 
    // Read scene from database
    //
    Transaction t;
    t.begin();
    POId poid(1,oid);
    PRef<GraphicsDataBase> gdb(aDB.lookupObject((char*)"GraphicsBase"));
    
    GDBOperation* op = gdb->getOperation("Exporter");
    GDBExport *exporter = dynamic_cast<GDBExport*>(op);
    if (exporter == NULL) {
       Report::error("[main] GDBOperation 'Exporter' not found");
       exit(1);
    }
    exporter->execute(poid, POID_NULL);
    BSDL3DParser parser;
    parser.setFilename(exporter->getFilename());
    t.commit();

    parser.execute(world3D);

    //
    // Write BSDLFormat to single file
    //
    SingleFileStore fileStore(filename);
    BSDLWriter writer(fileStore);
    writer.execute(world3D);
  }
  if (mode == 'c') {
    Transaction t;
    t.begin();
    PRef<GraphicsDataBase> gdb(aDB.lookupObject((char*)"GraphicsBase"));
    GDBDataType* gdbObject3D = gdb->getDataType("Object3D");
 
    GDBOperation* op = gdb->getOperation("CanonicalViews");
    if (op == NULL) {
       Report::error("[main] GDBOperation 'CanonicalViews' not found");
       exit(1);
    }    

    for (int i=0; i<gdbObject3D->getExtent().count(); i++) {
      std::stringstream os;
      os << gdbObject3D->getExtent().getKey(i) << " "
         << gdbObject3D->getExtent().getData(i).getPOId() << std::endl;
      POId poid(gdbObject3D->getExtent().getData(i).getPOId());
      Report::hint(os);
      op->execute(poid, POID_NULL);
    }
    t.commit();
  }
//  if (mode == 'r') {
//    //
//    // Process scene
//    //
//    RaytraceBSDL3 raytracer("bsdl3");
//    POId poid(1,oid);
//    raytracer.execute(poid,POID_NULL);
//  }
//  if (mode == 'w') {
//    //
//    // Process scene
//    //
//    WireframeBSDL3 wireframe("bsdl3");
//    POId poid(1,oid);
//    wireframe.execute(poid,POID_NULL);
//  }
  if (mode == 'i') {
    Transaction t;
    t.begin();
    PRef<GraphicsDataBase> gdb(aDB.lookupObject((char*)"GraphicsBase"));
    gdb->getOperation("Icon Builder")->execute(POId(1,oid), POID_NULL);
    t.commit();
  }
//  if (mode == 'j') {
//    //
//    // Process scene
//    //
//    GDBCompute3Icons iconizer(128, 128);
//    POId poid(1,oid);
//    iconizer.execute(poid,POID_NULL);
//  }
//  if (mode == 'z') {
//    // 
//    // Read scene from database
//    //
//    POId poid(1,oid);
//    GDBExport exporter;
//    exporter.execute(poid, POID_NULL);
//
//    BSDL3DParser parser;
//    parser.setFilename(exporter.getFilename());
//    parser.execute(world3D);
//
//    //
//    // Process scene
//    //
//    ZBuffer zbuffer;
//    World2D* world2D;
//    world2D=zbuffer.execute(world3D);
//    //
//    // Write image
//    //
//    PPMWriter writer(filename);
//    // PixiWriter writer(filename);
//    writer.execute(world2D);
//    delete world2D;
//  }  
  if (mode == 'd') {
    Transaction t;
    t.begin();
    PRef<GraphicsDataBase> gdb(aDB.lookupObject((char*)"GraphicsBase"));
    GDBRepType* gdbBsdl3 = gdb->getRepType("BSDL3");
    std::stringstream os;
    for (int i=0; i<gdbBsdl3->getExtent().count(); i++) {
      os << gdbBsdl3->getExtent().getKey(i) << " "
         << gdbBsdl3->getExtent().getData(i).getPOId() << std::endl;
    }
    t.commit();
    Report::hint(os);
  }
  if (mode == ' ') {
    // 
    // Read scene from file
    //
    BSDL3DParser parser;
    parser.setFilename(filename);
    parser.execute(world3D);

    //
    // Write BSDLFormat to database.
    //
    SingleFileStore(filename);
    Transaction t;
    t.begin();
    PRef<GraphicsDataBase> gdb(aDB.lookupObject((char*)"GraphicsBase"));
    gdb->markChanged(); // just to be sure to have the GDBDataBase loaded
    BSDLWriter writer(gdbStore);
    writer.execute(world3D);
    t.commit();
  }
  delete world3D;
  return 0;
}


void parseCmdLine(int argc, char* argv[], char& mode, unsigned long& oid, RCString& filename)
{
  int next = 1;
  mode = ' ';
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc == 1) {
    usage(argv[0]);
    exit(0);
  }

  if (!strcmp(argv[1], "-I")) {
    mode = 'I';
    next++;
  }

  if (!strcmp(argv[1], "-g")) {
    mode = 'g';
    next++;
  }

  if (!strcmp(argv[1], "-c")) {
    mode = 'c';
    next++;
  }  

  if (!strcmp(argv[1], "-r")) {
    mode = 'r';
    next++;
  }

  if (!strcmp(argv[1], "-z")) {
    mode = 'z';
    next++;
  }

  if (!strcmp(argv[1], "-w")) {
    mode = 'w';
    next++;
  }
  
  if (!strcmp(argv[1], "-i")) {
    mode = 'i';
    next++;
  }
  
  if (!strcmp(argv[1], "-j")) {
    mode = 'j';
    next++;
  }  

  if (!strcmp(argv[1], "-d")) {
    mode = 'd';
    next++;
  }  
  
  if (mode != ' ') {
    if (next >= argc) return;
    oid = atol(argv[next]);
    next++;
  }
  
  if (next >= argc) return;
  filename = argv[next];
  next++;
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [-g oid] [file]]\n";
    std::cerr << "Without option: " << std::endl;
    std::cerr << "  Writes file <file> to database. " << std::endl;
    std::cerr << "Options: " << std::endl;
    std::cerr << "  -g (get) option the object <oid> is retrieved from the data base " << std::endl;
    std::cerr << "     and stored in the file <file>. " << std::endl;
    std::cerr << "  -c compute the contour of object in image <oid> " << std::endl;
    std::cerr << "  -i compute an icon for the object <oid> " << std::endl;
    std::cerr << "  -r raytrace the scene <oid> and store the image in the database " << std::endl;
    std::cerr << "  -w wireframe render the scene <oid>, store image in database " << std::endl;
    std::cerr << "  -I initialize data base (only to be used once!)" << std::endl;
}

