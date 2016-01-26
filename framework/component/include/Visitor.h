/*
 * $RCSfile: Visitor.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Visitor.h,v 1.2 1997/09/19 07:15:18 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Visitor_H
#define _Visitor_H

#include "booga/base/RTTI.h" 
#include "booga/component/Traversal.h"  // enum Traversal::Result

class Makeable;

//______________________________________________________________________ Visitor

class Visitor {
declareRTTI(Visitor);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Visitor();                           // Use default version.
  // Visitor(const Visitor&);             // Use default version.

public:
  // virtual ~Visitor();                  // Use default version.

public:  
  // Visitor& operator=(const Visitor&);  // Use default version.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void incLevel();
  virtual void decLevel();
  // The traversal operation may increase ordecreases the level in the 
  // object structure; the two methods are called accordingly.
  
  virtual Traversal::Result dispatch(Makeable* obj) = 0;
  // Visitors will have do provide and appropriate dispatch method in 
  // order to handle the different object types. The dispatch should look 
  // as follows:
  //
  //   Traversal::Result MyVisitor::dispatch(Makeable* obj)
  //   {
  //     tryConcrete(Triangle3D, obj);
  //     tryAbstract(Primitive3D, obj);
  //     return Traversal::UNKNOWN;
  //   }
  //
  // If a tryXXXXXX statement matches, the corresponding visit() method will
  // be called.
  //  
};

//________________________________________________________________ Helper macros

#ifdef WIN32
#define tryConcrete(Type, obj)    \
if (dynamic_cast(Type,obj))       \
  return visit((Type*) obj)
#else
#define tryConcrete(Type, obj)             \
if (Type::ourTypeId_ == typeid(obj))       \
  return visit((Type*) obj)
#endif
  
#define tryAbstract(Type, obj)             \
if (dynamic_cast(Type, obj))               \
  return visit((Type*) obj)                


#endif // _Visitor_H
