/*
 * $RCSfile: PatternTexture2D.h,v $
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
 *  $Id: PatternTexture2D.h,v 1.4 1996/08/30 13:53:27 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PatternTexture2D_H
#define _PatternTexture2D_H

#include "booga/base/List.h"
#include "booga/base/Color.h"
#include "booga/object/Texture2D.h"

//_____________________________________________________________ PatternTexture2D

class PatternTexture2D : public Texture2D {
declareRTTI(PatternTexture2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PatternTexture2D();
  PatternTexture2D(Exemplar);
  PatternTexture2D(const PatternTexture2D& pattern);

public:
  virtual ~PatternTexture2D();

private:
  PatternTexture2D& operator=(const PatternTexture2D&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PatternTexture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setPattern(const List<float>& pattern);
  void adoptSolid(Texture2D* texture);
  void adoptGap  (Texture2D* texture);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Texture2D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Texture2D* copy() const;
  virtual void doTexturing(Texture2DContext& context) const;
  virtual void computeCumulatedTransform(const Transform2D& additionalTransform);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<float> myPattern;
  float myPatternLength;
  Texture2D* mySolid;
  Texture2D* myGap;
};

#endif // _PatternTexture2D_H

