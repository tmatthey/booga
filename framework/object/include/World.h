/*
 * $RCSfile: World.h,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
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
 *  $Id: World.h,v 1.3 1996/08/01 12:01:45 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _World_H
# define _World_H

#include "booga/object/Makeable.h"

//________________________________________________________________________ World

class World : public Makeable {
  declareRTTI(World);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // World();
  // World(const World&);          // Use default version.

public:
  // virtual ~World();             // Use default version.

private:
  World& operator=(const World&);  // No assignments.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class World
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual World* copy() const = 0;
  // Make a copy of the world.
  
  virtual bool isEmpty() const = 0;
  // Returns true if the world is empty, false otherwise.
};

#endif // _World_H
