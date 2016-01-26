/*
 * $RCSfile: InteractionObject2D.C,v $ 
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
 *  $Id: InteractionObject2D.C,v 1.2 1996/08/09 14:53:06 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/object/InteractionObject2D.h"

//________________________________________________________ InteractionObject2D

implementRTTI(InteractionObject2D, Proxy2D);

InteractionObject2D::InteractionObject2D(Exemplar exemplar)
: MInteractionObject<Proxy2D, InteractionObject2D, Path2D, World2D>(exemplar) 
{}

InteractionObject2D::InteractionObject2D()
: MInteractionObject<Proxy2D, InteractionObject2D, Path2D, World2D>() 
{}
