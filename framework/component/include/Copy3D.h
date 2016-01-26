/*
 * $RCSfile: Copy3D.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: Copy3D.h,v 1.3 1996/08/01 11:59:40 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _Copy3D_H
#define _Copy3D_H

#include "booga/component/Operation3D.h"

//_______________________________________________________________________ Copy3D

class Copy3D : public Operation3D {
declareRTTI(Copy3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Copy3D();
  // Copy3D(const Copy3D&);          // Use default version.

public:
  // virtual ~Copy3D();              // Use default version.

private:
  Copy3D& operator=(const Copy3D&);  // No assignments.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();
};

#endif // _Copy3D_H
