/*
 * MatteAttr.h
 *
 * Copyright (C) 1994-96, University of Berne, Switzerland
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
 */

#ifndef _MatteAttr_H
#define _MatteAttr_H

#include "booga/base/Value.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3DAttr.h"

class Matte;
class RCString;

//____________________________________________________________________ MatteAttr

class MatteAttr : public Texture3DAttr {
declareRTTI(MatteAttr);
// enable RTTI support

public:
  virtual void setAttribute(Matte* matte) const = 0;
  // Interface to class Matte. Whenever setSpecifier(specifier)
  // is called for an instance of class Matte,
  // specifier->setAttribute(matteObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Matte
  // object by executing the right method. The corresponding call graph:
  //
  //   matteObject->setSpecifier(specifier)
  //       specifier->setAttribute(matteObject)
  //           matteObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ MatteAttrAmbient

class MatteAttrAmbient : public MatteAttr {
declareRTTI(MatteAttrAmbient);
// enable RTTI support

public:
  MatteAttrAmbient(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Matte* matte) const;
  MatteAttrAmbient(const Color& ambient);

private:
  Color myAmbient;
};

//_____________________________________________________________ MatteAttrDiffuse

class MatteAttrDiffuse : public MatteAttr {
declareRTTI(MatteAttrDiffuse);
// enable RTTI support

public:
  MatteAttrDiffuse(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Matte* matte) const;
  MatteAttrDiffuse(const Color& diffuse);

private:
  Color myDiffuse;
};

#endif // _MatteAttr_H
