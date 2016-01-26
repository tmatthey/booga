/* -*- c++ -*- 
 * RTTI.h 
 *
 * C++ will allow dynamic cast (save down casts) as proposed in the
 * draft for ANSI C++. The provided macros in this file will allow
 * a (limited) simulation of the features (dynamic_cast, typeid).
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: RTTI.h,v 1.5 1997/09/19 07:14:44 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */



#ifndef _RTTI_H
# define _RTTI_H

#ifndef HAVE_RTTI

#include "booga/base/Name.h"

#define declareRTTI(ClassName) 	                     \
  public:                                 	     \
    static const type_info ourTypeId_;               \
    virtual int isA_(const type_info& type) const;   \
    virtual const type_info& getTypeId_() const  

#define implementRTTIBase(ClassName)	             \
  const type_info ClassName::ourTypeId_(#ClassName); \
  int ClassName::isA_(const type_info& type) const   \
  { return (type == ClassName::ourTypeId_); }	     \
  const type_info& ClassName::getTypeId_() const     \
  { return ClassName::ourTypeId_; }                  

#define implementRTTI(ClassName,BaseClass)           \
  const type_info ClassName::ourTypeId_(#ClassName); \
  int ClassName::isA_(const type_info& type) const   \
  { return type == ClassName::ourTypeId_ ||          \
	    BaseClass::isA_(type);                   \
  }                                                  \
  const type_info& ClassName::getTypeId_() const     \
  { return ClassName::ourTypeId_; }                  


/* 
//
// Simulates T* dynamic_cast<T*>(object) construct
//
#define dynamic_cast(Type,obj) \
  (((obj) == NULL) ? (Type*)NULL : \
   ((obj)->isA_(Type::ourTypeId_)) ? (Type*)(obj) : (Type*)NULL) 

//
// Simulates T* const_cast<T*>(object) construct
//
#define const_cast(Type,obj) \
  (((obj) == NULL) ? (Type*)NULL : \
   ((obj)->isA_(Type::ourTypeId_)) ? (Type*)(obj) : (Type*)NULL) 

*/

//
// Simulates operator int typeid(T)
//

#define typeid(obj) (obj)->getTypeId_()


//
// "The design and Evolution of C++", B. Stroustrup, 1994, pp. 317
//
class type_info {
public:
  type_info(const char* typeName);
   
  int operator==(const type_info&) const;
  int operator!=(const type_info&) const;
  // can be compared

  const char* name() const;
  // name of type

private:
  type_info(const type_info&);             
  type_info& operator=(const type_info&);  
  // users can't copy type_info

private:
  Name myName;
};

inline type_info::type_info(const char* typeName)
: myName(typeName)
{}

inline int type_info::operator==(const type_info& type) const
{
  return (myName == type.myName);
}

inline int type_info::operator!=(const type_info& type) const
{
  return (myName != type.myName);
}

inline const char* type_info::name() const
{
  return ((RCString)myName).chars();
}
#else // HAVE_RTTI

#define declareRTTI(ClassName)
#define implementRTTIBase(ClassName)
#define implementRTTI(ClassName,BaseClass)

#endif // HAVE_RTTI

#endif // _RTTI_H

