/*
 * PixmapOf.h
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: PixmapOf.h,v 1.3 1998/02/04 12:51:22 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PixmapOf_H
#define  _PixmapOf_H

#include "booga/base/ColorTypes.h"
#include "booga/base/AbstractPixmap.h"

//_________________________________________________________________ PixmapOf<T>

template <class TColor>
class PixmapOf : public AbstractPixmap {
public:
  PixmapOf(int resX = 512, int resY = 512);
  PixmapOf(const RCString& fileName);
  PixmapOf(ifstream& ifs);
  PixmapOf(const PixmapOf<TColor>& pm);
  ~PixmapOf();
  
  PixmapOf<TColor>& operator=(const PixmapOf<TColor>& pm);
  virtual AbstractPixmap* copy() const;

  virtual void setResolution(int resX, int resY);

  virtual void setColor(float c1, float c2, float c3);
  virtual void setColor(float value);
  virtual void setColor(bool value);
  virtual void getColor(float& c1, float& c2, float& c3) const;
  virtual void getColor(float& value) const;
  virtual void getColor(bool& value) const;
  virtual TColor* getColors() const;
  // Get/set color value of pixel indicated by setPosition.

private:
  TColor* myColors;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../base/src/PixmapOf.C"
#endif // TEMPLATE_IN_HEADER

#endif // _PixmapOf_H
