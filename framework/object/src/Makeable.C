/*
 * Makeable.C
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
 *  $Id: Makeable.C,v 1.16 1996/11/13 10:11:51 collison Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/object/Makeable.h"
#include "booga/object/MakeableAttr.h"

//_____________________________________________________________________ Makeable

implementRTTIBase(Makeable);
implementInitStatics(Makeable);

const int NUMBER_OF_NAMESPACES = 100;
const int NAMESPACE_SIZE       = 500;

SymTable<Name, SymTable<Name, Makeable*>*>* Makeable::ourNamespaces;

void Makeable::initClass()
{
  // !!! optimize the size of SymTable when its rather full ...
  ourNamespaces = 
    new SymTable<Name, SymTable<Name, Makeable*>*>(NUMBER_OF_NAMESPACES);
  ourNamespaces->insert(ScopedName::getGlobalNS(), 
			new SymTable<Name, Makeable*>(NAMESPACE_SIZE));
}

Makeable::~Makeable() {}

int Makeable::setSpecifier(RCString& errMsg, Makeable* adoptSpecifier)
{
  MakeableAttr* attr = dynamic_cast<MakeableAttr*>(adoptSpecifier);
  if (attr != NULL) {
    // The MakeableAttr object knows best which method has to be called.
    // So let the object do the job.
    attr->setAttribute(this);

    delete attr;
    return 1;  
  }

  errMsg = RCString("specifier of type ") + typeid(adoptSpecifier).name() 
                                          + " not recognized";
  return 0;
}

//--------------------------------------------------------------- STATIC MEMBERS

int Makeable::createNamespace(const Name& name)
{
  if (ourNamespaces->find(name))
    return 0;

  ourNamespaces->insert(name, new SymTable<Name, Makeable*>(NAMESPACE_SIZE));

  return 1;
}

int Makeable::clearNamespace(const Name& name)
{
  SymTable<Name, Makeable*>* tmpNamespace = NULL;

  if (!ourNamespaces->lookup(name, tmpNamespace))
    return 0;
  tmpNamespace->removeAll();

  return 1;
}

int Makeable::removeNamespace(const Name& name)
{
  SymTable<Name, Makeable*>* tmpNamespace = NULL;

  if (ourNamespaces->findAndRemove(name, tmpNamespace)) {
    delete tmpNamespace;  
    return 1;
  } 
  
  return 0;
}

void Makeable::removeNamespaces()
{
  SymTableIterator<Name, SymTable<Name, Makeable*>*> namespaceItr(*ourNamespaces);
  List<Name> namespaceNames;

  //
  // Find the names of the registered namespaces. 
  //
  while (namespaceItr.more()) {
    namespaceNames.append(namespaceItr.curKey());
    namespaceItr.next();
  }

  for (long i=0; i<namespaceNames.count(); i++)
    removeNamespace(namespaceNames.item(i));

  ourNamespaces->insert(ScopedName::getGlobalNS(), 
		      new SymTable<Name, Makeable*>(NAMESPACE_SIZE));
}

Makeable* Makeable::make(RCString& errMsg, 
                         const ScopedName& name, 
                         const List<Value*>* parameters)
{
  SymTable<Name, Makeable*>* tmpNamespace = NULL;
  Makeable* exemplar = NULL;

  //
  // First of all: try in the indicated namespace
  //
  ourNamespaces->lookup(name.getNamespace(), tmpNamespace);
  if (tmpNamespace != NULL) {
    tmpNamespace->lookup(name.getIdentifier(), exemplar);

    if (exemplar != NULL)
      return exemplar->make(errMsg, parameters);
  }

  //
  // Not found, lets try in the global namespace
  //
  if (name.getNamespace() != ScopedName::getGlobalNS()) {
    ourNamespaces->lookup(ScopedName::getGlobalNS(), tmpNamespace);
    if (tmpNamespace != NULL) {
      tmpNamespace->lookup(name.getIdentifier(), exemplar);
      
      if (exemplar != NULL)
	return exemplar->make(errMsg, parameters);
    }
  }

  return NULL;
}

int Makeable::registerExemplar(RCString& errMsg,
			       const ScopedName& exemplarName, Makeable* exemplar)
{
  SymTable<Name, Makeable*>* tmpNamespace = NULL;

  Name ns = exemplarName.getNamespace();
  Name id = exemplarName.getIdentifier();

  if (ourNamespaces->lookup(ns, tmpNamespace) &&
      (!tmpNamespace->find(id))) {
    tmpNamespace->insert(id, exemplar);
    exemplar->myName = id;
    return 1;
  }

  if (tmpNamespace == NULL)
    errMsg = "namespace " + 
      (RCString)exemplarName.getNamespace() + " does not exist";
  else
    errMsg = "specifier " + exemplarName.getScopedName() + " already exists";

  return 0;
}

int Makeable::unregisterExemplar(RCString& errMsg,
				 const ScopedName& exemplarName, Makeable*& exemplar)
{
  SymTable<Name, Makeable*>* tmpNamespace = NULL;

  if (ourNamespaces->lookup(exemplarName.getNamespace(), tmpNamespace) &&
      (tmpNamespace->findAndRemove(exemplarName.getIdentifier(), exemplar)))
    return 1;

  if (tmpNamespace == NULL)
    errMsg = "namespace " + 
      (RCString)exemplarName.getNamespace() + " does not exist";
  else
    errMsg = "specifier " + exemplarName.getScopedName() + " does not exist";

  exemplar = NULL;
  return 0;
}

void Makeable::printRegistered()
{
  SymTableIterator<Name, SymTable<Name, Makeable*>*> namespaceItr(*ourNamespaces);

  while (namespaceItr.more()) {
    SymTableIterator<Name,Makeable*> itr(*namespaceItr.curValue());
    std::cout << "\n------------------- Namespace " << namespaceItr.curKey() << "::\n" << std::flush;
    while (itr.more()) {
      std::cout << itr.curKey() << "\n\t"
	   << itr.curValue()->myName << " "
	   << typeid(itr.curValue()).name() << std::endl << std::flush;
      itr.next();
    }
    namespaceItr.next();
  }
}

static const RCString makeableKeyword("NO_MakeableHandler_SUPPORT");

RCString Makeable::getKeyword() const {
  Report::warning(RCString("[Makeable::getKeyword] MakeableHandler not supported by ")
                + RCString(typeid(this).name()));
  return (makeableKeyword + "_" + RCString(typeid(this).name()));
}

List<Value*>* Makeable::createParameters() {
  List<Value*>* parameters = new List<Value*>;
  return parameters;
}

void Makeable::iterateAttributes(MakeableHandler* ) {
}
