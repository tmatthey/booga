/*
 * $RCSfile: PixmapUtilities.h,v $
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
 *  $Id: PixmapUtilities.h,v 1.2 1996/08/09 14:53:17 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapUtilities_H
#define _PixmapUtilities_H

#include "booga/base/PrimitiveTypes.h"

class AbstractPixmap;

//____________________________________________________ PixmapUtilities

class PixmapUtilities  {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PixmapUtilities();                                  // No construction
  PixmapUtilities(const PixmapUtilities&);            // No copies.

private:
  ~PixmapUtilities();                                 // No destruction

private:
  PixmapUtilities& operator=(const PixmapUtilities&); // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PixmapUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static unsigned char* createPPMPicture(bool& didCut, 
                                         const AbstractPixmap* pixi);
  // Create a PPM Picture of the same size as the pixi but with
  // only 8 Bits per channel.
  // If didCut holds true, at least one Pixel had to be cut down
  // in color space.

  friend class _dummy;
  // Avoid warning about private ctor/dtor and no friends.
};

//______________________________________________________________________ INLINES

#endif // _PixmapUtilities_H

