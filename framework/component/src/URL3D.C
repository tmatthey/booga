/*
 * $RCSfile: URL3D.C,v $
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
 *
 * READ THIS!
 *  The currently used version of libwww has a bug that has severe
 *  influence on this code. The library has to be corrected in order
 *  to use url objects.
 *
 *  Enter directory WWW/Library/Implementation of the libwww distribution
 *  and edit file HTEvntrg.c. In function HTEvent_Loop for standard
 *  UNIX version add the following line:
 *   HTEndLoop = 0;
 *
 * -----------------------------------------------------------------------------
 *  $Id: URL3D.C,v 1.8 1996/09/13 08:06:54 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/component/URL3D.h"

//_____________________________________________________________________ URL3D

implementRTTI(URL3D, Proxy3D);

URL3D::URL3D(const RCString& url) 
: MURL<Object3D, Proxy3D, URL3D, Aggregate3D, World3D, Parser3D>(url) {}

URL3D::URL3D(Exemplar exemplar) 
: MURL<Object3D, Proxy3D, URL3D, Aggregate3D, World3D, Parser3D>(exemplar) {}


