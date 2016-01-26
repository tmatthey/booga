/*
 * ColorTransformation.h
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
 *  $Id: ColorTransformation.h,v 1.5 1996/07/05 11:43:55 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ColorTransformation_H
#define _ColorTransformation_H

#include "booga/pixmapOp/PixmapGenerator.h"

//__________________________________________________________ ColorTransformation

class ColorTransformation : public PixmapGenerator {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  ColorTransformation();
private:
  ColorTransformation(const ColorTransformation&);	         // No copies.

public:
  // virtual ~ColorTransformation();   // Use default version.

private:
  ColorTransformation& operator=(const ColorTransformation&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class PixmapGenerator
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual AbstractPixmap* generate(const AbstractPixmap* pm);
};

#endif // _ColorTransformation_H

