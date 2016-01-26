/*
 * PixmapOf.C 
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
 *  $Id: PixmapOf.C,v 1.3 1998/02/04 12:51:20 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <string.h>  // memcpy
#include <math.h>
#include <fstream>

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/base/PixmapOf.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//__________________________________________________________________PixmapOf<T>

template <class TColor>
INLINE PixmapOf<TColor>::PixmapOf(int resX, int resY)
: AbstractPixmap(resX, resY)
{
  myColors = new TColor[getSize()];
}

template <class TColor>
INLINE PixmapOf<TColor>::PixmapOf(const RCString& fileName)
: AbstractPixmap(0,0)
{
  myColors = NULL;
  load(fileName);
}

template <class TColor>
INLINE PixmapOf<TColor>::PixmapOf(std::ifstream& ifs)
: AbstractPixmap(0,0)
{
  myColors = NULL;
  load(ifs);
}

template <class TColor>
INLINE PixmapOf<TColor>::PixmapOf(const PixmapOf<TColor>& pm)
: AbstractPixmap(pm)
{
  myColors = new TColor[getSize()];
  memcpy(myColors, pm.myColors, getSize()*sizeof(TColor));
}

template <class TColor>
INLINE PixmapOf<TColor>::~PixmapOf()
{
  if (myColors) delete [] myColors;
}

template <class TColor>
INLINE PixmapOf<TColor>& PixmapOf<TColor>::operator=(const PixmapOf<TColor>& pm)
{
  if (this == &pm)
    return *this;

  assign(pm);

  delete [] myColors;  
  myColors = new TColor[getSize()];
  memcpy(myColors, pm.myColors, getSize()*sizeof(TColor));
  
  return *this;  
}

template <class TColor>
INLINE AbstractPixmap* PixmapOf<TColor>::copy() const
{
  return new PixmapOf<TColor>(*this);
}

template <class TColor>
INLINE void PixmapOf<TColor>::setResolution(int resX, int resY)
{
  AbstractPixmap::setResolution(resX, resY);

  if (myColors) delete [] myColors;
  myColors = new TColor[getSize()];
}

template <class TColor>
INLINE void PixmapOf<TColor>::setColor(float c1, float c2, float c3)
{
  if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].setValue(c1, c2, c3);
}

template <class TColor>
INLINE void PixmapOf<TColor>::setColor(float value)
{
  if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].setValue(value);
}

template <class TColor>
INLINE void PixmapOf<TColor>::setColor(bool value)
{
  if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].setValue(value);
}

template <class TColor>
INLINE void PixmapOf<TColor>::getColor(float& c1, float& c2, float& c3) const
{
 if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].getValue(c1, c2, c3);
}

template <class TColor>
INLINE void PixmapOf<TColor>::getColor(float& value) const
{
  if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].getValue(value);
}

template <class TColor>
INLINE void PixmapOf<TColor>::getColor(bool& value) const
{
  if (myCurrentPos < 0) {
    Report::recoverable("[PixmapOf<>::setColor] use setPosition first");
    return;
  }
  
  myColors[myCurrentPos].getValue(value);
}

template <class TColor>
INLINE TColor* PixmapOf<TColor>::getColors() const
{
  return myColors;
}
#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)


