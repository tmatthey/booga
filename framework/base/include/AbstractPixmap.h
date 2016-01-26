/*
 * AbstractPixmap.h
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
 *  $Id: AbstractPixmap.h,v 1.7 1996/07/01 14:58:39 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AbstractPixmap_H
#define _AbstractPixmap_H

#include <fstream>
#include <iostream>
#include <stdlib.h>   // NULL

#include "booga/base/RCString.h"
#include "booga/base/PrimitiveTypes.h"

//_______________________________________________________________ AbstractPixmap

class AbstractPixmap {
public:
  static const RCString MAGIC_NUMBER;
  static const RCString EXTENSION;
  static const int MAX_USERCHANNELS;

public:
  AbstractPixmap(int resX = 512, int resY = 512);
  AbstractPixmap(const AbstractPixmap& pm);
  virtual ~AbstractPixmap();

  virtual AbstractPixmap* copy() const = 0;

  // ------------------------------------------------------- Resolution
  virtual void setResolution(int resX, int resY) = 0;
  int getResolutionX() const;
  int getResolutionY() const;
  long getSize() const;
  // Set/change/get resolution of Pixmap.
  // All currently saved information in Pixmap will be lost.

  // ------------------------------------------------------------ Range
  void setRange(float min, float max);
  float getRangeMin() const;
  float getRangeMax() const;

  // --------------------------------------------------------- Position
  void setPosition(int x, int y) const;
  void setPosition(long pos) const;
  // Indicate a position of the pixmap to alter/read from with
  // calls to setColor, getColor, setDepth, getDepth, ...
  // First method: set position as x/y indices in pixmap space
  // Second meth.: set position in linear memory space (faster)

  // ------------------------------------------------------------ Color
  void clearColor(float c1, float c2, float c3);
  void clearColor(float value);
  void clearColor(bool value);
  // Clear color value of all pixels.

  virtual void setColor(float c1, float c2, float c3) = 0;
  virtual void setColor(float value) = 0;
  virtual void setColor(bool value) = 0;
  // Set color value of pixel current by setPosition.

  virtual void getColor(float& c1, float& c2, float& c3) const = 0;
  virtual void getColor(float& value) const = 0;
  virtual void getColor(bool& value) const = 0;
  // Get color value of pixel current by setPosition.
 
  // ------------------------------------------------------------ Depth
  bool haveDepth() const;
  void clearDepth(float depth=MAXFLOAT);
  void setDepth(float depth);
  void getDepth(float& depth) const;
  // Get/set depth channel of current pixel.

  // ------------------------------------------------------------ Alpha
  bool haveAlpha() const;
  void clearAlpha(float alpha=0);
  void setAlpha(float alpha);
  void getAlpha(float& alpha) const;
  // Get/set alpha channel of current pixel.

  // ---------------------------------------------------- User channels
  bool getUnusedUserChannel(int& channel) const;
  bool haveUserChannel(int channel) const;
  void clearUserChannel(int channel, float value=0);
  void setUserChannel(int channel, float value);
  void getUserChannel(int channel, float& value) const;
  // Get/set user channel of current pixel.

  // -------------------------------------------------------------- I/O
  bool load(const RCString& fileName);
  bool load(std::istream& ifs);
  // Load Pixmap from file. 
  // Returns:  true on success, false on failure

  bool save(const RCString& fileName, const RCString& comment = "") const;
  bool save(std::ostream& ofs, const RCString& comment = "") const;
  // Save Pixmap to file.
  // Returns:  true on success, false on failure 

protected:
  void assign(const AbstractPixmap& pm);

protected:
  long myCurrentPos;

private:
  bool haveChannel(int channel) const;
  void clearChannel(int channel, float value=0);
  void setChannel(int channel, float value);
  void getChannel(int channel, float& value) const;
  
private:
  enum { DEPTH, ALPHA };
  static const int MAX_CHANNELS;
  static const int MAX_SYSCHANNELS;
  
private:
  int myResX, myResY;
  float myRangeMin, myRangeMax;
  long mySize;
  float** myChannels;
  
private:
  AbstractPixmap& operator=(const AbstractPixmap&);  // No assignments.
};

//_______________________________________________________ INLINES AbstractPixmap

inline int AbstractPixmap::getResolutionX() const 
{ 
  return myResX; 
}

inline int AbstractPixmap::getResolutionY() const 
{ 
  return myResY; 
}

inline long AbstractPixmap::getSize() const
{
  return mySize;
}

inline float AbstractPixmap::getRangeMin() const
{
  return myRangeMin;
}

inline float AbstractPixmap::getRangeMax() const
{
  return myRangeMax;
}

inline bool AbstractPixmap::haveChannel(int channel) const
{
  return (myChannels[channel] != NULL);
}

inline bool AbstractPixmap::haveDepth() const
{
  return haveChannel(AbstractPixmap::DEPTH);
}

inline bool AbstractPixmap::haveAlpha() const
{
  return haveChannel(AbstractPixmap::ALPHA);
}

#endif // _AbstractPixmap_H

