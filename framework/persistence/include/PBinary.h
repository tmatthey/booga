/*
 * $RCSfile: PBinary.h,v $
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
 *  $Id: PBinary.h,v 1.2 1996/12/18 10:25:32 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _PBinary_H
#define _PBinary_H

#include "booga/base/RCString.h"
#include "booga/persistence/Persistent.h"

class Marshal;

//_____________________________________________________________________ PBinary

class PBinary : public Persistent {
  declareRTTI(PBinary);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PBinary(DataBase& aDB);
  PBinary(Prototype& aPrototype);
private:
  PBinary(const PBinary&);             // No copies.

public:
  virtual ~PBinary();                

private:
  PBinary& operator=(const PBinary&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class PBinary
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  RCString getFilename();
  RCString getFiletype();
  void setFiletype(const RCString& filetype);
  long getSize();
  char* getBuffer();
  int loadFile(const RCString& filename);
  int saveFile();
  int saveFileAs(const RCString& filename);
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Persistent
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Persistent* newInstance();
  virtual int destroy();  // destroyes persistent object in database

  virtual void marshal(Marshal* aMarshal);
  virtual void unmarshal(Marshal* aMarshal);

  friend Marshal& operator<<(Marshal& aDB, PBinary& obj);
  friend Marshal& operator>>(Marshal& aDB, PBinary& obj);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFilename;
  RCString myFiletype;
  long mySize;
  char *myBuffer;
};

//______________________________________________________________________ INLINES

#endif // _PBinary_H

