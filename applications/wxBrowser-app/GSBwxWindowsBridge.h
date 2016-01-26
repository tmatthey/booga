/*
 * GSBwxWindowsBridge.h
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
 *  $Id: GSBwxWindowsBridge.h,v 1.4 1997/04/08 11:05:42 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBwxWindowsBridge_H
#define _GSBwxWindowsBridge_H

#include "booga/glwrapper/GLAbstractBridge.h"

//_______________________________________________________________________ GLwxWindows

class GSBwxWindowsBridge : public GLAbstractBridge {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLwxWindows();                         // Use default version.
private:
  // GLwxWindows(const GLwxWindows&);            // Use default version.

public:
  // virtual ~GLwxWindows();                // Use default version.

private:
  // GLwxWindows& operator=(const GLwxWindows&);  // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLAbstractToolkit
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool isEventPending();
  virtual void swapBuffers();
};

//______________________________________________________________________ INLINES

#endif // _GSBwxWindowsBridge_H


