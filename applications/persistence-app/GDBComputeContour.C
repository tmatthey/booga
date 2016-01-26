/*
 * $RCSfile: GDBComputeContour.C,v $
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
 *  $Id: GDBComputeContour.C,v 1.1 1996/10/09 14:12:02 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "GDBData.h"
#include "GDBComputeContour.h"
#include "GDBExport.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/object/Polygon2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Viewing2D.h"
#include "booga/component/SingleFileStore.h"
#include "booga/pixmapOp/ImageReaders.h"
#include "booga/component/ReadImage.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/PixmapGeneratorWrapper.h"
#include "booga/component/Rasterizer.h"
#include "booga/component/BSDL2DWriter.h"
#include "ComputeBoundary.h"
#include "Boundary2D.h"

//_____________________________________________________________________ GDBComputeContour

implementRTTI(GDBComputeContour, GDBOperation);
GDBComputeContour::GDBComputeContour() :
GDBOperation(RCString("Contour Computer"), RCString("Icon"), RCString("ppm"), 
                                RCString("Image"), RCString("ppm"))
{
}

GDBComputeContour::~GDBComputeContour() {}

bool GDBComputeContour::doExecute() {
  GDBExport exporter;
  exporter.execute(mySource->getPOId(), POID_NULL);

  World2D* world2D = new World2D;

  ReadImage reader;
  reader.setFilename(exporter.getFilename());
  reader.execute(world2D);
  if (reader.hasFailed()) {
    Report::recoverable("[GDBComputeContour::doExecute()] Could not read input file due to prior error(s)");
    failed();
    return false;
  }

  Boundary2D boundarizer;
  
  boundarizer.execute(world2D);
  SingleFileStore sf("gdb4.tmp");
  BSDL2DWriter writer2D(sf);
  writer2D.execute(world2D);
  PPMWriter writer(RCString("gdb1.tmp"));
  writer.execute(world2D);
  delete world2D;
  
//  ComputeBoundary boundaryComputer;
//  PixmapGeneratorWrapper ppmComputeBoundary(&boundaryComputer);
//
//  World2D* boundaryWorld;
//  boundaryWorld = ppmComputeBoundary.execute(world2D);
//  PPMWriter writer(RCString("gdb1.tmp"));
//  writer.execute(boundaryWorld);
//  delete world2D;
//  delete boundaryWorld;
//    
//  Polygon2D exactContour(boundaryComputer.getBoundaryPoints());
//  Polygon2D approxContour(exactContour.computeApproximation(32,1.0));
//  
//  World2D* approxWorld = new World2D;
//  approxWorld->getObjects()->adoptObject(&approxContour);
//  Camera2D camera;
//  camera.setBackground(Color(0.,0.,0.));
//  camera.getViewing()->setResolution(100,100);
//  camera.getViewing()->setWindow(Vector2D(0.,0.),Vector2D(100.,100.));
//  approxWorld->getObjects()->adoptObject(&camera);
//
//  SingleFileStore sf("gdb4.tmp");
//  BSDL2DWriter writer2D(sf);
//  writer2D.execute(approxWorld);
//
//  Rasterizer rasterizer;
//  World2D* generatedPixmap;
//  generatedPixmap = rasterizer.execute(approxWorld);
//  delete approxWorld;
//
//  PPMWriter writer2(RCString("gdb2.tmp"));
//  writer2.execute(generatedPixmap);
//  delete generatedPixmap;

  return true;
}

