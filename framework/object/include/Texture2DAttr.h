/*
 * Texture2DAttr.h 
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Texture2DAttr.h,v 1.2 1995/04/21 12:35:58 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Texture2DAttr_H
# define _Texture2DAttr_H

#include "booga/object/ObjectSpecifierAttr.h"

//_______________________________________________________________ Texture2DAttr

class Texture2DAttr : public ObjectSpecifierAttr {
declareRTTI(Texture2DAttr);
// enable RTTI support
};

#endif // _Texture2DAttr_H
