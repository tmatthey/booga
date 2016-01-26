/*
 * Makeable.h
 *
 * Abstract base class for all the elements that that can be used within the 
 * parser. An instance of a subclass of class Makeable may be added to the 
 * global name space by using the member function Makeable::registerExemplar. 
 * The parser has now access to this exemplar and by invoking the make or
 * setSpecifier method it can create new instances or may attach attributes
 * to an existing instance.
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
 *  $Id: Makeable.h,v 1.9 1996/10/04 09:47:05 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Makeable_H
#define _Makeable_H

#include "booga/base/StaticInit.h"
#include "booga/base/RTTI.h"
#include "booga/base/ScopedName.h"
#include "booga/base/Exemplar.h"
#include "booga/base/List.h"
#include "booga/base/RCString.h"

class Value;
class MakeableHandler;

//_____________________________________________________________________ Makeable

class Makeable {
declareRTTI(Makeable); 
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Makeable();                            // Use default version.
  // Makeable(const Makeable&);             // Use default version.

public:
  // Makeable& operator=(const Makeable&);  // Use default version.

public:
  virtual ~Makeable();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static void initClass(); 
  
  virtual int setSpecifier(RCString& errMsg, Makeable* adoptSpecifier);
  // setSpecifier is used to assign a value to a member of the instance,
  // e.g. to attach a Texture or Property structure to an object of type 
  // Object3D.
  //
  // Returns: 1 if successful, 0 otherwise and 'errMsg' is set to the
  //                             appropriate error message.

  virtual Makeable* make(RCString& errMsg, 
                         const List<Value*>* parameters) const = 0;
  // The make method has to check the 'parameters' provided and then build an 
  // new instance of its type by using the parameters. E.g. an instance of class 
  // Sphere3D accepts a Real (radius) and a Vector (position) value as parameters. 
  // The result of the call to the make method is a new instance of class Sphere3D 
  // with radius and position set correspondingly.
  //
  // Returns: a cloned Makeable if successful, NULL otherwise and 'errMsg' is set 
  //                                           to the appropriate error message.

  void setName(const Name& name);
  const Name& getName() const;
  
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();
  virtual void iterateAttributes(MakeableHandler *handler);

public:
  static int createNamespace(const Name& name);
  static int clearNamespace(const Name& name);
  static int removeNamespace(const Name& name);
  static void removeNamespaces();

  static Makeable* make(RCString& errMsg, 
		      const ScopedName& name, const List<Value*>* parameters);
  // This static member looks up the 'name' in the global name space. If an 
  // exemplar is registered for this name its make method is called.

  static int registerExemplar(RCString& errMsg, 
			   const ScopedName& exemplarName, Makeable* exemplar);
  static int unregisterExemplar(RCString& errMsg, 
			     const ScopedName& exemplarName, Makeable*& exemplar);
  // Add/remove an exemplar to/from the system.

  static void printRegistered(); // !!!!! temporary !!!!

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Name myName; 
  // Each Makeable has its own name.

private:
  static SymTable<Name, SymTable<Name, Makeable*>*>* ourNamespaces;
  // Namespaces for all the exemplars of the application.
  // The same exemplar may be registered with several names in the same
  // or different namespaces.
};

declareInitStatics(Makeable);

//______________________________________________________________________ INLINES

inline void Makeable::setName(const Name& name)
{
  myName = name;
}

inline const Name& Makeable::getName() const
{
  return myName;
}

/*_______________________________________________________________________ Macros
 *
 * The following macros are used to simplify the coding of the make and 
 * setSpecifier methods.
 */

#define castSpecifier(Type, variableName, expectedType)             \
  Type* variableName = dynamic_cast<Type*>(specifier);              \
  if (variableName == NULL) {			                    \
    errMsg = "expecting " expectedType ", type was " +              \
             RCString(typeid(specifier).name());                    \
    return 0;					                    \
  }

#define checkParameterNumber(requiredNum) 	                   \
  long provided_ = (!parameters ? 0 : parameters->count());        \
  if (provided_ != requiredNum) {		                   \
    std::stringstream str;                                         \
    str << #requiredNum << " parameter(s) required, "              \
        << provided_ << " provided";                               \
    errMsg = RCString(str);                                        \
    return NULL;				                   \
  }

#define getParameter(nthParameter, Type, variableName)              \
  Type variableName;				                    \
  if (!parameters->item(nthParameter-1)->to##Type(variableName)) {  \
    errMsg = RCString("expecting ") + #Type                         \
             " value as " #nthParameter ". parameter";              \
    return NULL;				                    \
  }

#endif // _Makeable_H
