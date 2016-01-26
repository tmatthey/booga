/*
 * $RCSfile: Collector2DFor.h,v $
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
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: Collector2DFor.h,v 1.7 1996/08/09 14:13:57 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Collector2DFor_H
#define _Collector2DFor_H

#include "booga/object/Shared2D.h"
#include "booga/object/Aggregate2D.h"
#include "booga/object/Path2D.h"
#include "booga/component/Operation2D.h"
#include "booga/component/CollectorFor.h"

//__________________________________________________________ Collector32For<>

template <class TSearchObject>
class Collector2DFor : public CollectorFor<TSearchObject, Object2D, 
                                             Operation2D, 
                                             Path2D, World2D, Shared2D> {
// GNU !! declareRTTI(Collector2DFor);
// enable RTTI support


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // Collector2DFor();           // Use default version.
  // Collector2DFor(const Collector2DFor<TSearchObject>&);    
  // Use default version.

public:
  // virtual ~Collector2DFor();  // Use default version.

private:
  Collector2DFor<TSearchObject>& operator=(const Collector2DFor<TSearchObject>&);  
  // No assignments.  
};


#endif // _Collector2DFor_H


