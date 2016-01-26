/*
 * $RCSfile: Component.C,v $
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
 *  $Id: Component.C,v 1.6 1996/09/13 08:03:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Report.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/component/Component.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//_________________________________________________________________ Component<>

template <class TWorldInput, class TWorldResult, 
          class TTraversal>     
INLINE Component<TWorldInput,TWorldResult,TTraversal>::Component()
{
  myCurrentWorld = NULL;
  myResultWorld  = NULL;
  myTraversal    = NULL;
  reset();
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE Component<TWorldInput,TWorldResult,TTraversal>::~Component()
{
  delete myTraversal;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE TWorldResult* Component<TWorldInput,TWorldResult,
                               TTraversal>::execute(TWorldInput* world)
{
  reset();

  if (world == NULL) {
    failed();
    Report::recoverable("[Component<>::execute] world object == NULL");
    return NULL;
  }
  
  myCurrentWorld = world;
  myResultWorld  = new TWorldResult;
  bool success   = true;

  success = preprocessing();
  if (!success) {
    failed();
    Report::recoverable("[Component<>::execute] preprocessing() failed");
    delete myResultWorld;
    myResultWorld = NULL;
    cleanupAfterFailure();

    return NULL;
  }

  success = doExecute();
  if (!success) {
    failed();
    Report::recoverable("[Component<>::execute] doExecute() failed");
    delete myResultWorld;
    myResultWorld = NULL;
    cleanupAfterFailure();

    return NULL;
  }

  success = postprocessing(); 
  if (!success) {
    failed();
    Report::recoverable("[Component<>::execute] postprocessing() failed");
    delete myResultWorld;
    myResultWorld = NULL;
    cleanupAfterFailure();

    return NULL;
  }

  if (myResultWorld->isEmpty()) {
    delete myResultWorld;
    return NULL;
  }
  else
    return myResultWorld;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE void Component<TWorldInput,TWorldResult,
                      TTraversal>::adoptTraversal(TTraversal* traversal) 
{
  if (traversal == NULL) {
    Report::warning("[Component<>::adoptTraversal] NULL pointer passed");
    return;
  }
    
  if (myTraversal != NULL && myTraversal != traversal)
    delete myTraversal;

  myTraversal = traversal;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE void Component<TWorldInput,TWorldResult,
                      TTraversal>::adoptResult(TWorldResult* world) 
{
  if (world == NULL) {
    Report::warning("[Component<>::adoptResult] NULL pointer passed");
    return;
  }
    
  if (myResultWorld != NULL && myResultWorld != world)
    delete myResultWorld;

  myResultWorld = world;
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE bool Component<TWorldInput,TWorldResult,
                      TTraversal>::traverse(TWorldInput* world)
{
  if (world == NULL) {
    Report::recoverable("[Component<>::traverse] world object == NULL");
    return false;
  }

  if (getTraversal() == NULL) {
    Report::recoverable("[Component<>::traverse] no traversal object set, use adoptTraversal() first");
    return false;
  }
    
  return getTraversal()->apply(world, this);
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE bool Component<TWorldInput,TWorldResult,
                      TTraversal>::preprocessing()   
{ 
  return true; 
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE bool Component<TWorldInput,TWorldResult,
                      TTraversal>::doExecute()       
{ 
  return traverse(getWorld()); 
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE bool Component<TWorldInput,TWorldResult,
                      TTraversal>::postprocessing()  
{ 
  return true; 
}

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE void Component<TWorldInput,TWorldResult,
                      TTraversal>::cleanupAfterFailure()
{
  // Nothing performed by default.
}                      

template <class TWorldInput, class TWorldResult,
          class TTraversal>     
INLINE Traversal::Result Component<TWorldInput,TWorldResult,
                                   TTraversal>::dispatch(Makeable* /* obj */)
{
  //
  // No decomposition is performed by default.
  //
  return Traversal::CONTINUE; 
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)


