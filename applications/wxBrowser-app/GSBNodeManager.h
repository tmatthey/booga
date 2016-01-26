/*
 * GSBNodeManager.h
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBNodeManager.h,v 1.4 1997/04/08 11:04:53 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBNodeManager_H
#define _GSBNodeManager_H

#include "booga/base/Option.h"
#include "GSBNode.h"


//_____________________________________________________________________ GSBNodeManager

class GSBNodeManager : public Option {
declareRTTI(GSBNodeManager);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBNodeManager();
  
private:
  GSBNodeManager(const GSBNodeManager&);

public:
  virtual ~GSBNodeManager(); 

private:
  GSBNodeManager& operator=(const GSBNodeManager&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBNodeManager
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  int		attachNode(GSBNode* aNode);
  void		detachNode(long viewID);
  GSBNode*	getNode(long viewID) const;
  
  void		setMarked(bool newFlag) { myMarkedFlag = newFlag; };
  bool		isMarked() const { return myMarkedFlag; };

  void		setPruned(bool pruning) { myPrunedFlag = pruning; };
  bool		isPruned() const {return myPrunedFlag; };
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Option
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Option* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  List<GSBNode*>	myNodes;
  bool				myMarkedFlag;
  bool				myPrunedFlag;
};

//______________________________________________________________________ INLINES

#endif // _GSBNodeManager_H

