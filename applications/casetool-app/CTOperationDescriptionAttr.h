/*
 * $RCSfile: CTOperationDescriptionAttr.h,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: CTOperationDescriptionAttr.h,v 1.1 1996/10/30 15:31:37 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _CTOperationDescriptionAttr_H
#define _CTOperationDescriptionAttr_H

#include <math.h>
#include "booga/base/Value.h"
#include "booga/object/ObjectAttr.h"

class CTOperationDescription;
class RCString;

//_____________________________________________________ CTOperationDescriptionAttr

class CTOperationDescriptionAttr : public ObjectAttr {
declareRTTI(CTOperationDescriptionAttr);
// enable RTTI support

public:
  virtual void setAttribute(CTOperationDescription* ctOpDescription) const = 0;
  // Interface to class CTOperationDescription. Whenever setSpecifier(specifier)
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

//_____________________________________________ CTOperationDescriptionAttrVirtual

class CTOperationDescriptionAttrVirtual : public CTOperationDescriptionAttr {
declareRTTI(CTOperationDescriptionAttrVirtual);
// enable RTTI support

public:
  CTOperationDescriptionAttrVirtual(Exemplar) {}
  CTOperationDescriptionAttrVirtual() {};
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTOperationDescription* ctOpDescription) const;
};

//_____________________________________________ CTOperationDescriptionAttrParameter

class CTOperationDescriptionAttrParameter : public CTOperationDescriptionAttr {
declareRTTI(CTOperationDescriptionAttrParameter);
// enable RTTI support

public:
  CTOperationDescriptionAttrParameter(Exemplar) {}
  CTOperationDescriptionAttrParameter(const RCString& type, 
                                      const RCString& name,
                                      const RCString& init);
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual void setAttribute(CTOperationDescription* ctOpDescription) const;
  
private:
  RCString myType;
  RCString myName;
  RCString myInit;
};


#endif // _CTOperationDescriptionAttr_H
