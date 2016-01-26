/*
 * $RCSfile: Transaction.C,v $
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
 *  $Id: Transaction.C,v 1.2 1996/12/06 16:47:20 collison Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Report.h"
#include "DataBase.h"
#include "Transaction.h"


Stack<Transaction*> Transaction::ourTransactionStack;

AsciiMarshal Transaction::ourMarshal;

//_____________________________________________________________________ Transaction

Transaction::Transaction() :
myActive(false),
myLevel(0),
myBuffers(128)
{
}

Transaction::~Transaction() {
  if (myActive) abort();
}

void Transaction::begin() {
  //
  // prohibit multiple beginning of transaction
  //
  if (myActive) {
    Report::error("[Transaction::begin] Transcaction allready active");
  }
  myActive = true;
  myLevel = ourTransactionStack.count() + 1;

  //
  // buffer objects for possible abort
  //
  if (!isRootTransaction()) {
    buildBuffer();
  }

  ostrstream os;
  os << "[Transaction::begin] Transaction level " << myLevel << " started";
  Report::hint(os);
  ourTransactionStack.push(this);
}

void Transaction::commit() {
  //
  // prohibit illegel nesting of transactions
  //
  if (!myActive) {
    Report::error("[Transaction::commit] Transaction not active");
  }
  myActive = false;
  if (this != ourTransactionStack.pop()) {
    Report::error("[Transaction::commit] Transaction nesting missmatch");
  }

  int i;
  if (isRootTransaction()) {
    //
    // root transaction commited! save all changed objects
    //
    for (i=0; i<myChanged.count(); i++) {
      Persistent *p = myChanged.getElement(i);
      p->getDataBase().write(p); // write persistent to its database
      ostrstream ss;
      ss << "[Transaction::commit] wrote " << p->getPOId();
      Report::hint(ss);
    }
    unload();
  }
  else {
    //
    // keep track of loaded and changed objects in outer Transaction
    //
    Transaction* outer = ourTransactionStack.top();
    outer->myLoaded = outer->myLoaded.unionOp(myLoaded);
    outer->myChanged = outer->myChanged.unionOp(myChanged);

    //
    // remove transaction buffers;
    //
    removeBuffer();
  }
  ostrstream os;
  os << "[Transaction::commit] Transaction level " << myLevel << " commited";
  Report::hint(os);
}

void Transaction::abort() {
  if (!myActive) {
    Report::error("[Transaction::abort] Transaction not active");  
  }

  //
  // abort possible inner transactions
  //
  while (this != ourTransactionStack.top()) {
    ourTransactionStack.pop()->abort();
  }

  //
  // reproduce state of buffered objects
  //
  reset();
  
  //
  // remove objects from memory which have been loaded during transaction
  //
  unload();
  
  myActive = false;
  ourTransactionStack.pop();
  
  ostrstream os;
  os << "[Transaction::abort] Transaction level " << myLevel << " aborted";
  Report::hint(os);
}

void Transaction::checkpoint() {
  if (!myActive) {
    Report::error("[Transaction::abort] Transaction not active");  
  }
  if (this != ourTransactionStack.top()) {
    Report::error("[Transaction::checkpoint] Transaction nesting missmatch");
  }
  Report::error("[Transaction::checkpoint] not implemented yet");
}


void Transaction::unload() {
  for (int i=0; i<myLoaded.count(); i++) {
    ostrstream os;
    os << "[Transaction::unload] unloading " << myLoaded.getElement(i)->getPOId();
    Report::hint(os);
    delete myLoaded.getElement(i);
  }
}

void Transaction::buildBuffer() {
  // only buffer the obj's wich have changed in outer Transaction
  Transaction* outer = ourTransactionStack.top();
  for (int i=0; i < outer->myChanged.count(); i++) {
    Persistent* p = outer->myChanged.getElement(i);
    strstream* ss = new strstream();
    ourMarshal.marshal(p, *ss);   // flatten persistent obj
    myBuffers.insert(p, ss);      // buffer the flat representation
    myBuffered.insertElement(p);  // remember which obj's have been buffered
  }
}

void Transaction::removeBuffer() {
  for (int i=0; i<myBuffered.count(); i++) {
    Persistent *p = myBuffered.getElement(i);
    strstream *ss = NULL;
    myBuffers.findAndRemove(p, ss);
    delete ss;
  }
}

void Transaction::reset() {
  for (int i=0; i<myChanged.count(); i++) {
    Persistent *p = myChanged.getElement(i);
    strstream *ss = NULL;
    bool done = false;
    Stack<Transaction*> tempStack;
    do {
      if (ourTransactionStack.count() > 0) {
        tempStack.push(ourTransactionStack.pop());
        if (tempStack.top()->myBuffers.lookup(p, ss)) {
          ourMarshal.unmarshal(p, *ss); // Warning ss needs a reset or so! or copy from ss
          done = true;
          ostrstream os;
          os << "[Transaction::reset] restored " << p->getPOId();
          Report::hint(os);
        }
      }
    } while (!done);
    // rebuild transaction stack
    while (tempStack.count() > 0) ourTransactionStack.push(tempStack.pop());
  }
}

int Transaction::isRootTransaction() {
  return (myLevel == 1);
}

Transaction* Transaction::getCurrentTransaction() {
  if (ourTransactionStack.count() == 0) return NULL;
  return ourTransactionStack.top();
}

int Transaction::getTransactionLevel() {
  return ourTransactionStack.count() + 1;
}

void Transaction::changed(Persistent* p) {
  ourTransactionStack.top()->myChanged.insertElement(p);
}

void Transaction::loaded(Persistent* p) {
  ourTransactionStack.top()->myLoaded.insertElement(p);
  ostrstream os;
  os << "[Transaction::loaded] loaded " << p->getPOId();
  Report::hint(os);
}
