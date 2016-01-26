/*
 * Statistic.C 
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
 *  $Id: Statistic.C,v 1.6 1997/09/19 07:14:54 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifdef SVR4
#include <stream.h>
#endif
#include "booga/base/Report.h"
#include "booga/base/Configuration.h"
#include "booga/base/StreamOption.h"
#include "booga/base/Statistic.h"

//____________________________________________________________________ Statistic

SymTable<RCString, Value> Statistic::ourEntries(100);
ostream* Statistic::ourOutputStream;

Value Statistic::getEntry(const RCString& entryName)
{
  Value retval;

  if (!ourEntries.lookup(entryName, retval))
    Report::recoverable("[Statistic::getEntry] entry '" + entryName + "' not found");

  return retval;
}

void Statistic::setEntry(const RCString& entryName, const Value& value)
{
  // 
  // Entry already present?
  //
  if (ourEntries.find(entryName))
    ourEntries.findAndReplace(entryName, value);
  else
    ourEntries.insert(entryName, value);
}

void Statistic::addEntry(const RCString& entryName, const Value& value)
{
  // 
  // Entry already present?
  //
  Value curValue;
  if (!ourEntries.lookup(entryName, curValue))
    ourEntries.insert(entryName, value);  // New entry: insert it.
  else { 
    curValue += value;
    ourEntries.findAndReplace(entryName, curValue);
  }
}

void Statistic::removeEntry(const RCString& entryName)
{
  Value dummy;

  if (!ourEntries.findAndRemove(entryName, dummy))
    Report::recoverable("[Statistic::removeEntry] entry '" + entryName + "' not found");
}

void Statistic::removeEntries(const RCString& entryNames)
{
  List<RCString> foundEntries;
  searchForMatchingEntries(entryNames, foundEntries);

  for (long i=0; i<foundEntries.count(); i++)
    removeEntry(foundEntries.item(i));
}

void Statistic::print(const RCString& entryNames)
{
  Statistic::setOutputStream();

  List<RCString> foundEntries;
  searchForMatchingEntries(entryNames, foundEntries);

  if (foundEntries.count() <= 0)
    return;
    
  //
  // Sort (Bubble sort) the elements in the list.
  //
  RCString tmp;
  for (long i=foundEntries.count()-1; i>0; i--)
    for (long j=1; j<=i; j++)
      if (foundEntries.item(j-1) > foundEntries.item(j)) {
	tmp = foundEntries.item(j-1);
	foundEntries.item(j-1) = foundEntries.item(j);
	foundEntries.item(j) = tmp;
      }

  *ourOutputStream << "Statistics:\n"
		 << "----------------------------------------------------------\n\n";

  Value value;

  for (long j=0; j<foundEntries.count(); j++) {
    ourEntries.lookup(foundEntries.item(j), value);
    *ourOutputStream << form("%-30s: ", foundEntries.item(j).chars()) << value << endl;
  }
}

void Statistic::searchForMatchingEntries(const RCString& entryNames, 
				     List<RCString>& foundEntries)
{
  for (SymTableIterator<RCString, Value> itr(ourEntries); itr.more(); itr.next()) {
    //
    // Key in database has smaller length -> next entry.
    //
    if (entryNames.length() > itr.curKey().length())
      continue;

    //
    // Compare keys.
    //    
    int pos;
    for (pos = entryNames.length()-1; pos >=0; pos--) 
      if (entryNames[pos] != itr.curKey()[pos])
	break;

    //
    // Found matching entry -> append to the list.
    //
    if (pos < 0)
      foundEntries.append(itr.curKey());
  }
}

void Statistic::setOutputStream()
{
  getConfigurationOption(StreamOption, strOption, "Statistic.OutputStream");

  if (strOption != NULL)
    ourOutputStream = (ostream *)strOption->getStream();

  if (ourOutputStream == NULL)
    ourOutputStream = &cerr;
}
