/*
 * $RCSfile: Transaction.h,v $
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
 *  $Id: Transaction.h,v 1.1 1996/12/11 13:59:41 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Transaction_H
#define _Transaction_H

#include <strstream.h>
#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Stack.h"
#include "booga/base/SymTable.h"
#include "booga/persistence/AsciiMarshal.h"
#include "booga/persistence/Set.h"

//_____________________________________________________________________ Transaction

class Transaction {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Transaction();                         // Use default version.
  ~Transaction();

private:
  Transaction(const Transaction&);             // No copies.

public:
  // virtual ~Transaction();                // Use default version.

private:
  Transaction& operator=(const Transaction&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Transaction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void begin();
  void commit();
  void abort();
  void checkpoint();

  static void changed(Persistent* p); // inform the current Transaction about object change
  static void loaded(Persistent* p);  // inform the current Transaction about newly load

  static Transaction* getCurrentTransaction();
  static int getTransactionLevel();

private:
  void unload();
  void buildBuffer();
  void removeBuffer();
  void reset();
  int isRootTransaction();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  static Stack<Transaction*> ourTransactionStack; // Stack of active Transactions
  static AsciiMarshal ourMarshal;
  
  bool myActive;
  int myLevel;
  Set<Persistent*> myLoaded; // loaded during current Transaction
  Set<Persistent*> myChanged; // changed during current Transaction
  Set<Persistent*> myBuffered; // objects beeing buffered for abort();
  SymTable<Persistent*,strstream*> myBuffers;
};

//______________________________________________________________________ INLINES

#endif // _Transaction_H

