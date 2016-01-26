/*
 * $RCSfile: RaytraceBSDL3.C,v $
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
 *  $Id: RaytraceBSDL3.C,v 1.4 1996/10/09 14:13:35 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "RaytraceBSDL3.h"
#include "booga/component/Parser3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Raytracer.h"
#include "booga/component/PPMWriter.h"
#include "GDBExport.h"
#include "GDBStore.h"

//_____________________________________________________________________ RaytraceBSDL3

implementRTTI(RaytraceBSDL3, GDBOperation);

RaytraceBSDL3::RaytraceBSDL3(RCString inputType) :
GDBOperation(RCString("BOOGA Raytracer"), inputType, RCString("BSDL3"), 
                                RCString("Icon"), RCString("ppm"))
{
}

bool RaytraceBSDL3::doExecute() {
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
  // Process scene
  //
  Raytracer raytrace;
  World2D* world2D;
  world2D=raytrace.execute(world3D);

  //
  // Write image to tmp
  //
  PPMWriter writer("gdb2.tmp");
  writer.execute(world2D);
  delete world2D;

  //
  // Create target object on database (if necessary)
  // 
  if (myTarget == NULL) {
    // we have to create a new GDBObject
    myTarget = new GDBData(mySource->getDataBase(), mySource->getName());
  }
  myTarget->setType("Image");
  myTarget->setFormat("ppm");

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

  //
  // set source to target relation
  //
  PRef<GDBData> targetRef(myTarget);
  if (!mySource->getTarget().isElement(myTarget)) {
    mySource->addTarget(myTarget);
    mySource->write();
  }

  ostrstream ss;
  ss << "[RaytraceBSDL3::doExecute] wrote PPM Image " 
     << myTarget->getPOId() << " " << myTarget->getName();
  Report::hint(ss);
  return true;
}
