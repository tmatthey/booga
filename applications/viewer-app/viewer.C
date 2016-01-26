/*
 * $RCSfile: viewer.C,v $
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
 *  $Id: viewer.C,v 1.2 1996/08/04 14:42:31 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef HAVE_OPENGL

#include "booga/base/ReportConfigurationHandler.h"

#include "booga/component/Parser3D.h"
#include "booga/component/BSDL2DParser.h"
#include "booga/component/ConfigurationHandlers.h"
#include "booga/glwrapper/GLBSDLParserInit.h"
#include "booga/glwrapper/GLViewer2D.h"
#include "booga/glwrapper/GLViewer3D.h"

//_____________________________________________________________________ Globals

RCString filename;

//__________________________________________________________________ Initialiser
 
static void parseCmdLine(int argc, char* argv[]);
static void usage(const RCString& name);

//__________________________________________________________________ Applikation

int main(int argc, char* argv[])
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  parseCmdLine(argc, argv);

  initGLBSDLParserGlobalNS();
  initGLBSDLParser3DNS();
  initGLBSDLParser2DNS();

  if (strstr(filename.chars(), ".bsdl2")) {
    World2D* world = new World2D;

    BSDL2DParser parser;
    parser.setFilename(filename);
    parser.execute(world);

    // 
    //  Start displaying of scene.
    //
    GLViewer2D viewer;
    viewer.execute(world);
  }
  else {  // I guess its a 3D world.
    World3D* world = new World3D;

    Parser3D parser;
    parser.setFilename(filename);
    parser.execute(world);

    // 
    //  Start displaying of scene.
    //
    GLViewer3D viewer;
    viewer.execute(world);
  }

  return 0;
}


void parseCmdLine(int argc, char* argv[])
{
  if (argc >= 2 && !strcmp(argv[1], "-h")) {
    usage(argv[0]);
    exit(0);
  }
    
  if (argc >= 2) 
    filename = argv[argc-1];
}

void usage(const RCString& name)
{
  cerr << "Usage: " << name << " [in-file]\n";
  cerr << " where:\n";
  cerr << "  in-file  : (optional) filename of input\n";
}


#else // HAVE_OPENGL -----------------------------------------------------------

#include <stream.h>

int main ()
{
  cerr << "\nThis application needs the OpenGL graphics package.\n" 
       << "When compiling this application your site was \n"
       << "configured not to use OpenGL.\n\n";
}

#endif // HAVE_OPENGL

