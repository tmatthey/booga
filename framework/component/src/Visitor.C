/*
 * $RCSfile: Visitor.C,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Visitor.C,v 1.1 1996/09/13 08:07:00 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#include "booga/component/Visitor.h"

//______________________________________________________________________ Visitor

implementRTTIBase(Visitor);

void Visitor::incLevel()
{}

void Visitor::decLevel()
{}
