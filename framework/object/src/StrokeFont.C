/*
 * StrokeFont.C
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
 *  $Id: StrokeFont.C,v 1.4 1996/04/18 08:42:59 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include <strstream.h>
#include "booga/base/Report.h"
#include "booga/object/StrokeFont.h"
#include "booga/object/RomanFont.h"
#include "booga/object/MonoRomanFont.h"

//_______________________________________________________________ StrokeCharacter

SymTable<RCString,const StrokeFont*>* StrokeFont::ourAvailableFonts;

StrokeFont::StrokeFont(const RCString& name, 
                       int numChars, CharRec* adoptChars,
                       Real top, Real bottom)
: myName(name),
  myNumChars(numChars), myChars(adoptChars),
  myTop(top), myBottom(bottom)
{}

const CharRec* StrokeFont::getChar(int index) const
{
  if (index < 0 || index >= myNumChars) {
    ostrstream os;
    os << "[StrokeFont::getChar] illegal index: " << index;
    Report::warning(os);
    return NULL;
  }

  return &myChars[index];
}

const StrokeFont* StrokeFont::searchFont(const RCString& fontName)
{
  //
  // Do we have to setup the font table?
  //
  if (ourAvailableFonts == NULL) {
    ourAvailableFonts = new SymTable<RCString,const StrokeFont*>(31);
    ourAvailableFonts->insert(ROMAN_FONT.getName(), &ROMAN_FONT);
    ourAvailableFonts->insert(MONO_ROMAN_FONT.getName(), &MONO_ROMAN_FONT);
  }

  const StrokeFont* font = NULL;
  ourAvailableFonts->lookup(fontName, font); 
  
  if (font == NULL) {
    ostrstream os;
    os << "[StrokeFont::searchFont] unknown font: " << fontName;
    Report::warning(os);
  }

  return font;
}

