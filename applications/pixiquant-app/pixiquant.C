/*
 * $RCSfile: pixiquant.C,v $ 
 *
 * Perform color quantisation on a pixmap
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: pixiquant.C,v 1.3 1996/08/01 12:00:33 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <stdlib.h>     // atoi()
#include <string.h>     // strcmp()
#include <strstream.h>  // class ostrstream

#include "booga/base/RCString.h"
#include "booga/base/Configuration.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapOf.h"
#include "booga/base/ColorTypes.h"
#include "booga/pixmapOp/NeuroQuantize.h"

static void usage(const RCString& name);
static void parseCmdLine(int argc, char* argv[], 
                         RCString& in, RCString& out, 
                         int& colors, int& samplingFactor);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  int colors = 256;
  int samplingFactor = 5;
  RCString in, out;
  
  parseCmdLine(argc, argv, in, out, colors, samplingFactor);
  
  AbstractPixmap* pm = new PixmapOf<RGB>(in);
  
  NeuroQuantize quantize;
  quantize.setMaxColors(colors);
  quantize.setSamplingFactor(samplingFactor);
  quantize.apply(pm);
  
  pm->save(out);

  delete pm;

  return 0;  
}

void parseCmdLine(int argc, char* argv[], RCString& in, RCString& out, 
                  int& colors, int& samplingFactor)
{
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>5) {
    usage(argv[0]);
    exit(0);
  }
  
  int cur = 1;  
  if (cur < argc) {
    if (!strcmp(argv[cur],"-n")) {
      colors = atoi(argv[++cur]);
      cur++;
    }
  }
  
  if (cur < argc) {
    if (!strcmp(argv[cur],"-s")) {
      samplingFactor = atoi(argv[++cur]);
      cur++;
    }
  }
  
  if (cur < argc) 
    in = argv[cur++];
  if (cur < argc)
    out = argv[cur];
}

void usage(const RCString& name)
{
    cerr << "Usage: " << name << " [-h] [-n colors] [-s factor] [in-file [out-file]]\n";
    cerr << " where:\n";
    cerr << "  -h         : print this message\n";
    cerr << "  -n color   : (optional) 256 <= color > 0\n";
    cerr << "  -s factor  : (optional) 30 <= sampling factor > 0\n";
    cerr << "  in-file    : (optional) filename of input\n";
    cerr << "  out-file   : (optional) filename of output\n";
}
