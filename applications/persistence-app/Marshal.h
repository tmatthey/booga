/*
 * $RCSfile: Marshal.h,v $
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
 *  $Id: Marshal.h,v 1.1 1996/12/06 16:44:54 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Marshal_H
#define _Marshal_H

#include <iostream>

class Persistent;

//_____________________________________________________________________ Marshal

class Marshal {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Marshal();
private:
  Marshal(const Marshal&);             // No copies.

public:
  virtual ~Marshal();                

private:
  Marshal& operator=(const Marshal&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Marshal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void marshal(Persistent* p, std::ostream& os);
  void unmarshal(Persistent* p, std::istream& is);

  virtual Marshal& operator<<(char c)=0;
  virtual Marshal& operator<<(unsigned char uc)=0;
  virtual Marshal& operator<<(short s)=0;
  virtual Marshal& operator<<(unsigned short us)=0;
  virtual Marshal& operator<<(int i)=0;
  virtual Marshal& operator<<(unsigned int ui)=0;
  virtual Marshal& operator<<(long l)=0;
  virtual Marshal& operator<<(unsigned long ul)=0;
  virtual Marshal& operator<<(float f)=0;
  virtual Marshal& operator<<(double d)=0;
  virtual Marshal& operator<<(const char* buf)=0;
  virtual Marshal& write(const char *buf, long len)=0;
  virtual Marshal& write(const unsigned char* buf, long len)=0;
    
  virtual Marshal& operator>>(char& c)=0;
  virtual Marshal& operator>>(unsigned char& uc)=0;
  virtual Marshal& operator>>(short& s)=0;
  virtual Marshal& operator>>(unsigned short& us)=0;
  virtual Marshal& operator>>(int& i)=0;
  virtual Marshal& operator>>(unsigned int& ui)=0;
  virtual Marshal& operator>>(long& l)=0;
  virtual Marshal& operator>>(unsigned long& ul)=0;
  virtual Marshal& operator>>(float& f)=0;
  virtual Marshal& operator>>(double& d)=0;
  virtual Marshal& operator>>(char*& buf)=0;
  virtual Marshal& read(char*& buf, long& len)=0;
  virtual Marshal& read(unsigned char*& buf, long& len)=0;
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
protected:
  std::ostream* myOs;
  std::istream* myIs;
};

//______________________________________________________________________ INLINES

#endif // _Marshal_H

