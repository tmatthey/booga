/*
 * $RCSfile: MFile.C,v $
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: MFile.C,v 1.4 1996/09/13 08:04:54 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <string.h>

#include "booga/base/Value.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/component/MFile.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER

//_____________________________________________________________________ MFile

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::MFile(const RCString& name) 
{
  myFilename = name;
}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::MFile(Exemplar exemplar) 
: TProxy(exemplar)
{}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE void MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::setFilename(const RCString& name)
{
  myFilename = name;
}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE RCString MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::getFilename() const
{
  return myFilename;
}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE TObject* MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::createSubject() const
{
  TWorld* world = new TWorld;

  // Read in new world.
  TParser parser;
  parser.setFilename(myFilename);
  parser.execute(world);
    
  TAggregate* retval;
  if (parser.hasFailed())
    retval = NULL;
  else
    retval = world->orphanObjects();
    
  delete world;
  
  return retval;
}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE TObject* MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::copy() const
{
  return new TFile(*((TFile*)this));
}

template <class TObject, class TProxy, class TFile, class TAggregate, class TWorld, class TParser>
INLINE Makeable* MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>
::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);

  getParameter(1, RCString, name);
  if (name.isEmpty()) {
    errMsg = "Filename required";
    return NULL;    
  }

  return new TFile(name);
}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

