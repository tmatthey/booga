/*
 * $RSCfile:$
 *
 * Perform gamma correction on pixmap
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
 *  $Id: gamma.C,v 1.11 1996/08/01 11:59:46 streit Exp $
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
#include "booga/pixmapOp/GammaCorrection.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], float& gamma, RCString& in, RCString& out);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  float gamma;
  RCString in, out;
  
  parseCmdLine(argc, argv, gamma, in, out);
  
  AbstractPixmap* pm = new PixmapOf<RGB>(in);
  
  GammaCorrection gammaCor;
  gammaCor.setGamma(gamma);
  
  gammaCor.apply(pm);
  
  pm->save(out);

  delete pm;

  return 0;  
}

void parseCmdLine(int argc, char* argv[], float& gamma, RCString& in, RCString& out)
{
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }
  
  if (!strcmp(argv[1], "-h")) {
    usage(argv[0]);
    exit(0);
  }
  
  sscanf(argv[1], "%f", &gamma);
  if (gamma <= 0) {
    usage(argv[0]);
    exit(1);
  }
  
  if (argc >= 3) 
    in = argv[2];
  if (argc == 4)
    out = argv[3];
}

void usage(const RCString& name)
{
    std::cerr << "Usage: " << name << " [-h] gamma [in-file [out-file]]\n";
    std::cerr << " where:\n";
    std::cerr << "  -h       : print this message\n";
    std::cerr << "  gamma    : float value > 0\n";
    std::cerr << "  in-file  : (optional) filename of input\n";
    std::cerr << "  out-file : (optional) filename of output\n";
}
