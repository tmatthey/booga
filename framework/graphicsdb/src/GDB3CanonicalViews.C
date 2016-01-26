/*
 * $RCSfile: GDB3CanonicalViews.C,v $
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
 *  $Id: GDB3CanonicalViews.C,v 1.2 1997/02/20 09:30:18 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/graphicsdb/GDB3CanonicalViews.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/BSDL2DWriter.h"
#include "booga/component/SingleFileStore.h"
#include "booga/component/SetStandardView3D.h"
#include "booga/object/Object3D.h"
#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Sphere3D.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/PointLight.h"
#include "booga/object/Texture3D.h"
#include "booga/object/Camera2D.h"
#include "booga/component/Boundary2D.h"
#include "booga/graphicsdb/GDBExport.h"
#include "booga/graphicsdb/GDBStore.h"
#include "booga/graphicsdb/GraphicsDataBase.h"

//_____________________________________________________________________ GDB3CanonicalViews

implementRTTI(GDB3CanonicalViews, GDBOperation);

GDB3CanonicalViews::GDB3CanonicalViews(DataBase& aDB,
GDBDataType* sourceType, GDBRepType* sourceRep,
GDBDataType* targetType, GDBRepType* targetRep,
int xsize, int ysize) :
GDBOperation(aDB, RCString("CanonicalViews"), 
             sourceType, sourceRep, targetType, targetRep),
myIconSizeX(xsize),
myIconSizeY(ysize),
myMaxBoundaryPoints(64),
myBoundaryPrecision(0.5)
{
}

GDB3CanonicalViews::GDB3CanonicalViews(Prototype aPrototype) :
GDBOperation(aPrototype),
myIconSizeX(100),
myIconSizeY(100),
myMaxBoundaryPoints(64),
myBoundaryPrecision(0.5)
{
}

GDB3CanonicalViews::~GDB3CanonicalViews() 
{
}

Persistent* GDB3CanonicalViews::newInstance() {
  return new GDB3CanonicalViews(aPrototype);
}

bool GDB3CanonicalViews::doExecute() {

  Value value;
  if (getConfigValue(RCString("Resolution"), value)) {
    std::stringstream ss;
    ss << value;
    Vector2D resol;
    ss >> resol;
    myIconSizeX = (int) resol.x();
    myIconSizeY = (int) resol.y();
  }
  if (getConfigValue(RCString("MaxBoundaryPoints"), value)) {
    std::stringstream ss;
    ss << value;
    ss >> myMaxBoundaryPoints;
  }
  if (getConfigValue(RCString("BoundaryPrecision"), value)) {
    std::stringstream ss;
    ss << value;
    ss >> myBoundaryPrecision;
  }
  World3D *world3D = new World3D;
  // 
  // Read scene from database into tmp file
  //
  GDBOperation* op = GraphicsDataBase::getTheGraphicsDataBase()->getOperation("Exporter");
  GDBExport *exporter = dynamic_cast<GDBExport*>(op);
  if (exporter == NULL) {
    Report::recoverable("[IconBuilderForBSDL3::doExecute()] GDBOperation 'Exporter' not found");
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
  // If there is no instance of an object create one and insert it into the world3D
  // 
  if (world3D->getObjects()->countSubobject() == 0) {
    std::stringstream os;
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
        std::stringstream msg;
        msg << "[GDB3CanonicalViews::doExecute] object " 
            << objectName << " not found after parsing";
        Report::recoverable(msg);
        failed();
        return false;
      }
    }
    Object3D *obj = dynamic_cast<Object3D*>(makeable);
    if (obj == NULL) {
      Texture3D *texture = dynamic_cast<Texture3D*>(makeable);
      if (texture == NULL) {
        std::stringstream msg;
        msg << "[GDB3CanonicalViews::doExecute] cannot handle object type " 
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
  
  //
  //  add a camera and light
  //  
  SetStandardView3D setview;
  setview.setResolution(myIconSizeX, myIconSizeY);
  setview.setHFov(dtor(5.)); // nearly parallel projection
  World2D* world2D;
  World2D* all = new World2D;
  Raytracer raytrace;
  
  //
  // Process scene1
  // 
  setview.setViewPlane(Viewing3D::XZ_PLANE);
  setview.execute(world3D);
  world2D = raytrace.execute(world3D);

  RCString filename = mySource->getName() + RCString("1.ppm");
  PPMWriter writer(filename);
  writer.execute(world2D);
  int i;
  for (i=0; i<world2D->getObjects()->countSubobject(); i++) {
    Object2D* obj = world2D->getObjects()->getSubobject(0);
    world2D->getObjects()->orphanObject(obj);
    obj->addTransform(Transform2D(TransMatrix2D::makeTranslate(0,0)));
    all->getObjects()->adoptObject(obj);
  }
  delete world2D;

  //
  // Process scene2
  // 
  setview.setViewPlane(Viewing3D::YZ_PLANE);
  setview.execute(world3D);
  world2D = raytrace.execute(world3D);

  filename = mySource->getName() + RCString("2.ppm");
  PPMWriter writer2(filename);
  writer2.execute(world2D);
  for (i=0; i<world2D->getObjects()->countSubobject(); i++) {
    Object2D* obj = world2D->getObjects()->getSubobject(0);
    world2D->getObjects()->orphanObject(obj);
    obj->addTransform(Transform2D(TransMatrix2D::makeTranslate(1.1*myIconSizeX,0)));
    all->getObjects()->adoptObject(obj);
  }
  delete world2D;

  //
  // Process scene3
  // 
  setview.setViewPlane(Viewing3D::XY_PLANE);
  setview.execute(world3D);
  world2D = raytrace.execute(world3D);

  filename = mySource->getName() + RCString("3.ppm");
  PPMWriter writer3(filename);
  writer3.execute(world2D);
  for (i=0; i<world2D->getObjects()->countSubobject(); i++) {
    Object2D* obj = world2D->getObjects()->getSubobject(0);
    world2D->getObjects()->orphanObject(obj);
    obj->addTransform(Transform2D(TransMatrix2D::makeTranslate(2.2*myIconSizeX,0)));
    all->getObjects()->adoptObject(obj);
  }
  delete world2D;

  Camera2D* cam = new Camera2D;
  cam->getViewing()->setResolution((int) (myIconSizeX*3.3), myIconSizeY);
  cam->getViewing()->setWindow(Vector2D(0.,0.), Vector2D(myIconSizeX*3.3, myIconSizeY));
  all->getObjects()->adoptObject(cam);

  Boundary2D boundarizer(myMaxBoundaryPoints, myBoundaryPrecision);
  boundarizer.execute(all);

  filename = mySource->getName() + RCString(".bsdl2");
  SingleFileStore sf(filename);
  BSDL2DWriter writer2D(sf);
  writer2D.execute(all);
  return true;
}
