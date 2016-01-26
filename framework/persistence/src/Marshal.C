/*
 * $RCSfile: Marshal.C,v $
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
 *  $Id: Marshal.C,v 1.2 1996/12/23 10:58:03 collison Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/persistence/Marshal.h"
#include "booga/persistence/Persistent.h"

//_____________________________________________________________________ Marshal

Marshal::Marshal() {
}

Marshal::~Marshal() {
}

void Marshal::marshal(Persistent* p, ostream& os) {
  myOs = &os;
  p->marshal(this);
  myOs = NULL; // rather have core dumps than writing to wrong objects;
}

void Marshal::unmarshal(Persistent* p, istream& is) {
  myIs = &is;
  p->unmarshal(this);
  myIs = NULL; // rather have core dumps than reading from wrong objects;
}

void Marshal::useInputStream(istream& is) {
  myIs = &is;
}

void Marshal::useOutputStream(ostream& os) {
  myOs = &os;
}
