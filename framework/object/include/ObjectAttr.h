/*
 * ObjectAttr.h
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: ObjectAttr.h,v 1.2 1995/04/21 12:33:37 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _ObjectAttr_H
# define _ObjectAttr_H

#include "booga/object/Makeable.h"

//___________________________________________________________________ ObjectAttr

class ObjectAttr : public Makeable {
declareRTTI(ObjectAttr);
// enable RTTI support
};

#endif // _ObjectAttr_H
