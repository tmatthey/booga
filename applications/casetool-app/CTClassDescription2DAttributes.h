/*
 * CTClassDescription2DAttributes.h
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

#ifndef _CTClassDescription2DAttributes_H
#define _CTClassDescription2DAttributes_H

#include <math.h>
#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class CTClassDescription2D;
class RCString;

//_____________________________________________________ CTClassDescription2DAttr

class CTClassDescription2DAttr : public ObjectAttr {
declareRTTI(CTClassDescription2DAttr);
// enable RTTI support

public:
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const = 0;
  // Interface to class CTClassDescription2D. Whenever setSpecifier(specifier)
  // is called for an instance of class CTClassDescription2D,
  // specifier->setAttribute(ctclassdescription2dObject) will be called. Method
  // setAttribute has to alter the appropriate member of the CTClassDescription2D
  // object by executing the right method. The corresponding call graph:
  //
  //   ctclassdescription2dObject->setSpecifier(specifier)
  //       specifier->setAttribute(ctclassdescription2dObject)
  //           ctclassdescription2dObject->setTheAttribute(newValue)
  //
  // This technique allows a method dispatch without case analysis.
};

//_______________________________________________ CTClassDescription2DAttrOrigin

class CTClassDescription2DAttrOrigin : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrOrigin);
// enable RTTI support

public:
  CTClassDescription2DAttrOrigin(Exemplar) {}
  CTClassDescription2DAttrOrigin(const Vector2D& origin);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;

private:
  Vector2D myOrigin;
};

//________________________________________________ CTClassDescription2DAttrWidth

class CTClassDescription2DAttrWidth : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrWidth);
// enable RTTI support

public:
  CTClassDescription2DAttrWidth(Exemplar) {}
  CTClassDescription2DAttrWidth(const Real& width);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;

private:
  Real myWidth;
};

//_____________________________________________ CTClassDescription2DAttrTemplate

class CTClassDescription2DAttrTemplate : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrTemplate);
// enable RTTI support

public:
  CTClassDescription2DAttrTemplate(Exemplar) {}
  CTClassDescription2DAttrTemplate(const RCString& temp);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;

private:
  RCString myTemplate;
};

//_____________________________________________ CTClassDescription2DAttrAbstract

class CTClassDescription2DAttrAbstract : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrAbstract);
// enable RTTI support

public:
  CTClassDescription2DAttrAbstract(Exemplar) {}
  CTClassDescription2DAttrAbstract() {};
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;
};

//_____________________________________________ CTClassDescription2DAttrAttribute

class CTClassDescription2DAttrAttribute : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrAttribute);
// enable RTTI support

public:
  CTClassDescription2DAttrAttribute(Exemplar) {}
  CTClassDescription2DAttrAttribute(const RCString& view, 
                                    const RCString& type, 
                                    const RCString& name);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;
  
private:
  RCString myView;
  RCString myType;
  RCString myName;
};

//_____________________________________________ CTClassDescription2DAttrBase

class CTClassDescription2DAttrBase : public CTClassDescription2DAttr {
declareRTTI(CTClassDescription2DAttrBase);
// enable RTTI support

public:
  CTClassDescription2DAttrBase(Exemplar) {}
  CTClassDescription2DAttrBase(const RCString& view, const RCString& name);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTClassDescription2D* ctclassdescription2d) const;
  
private:
  RCString myView;
  RCString myName;
};

#endif // _CTClassDescription2DAttributes_H
