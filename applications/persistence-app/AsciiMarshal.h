/*
 * $RCSfile: AsciiMarshal.h,v $
 *
 * Copyright (C) 1996, Andrey Collison <collison@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: AsciiMarshal.h,v 1.1 1996/12/06 16:43:52 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AsciiMarshal_H
#define _AsciiMarshal_H

#include "Marshal.h"

//_____________________________________________________________________ AsciiMarshal

class AsciiMarshal : public Marshal {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AsciiMarshal();
private:
  AsciiMarshal(const AsciiMarshal&);             // No copies.

public:
  virtual ~AsciiMarshal();

private:
  AsciiMarshal& operator=(const AsciiMarshal&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AsciiMarshal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Marshal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Marshal& operator<<(char c);
  virtual Marshal& operator<<(unsigned char uc);
  virtual Marshal& operator<<(short s);
  virtual Marshal& operator<<(unsigned short us);
  virtual Marshal& operator<<(int i);
  virtual Marshal& operator<<(unsigned int ui);
  virtual Marshal& operator<<(long l);
  virtual Marshal& operator<<(unsigned long ul);
  virtual Marshal& operator<<(float f);
  virtual Marshal& operator<<(double d);
  virtual Marshal& operator<<(const char* buf);
  virtual Marshal& write(const char *buf, long len);
  virtual Marshal& write(const unsigned char* buf, long len);
    
  virtual Marshal& operator>>(char& c);
  virtual Marshal& operator>>(unsigned char& uc);
  virtual Marshal& operator>>(short& s);
  virtual Marshal& operator>>(unsigned short& us);
  virtual Marshal& operator>>(int& i);
  virtual Marshal& operator>>(unsigned int& ui);
  virtual Marshal& operator>>(long& l);
  virtual Marshal& operator>>(unsigned long& ul);
  virtual Marshal& operator>>(float& f);
  virtual Marshal& operator>>(double& d);
  virtual Marshal& operator>>(char*& buf);
  virtual Marshal& read(char*& buf, long& len);
  virtual Marshal& read(unsigned char*& buf, long& len);
  // 
  // the member functions operator>>(char*& buf), read(char*& buf, long& len),
  // and read(unsigned char*& buf, long& len) do accept a NULL buf
  // in which case they allocate the appropriate amount of memory.
  // It is the responsibility of the user to free this memory.
  // Warning: The equivalent number of write operations used to write an object
  // must be used to read the same object. e.g.
  //    write(buf,100) ...... read(buf,50); read(buf,50); // illegal
  //    write(buf,100) ...... read(buf,100);  // correct
  //

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:

};

//______________________________________________________________________ INLINES

#endif // _AsciiMarshal_H

