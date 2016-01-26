/*
 * Thin.h
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
 * ----------------------------------------------------------------------------
 *  $Id: Thin.h,v 1.3 1996/07/05 13:33:12 amann Exp $
 * ----------------------------------------------------------------------------
 */

#ifndef _Thin_H
#define _Thin_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/BoundingRect.h"
#include "booga/pixmapOp/PixmapTransformer.h"

#ifndef _EWO
#define _EWO
enum EWriteOption { IMAGE, NEW_CHANNEL, EXISTING_CHANNEL};
#endif

//_____________________________________________________________________ Thin

class Thin : public PixmapTransformer {
public:
  Thin(int verbose=0);
  virtual ~Thin();
  
  void setBackground(float background) { myBackground = background; };
  void setNumber(int number) { myNumber = number; };
  void setSourceChannel(int sourceChannel) { mySourceChannel = sourceChannel; };
  int  getSourceChannel() const { return mySourceChannel; };
  void setObjects(BoundingRect* objects) { myObjects = objects; };
  virtual void apply(AbstractPixmap* pm);

private:
  Thin(Thin&);			// No copies.
  Thin& operator=(const Thin&);	// No assignments.

private:  
  float myBackground;		// Color to consider as background
  int myVerbose;		// Verbose flag
  int myNumber;			// Number of connected objects
  EWriteOption myWriteOption;   // -> myTargetChannel
  int mySourceChannel;		// Channel used for original "image"
  BoundingRect* myObjects;	// Bounding boxes of each object
};
#endif // _Thin_H

