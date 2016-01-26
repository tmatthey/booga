/*
 * PixmapOption.C 
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: PixmapOption.C,v 1.3 1995/10/18 10:09:16 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/PixmapOption.h"
#include "booga/base/AbstractPixmap.h"

//_________________________________________________________________ PixmapOption

implementRTTI(PixmapOption, Option);

PixmapOption::PixmapOption(const PixmapOption& option)
{
  if (option.myPixmap == NULL)
    myPixmap = NULL;
  else
    myPixmap = option.myPixmap->copy();
}

PixmapOption::PixmapOption(AbstractPixmap* adoptPixmap)
{
  myPixmap = adoptPixmap;
}

PixmapOption::~PixmapOption()
{
  delete myPixmap;
}

Option* PixmapOption::copy() const
{
  return new PixmapOption(*this);
}
