/*
 * $RCSfile: AsciiMarshal.C,v $
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
 *  $Id: AsciiMarshal.C,v 1.1 1996/12/06 16:43:50 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "AsciiMarshal.h"
#include <string.h>  // strlen()

//_____________________________________________________________________ AsciiMarshal

AsciiMarshal::AsciiMarshal() {
}

AsciiMarshal::~AsciiMarshal(){
}

Marshal& AsciiMarshal::operator<<(char c) {
  *myOs << c;
  return *this;
}

Marshal& AsciiMarshal::operator<<(unsigned char uc) {
  *myOs << uc;
  return *this;
}

Marshal& AsciiMarshal::operator<<(short s) {
  *myOs << s << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(unsigned short us) {
  *myOs << us << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(long l) {
  *myOs << l << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(unsigned long ul) {
  *myOs << ul << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(int i) {
  *myOs << i << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(unsigned int ui) {
  *myOs << ui << std::endl;
  return *this;
}
Marshal& AsciiMarshal::operator<<(float f) {
  *myOs << f << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(double d) {
  *myOs << d << std::endl;
  return *this;
}

Marshal& AsciiMarshal::operator<<(const char* buf) {
  *myOs << strlen(buf) << " ";
  *myOs << buf << std::endl;
  return *this;
}


Marshal& AsciiMarshal::write(const char *buf, long len) {
  *myOs << len << " ";
  myOs->write(const_cast<char*>(buf),len);
  *myOs << std::endl;
  return *this;
}

Marshal& AsciiMarshal::write(const unsigned char* buf, long len) {
  *myOs << len << " ";
  myOs->write(reinterpret_cast<char*>(const_cast<unsigned char*>(buf)), len);
  *myOs << std::endl;
  return *this;
}



Marshal& AsciiMarshal::operator>>(char& c) {
  *myIs >> c;
  return *this;
}

Marshal& AsciiMarshal::operator>>(unsigned char& uc) {
  *myIs >> uc;
  return *this;
}

Marshal& AsciiMarshal::operator>>(short& s) {
  *myIs >> s;
  return *this;
}

Marshal& AsciiMarshal::operator>>(unsigned short& us) {
  *myIs >> us;
  return *this;
}

Marshal& AsciiMarshal::operator>>(long& l) {
  *myIs >> l;
  return *this;
}

Marshal& AsciiMarshal::operator>>(unsigned long& ul) {
  *myIs >> ul;
  return *this;
}

Marshal& AsciiMarshal::operator>>(int& i) {
  *myIs >> i;
  return *this;
}

Marshal& AsciiMarshal::operator>>(unsigned int& ui) {
  *myIs >> ui;
  return *this;
}
Marshal& AsciiMarshal::operator>>(float& f) {
  *myIs >> f;
  return *this;
}

Marshal& AsciiMarshal::operator>>(double& d) {
  *myIs >> d;
  return *this;
}

Marshal& AsciiMarshal::operator>>(char*& buf) {
  long len;
  *myIs >> len;
  if (buf == NULL) {      // allocate memory
    buf = new char[len+1];
  }                       // else assume buf is big enough
  myIs->read(buf,1);     // dummy read delimiter
  myIs->read(buf,len);   // read the string
  buf[len] = '\0';        // terminate string by a null character
  return *this;
}

Marshal& AsciiMarshal::read(char*& buf, long& len) {
  long readlen;
  *myIs >> readlen;
  if (buf == NULL) {      // allocate memory
    buf = new char[readlen];
    len = readlen;
  }
  myIs->read(buf,1);     // dummy read delimiter
  if (readlen <= len) {
    myIs->read(buf,len);   // read the data
  }
  else {
    myIs->read(buf,len);  // read as much data as possible
    char *dummybuf = new char[readlen-len];
    myIs->read(dummybuf,readlen - len); // skip the rest
    delete dummybuf;
  }
  return *this;
}

Marshal& AsciiMarshal::read(unsigned char*& buf, long& len) {
  long readlen;
  *myIs >> readlen;
  if (buf == NULL) {      // allocate memory
    buf = new unsigned char[readlen];
    len = readlen;
  }
  myIs->read(reinterpret_cast<char*>(buf),1);     // dummy read delimiter
  if (readlen <= len) {
    myIs->read(reinterpret_cast<char*>(buf),len);   // read the data
  }
  else {
    myIs->read(reinterpret_cast<char*>(buf),len);  // read as much data as possible
    unsigned char *dummybuf = new unsigned char[readlen-len];
    myIs->read(reinterpret_cast<char*>(dummybuf),readlen - len); // skip the rest
    delete dummybuf;
  }
  return *this;
}
