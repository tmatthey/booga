/*
 * $RCSfile: Proxy2D.C,v $
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
 *  $Id: Proxy2D.C,v 1.2 1996/08/09 14:53:18 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>

#include "booga/base/Report.h" 
#include "booga/object/Proxy2D.h" 

//_____________________________________________________________________ Proxy2D

implementRTTI(Proxy2D, Object2D);

Proxy2D::Proxy2D()
: MProxy<Object2D, Proxy2D, Path2D, Ray2D>() 
{}

Proxy2D::Proxy2D(Exemplar exemplar) 
: MProxy<Object2D, Proxy2D, Path2D, Ray2D>(exemplar) 
{}

