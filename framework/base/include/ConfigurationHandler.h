/*
 * ConfigurationHandler.h
 *
 * Copyright (C) 1995, Stephan Amann <amann@iam.unibe.ch>
 *                     Christoph Streit <streit@iam.unibe.ch>
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: ConfigurationHandler.h,v 1.2 1995/04/21 12:32:03 amann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _ConfigurationHandler_H
#define _ConfigurationHandler_H

#include "booga/base/Configuration.h"
#include "booga/base/Name.h"

class Option;

class ConfigurationHandler {
public:
  virtual Option* handleOption(const Name& name, const Name& option) = 0;
};

#endif // _ConfigurationHandler_H
