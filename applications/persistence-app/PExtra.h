/*
 * $RCSfile: PExtra.h
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
 *  $Id: PExtra.h,v 1.7 1996/12/06 16:46:31 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PExtra_H
#define _PExtra_H

/*
 * Add semi-persistence to several 'standard' classes by providing
 * operator<< and operator>> functions for these classes.
 * As a result instances of these classes may be saved inside 
 * persistent objects (i.e. objects derived from class Persistent) but
 * not as stand alone persistent objects.
 */

#include "DataBase.h" 
class RCString;
class Marshal;

//_____________________________________________________________________ PExtra

Marshal& operator<<(Marshal& aDB, const RCString& s);

Marshal& operator>>(Marshal& aDB, RCString& s);
 
#endif // _PExtra_H

