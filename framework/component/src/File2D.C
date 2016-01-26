/*
 * $RCSfile: File2D.C,v $
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
 *  $Id: File2D.C,v 1.2 1996/09/13 08:04:04 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/File2D.h"

//_____________________________________________________________________ File2D

implementRTTI(File2D, Proxy2D);

File2D::File2D(const RCString& name) 
: MFile<Object2D, Proxy2D, File2D, Aggregate2D, World2D, BSDL2DParser>(name) {}

File2D::File2D(Exemplar exemplar) 
: MFile<Object2D, Proxy2D, File2D, Aggregate2D, World2D, BSDL2DParser>(exemplar) {}

