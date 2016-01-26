/*
 * $RCSfile: PExtraTemplates.h
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
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
 *  $Id: PExtraTemplates.h,v 1.7 1996/12/06 16:46:37 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PExtraTemplates_H
#define _PExtraTemplates_H

#include "DataBase.h"
#include "booga/base/List.h"

class Marshal;

template <class T>
Marshal& operator<<(Marshal& aDB, const List<T>& list);

template <class T>
Marshal& operator>>(Marshal& aDB, List<T>& list);
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
 #define TEMPLATE_IS_INCLUDE_FROM_H
 #include "PExtraTemplates.C"
#endif // TEMPLATE_IN_HEADER
 
//______________________________________________________________________ INLINES

#endif // _PExtraTemplates_H

