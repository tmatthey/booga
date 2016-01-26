/*
 * $RCSfile: Component.h,v $
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
 *  $Id: Component.h,v 1.8 1996/09/13 08:03:51 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Component_H
#define _Component_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/component/Traversal.h"   // enum Traversal::Result
#include "booga/component/Visitor.h"

//_________________________________________________________________ Component<>

template <class TWorldInput,     //  Input:  World3D or World2D
          class TWorldResult,    //  Result: World3D pr World3D
          class TTraversal>      //  AbstractTraversal3D or AbstractTraversal2D
class Component : public Visitor {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Component();
private:
  Component(const Component<TWorldInput,TWorldResult,TTraversal>&);            
  // No copies.

public:
  virtual ~Component();

private:
  Component<TWorldInput,TWorldResult,TTraversal>& 
    operator=(const Component<TWorldInput,TWorldResult,TTraversal>&);  
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  bool hasFailed() const;
  // Returns true if operation has failed, flase otherwise.
  
public:
  TWorldResult* execute(TWorldInput* world);
  // Execute the operation. 
  // The operation may produce a result (generate a new world): return value != NULL
  // or just traverse and/or modify the passed world object: return value == NULL.
  // It is also possible to modify the provided world object *AND* generate a result.
  //
  // If the return value != NULL, the caller is responsible for the memory allocated.
  
public:
  TTraversal* getTraversal() const;
  void adoptTraversal(TTraversal* traversal);
  // Setter and getter methods to access the traversal object that is used 
  // to traverse the world.

protected:
  TWorldInput*  getWorld()  const;
  // Accessor to the world passed with the execute(world) method.  
  TWorldResult* getResult() const;
  void adoptResult(TWorldResult* world);
  // Accessor to the world automatically generated in the execute() method. 
  // This world object is used as the result of the call to execute().
 
protected:
  bool traverse(TWorldInput* world);
  // true success
  // false otherwise
 
protected:
  virtual bool preprocessing();
  virtual bool doExecute();
  virtual bool postprocessing();
  // Each of these methods returns true on success, false otherwise.
  //
  // The code fragment
  //
  //    Component c;
  //    result = c.execute(world);
  //
  // leads to the following calls
  //
  //    execute(world)
  //      preprocessing()
  //      doExecute()
  //        traverse(world)
  //      posprocessing()
  //
  // The behaviour may be individually overridden by subclassing.
 
protected:
  void reset();
  // Reset the failure flag.
  void failed();
  // To be called if the operation failed.

private:
  virtual void cleanupAfterFailure();
  // This method is called if one of the methods preprocessing(), 
  // doExecute() or postprocessing() returned false. By overriding this 
  // method a component may do individual cleanup work (e.g. release 
  // allocted memory) as required.
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Traversal::Result dispatch(Makeable* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TWorldInput*   myCurrentWorld;  // The input world to work on.
  TWorldResult*  myResultWorld;   // The result of the operation.
  TTraversal*    myTraversal;     // The traversal object to be used.
  bool           myFailedFlag;    // True indicates failure of the operation.
};

//______________________________________________________________________ INLINES

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline bool Component<TWorldInput,TWorldResult,
                      TTraversal>::hasFailed() const
{
  return myFailedFlag;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline void Component<TWorldInput,TWorldResult,
                      TTraversal>::reset()
{
  myFailedFlag = false;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline void Component<TWorldInput,TWorldResult,
                      TTraversal>::failed()
{
  myFailedFlag = true;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline TWorldInput* Component<TWorldInput,TWorldResult,
                              TTraversal>::getWorld() const 
{ 
  return myCurrentWorld; 
}
                       
template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline TWorldResult* Component<TWorldInput,TWorldResult,
                               TTraversal>::getResult() const 
{ 
  return myResultWorld;  
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
inline TTraversal* Component<TWorldInput,TWorldResult,
                             TTraversal>::getTraversal() const 
{ 
  return myTraversal;
}

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../component/src/Component.C"
#endif // TEMPLATE_IN_HEADER

#endif // _Component_H

