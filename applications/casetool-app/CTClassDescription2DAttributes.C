/*
 * CTClassDescription2DAttributes.C
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

#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "CTClassDescription2D.h"
#include "CTClassDescription2DAttributes.h"

//_____________________________________________________ CTClassDescription2DAttr

implementRTTI(CTClassDescription2DAttr, ObjectAttr);

//_______________________________________________ CTClassDescription2DAttrOrigin

implementRTTI(CTClassDescription2DAttrOrigin, CTClassDescription2DAttr);

CTClassDescription2DAttrOrigin::CTClassDescription2DAttrOrigin(const Vector2D& origin)
: myOrigin(origin)
{}

Makeable* CTClassDescription2DAttrOrigin::make(RCString& errMsg,
                                               const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Vector2D, value);

  return new CTClassDescription2DAttrOrigin(value);
}

void CTClassDescription2DAttrOrigin::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  ctclassdescription2d->setOrigin(myOrigin);
}

//________________________________________________ CTClassDescription2DAttrWidth

implementRTTI(CTClassDescription2DAttrWidth, CTClassDescription2DAttr);

CTClassDescription2DAttrWidth::CTClassDescription2DAttrWidth(const Real& width)
: myWidth(width)
{}

Makeable* CTClassDescription2DAttrWidth::make(RCString& errMsg,
                                              const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, Real, value);

  return new CTClassDescription2DAttrWidth(value);
}

void CTClassDescription2DAttrWidth::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  ctclassdescription2d->setWidth(myWidth);
}

//_____________________________________________ CTClassDescription2DAttrTemplate

implementRTTI(CTClassDescription2DAttrTemplate, CTClassDescription2DAttr);

CTClassDescription2DAttrTemplate::CTClassDescription2DAttrTemplate(const RCString& temp)
: myTemplate(temp)
{}

Makeable* CTClassDescription2DAttrTemplate::make(RCString& errMsg,
                                                 const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, value);

  return new CTClassDescription2DAttrTemplate(value);
}

void CTClassDescription2DAttrTemplate::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  ctclassdescription2d->setIsTemplate(true);
  ctclassdescription2d->setTemplateParameters(myTemplate);
}

//_____________________________________________ CTClassDescription2DAttrAbstract

implementRTTI(CTClassDescription2DAttrAbstract, CTClassDescription2DAttr);

Makeable* CTClassDescription2DAttrAbstract::make(RCString& errMsg,
                                                 const List<Value*>* parameters) const
{
  checkParameterNumber(0);

  return new CTClassDescription2DAttrAbstract();
}

void CTClassDescription2DAttrAbstract::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  ctclassdescription2d->setIsAbstract(true);
}

//_____________________________________________ CTClassDescription2DAttrAttribute

implementRTTI(CTClassDescription2DAttrAttribute, CTClassDescription2DAttr);

CTClassDescription2DAttrAttribute::CTClassDescription2DAttrAttribute(
                                    const RCString& view, 
                                    const RCString& type, 
                                    const RCString& name)
: myView(view), myType(type), myName(name)
{}

Makeable* CTClassDescription2DAttrAttribute::make(RCString& errMsg,
                                                 const List<Value*>* parameters) const
{
  checkParameterNumber(3);
  getParameter(1, RCString, view);
  
  if (view != "public" && view != "protected" && view != "private") {
    errMsg = "illegal view specified. Allowed views are: public, protected, private";
    return NULL;
  }
  
  getParameter(2, RCString, type);
  getParameter(3, RCString, name);
  if (name.isEmpty()) {
    errMsg = "empty name";
    return NULL;
  }

  return new CTClassDescription2DAttrAttribute(view, type, name);
}

void CTClassDescription2DAttrAttribute::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  CTAttributeDescription desc;
  if (myView == "public")
    desc.setView(CTAttributeDescription::Public);
  else if (myView == "protected")
    desc.setView(CTAttributeDescription::Protected);
  else if (myView == "private")
    desc.setView(CTAttributeDescription::Private);
  else 
    desc.setView(CTAttributeDescription::Unspecified);
  desc.setType(myType);
  desc.setName(myName);
  
  ctclassdescription2d->addAttribute(desc);
}

//_____________________________________________ CTClassDescription2DAttrBase

implementRTTI(CTClassDescription2DAttrBase, CTClassDescription2DAttr);

CTClassDescription2DAttrBase::CTClassDescription2DAttrBase(
                                    const RCString& view, 
                                    const RCString& name)
: myView(view), myName(name)
{}

Makeable* CTClassDescription2DAttrBase::make(RCString& errMsg,
                                             const List<Value*>* parameters) const
{
  checkParameterNumber(2);
  getParameter(1, RCString, view);
  
  if (view != "public" && view != "protected" && view != "private") {
    errMsg = "illegal view specified. Allowed views are: public, protected, private";
    return NULL;
  }
  
  getParameter(2, RCString, name);
  if (name.isEmpty()) {
    errMsg = "empty name";
    return NULL;
  }

  return new CTClassDescription2DAttrBase(view, name);
}

void CTClassDescription2DAttrBase::setAttribute(CTClassDescription2D* ctclassdescription2d) const
{
  CTBaseclassDescription desc;
  if (myView == "public")
    desc.setView(CTBaseclassDescription::Public);
  else if (myView == "protected")
    desc.setView(CTBaseclassDescription::Protected);
  else if (myView == "private")
    desc.setView(CTBaseclassDescription::Private);
  else 
    desc.setView(CTBaseclassDescription::Unspecified);
  desc.setName(myName);
  
  ctclassdescription2d->addBaseclass(desc);
}

