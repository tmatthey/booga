/*
 * $RCSfile: IconBuilderForBSDL3.C,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: IconBuilderForBSDL3.C,v 1.4 1996/10/09 14:12:27 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "IconBuilderForBSDL3.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "SetStandardView3D.h"
#include "booga/object/Object3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Texture3D.h"
#include "GDBExport.h"
#include "GDBStore.h"

//_____________________________________________________________________ IconBuilderForBSDL3

implementRTTI(IconBuilderForBSDL3, GDBOperation);

IconBuilderForBSDL3::IconBuilderForBSDL3(RCString inputType, int xsize, int ysize) :
GDBOperation(RCString("Icon Builder"), inputType, RCString("BSDL3"), 
                                RCString("Icon"), RCString("ppm")),
myIconSizeX(xsize),
myIconSizeY(ysize)
{
}

bool IconBuilderForBSDL3::doExecute() {
  World3D *world3D = new World3D;
  // 
  // Read scene from database into tmp file
  //
  GDBExport exporter;
  exporter.execute(mySource->getPOId(), POID_NULL);

  // 
  // Read tmp file -> BOOGA representation
  //
  BSDL3DParser parser;
  parser.setFilename(exporter.getFilename());
  parser.execute(world3D);

  //
  // If there is no instance of an object create one and insert it into the world3D
  // 
  if (world3D->getObjects()->countSubobject() == 0) {
    ostrstream os;
    os << mySource->getName() << "." << mySource->getPOId().getPDBId() 
                              << "." << mySource->getPOId().getPObjectId();
    RCString objectName(os);
    RCString errmsg;
    Makeable* makeable = Makeable::make(errmsg, 
                         ScopedName(Name(RCString("3D")), Name(objectName)), 
                         new List<Value*>());
    if (makeable == NULL) { // some objs as textures still havn't got oid in name definition
      makeable = Makeable::make(errmsg, 
                 ScopedName(Name(RCString("3D")), Name(mySource->getName())), 
                 new List<Value*>()); // try without oid
      if (makeable == NULL) {
        ostrstream msg;
        msg << "[IconBuilderForBSDL3::doExecute] object " 
            << objectName << " not found after parsing";
        Report::recoverable(msg);
        failed();
        return false;
      }
    }
    Object3D *obj = dynamic_cast(Object3D, makeable);
    if (obj == NULL) {
      Texture3D *texture = dynamic_cast(Texture3D, makeable);
      if (texture == NULL) {
        ostrstream msg;
        msg << "[IconBuilderForBSDL3::doExecute] cannot handle object type " 
            << typeid(makeable).name();
        Report::recoverable(msg);
        failed();
        return false;
      } else {
        Sphere3D *sphere = new Sphere3D(1.0,Vector3D(0.,0.,0.));
        sphere->setSpecifier(errmsg, makeable);
        world3D->getObjects()->adoptObject(sphere);
      }
    }
    else {
      world3D->getObjects()->adoptObject(obj->copy());
    }
    world3D->getObjects()->computeBounds();
  }

  Raytracer raytrace; // allready generate renderer so that it can accept a camera if necessary
  Aggregate3D *root = world3D->getObjects();

  //
  // check if a top level camera exists: if not add a camera
  //  
  Camera3D *camera = NULL;
  long i;
  for(i=0; i<root->countSubobject(); i++) {
    camera = dynamic_cast(Camera3D,root->getSubobject(i));
    if (camera != NULL) break;
  }
  if (camera == NULL) {
    SetStandardView3D setview;
    setview.setResolution(100,100);
    setview.execute(world3D);
  }

  //
  // Process scene
  // 
  World2D* world2D;
  OversamplingAntialiaser antialiasing;
  antialiasing.setRenderer(&raytrace);
  antialiasing.setSamplingRate(2);
  world2D=antialiasing.execute(world3D);
  // world2D=raytrace.execute(world3D);

  //
  // Write image to tmp
  //
  PPMWriter writer("gdb2.tmp");
  writer.execute(world2D);
  delete world2D;

  //
  // Store icon in database
  //
  if (myTarget == NULL) {
    myTarget = mySource->getIcon();
  }
  if (myTarget == NULL) {
    myTarget = new GDBData(mySource->getDataBase(), mySource->getName());
  }
  myTarget->setFormat("ppm");
  myTarget->setType("Icon");

  //
  // Write image to database
  // 
  PBinary* binary = myTarget->getBinaryData();
  if (binary == NULL) {
    binary = new PBinary(myTarget->getDataBase());
  }
  binary->setFiletype("ppm");
  binary->loadFile("gdb2.tmp");
  binary->write();
  myTarget->setBinaryData(binary);
  myTarget->setSource(mySource);  // set target to source relation
  myTarget->write();
  mySource->setIcon(myTarget);
  mySource->write();
  return true;
}
