/*
 * $RCSfile: triangulate.C,v $ 
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
 *  $Id: triangulate.C,v 1.15 1996/08/01 12:01:24 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/ReportConfigurationHandler.h"

#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/Triangulator.h"
#include "booga/component/ConfigurationHandlers.h"

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
  
  //
  // Read scene
  //
  BSDL3DParser parser;
  World3D* world3D = new World3D;
  
  if (argc == 2)
    parser.setFilename(argv[1]);
  parser.execute(world3D);

  //
  // Process scene
  //
  Triangulator triang(std::cout);
  triang.execute(world3D);
  
  return 0;
}
