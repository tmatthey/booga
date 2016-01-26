/*
 * LabelConnectedComponents.h
 *
 * Copyright (C) 1995, Daniel Moeri <moeri@iam.unibe.ch>
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
 *  $Id: LabelConnectedComponents.h,v 1.3 1996/07/05 13:32:56 amann Exp $
 * ----------------------------------------------------------------------------
 */

#ifndef _LabelConnectedComponents_H
#define _LabelConnectedComponents_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/BoundingRect.h"
#include "booga/pixmapOp/PixmapTransformer.h"

#ifndef _EWO
#define _EWO
enum EWriteOption { IMAGE, NEW_CHANNEL, EXISTING_CHANNEL};
#endif

//____________________________________________________ LabelConnectedComponents

class LabelConnectedComponents : public PixmapTransformer {
public:
  LabelConnectedComponents(EWriteOption = IMAGE, int verbose=0);
  virtual ~LabelConnectedComponents();
  
  void setBackground(float background) { myBackground = background; };
  int  getNumber() const { return myNumber; };
  void setSourceChannel(int sourceChannel) { mySourceChannel = sourceChannel; };
  int  getSourceChannel() const { return mySourceChannel; };
  void setTargetChannel(int targetChannel) { myTargetChannel = targetChannel; };
  int  getTargetChannel() const { return myTargetChannel; };
  BoundingRect* getObjects() const { return myObjects; };

  virtual void apply(AbstractPixmap* pm);

private:
  LabelConnectedComponents(LabelConnectedComponents&);		          // No copies.
  LabelConnectedComponents& operator=(const LabelConnectedComponents&);	  // No assignments.

private:  
  float myBackground;		// Color to consider as background
  int myVerbose;		// Verbose flag
  int myNumber;			// Number of connected objects
  EWriteOption myWriteOption;   // -> myTargetChannel
  int mySourceChannel;		// Channel used for original "image"
  int myTargetChannel;		// Channel used for resulting "image"
  BoundingRect* myObjects;	// Bounding boxes of each object
}
;
#endif // _LabelConnectedComponents_H

