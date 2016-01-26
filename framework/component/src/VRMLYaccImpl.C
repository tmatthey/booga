/*
 * $RCSfile: VRMLYaccImpl.C,v $ 
 *
 * Copyright (C) 1996, Beat Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRMLYaccImpl.C,v 1.2 1996/08/01 12:01:39 streit Exp $
 * -----------------------------------------------------------------------------
 */

#include "VRMLLex.h"
#include "VRMLYacc.h"

//_______________________________________________________________ VRMLYacc

void VRMLYacc::begDef(const RCString& key)
{
  VRMLList *vrmlList;

  myDefList.append(key);
  if (mySymTable.lookup(key, vrmlList))
    vrmlList->reset();
  else
  {
    vrmlList = new VRMLList;
    mySymTable.insert(key,vrmlList);
  }    
}

void VRMLYacc::endDef(const RCString& key)
{
  for (long i = 0; i < myDefList.count(); i++)
    if (myDefList.item(i) == key)
      myDefList.remove(i);
}

void VRMLYacc::objDef(VRMLObject& vrmlObject)
{
  VRMLList *vrmlList;

  for (long i = 0; i < myDefList.count(); i++)  
    if (mySymTable.lookup(myDefList.item(i), vrmlList))
      vrmlList->add(vrmlObject);  
}

void VRMLYacc::useDef(const RCString& key)
{
  VRMLList *vrmlList;

  if (mySymTable.lookup(key, vrmlList))
  {
    objDef(*vrmlList);
    vrmlList->apply(myStateStack);
  }
}
