/*
 * $RCSfile: zbuffer.C,v $
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: zbuffer.C,v 1.28 1996/08/01 12:02:03 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h>

#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/ZBuffer.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/ConfigurationHandlers.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, RCString& interpol);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));
  Configuration::setOption(Name("Statistic.OutputStream"),Name("cerr"));
  
  initBSDLParserGlobalNS();
  initBSDLParser3DNS();
  
  RCString in, out, interpol("Flat");
  parseCmdLine(argc, argv, in, out, interpol);
  
  if (!Configuration::setOption(Name("ZBuffer.TriangleInterpolator"), Name(interpol)))
    Report::error("Unknown Shader \"" + interpol + "\"");
    
  //
  // Read scene
  //
  World3D* world3D = new World3D;
  Parser3D parser;
  parser.setFilename(in);
  
  setExecTime(parser.execute(world3D), "zbuffer: 1: Parsing");
  
  //
  // Print scene
  //
  PrintWorld3D printer(cerr);
  printer.execute(world3D);

  //
  // Process scene
  //
  ZBuffer zbuffer;
  World2D* world2D;
  setExecTime(world2D=zbuffer.execute(world3D), "zbuffer: 2: Rendering");

  //
  // Write image(s)
  //
  PixiWriter writer(out);
  setExecTime(writer.execute(world2D), "zbuffer: 3: Writing output");

  delete world3D;
  delete world2D;

  //
  // Write out statistics
  //
  Statistic::print();

  return 0;
}

void parseCmdLine(int argc, char* argv[], 
                  RCString& in, RCString& out, RCString& interpol)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>5) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;  
  if (!strcmp(argv[cur],"-s")) {
    interpol = argv[++cur];
    cur++;
  }
  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
    cerr << "Usage: " << name << " [-s shading] [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  shading  : (optional) ( Flat | Gouraud | Phong )\n";
    cerr << "  in-file  : (optional) filename of input\n";
    cerr << "  out-file : (optional) filename of output\n";
}

