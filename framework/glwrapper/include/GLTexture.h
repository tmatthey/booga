/*
 * GLTexture.h
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: GLTexture.h,v 1.1 1995/12/14 17:27:57 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GLTexture_H
#define _GLTexture_H

//____________________________________________________________________ GLTexture

class GLTexture {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // GLTexture();                            // Use default version.
  // GLTexture(const GLTexture&);            // Use default version.

public:
  // virtual ~GLTexture();                   // Use default version.

public:
  // GLTexture& operator=(const GLTexture&); // Use default version.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class GLTexture
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum TexturingType { 
     GL,    // Perform texture operation using the GL engine.
     BOOGA  // Perform texture opertaion the BOOGA way.
  };
  
  static void setTexturingType(TexturingType type);
  static TexturingType getTexturingType();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  static TexturingType ourTexturingType;
};

//______________________________________________________________________ INLINES

#endif // _GLTexture_H

