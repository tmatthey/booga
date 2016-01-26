/*
 * $RCSfile: CTOperationDescriptionAttr.C,v $
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
 *  $Id: CTOperationDescriptionAttr.C,v 1.1 1996/10/30 15:31:36 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "CTOperationDescription.h"
#include "CTOperationDescriptionAttr.h"

//_____________________________________________________ CTOperationDescriptionAttr

implementRTTI(CTOperationDescriptionAttr, ObjectAttr);

//_____________________________________________ CTOperationDescriptionAttrVirtual

implementRTTI(CTOperationDescriptionAttrVirtual, CTOperationDescriptionAttr);

Makeable* CTOperationDescriptionAttrVirtual::make(RCString& errMsg,
                                                  const List<Value*>* parameters) const
{
  checkParameterNumber(0);

  return new CTOperationDescriptionAttrVirtual();
}

void CTOperationDescriptionAttrVirtual::setAttribute(CTOperationDescription* ctOpDesc) const
{
  ctOpDesc->setIsAbstract(true);
}

//_____________________________________________ CTOperationDescriptionAttrParameter

implementRTTI(CTOperationDescriptionAttrParameter, CTOperationDescriptionAttr);

CTOperationDescriptionAttrParameter::CTOperationDescriptionAttrParameter(
                                    const RCString& type, 
                                    const RCString& name, 
                                    const RCString& init)
: myType(type), myName(name), myInit(init)
{}

Makeable* CTOperationDescriptionAttrParameter::make(RCString& errMsg,
                                                    const List<Value*>* parameters) const
{
  long nOfPara = !parameters ? 0 : parameters->count();
  switch (nOfPara)
  {
    case 1: {
      getParameter(1, RCString, type);
      return new CTOperationDescriptionAttrParameter(type, "", "");
      break;
    }
    case 2: {
      getParameter(1, RCString, type);
      getParameter(2, RCString, name);
      if (name.isEmpty()) {
        errMsg = "empty name";
        return NULL;
      }
      return new CTOperationDescriptionAttrParameter(type, name, "");
      break;
    }
    case 3: {
      getParameter(1, RCString, type);
      getParameter(2, RCString, name);
      if (name.isEmpty()) {
        errMsg = "empty name";
        return NULL;
      }
      getParameter(3, RCString, init);
      return new CTOperationDescriptionAttrParameter(type, name, type);
      break;
    }      
    default:
      extern char* form(const char * ...);
      errMsg = RCString("1, 2 or 3 Parameters required, ") + form("%ld", nOfPara) + " provided";
  }

  return NULL;
}

void CTOperationDescriptionAttrParameter::setAttribute(CTOperationDescription* ctOpDesc) const
{
  CTVariableDescription desc;
  desc.setType(myType);
  desc.setName(myName);
  desc.setInitValue(myInit);
  
  ctOpDesc->addParameter(desc);
}


