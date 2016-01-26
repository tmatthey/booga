/*
 * $RCSfile: bsdl2ray.C,v $ 
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
 *  $Id: bsdl2ray.C,v 1.3 1996/08/01 11:58:58 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/RayshadeWriter.h"
#include "booga/component/ConfigurationHandlers.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
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
  
  parseCmdLine(argc, argv, in, out);

  //
  // Read scene
  //
  World3D* world3D = new World3D;
  BSDL3DParser parser;
  parser.setFilename(in);
  parser.execute(world3D);
  
  //
  // Convert to rayshade format.
  //
  RayshadeWriter writer(out);
  writer.execute(world3D);

  delete world3D;

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
    cerr << "Usage: " << name << " [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  in-file        : (optional) filename of input\n";
    cerr << "  out-file       : (optional) filename of output\n";
}

