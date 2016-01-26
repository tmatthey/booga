/*
 * $RCSfile: MURL.C,v $
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
 *  $Id: MURL.C,v 1.4 1996/09/13 08:05:04 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include <strstream.h>
#include "booga/base/Report.h" 
#include "URLContext.h" 

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/component/MURL.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


#include <string.h>

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
#endif

#include "booga/base/Value.h"

const char TEMP_DIR[] = "/tmp/";

//_____________________________________________________________________ URL3D

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::MURL(const RCString& url) 
{
#ifdef HAVE_WWW
  myURL = url;
  myTmpFile = RCString(TEMP_DIR);
  myTmpFile += myURL;
  
  long len = myTmpFile.length();
  for (long i=0; i<len; i++)
    switch (myTmpFile[i]) {
      case '/': case '~':
      case '*': case '?':
        myTmpFile[i] = '_';
        break;
        
      default:
        break;
    }
#else
  Report::warning("[MURL::MURL] Can not handle WWW calls on current system, ignoring");
#endif
}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::MURL(Exemplar exemplar) 
: TProxy(exemplar)
{}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE void MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::setURL(const RCString& name)
{
  myURL = name;
}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE RCString MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::getURL() const
{
  return myURL;
}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE TObject* MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::createSubject() const
{
  TWorld* world = new TWorld;

#ifdef HAVE_WWW
  // Read file into temporary file
  if (!readURL()) { 
    ostrstream os;
    os << "[MURL::createSubject] Failed to read URL ";
    os << "'" << myURL << "'";
    Report::warning(os);
  } else { // Read in new world.
    TParser parser;
    parser.setFilename(myTmpFile);
    parser.execute(world);
  }
  
  remove(myTmpFile.chars());

#endif
  
  TAggregate* retval = world->orphanObjects();
  delete world;
  
  return retval;
}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE TObject* MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::copy() const
{
  return new MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>(*this);
#ifndef HAVE_WWW
  Report::warning("[MURL::MURL] Can not handle WWW calls on current system, ignoring");
#endif
}

template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE Makeable* MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);

  getParameter(1, RCString, url);
  if (url.isEmpty()) {
    errMsg = "URL is required required";
    return NULL;    
  }

  return new TURL(url);
}

#ifdef HAVE_WWW
template<class TObject, class TProxy, class TURL, class TAggregate, class TWorld, class TParser>
INLINE bool MURL<TObject, TProxy, TURL, TAggregate, TWorld, TParser>
::readURL() const 
{
  URLContext* context = new URLContext(myTmpFile);
  bool success = false;
  
  if (context->error)
    return success;

  // Initiate W3C Reference Library
  HTLibInit("","");
  HTAlert_setInteractive(NO);

  // Initialize the protocol modules 
  HTProtocol_add("http", NO, HTLoadHTTP, NULL);
  HTProtocol_add("file", NO, HTLoadFile, NULL);
  HTProtocol_add("ftp", NO, HTLoadFTP, NULL);
  HTProtocol_add("gopher", NO, HTLoadGopher, NULL);

  // Initialize bindings between file suffixes and media types 
  HTFileInit();

  // Initialize set of converters 
  HTList* conv = HTList_new();

  // GENERIC converters 
  HTConversion_add(conv, "text/x-http", "*/*", HTTPStatus_new, 1.0, 0.0, 0.0);
  HTConversion_add(conv, "message/rfc822", "*/*", HTMIMEConvert, 1.0, 0.0, 0.0);
  HTConversion_add(conv, "multipart/*", "*/*", HTBoundary, 1.0, 0.0, 0.0);
  HTConversion_add(conv, "www/unknown", "*/*", HTGuess_new, 1.0, 0.0, 0.0);

  // Bind the list of converters to the request object 
  HTRequest_setConversion(context->request, conv, YES);

  // Get any proxy or gateway environment variables 
  HTProxy_getEnvVar();

  // Scan command Line for parameters 
  char * ref = HTParse(myURL.chars(), context->cwd.chars(), PARSE_ALL);
  context->anchor = (HTParentAnchor *) HTAnchor_findAddress(ref);
  HT_FREE(ref);

  /*
   ** Set up the output. Even though we don't use this explicit, it is
   ** required in order to show the stream stack that we know that we are
   ** getting raw data output on the output stream of the request object.
   */
  HTRequest_setOutputStream(context->request, 
                            HTFWriter_new(context->request, context->output, YES));

  // Register a call back function for the Net Manager 
  HTNetCall_addBefore(HTLoadStart, 0);
  HTNetCall_addAfter(URLContext::authentication_handler, HT_NO_ACCESS);
  HTNetCall_addAfter(URLContext::terminate_handler, HT_ALL);
    
  // Register our own MIME header handler for extra headers 
  HTHeader_addParser("*", NO, URLContext::header_handler);

  // Set timeout on sockets 
  HTEvent_registerTimeout(context->tv, context->request, URLContext::timeout_handler, NO);

  // Start the request 
  int status = HTLoadAnchor((HTAnchor *) context->anchor, context->request);

  if (status != YES) {
    ostrstream os;
    os << "[URL3D::readURL] Can't access resource '" << myURL << "'";
    Report::warning(os);
    success = false;
  } else {
    // Go into the event loop...
    HTEvent_Loop(context->request); 
    success = true;
  }
  
  delete context;
  HTLibTerminate();
  
  return success;
}

#endif // HAVE_WWW

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

