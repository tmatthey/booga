/*
 * $RCSfile: pixi2ppm.C,v $ 
 *
 * Convert pixi to ppm
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: pixi2ppm.C,v 1.17 1996/08/01 12:00:31 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h> // strcmp
#include <stdlib.h> // exit 
  
#include "booga/base/Configuration.h"
#include "booga/pixmapOp/ImageReaders.h"
#include "booga/component/ReadImage.h"
#include "booga/component/JPEGWriter.h"
#include "booga/component/ConfigurationHandlers.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  RCString in, out;
  
  parseCmdLine(argc, argv, in, out);

  ReadImage reader;
  reader.setFilename(in);
  World2D* world = new World2D;

  reader.execute(world);

  // Test, ob OK
  if (reader.hasFailed()) {
    Report::error("Could not read input file due to prior error(s)");
    return 1;
  }

  JPEGWriter writer(out);
  writer.execute(world);

  // Test, ob OK
  if (writer.hasFailed()) {
    Report::error("Could not write output file due to prior error(s)");
    return 1;
  }

  delete world;
  
  return 0;
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>3) {
    usage(argv[0]);
    exit(0);
  }
    
  if (argc >= 2) 
    in = argv[1];
  if (argc == 3)
    out = argv[2];
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [in-file [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  in-file  : (optional) filename of input\n";
    std::cerr << "  out-file : (optional) filename of output\n";
}

