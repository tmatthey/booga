/*
 * $RCSfile: POId.h
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
 *  $Id: POId.h,v 1.10 1996/12/06 16:46:46 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _POId_H
#define _POId_H

typedef unsigned long PDBId ;
typedef unsigned long PObjectId ;

#define PDBID_NULL 0
#define POBJECTID_NULL 0

#include <ostream>
class Marshal;
//_____________________________________________________________________ POId

class POId {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  POId();
  POId(PDBId, PObjectId);
  POId(const POId&);
  // virtual ~POId(); use default version
  POId& operator=(const POId&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class POId
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
  PDBId getPDBId() const;
  PObjectId getPObjectId() const;

  int operator==(const POId& anId) const;
  int operator!=(const POId& anId) const;
  int operator<(const POId& anId) const;

  friend Marshal& operator<<(Marshal& m, const POId& id);
  friend Marshal& operator>>(Marshal& m, POId& id);

  friend std::ostream& operator<<(std::ostream& out, const POId& anId);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  PDBId myPDBId;
  PObjectId myPObjectId;
};

//______________________________________________________________________ INLINES

//
// to be used with class SymTable
//
inline unsigned long _keyToHash(const POId& id) {
  return (unsigned long) 9029*id.getPDBId()+id.getPObjectId();
}

extern const POId POID_NULL;
#endif // _POId_H

