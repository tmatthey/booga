/*
 * StrokeFont.h
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: StrokeFont.h,v 1.2 1995/12/21 16:07:57 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _StrokeFont_H
#define _StrokeFont_H

#include "booga/base/RCString.h"
#include "booga/base/Vector2D.h"
#include "booga/base/SymTable.h"

//_______________________________________________________________ StrokeCharacter

struct StrokeRec {
  int myNumCoords;
  Vector2D* myCoords;
}; 

struct CharRec {
  int myNumStrokes;
  StrokeRec* myStrokes;
  Real myCenter;
  Real myRight;
};

//____________________________________________________________________ StrokeFont

class StrokeFont {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  StrokeFont(const RCString& name, 
             int numChars, CharRec* adoptChars,
             Real top, Real bottom);
             
private:
  StrokeFont(const StrokeFont&);             // No copies.

public:
  // ~StrokeFont();                          // Use default version.

private:
  StrokeFont& operator=(const StrokeFont&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class StrokeFont
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  const RCString& getName() const;
  int getNumChars() const;
  const CharRec* getChar(int index) const;
  Real getTop() const;
  Real getBottom() const;

public:
  static const StrokeFont* searchFont(const RCString& fontName);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myName;
  int myNumChars;
  CharRec* myChars;
  Real myTop;
  Real myBottom;

private:
  static SymTable<RCString,const StrokeFont*>* ourAvailableFonts;
};

//_______________________________________________________________________ INLINES

inline const RCString& StrokeFont::getName() const
{
  return myName;
}

inline int StrokeFont::getNumChars() const
{
  return myNumChars;
}

inline Real StrokeFont::getTop() const
{
  return myTop;
}

inline Real StrokeFont::getBottom() const
{
  return myBottom;
}

#endif // _StrokeFont_H

