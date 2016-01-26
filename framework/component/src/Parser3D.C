/*
 * $RCSfile: Parser3D.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Parser3D.C,v 1.2 1996/08/01 12:00:22 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h>
#include "booga/component/VRMLParser.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/Parser3D.h"

//_________________________________________________________________ Parser3D

implementRTTI(Parser3D, Operation3D);

bool Parser3D::doExecute()
{
  if (strstr(myFilename.chars(), ".wrl")) {
    VRMLParser parser;
    parser.setFilename(myFilename);
    parser.execute(getWorld());

    if (parser.hasFailed())
      return false;
  }
  else {
    BSDL3DParser parser;
    parser.setFilename(myFilename);
    parser.addCppParameters(myCppParameters);
    parser.execute(getWorld());
    
    if (parser.hasFailed())
      return false;
  }
  
  return true;
}

void Parser3D::setFilename(const RCString& filename)
{
  myFilename = filename;
}
