/*
 * $RCSfile: URLContext.C,v $
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
 *  $Id: URLContext.C,v 1.2 1996/08/07 16:16:43 streit Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "URLContext.h"

#ifdef HAVE_WWW

const long DEFAULT_TIMEOUT = 10;

URLContext::URLContext(RCString file)
{
  tv = new timeval;
  tv->tv_sec = DEFAULT_TIMEOUT;
  
  char* temp = HTFindRelatedName();
  cwd = RCString(temp);
  HT_FREE(temp);
  
  if ((output = fopen(file.chars(),"w")) == NULL) {
    ostrstream os;
    os << "[URLContext::URLContext] couldn't open file ";
    os << "'" << file << "'";
    Report::recoverable(os);
    error = true;  
  } else
    error = false;

  /* Bind the ConLine object together with the Request Object */
  request = HTRequest_new();
  HTRequest_setOutputFormat(request, WWW_SOURCE);
  HTRequest_setContext (request, this);
}

URLContext::~URLContext()
{
  HTRequest_delete(request);
  fclose(output);
  delete tv;
}

// ___________________________________________________________________ callbacks

/*
 *  This function is registered to handle access authentication,
 *  for example for HTTP
 */
int URLContext::authentication_handler (HTRequest* request, int)
{
  URLContext* context = (URLContext*) HTRequest_context(request);

  // Ask the authentication module for getting credentials 
  if (HTAA_authentication(request) && HTAA_retryWithAuth(request)) {
    // Make sure we do a reload from cache 
    HTRequest_setReloadMode(request, HT_FORCE_RELOAD);

    // Start request with new credentials 
    HTLoadAnchor((HTAnchor *) context->anchor, context->request);
  } else {
    Report::warning("[authentication_handler] Access denied");
  }

  return HT_ERROR;  // Make sure this is the last callback in the list 
}

/*
 *  This function is registered to handle the result of the request
 */
int URLContext::terminate_handler (HTRequest* request, int status) 
{
  if (status != HT_LOADED) {
    HTAlertCallback *cbf = HTAlert_find(HT_A_MESSAGE);
    if (cbf) 
      (*cbf)(request, HT_A_MESSAGE, HT_MSG_NULL, NULL, HTRequest_error(request), NULL);
  }

  // Terminate Event Loop
  HTEvent_stopLoop();

  return HT_OK;
}

/*
 *  This function is registered to handle timeout in select eventloop
 */
int URLContext::timeout_handler (HTRequest* request)
{
  Report::warning("[timeout_handler] Request timeout");

  HTRequest_kill(request);

  return 0;
}

/*
 *  This function is registered to handle unknown MIME headers
 */
int URLContext::header_handler (HTRequest*, CONST char* token)
{
  ostrstream os;
  os << "[header_handler] Parsing unknown header ";
  os << token;
  Report::warning(os);

  return HT_OK;
}

#endif // HAVE_WWW

