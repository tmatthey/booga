/*
 * ExtractChannel.h
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
 *  $Id: ExtractChannel.h,v 1.2 1995/08/28 07:04:29 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ExtractChannel_H
#define _ExtractChannel_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/pixmapOp/PixmapGenerator.h"

//_______________________________________________________________ ExtractChannel

class ExtractChannel : public PixmapGenerator {
public:
  ExtractChannel();
  // virtual ~ExtractChannel();  // Use default version.

  virtual AbstractPixmap* generate(const AbstractPixmap* pm);

  void selectUserChannel(int channel);
  void selectDepth();
  void selectAlpha();
  
private:
  bool haveChannel(const AbstractPixmap* pm) const;
  void getChannel(const AbstractPixmap* pm, float& value) const;
  
private:
  int myChannel;
  enum { ALPHA, DEPTH, USER } myType;
  
private:
  ExtractChannel(const ExtractChannel&);                // No copies.
  ExtractChannel& operator=(const ExtractChannel&);	  // No assignments.
};

#endif // _ExtractChannel_H

