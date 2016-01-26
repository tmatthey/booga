/*
 * $RCSfile: CollectorFor.C,v $
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
 *  $Id: CollectorFor.C,v 1.11 1996/09/13 08:03:35 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/PrimitiveTypes.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/component/CollectorFor.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//____________________________________________________________________ TestFor<>

template <class TSearchObject, // Object class to test for.
          class TOperation,    // Operation2D or Operation3D
          class TWorld,        // World2D or World3D
          class TShared>       // Shared2D or Shared3D
class TestFor : public TOperation {

#ifdef __GNUC__
// declareRTTI(TestFor);
// enable RTTI support
#endif // __GNUC__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // TestFor();           // Use default version.
  // TestFor(const TestFor<TSearchObject,TOperation,TWorld,TShared>&);    
  // Use default version.

public:
  // virtual ~TestFor();  // Use default version.

private:
  TestFor<TSearchObject,TOperation,TWorld,TShared>& 
    operator=(const TestFor<TSearchObject,TOperation,TWorld,TShared>&);  
  // No assignments.  
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class TestFor<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  bool hasFound() const;

private:
  Traversal::Result visit(TShared* obj);
  Traversal::Result visit(TSearchObject* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool preprocessing();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  bool myFound;
};

//____________________________________________________________________ TestFor<>

#ifndef __GNUC__
// implementRTTI(TestFor, Transformer??);
#endif // __GNUC__

template <class TSearchObject, class TOperation, class TWorld, class TShared>
INLINE bool 
TestFor<TSearchObject,TOperation,TWorld,TShared>::preprocessing()
{
  if (!TOperation::preprocessing())
    return false;

  myFound = false;
  return true;
}

template <class TSearchObject, class TOperation, class TWorld, class TShared>
INLINE Traversal::Result 
TestFor<TSearchObject,TOperation,TWorld,TShared>::visit(TShared* obj)
{
  TWorld localWorld;
  localWorld.getObjects()->adoptObject(obj->getSubobject(0));

  TestFor<TSearchObject,TOperation,TWorld,TShared> finder;
  finder.execute(&localWorld);

  localWorld.getObjects()->orphanObject(obj->getSubobject(0));

  if (finder.hasFound()) {
    myFound = true;
    return Traversal::EXIT;
  } else
    return Traversal::PRUNE;
}

template <class TSearchObject, class TOperation, class TWorld, class TShared>
INLINE Traversal::Result 
TestFor<TSearchObject,TOperation,TWorld,TShared>::visit(TSearchObject* /* obj */)
{
  myFound = true;
  return Traversal::EXIT;
}

template <class TSearchObject, class TOperation, class TWorld, class TShared>
INLINE bool 
TestFor<TSearchObject,TOperation,TWorld,TShared>::hasFound() const
{
  return myFound;
}

template <class TSearchObject, class TOperation, class TWorld, class TShared>
INLINE Traversal::Result 
TestFor<TSearchObject,TOperation,TWorld,TShared>::dispatch(Makeable* obj)
{
  tryConcrete(TShared,       obj);
  tryAbstract(TSearchObject, obj);
  // Searching for abstract since TSearchObject may be concrete or abstract, 
  // and tryAbstract works for both cases.
  
  return Traversal::CONTINUE;
}

//_______________________________________________________________ CollectorFor<>

#ifdef __GNUC__
// implementRTTI(CollectorFor, TOperation);
#endif // __GNUC__

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::CollectorFor(int size)
: myVisitedShareds(size)
{}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::~CollectorFor()
{
  for (long i=0; i<myCollection.count(); i++)
    delete myCollection.item(i);
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE List<TPathOf*>* 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::getContainer()
{
  return &myCollection;
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE bool 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::preprocessing()
{
  if (!TOperation::preprocessing())
    return false;

  myVisitedShareds.removeAll();
  myCollection.removeAll();
  
  return true;
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE Traversal::Result 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::visit(TShared* obj)
{
  TObjectBase* child = obj->getSubobject(0);
  char needTraverse;
  
  // 
  // If shared has already been processed, we know whether we have to descend
  // or not.
  //
  if (myVisitedShareds.lookup((void*)child, needTraverse)) {
    if (needTraverse)
      return Traversal::CONTINUE;
    else
      return Traversal::PRUNE;
  } 
  //
  // It's a complete new Shared object never been visited.
  // 
  else {
    // 
    // First lets test, wheather there is a render option inside the shared object.
    //
    TWorld localWorld;
    localWorld.getObjects()->adoptObject(child);
    
    TestFor<TSearchObject,TOperation,TWorld,TShared> finder;
    finder.execute(&localWorld);
    
    localWorld.getObjects()->orphanObject(child);
    
    needTraverse = (char)finder.hasFound();
    myVisitedShareds.insert((void*)child, needTraverse);

    if (needTraverse)
      return Traversal::CONTINUE;
    else
      return Traversal::PRUNE;
  }
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE Traversal::Result 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::visit(TSearchObject* /* obj */)
{
  myCollection.append(new TPathOf(*(getTraversal()->getPath())));
  
  return Traversal::CONTINUE;
}

template <class TSearchObject, class TObjectBase,
          class TOperation,
          class TPathOf, class TWorld, class TShared>
INLINE Traversal::Result 
CollectorFor<TSearchObject,TObjectBase,TOperation,TPathOf,TWorld,TShared>::dispatch(Makeable* obj)
{
  tryConcrete(TShared,       obj);
  tryAbstract(TSearchObject, obj);
  // Searching for abstract since TSearchObject may be concrete or abstract, 
  // and tryAbstract works for both cases.
  
  return Traversal::CONTINUE;
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
