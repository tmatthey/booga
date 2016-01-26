/*
 * $RCSfile: PBinary.C,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: PBinary.C,v 1.3 1996/12/06 16:44:57 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <fstream>
#include <sstream>
#include "PBinary.h"
#include "DataBase.h"
#include "PExtra.h"
#include "Marshal.h"


//_____________________________________________________________________ PBinary

implementRTTI(PBinary, Persistent);

PBinary::PBinary(DataBase& aDB) 
: Persistent(aDB),
myFilename(""),
myFiletype(""),
mySize(0),
myBuffer(NULL)
{
}

PBinary::PBinary(Prototype& aPrototype) 
: Persistent(aPrototype),
myFilename(""),
myFiletype(""),
mySize(0),
myBuffer(NULL)
{
}

PBinary::~PBinary()
{
   delete myBuffer;
}

Persistent* PBinary::newInstance()
{
  return new PBinary(aPrototype);
}

int PBinary::destroy() {
  return 0;
}

void PBinary::marshal(Marshal* aMarshal) {
  *aMarshal << *this;
}

void PBinary::unmarshal(Marshal* aMarshal) {
  *aMarshal >> *this;
}

Marshal& operator<<(Marshal& aDB, PBinary& obj) {
  aDB << obj.myFilename;
  aDB.write(obj.myBuffer, obj.mySize);
  return aDB;
}

Marshal& operator>>(Marshal& aDB, PBinary& obj) {
  aDB  >> obj.myFilename;
  delete obj.myBuffer;
  obj.myBuffer = NULL;
  aDB.read(obj.myBuffer, obj.mySize);
  return aDB;
}

RCString PBinary::getFilename() {
  return myFilename;
}

long PBinary::getSize() {
  return mySize;
}

char* PBinary::getBuffer() {
  return myBuffer;
}

int PBinary::loadFile(const RCString& filename) {
  std::fstream file;
  std::stringstream os;
  file.open(filename.chars(),std::ios::in);  
  // file.tie(0);
  // os.tie(0);
  file >> os.rdbuf(); // see ios(3C++) for rdbuf
  //  file.read(bla);
  file.close();
  mySize = os.str().size();
  myBuffer = const_cast<char*>(os.str().c_str());
  myFilename = filename;
  return 1;
}

int PBinary::saveFile() {
  std::fstream file;
  file.open(myFilename.chars(),std::ios::out);  
  file.write(myBuffer, mySize);
  file.close();
  return 1;
}

int PBinary::saveFileAs(const RCString& filename) {
  myFilename = filename;
  return saveFile();
}
  
RCString PBinary::getFiletype() {
  return myFiletype;
}

void PBinary::setFiletype(const RCString& filetype) {
  myFiletype = filetype;
}
