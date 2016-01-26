/*
 * $RCSfile: InteractionObject2D.h,v $
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
 *  $Id: InteractionObject2D.h,v 1.2 1996/08/09 14:53:07 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InteractionObject2D_H
#define _InteractionObject2D_H

class World2D;
class Path2D;

#include "booga/object/MInteractionObject.h"
#include "booga/object/Proxy2D.h"

//________________________________________________________ InteractionObject2D

class InteractionObject2D : public MInteractionObject<Proxy2D, InteractionObject2D, Path2D, World2D> {
declareRTTI(InteractionObject2D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InteractionObject2D(Exemplar);
  InteractionObject2D();
  
private:
  InteractionObject2D(const InteractionObject2D&); // No copies.

public:
  // virtual ~InteractionObject2D();               // Use default version.

private:
  InteractionObject2D& operator=(const InteractionObject2D&);  // No assignments.
};

//______________________________________________________________________ INLINES

#endif // _InteractionObject2D_H

