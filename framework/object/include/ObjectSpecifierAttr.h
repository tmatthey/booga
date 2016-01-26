/*
 * ObjectSpecifierAttr.h 
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ObjectSpecifierAttr.h,v 1.2 1995/04/21 12:33:43 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ObjectSpecifierAttr_H
# define _ObjectSpecifierAttr_H

#include "booga/object/Makeable.h"

//__________________________________________________________ ObjectSpecifierAttr

class ObjectSpecifierAttr : public Makeable {
declareRTTI(ObjectSpecifierAttr);
// enable RTTI support
};

#endif // _ObjectSpecifierAttr_H
