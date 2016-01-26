/*
 * $RCSfile: URL2D.C,v $
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
 *  $Id: URL2D.C,v 1.2 1996/09/13 08:06:52 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/component/URL2D.h"

//_____________________________________________________________________ URL2D

implementRTTI(URL2D, Proxy2D);

URL2D::URL2D(const RCString& url) 
: MURL<Object2D, Proxy2D, URL2D, Aggregate2D, World2D, BSDL2DParser>(url) {}

URL2D::URL2D(Exemplar exemplar) 
: MURL<Object2D, Proxy2D, URL2D, Aggregate2D, World2D, BSDL2DParser>(exemplar) {}


