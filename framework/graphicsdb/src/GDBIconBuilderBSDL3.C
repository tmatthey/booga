/*
 * $RCSfile: GDBIconBuilderBSDL3.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: GDBIconBuilderBSDL3.C,v 1.2 1997/03/21 13:09:09 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/object/Object3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Texture3D.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/SetStandardView3D.h"
#include "booga/graphicsdb/GDBExport.h"
#include "booga/graphicsdb/GDBStore.h"
#include "booga/graphicsdb/GDBIconBuilderBSDL3.h"
#include "booga/graphicsdb/GraphicsDataBase.h"

//_____________________________________________________________________ GDBIconBuilderBSDL3

implementRTTI(GDBIconBuilderBSDL3, GDBOperation);

GDBIconBuilderBSDL3::GDBIconBuilderBSDL3(DataBase& aDB, 
GDBDataType* sourceType, GDBRepType* sourceRep,
GDBDataType* targetType, GDBRepType* targetRep,
int xsize, int ysize) :
GDBOperation(aDB, RCString("Icon Builder"), 
             sourceType, sourceRep, targetType, targetRep),
myIconSizeX(xsize),
myIconSizeY(ysize)
{
}

GDBIconBuilderBSDL3::GDBIconBuilderBSDL3(Prototype aPrototype) :
GDBOperation(aPrototype),
myIconSizeX(50),
myIconSizeY(50)
{
}

GDBIconBuilderBSDL3::~GDBIconBuilderBSDL3() 
{
}

Persistent* GDBIconBuilderBSDL3::newInstance() {
  return new GDBIconBuilderBSDL3(aPrototype);
}

bool GDBIconBuilderBSDL3::doExecute() {
  Value value;
  if (getConfigValue(RCString("IconResolution"), value)) {
    strstream ss;
    ss << value;
    Vector2D resol;
    ss >> resol;
    myIconSizeX = (int) resol.x();
    myIconSizeY = (int) resol.y();
  }
  World3D *world3D = new World3D;
  // 
  // Read scene from database into tmp file
  //
  GDBOperation* op = GraphicsDataBase::getTheGraphicsDataBase()->getOperation("Exporter");
  GDBExport *exporter = dynamic_cast(GDBExport, op);
  if (exporter == NULL) {
    Report::recoverable("[GDBIconBuilderBSDL3::doExecute()] GDBOperation 'Exporter' not found");
    failed();
    return false;
  }
  exporter->execute(mySource->getPOId(), POID_NULL);

  // 
  // Read tmp file -> BOOGA representation
  //
  BSDL3DParser parser;
  parser.setFilename(exporter->getFilename());
  parser.execute(world3D);

  //
  // If there is no instance of an object create one and insert it into world3D
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
        msg << "[GDBIconBuilderBSDL3::doExecute] object " 
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
        msg << "[GDBIconBuilderBSDL3::doExecute] cannot handle object type " 
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
    setview.setResolution(myIconSizeX,myIconSizeY);
    setview.execute(world3D);
  } else {
    camera->getViewing()->setResolution(myIconSizeX,myIconSizeY);
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
  myTarget->setFormat(myTargetFormat);
  myTarget->setType(myTargetType);

  //
  // Write image to database
  // 
  PBinary* binary = myTarget->getBinaryData();
  if (binary == NULL) {
    binary = new PBinary(myTarget->getDataBase());
  }
  binary->setFiletype("ppm");
  binary->loadFile("gdb2.tmp");
  binary->markChanged();
  myTarget->setBinaryData(binary);
  myTarget->setSource(mySource);  // set target to source relation
  myTarget->markChanged();
  mySource->setIcon(myTarget);
  mySource->markChanged();
  return true;
}
