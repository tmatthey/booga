/*
 * StatisticUtilities.h
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: StatisticUtilities.h,v 1.1 1995/10/06 14:09:35 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _StatisticUtilities_H
#define _StatisticUtilities_H

#include "booga/base/Timer.h"
#include "booga/base/Statistic.h"

#define setExecTime(cmd,string) \
{ \
  Timer time; \
  time.start(); \
  cmd; \
  time.stop(); \
  Value result(time.getTime().getProcessTime()); \
  Statistic::setEntry(string, result); \
}

#define addExecTime(cmd,string) \
{ \
  Timer time; \
  time.start(); \
  cmd; \
  time.stop(); \
  Value result(time.getTime().getProcessTime()); \
  Statistic::addEntry(string, result); \
}

#endif // _StatisticUtilities_H

