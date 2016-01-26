/*
 * $RCSfile: Proxy3D.C,v $
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
 *  $Id: Proxy3D.C,v 1.7 1996/08/09 14:53:21 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>

#include "booga/base/Report.h" 
#include "booga/object/Proxy3D.h" 

//_____________________________________________________________________ Proxy3D

implementRTTI(Proxy3D, Object3D);

Proxy3D::Proxy3D()
: MProxy<Object3D, Proxy3D, Path3D, Ray3D>() 
{}

Proxy3D::Proxy3D(Exemplar exemplar) 
: MProxy<Object3D, Proxy3D, Path3D, Ray3D>(exemplar) 
{}

