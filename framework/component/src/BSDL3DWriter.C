/*
 * $RCSfile: BSDL3DWriter.C,v $
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
 *  $Id: BSDL3DWriter.C,v 1.3 1996/10/04 09:45:53 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
//_____________________________________________________________________ BSDL3DWriter


#include <sstream>  // STDOUT_FILENO

#include "booga/component/BSDL3DWriter.h"

implementRTTI(BSDL3DWriter, Operation3D);

BSDL3DWriter::BSDL3DWriter(DocumentStore& docuStore) :
myBSDLWriter(docuStore)
{
}

BSDL3DWriter::~BSDL3DWriter()
{
}

bool BSDL3DWriter::doExecute() {
  myBSDLWriter.execute(getWorld());
  return true;
}

