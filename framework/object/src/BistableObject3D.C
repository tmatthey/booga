/*
 * $RCSfile: BistableObject3D.C,v $ 
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: BistableObject3D.C,v 1.5 1996/09/13 08:03:23 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/BistableObject3D.h"

//________________________________________________________________ BistableObject3D

implementRTTI(BistableObject3D, InteractionObject3D);

BistableObject3D::BistableObject3D(Exemplar exemplar)
: MBistableObject<InteractionObject3D, BistableObject3D, Object3D, Object3DAttr, Shared3D, World3D, Path3D>(exemplar) {}

BistableObject3D::BistableObject3D(Object3D* on, Object3D* off, Switch state)
: MBistableObject<InteractionObject3D, BistableObject3D, Object3D, Object3DAttr, Shared3D, World3D, Path3D>(on, off, state) {}

