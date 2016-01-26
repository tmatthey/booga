/*
 * $RCSfile: URLContext.h,v $
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
 *  $Id: URLContext.h,v 1.2 1996/08/07 16:16:43 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _URLContext_H
#define _URLContext_H


#ifdef HAVE_WWW
extern "C" {
#include <www/WWWLib.h>
#include <www/WWWHTTP.h>
#include <www/WWWFTP.h>
#include <www/WWWFile.h>
#include <www/WWWGophe.h>
#include <www/HTInit.h>
#include <www/HTProxy.h>
#include <www/HTFormat.h>
#include <www/HTHeader.h>
#include <www/HTHome.h>
}


#include "booga/base/RCString.h"

//______________________________________________________________ URL3DContext

class URLContext {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  URLContext(RCString file);                         
private:
  URLContext(const URLContext&);             // No copies.

public:
  virtual ~URLContext();                

private:
  URLContext& operator=(const URLContext&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class URLContext
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  static int authentication_handler (HTRequest* request, int status);
  static int terminate_handler (HTRequest* request, int status);
  static int timeout_handler (HTRequest* request);
  static int header_handler (HTRequest* request, CONST char* token);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum CLFlags {
    CL_FILTER = 0x1,
    CL_COUNT  = 0x2
  };

public:                    // Only a local class, so don't worry
  HTRequest* request;
  HTParentAnchor*	anchor;
  HTMethod method;         // What method are we envoking 
  struct timeval* tv;	// Timeout on socket 
  RCString cwd;            // Current dir URL 
  FILE* output;
  HTFormat format;         // Input format from console 
  CLFlags flags;
  bool error;              // Error has occured
};

#endif // HAVE_WWW

#endif // _URLContext_H

