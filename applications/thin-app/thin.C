/*
 * thin.C 
 *
 * Copyright (C) 1995, Daniel Moeri <moeri@iam.unibe.ch>
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
 *  $Id: thin.C,v 1.6 1995/10/18 12:21:28 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include <stdio.h>
#include <string.h>

#include "booga/base/RCString.h"
#include "booga/base/Timer.h"
#include "booga/base/Configuration.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapOf.h"
#include "booga/base/ColorTypes.h"
#include "booga/pixmapOp/LabelConnectedComponents.h"
#include "booga/pixmapOp/ExtractChannel.h"
#include "booga/pixmapOp/Thin.h"

static void usage(RCString name);
static void parseCmdLine(int, char*[], int&, bool&, float&, EWriteOption&, RCString&, RCString&);

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  int verbose = 0;
  bool labelOption = false;
  float background = 0;
  EWriteOption writeOption = IMAGE;
  RCString in, out;
  
  parseCmdLine(argc, argv, verbose, labelOption, background, writeOption, in, out);
  
  Timer t;
  t.start();

  AbstractPixmap* pm = new PixmapOf<Grey>(in);
  t.lap();
  std::cerr << "read  -> " << t.getLapTime() << std::endl;
  
  LabelConnectedComponents label(writeOption, verbose);

  if (labelOption) {
    if (background)
      label.setBackground(background);
    
    label.apply(pm);
    t.lap();
    std::cerr << "label -> " << t.getLapTime() << std::endl;
  }
  
  Thin thin(verbose);
  
  if (labelOption) {
    thin.setNumber(label.getNumber());
    thin.setSourceChannel(label.getTargetChannel());
    thin.setObjects(label.getObjects());
  }
  
  thin.apply(pm);
  t.lap();
  std::cerr << "thin  -> " << t.getLapTime() << std::endl;
  
  if (label.getTargetChannel() >= 0) {
    ExtractChannel extract;
    extract.selectUserChannel(label.getTargetChannel());
    AbstractPixmap* savepm = extract.generate(pm);
    savepm->save(out);
  }
  else
    pm->save(out);
  t.lap();
  std::cerr << "save  -> " << t.getLapTime() << std::endl;

  delete pm;
  
  std::cerr << "----------------------------" << std::endl;
  std::cerr << "all   -> " << t.getTime() << std::endl;
  return(0);
}

void parseCmdLine(int argc, char* argv[], int& verbose, bool& labelOption, float& bg, EWriteOption &writeOption, RCString& in, RCString& out)
{
  int temp;

  for(int i=1; i<argc; i++) {
    if (argv[i][0] == '-') {
      switch(argv[i][1]) {
      case 'h':
	usage(argv[0]);
	exit(0);
      case 'b':
	if (
	    (sscanf(argv[++i], "%f", &bg) != 1)
	    ||
	    (bg < 0)
	    ||
	    (bg > 1)
	    ) {
	  usage(argv[0]);
	  exit(1);
	}
	break;
      case 'v':
	verbose = 1;
	break;
      case 'w':
	if (
	    (sscanf(argv[++i], "%d", &temp) != 1)
	    ||
	    (
	     (temp != 0)
	     &&
	     (temp != 1)
	     )
	    ) {
	  usage(argv[0]);
	  exit(1);
	}
 	labelOption = true;
	writeOption = (EWriteOption) temp;
	break;
     default:
	usage(argv[0]);
	exit(1);
	break;
      }  
    }
    else {
      in = argv[i];
      if ((i+1) < argc)
	out = argv[++i];
    }
  }
}

void usage(RCString name)
{
    std::cerr << "\nUsage:\t" << name << " [-h] [-b background_color] [-w write_option] [-v]\n";
    std::cerr << "\t[in-file [out-file]]\n";
    std::cerr << "where:\n";
    std::cerr << "  -h                  : print this\n";
    std::cerr << "  -v                  : (optional) verbose (default: no information)\n";
    std::cerr << "  -b background_color : (optional) set background_color (float) for labeling\n";
    std::cerr << "                           => 0==black (default) <= value <= 1==white\n";
    std::cerr << "  -w write_option     : (optional) labeling before thinning (default: no)\n";
    std::cerr << "                           write_option for result: 0 => IMAGE, 1 => CHANNEL\n";
    std::cerr << "  in-file             : (optional) filename of input\n";
    std::cerr << "  out-file            : (optional) filename of output\n\n";
}
  
