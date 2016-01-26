/*
 * $RCSfile: ParserUtilities.C,v $
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
 *  $Id: ParserUtilities.C,v 1.2 1997/09/19 07:14:25 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <errno.h>
#ifdef SVR4
#include <unistd.h>   // pipe(), fork(), execl()
#include <sys/wait.h> // wait()
#endif

#include "booga/base/ParserUtilities.h"

//______________________________________________________________ ParserUtilities

FILE* ParserUtilities::cppopen(FILE* fp, const RCString& cppParameters)
{
  if (fp == NULL)
    return NULL;

#ifdef WIN32
  return fp; // no cpp;
#else    
  //
  // Create pipe 1
  //
  int filedescPipe1[2];
  if (pipe(filedescPipe1) == -1)
    return NULL;

  // 
  // Spawn processes for pipe 1
  // 
  switch (fork()) {
    case -1:			// error
      return NULL;
    case 0:			// child process for pipe 1
      //
      // Attach side 1 of pipe 1 to stdout of child process for pipe 1
      // and create pipe 2 and the corresponding processes.
      //
      if (dup2(filedescPipe1[1], 1) == 1) {
	close(filedescPipe1[0]);
	close(filedescPipe1[1]);

	// ------------------------------------------------------------
	// 
	// Create pipe 2
	//
	int filedescPipe2[2];
	if (pipe(filedescPipe2) == -1)
	  return NULL;

	// 
	// Spawn processes for pipe 2
	//
	switch (fork()) {
	  case -1:			// error
	    return NULL;

	  case 0: {			// child process for pipe 2
	    // 
	    // Attach to side 1 of pipe 2. Read from provided FILE* (parameter) 
	    // and write to parent process through pipe 2.
	    //
	    FILE* toCPP = fdopen(filedescPipe2[1],"w");
	    if (toCPP != NULL) {
	      char ch[256];
	      while (fgets(ch, 255, fp))
		fputs(ch, toCPP);
	      fclose(toCPP);
	    }

	    close(filedescPipe2[0]);
	    close(filedescPipe2[1]);
	    _exit(127);
           }
           
	  default:			// parent process for pipe 2
	    // 
	    // Attach to side 0 of pipe 2 and execute C preprocessor with
	    // input attached to side 0 of pipe 2 and output attached to 
	    // side 1 of pipe 1.
	    //
	    if (dup2(filedescPipe2[0], 0) == 0) {
	      close(filedescPipe2[0]);
	      close(filedescPipe2[1]);

               RCString command = RCString(CPP) + RCString(" ") + cppParameters;
	      execl(SHELL, "sh", "-c", command.chars(), NULL);
	    }
	}
	// ------------------------------------------------------------
      }

      _exit(127);
	    
    default:			// parent process for pipe 1
      // 
      // Attach to side 0 of pipe 1. Create FILE* (return value) from
      // file descriptor, provided by pipe.
      //
      FILE* retval = fdopen(filedescPipe1[0],"r");
      if (retval == NULL)
	close(filedescPipe1[0]);
      close(filedescPipe1[1]);
      return retval;
  }
#endif
}

int ParserUtilities::cppclose(FILE* fp)
{
  if (fclose(fp) == EOF)
    return -1;
#ifdef WIN32
  return -1;
#else
  int status;
  while (wait(&status) == -1)
    if (errno != EINTR)
      return -1;

  return status;
#endif
}
