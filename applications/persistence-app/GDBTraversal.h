/*
 * $RCSfile: GDBTraversal.h,v $
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
 *  $Id: GDBTraversal.h,v 1.3 1996/12/06 16:44:38 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GDBTraversal_H
#define _GDBTraversal_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/SymTable.h"
#include "booga/base/RCString.h"


class GDBData;
class GDBOperation;

//_____________________________________________________________________ GDBTraversal

class GDBTraversal {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local types/enums
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  enum Result { 
    CONTINUE,  // Continue with traversal process, everything is OK.
    UNKNOWN,   // Unknown object visited -> try to transform it
    PRUNE,     // Stop traversal of current branch of the object hierarchie.
    EXIT       // Cleanup on exit the traversal process.
  };

  enum TraverseRelation {
    NONE=0,
    PARTS,
    PARTOF
//    NEXTVERSIONS,
//    PREVIOUSVERSION,
//    ICON,
//    TARGETS,
//    SOURCE
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GDBTraversal();
  ~GDBTraversal();
private:
  GDBTraversal(const GDBTraversal&);             // No copies.

public:
  // virtual ~GDBTraversal();                // Use default version.

private:
  GDBTraversal& operator=(const GDBTraversal&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GDBTraversal
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
bool traverse(GDBData *object);
bool doTraverse(GDBData *object);

void setPreorder() { myPreorder = true; }
void setPostorder() { myPreorder = false; }
void setMultiVisit() { myMultiVisit = true; }
void setSingleVisit() { myMultiVisit = false; }
void setTraverseRelation(TraverseRelation relation) { myTraverseRelation = relation; }
void setOperation(GDBOperation* anOp) { myOperation = anOp; }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TraverseRelation myTraverseRelation;
  bool myPreorder;
  bool myMultiVisit;     // false if objects should not be revisited
  SymTable<RCString, int> myVisited;
  GDBOperation* myOperation;
};

//______________________________________________________________________ INLINES

#endif // _GDBTraversal_H

