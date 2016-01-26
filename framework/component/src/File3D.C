/*
 * $RCSfile: File3D.C,v $
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
 *  $Id: File3D.C,v 1.10 1996/09/13 08:04:06 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/component/File3D.h"

//_____________________________________________________________________ File3D

implementRTTI(File3D, Proxy3D);

File3D::File3D(const RCString& name) 
: MFile<Object3D, Proxy3D, File3D, Aggregate3D, World3D, Parser3D>(name) {}

File3D::File3D(Exemplar exemplar) 
: MFile<Object3D, Proxy3D, File3D, Aggregate3D, World3D, Parser3D>(exemplar) {}

