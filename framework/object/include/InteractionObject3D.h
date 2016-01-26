/*
 * $RCSfile: InteractionObject3D.h,v $
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
 *  $Id: InteractionObject3D.h,v 1.5 1996/08/09 14:53:11 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _InteractionObject3D_H
#define _InteractionObject3D_H

class World3D;
class Path3D;

#include "booga/object/MInteractionObject.h"
#include "booga/object/Proxy3D.h"

//________________________________________________________ InteractionObject3D

class InteractionObject3D : public MInteractionObject<Proxy3D, InteractionObject3D, Path3D, World3D> {
declareRTTI(InteractionObject3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  InteractionObject3D(Exemplar);
  InteractionObject3D();
  
private:
  InteractionObject3D(const InteractionObject3D&); // No copies.

public:
  // virtual ~InteractionObject3D();               // Use default version.

private:
  InteractionObject3D& operator=(const InteractionObject3D&);  // No assignments.
};

//______________________________________________________________________ INLINES

#endif // _InteractionObject3D_H

