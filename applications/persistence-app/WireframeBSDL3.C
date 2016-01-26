/*
 * $RCSfile: WireframeBSDL3.C,v $
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
 *  $Id: WireframeBSDL3.C,v 1.4 1996/10/09 14:13:51 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "WireframeBSDL3.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Rasterizer.h"
#include "booga/component/Wireframe.h"
#include "booga/component/PPMWriter.h"
#include "GDBExport.h"
#include "GDBStore.h"

//_____________________________________________________________________ WireframeBSDL3

implementRTTI(WireframeBSDL3, GDBOperation);

WireframeBSDL3::WireframeBSDL3(RCString inputType) :
GDBOperation(RCString("BOOGA Wireframe"), inputType, RCString("BSDL3"), 
                                RCString("Icon"), RCString("ppm"))
{
}

bool WireframeBSDL3::doExecute() {
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
  Wireframe wireframe;
  World2D* generatedPixmap = NULL;

  World2D* world2D = wireframe.execute(world3D);
  Rasterizer rasterizer;
  generatedPixmap = rasterizer.execute(world2D);
  delete world2D;
    
  //
  // Write image to tmp
  //
  PPMWriter writer("gdb2.tmp");
  writer.execute(generatedPixmap);
  delete generatedPixmap;
  return true;
}
