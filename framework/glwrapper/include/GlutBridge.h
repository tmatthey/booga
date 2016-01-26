/*
 * GlutBridge.h
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
 *  $Id: GlutBridge.h,v 1.1 1996/04/25 09:58:56 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GlutBridge_H
#define _GlutBridge_H

#include "booga/glwrapper/GLAbstractBridge.h"

//___________________________________________________________________ GlutBridge

class GlutBridge : public GLAbstractBridge {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GlutBridge();                              // Use default version.
private:
  // GlutBridge(const GlutBridge&);             // Use default version.

public:
  // virtual ~GlutBridge();                     // Use default version.

private:
  // GlutBridge& operator=(const GlutBridge&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLAbstractBridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isEventPending();
  virtual void swapBuffers();
};

//______________________________________________________________________ INLINES

#endif // _GlutBridge_H

