/*
 * ReferenceCounting.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ReferenceCounting.C,v 1.2 1995/04/21 12:35:04 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/base/ReferenceCounting.h"

//_____________________________________________________________________ RCLetter

RCLetter::~RCLetter() {}

//___________________________________________________________________ RCEnvelope

RCEnvelope::~RCEnvelope() 
{
  if (myLetter->deref() <= 0)
    delete myLetter;
}

void RCEnvelope::rcAssign(const RCEnvelope& envelope)
{
  if (this == &envelope)
    return;

  if (myLetter->deref() <= 0)
    delete myLetter;

  myLetter = envelope.myLetter;
  myLetter->ref();
}

