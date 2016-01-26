/*
 * GSBNodeTools.h
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
 *  $Id: GSBNodeTools.h,v 1.6 1997/04/08 11:04:56 habegger Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _GSBNodeTools_H
#define _GSBNodeTools_H

#include "booga/object/Object3D.h"
#include "booga/component/Operation3D.h"

#include "GSBNodeManager.h"

//_____________________________________________________________________ GSBNodeTools

class GSBNodeTools : public Operation3D {
declareRTTI(GSBNodeTools);
// enable RTTI support

public:
  enum ActionType {
        INSTALL_MANAGERS = 0,
	INSTALL_NODES, 
	REMOVE_NODES,
	REMOVE_ALL = 9
  };


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  GSBNodeTools();
  GSBNodeTools(long viewID);
private:
  GSBNodeTools(const GSBNodeTools&);             // No copies.

public:
  virtual ~GSBNodeTools();              

private:
  GSBNodeTools& operator=(const GSBNodeTools&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class GSBNodeTools
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  int  attachNode(Object3D* obj, GSBNode* theNode);
  void detachNode(Object3D* obj, long viewID);

  GSBNodeManager* attachNodeManager(Object3D* obj);

  static GSBNodeManager* hasNodeManager(const Object3D* obj);
  static GSBNodeManager* getNodeManager(const Object3D* obj);

  static GSBNode* getNode(Object3D* obj, long viewID);
  static GSBNode* findNode(Object3D* obj, long viewID);

  void	     setActionType(ActionType toDo) { myToDo = toDo; };
  ActionType getActionType() const { return myToDo; };

  void setViewID(long viewID) { myViewID = viewID; };

  void adoptNodePrototype(GSBNode* nodeProto);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Operation3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Visitor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  virtual Traversal::Result dispatch(Makeable* obj);

private:
  Traversal::Result visit(Object3D* obj);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  long		myViewID;
  GSBNode*	myNodePrototype;
  ActionType	myToDo;
};

//______________________________________________________________________ INLINES

inline
GSBNodeTools::GSBNodeTools(long viewID)
: myViewID(viewID), 
  myNodePrototype(NULL), 
  myToDo(INSTALL_NODES)
{}


inline
GSBNodeTools::GSBNodeTools()
: myViewID(-1),
  myNodePrototype(NULL),
  myToDo(INSTALL_MANAGERS)
{}


inline
GSBNodeTools::~GSBNodeTools()
{
  delete myNodePrototype;
}


inline
void GSBNodeTools::adoptNodePrototype(GSBNode* nodeProto)
{
  delete myNodePrototype;
  myNodePrototype = nodeProto;
}


inline
void GSBNodeTools::detachNode(Object3D* obj, long viewID)
{
  getNodeManager(obj)->detachNode(viewID);
}

#endif // _GSBNodeTools_H
