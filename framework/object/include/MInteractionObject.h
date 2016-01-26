/*
 * $RCSfile: MInteractionObject.h,v $
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
 *  $Id: MInteractionObject.h,v 1.5 1997/12/10 14:45:22 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MInteractionObject_H
#define _MInteractionObject_H

#include "booga/base/Exemplar.h"

//___________________________________________________________ MInteractionObject

template <class TProxy, class TInteractioObject, class TPath, class TWorld>
class MInteractionObject : public TProxy {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  MInteractionObject(Exemplar);
  MInteractionObject() {}
  
private:
  MInteractionObject(const MInteractionObject<TProxy, TInteractioObject, TPath, TWorld>&); 
  // No copies.

public:
  // virtual ~MInteractionObject();               // Use default version.

private:
  MInteractionObject<TProxy, TInteractioObject, TPath, TWorld>& 
    operator=(const MInteractionObject<TProxy, TInteractioObject, TPath, TWorld>&);
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class InteractionObject3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual int activate(TWorld* world, const TPath* path, int x, int y) = 0;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../object/src/MInteractionObject.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MInteractionObject_H

