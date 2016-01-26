/*
 * $RCSfile: Collector3DFor.h,v $
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
 *  $Id: Collector3DFor.h,v 1.6 1996/09/13 08:03:33 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Collector3DFor_H
#define _Collector3DFor_H

#include "booga/object/Shared3D.h"
#include "booga/object/Aggregate3D.h"
#include "booga/object/Path3D.h"
#include "booga/component/Operation3D.h"
#include "booga/component/CollectorFor.h"

//__________________________________________________________ Collector3DFor<>

template <class TSearchObject>
class Collector3DFor : public CollectorFor<TSearchObject, Object3D, 
                                             Operation3D, 
                                             Path3D, World3D, Shared3D> {
// GNU !! declareRTTI(TestFor);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Collector3DFor();           // Use default version.
  // Collector3DFor(const Collector3DFor<TSearchObject>&);    
  // Use default version.

public:
  // virtual ~Collector3DFor();  // Use default version.

private:
  Collector3DFor<TSearchObject>& operator=(const Collector3DFor<TSearchObject>&);  
  // No assignments.  
};

#endif // _Collector3DFor_H

