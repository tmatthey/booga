/*
 * PhongAttr.h
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

#ifndef _PhongAttr_H
#define _PhongAttr_H

#include "booga/base/Value.h"
#include "booga/base/mathutilities.h"
#include "booga/base/Color.h"
#include "booga/object/Texture3DAttr.h"

class Phong;
class RCString;

//____________________________________________________________________ PhongAttr

class PhongAttr : public Texture3DAttr {
declareRTTI(PhongAttr);
// enable RTTI support

public:
  virtual void setAttribute(Phong* phong) const = 0;
  // Interface to class Phong. Whenever setSpecifier(specifier)
  // is called for an instance of class Phong,
  // specifier->setAttribute(phongObject) will be called. Method
  // setAttribute has to alter the appropriate member of the Phong
  // object by executing the right method. The corresponding call graph:
  //
  //   phongObject->setSpecifier(specifier)
  //       specifier->setAttribute(phongObject)
  //           phongObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_____________________________________________________________ PhongAttrAmbient

class PhongAttrAmbient : public PhongAttr {
declareRTTI(PhongAttrAmbient);
// enable RTTI support

public:
  PhongAttrAmbient(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Phong* phong) const;
  PhongAttrAmbient(const Color& ambient);

private:
  Color myAmbient;
};

//_____________________________________________________________ PhongAttrDiffuse

class PhongAttrDiffuse : public PhongAttr {
declareRTTI(PhongAttrDiffuse);
// enable RTTI support

public:
  PhongAttrDiffuse(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Phong* phong) const;
  PhongAttrDiffuse(const Color& diffuse);

private:
  Color myDiffuse;
};

//____________________________________________________________ PhongAttrSpecular

class PhongAttrSpecular : public PhongAttr {
declareRTTI(PhongAttrSpecular);
// enable RTTI support

public:
  PhongAttrSpecular(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Phong* phong) const;
  PhongAttrSpecular(const Color& specular);

private:
  Color mySpecular;
};

//_____________________________________________________________ PhongAttrSpecPow

class PhongAttrSpecPow : public PhongAttr {
declareRTTI(PhongAttrSpecPow);
// enable RTTI support

public:
  PhongAttrSpecPow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(Phong* phong) const;
  PhongAttrSpecPow(const int& specPow);

private:
  int mySpecPow;
};

#endif // _PhongAttr_H
