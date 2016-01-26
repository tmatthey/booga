/*
 * $RCSfile: depth2grey.C,v $ 
 *
 * Extract depth map from a pixi and convert it to a grey scale image.
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
 *  $Id: depth2grey.C,v 1.10 1996/08/01 11:59:41 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h>  // exit() 
#include <stdio.h>
#include <string.h>

#include "booga/base/mathutilities.h"
#include "booga/base/RCString.h"
#include "booga/base/Configuration.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapOf.h"
#include "booga/base/ColorTypes.h"
#include "booga/pixmapOp/ExtractChannel.h"

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
  
  AbstractPixmap* pm = new PixmapOf<RGB>(in);
  
  //
  // Depth channel is set to MAXFLOAT for all background pixels.
  // This results in a B/W picture, due to range scaling.
  //
  float value;
  for (long p=pm->getSize()-1; p>=0; p--) {
    pm->setPosition(p);
    pm->getDepth(value);
    if (equal(value, MAXFLOAT))
      pm->setDepth(0);
  }

  ExtractChannel extract;
  extract.adoptPixmapExemplar(new PixmapOf<Grey>(1,1));
  extract.selectDepth();
  AbstractPixmap* newPm = extract.generate(pm);
      
  newPm->save(out);

  delete pm;
  delete newPm;

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

