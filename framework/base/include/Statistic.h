/*
 * Statistic.h
 *
 * Copyright (C) 1995, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Statistic.h,v 1.3 1995/10/06 14:08:13 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Statistic_H
# define _Statistic_H

#include "booga/base/SymTable.h"
#include "booga/base/List.h"
#include "booga/base/Value.h"

class ostream;

//____________________________________________________________________ Statistic

class Statistic {
public:
  // Statistic(const Statistic&);             // Use default version.     
  // ~Statistic();                            // Use default version.
  // Statistic& operator=(const Statistic&);  // Use default version.  

  static Value getEntry(const RCString& entryName);
  static void setEntry(const RCString& entryName, const Value& value);
  static void addEntry(const RCString& entryName, const Value& value);

  static void removeEntry(const RCString& entryName);
  static void removeEntries(const RCString& entryNames);

  static void print(const RCString& entryNames = "");
  
private:
  static void searchForMatchingEntries(const RCString& entryNames, 
				   List<RCString>& foundEntries);
  static void setOutputStream();

private:
  static SymTable<RCString, Value> ourEntries;
  static ostream* ourOutputStream;

private:
  Statistic();  // Make constructor private -> no instance may be created.
};

#endif // _Statistic_H

