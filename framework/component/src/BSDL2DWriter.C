/*
 * $RCSfile: BSDL2DWriter.C,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: BSDL2DWriter.C,v 1.3 1996/10/04 09:45:51 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
//_____________________________________________________________________ BSDL2DWriter


#include <sstream>  // STDOUT_FILENO

#include "booga/component/BSDL2DWriter.h"

implementRTTI(BSDL2DWriter, Operation2D);

BSDL2DWriter::BSDL2DWriter(DocumentStore& docuStore) :
myBSDLWriter(docuStore)
{
}

BSDL2DWriter::~BSDL2DWriter()
{
}

bool BSDL2DWriter::doExecute() {
  myBSDLWriter.execute(getWorld());
  return true;
}

