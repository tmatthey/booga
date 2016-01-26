/*
 * PatternTexture2DAttr.h
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PatternTexture2DAttr.h,v 1.1 1995/08/24 10:19:06 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PatternTexture2DAttr_H
# define _PatternTexture2DAttr_H

#include "booga/object/Texture2DAttr.h"

class PatternTexture2D;
//_________________________________________________________ PatternTexture2DAttr

class PatternTexture2DAttr : public Texture2DAttr {
declareRTTI(PatternTexture2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(PatternTexture2D* pattern) const = 0;
  // Interface to class PatternTexture2D. Whenever setSpecifier(specifier)
  // is called for an instance of class PatternTexture2D,
  // specifier->setAttribute(patternObject) will be called. Method
  // setAttribute has to alter the appropriate member of the PatternTexture2D
  // object by executing the right method. The corresponding call graph:
  //
  //   patternObject->setSpecifier(specifier)
  //       specifier->setAttribute(patternObject)
  //           patternObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//__________________________________________________ PatternTexture2DAttrTexture

class PatternTexture2DAttrTexture : public PatternTexture2DAttr {
declareRTTI(PatternTexture2DAttrTexture);
// enable RTTI support

public:
  PatternTexture2DAttrTexture();
  PatternTexture2DAttrTexture(Exemplar);
  virtual int setSpecifier(RCString& errMsg, Makeable* specifier);

protected:
  Texture2D* myTexture;
};

//____________________________________________________ PatternTexture2DAttrSolid

class PatternTexture2DAttrSolid : public PatternTexture2DAttrTexture {
declareRTTI(PatternTexture2DAttrSolid);
// enable RTTI support

public:
  PatternTexture2DAttrSolid(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PatternTexture2D* pattern) const;
};

//______________________________________________________ PatternTexture2DAttrGap

class PatternTexture2DAttrGap : public PatternTexture2DAttrTexture {
declareRTTI(PatternTexture2DAttrGap);
// enable RTTI support

public:
  PatternTexture2DAttrGap(Exemplar);

  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(PatternTexture2D* pattern) const;
};

#endif // _PatternTexture2DAttr_H
