/*
 * $RCSfile: wireframe.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: wireframe.C,v 1.18 1996/08/01 12:01:42 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/ReportConfigurationHandler.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/BSDL2DWriter.h"
#include "booga/component/PixiWriter.h"
#include "booga/component/Rasterizer.h"
#include "booga/component/PSWriter2D.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/PrintWorld2D.h"
#include "booga/component/Wireframe.h"
#include "booga/component/OversamplingAntialiaser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/component/SingleFileStore.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         bool& bsdl, bool& print, bool& sort, bool& optimize, 
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
  bool bsdl = false;
  bool print = false;
  bool sort = false;
  bool optimize = false;
  parseCmdLine(argc, argv, bsdl, print, sort, optimize, in, out);

  //
  // Read scene
  //
  World3D* world3D = new World3D;
  Parser3D parser;
  parser.setFilename(in);
  parser.execute(world3D);

  //
  // Print scene
  //
  if (print){
    PrintWorld3D printer(std::cerr);
    printer.execute(world3D);
  }

  //
  // Process scene
  //
  Wireframe wireframe;
  wireframe.setOptimizeList(optimize);
  wireframe.setSortList(sort);
  World2D* world2D = wireframe.execute(world3D);
    
  //
  // Write image(s)
  //
  if (bsdl) {
    DocumentStore* docuStore = new SingleFileStore(out);
    BSDL2DWriter writer(*docuStore);
    writer.execute(world2D);
  }
  else {
    PSWriter2D* writer;
    if (!out.isEmpty())
      writer = new PSWriter2D(out);
    else
      writer = new PSWriter2D;

    writer->execute(world2D);
  }

  delete world3D;
  delete world2D;

  return 0;
}

void parseCmdLine(int argc, char* argv[], bool& bsdl, bool& print, bool& sort, bool& optimize, RCString& in, RCString& out)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>8) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;  

  while (cur<argc && argv[cur][0]=='-') {
 
    if (!strcmp(argv[cur],"--bsdl")){
      bsdl = true;
      cur++;
      continue;
    }
     
    if (!strcmp(argv[cur],"--print")){
      print = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--sort")){
      sort = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"--optimize")){
      sort = true;
      optimize = true;
      cur++;
      continue;
    }

    break;

  }  
  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " --bsdl [in-file [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  --bsdl         : (optional) BSDL output\n";
    std::cerr << "  --print        : (optional) print scene for debugging purpose\n";
    std::cerr << "  --sort         : (optional) sort the output\n";
    std::cerr << "  --optimize     : (optional) sort and optimize the output\n";
    std::cerr << "  in-file        : (optional) filename of input\n";
    std::cerr << "  out-file       : (optional) filename of output\n";
}
 
