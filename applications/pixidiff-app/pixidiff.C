/*
 * gamma.C 
 *
 * Perform gamma correction on pixmap
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: pixidiff.C,v 1.1 1996/07/01 16:04:15 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "booga/base/RCString.h"
#include "booga/base/Configuration.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapOf.h"
#include "booga/base/ColorTypes.h"
#include "booga/pixmapOp/PixiDiff.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], RCString& in1, RCString& in2, RCString& out);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  RCString in1, in2, out;
  
  parseCmdLine(argc, argv, in1, in2, out);
  
  AbstractPixmap* pm1 = new PixmapOf<RGB>(in1);
  AbstractPixmap* pm2 = new PixmapOf<RGB>(in2);
  
  PixiDiff diff;
  diff.adoptPixmapExemplar(new PixmapOf<RGB>(1,1));
  diff.adoptReference(pm1);
  
  AbstractPixmap* newPm = diff.generate(pm2);

  if (newPm) {
    newPm->save(out);
    delete newPm;
  }
  
  return 0;  
}

void parseCmdLine(int argc, char* argv[], 
                  RCString& in1, RCString& in2, RCString& out)
{
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  
  if (!strcmp(argv[1], "-h")) {
    usage(argv[0]);
    exit(0);
  }
  
  in1 = argv[1];
  
  if (argc >= 3) 
    in2 = argv[2];
    
  if (argc == 4)
    out = argv[3];
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [-h] in-file [in-file [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  -h       : print this message\n";
    std::cerr << "  in-file  : (mandatory) filename of input 1\n";
    std::cerr << "  in-file  : (optional)  filename of input 2\n";
    std::cerr << "  out-file : (optional)  filename of output\n";
}
