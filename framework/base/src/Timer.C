/*
 * Timer.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
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
 * ---------------------------------------------------------------------
 *  $Id: Timer.C,v 1.6 1998/04/29 12:07:06 buhlmann Exp $
 * ---------------------------------------------------------------------
 */
 
#ifdef SVR4
#include <unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/param.h>
#elif WIN32
#include <time.h>
#include <windows.h>  // mmsystem.h cannot exist without this.
#include <mmsystem.h> // timeGetTime()
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif
#ifdef WIN32
#include <iostream.h>
#elif SVR4
#include <stream.h>
#endif

#include "booga/base/Timer.h"
#include "booga/base/Report.h"

//_________________________________________________________________ TimerRep

TimeRep::TimeRep()
: myRealTime(0.0), myUserTime(0.0), mySysTime(0.0)
{}

TimeRep::TimeRep(double realTime, double userTime, double sysTime)
: myRealTime(realTime), myUserTime(userTime), mySysTime(sysTime)
{}

TimeRep TimeRep::operator+(const TimeRep& time) const
{
  return TimeRep(myRealTime + time.myRealTime,
                 myUserTime + time.myUserTime,
                 mySysTime  + time.mySysTime);
}

TimeRep TimeRep::operator-(const TimeRep& time) const
{
  return TimeRep(myRealTime - time.myRealTime,
                 myUserTime - time.myUserTime,
                 mySysTime  - time.mySysTime);
}

ostream& operator<<(ostream& os, const TimeRep& time)
{
  os << form("%.2f", time.myRealTime) << " real, "
     << form("%.2f", time.myUserTime) << " user, " 
     << form("%.2f", time.mySysTime)  << " sys"; 

  return os;
}

void TimeRep::setTimes(double realTime, double userTime, double sysTime)
{
  myRealTime = realTime;
  myUserTime = userTime;
  mySysTime  = sysTime;
}

//_________________________________________________________________ Timer

Timer::Timer()
: myRunningFlag(0)
{
  reset();
}

void Timer::start()
{
  if (myRunningFlag) {
    Report::warning("[Timer::start] Timer is already running");
    return;
  }

  myRunningFlag = 1;
  myStartTime   = getCurrentTime();
  myLastLapTime = myStartTime;
  myLapTime.setTimes();
}

void Timer::stop()
{
  if (!myRunningFlag) {
    Report::warning("[Timer::stop] Timer is not running");
    return;
  }

  myTotalTime = myTotalTime + (getCurrentTime() - myStartTime);
  myRunningFlag = 0;
}

void Timer::lap()
{
  if (!myRunningFlag) {
    Report::warning("[Timer::lap] Timer is not running");
    return;
  }

  myLapTime = getCurrentTime() - myLastLapTime;
  myLastLapTime = getCurrentTime();
}
 
void Timer::reset()
{
  myRunningFlag = 0;

  myStartTime.setTimes();
  myTotalTime.setTimes(); 
  myLastLapTime.setTimes();
  myLapTime.setTimes();   
}

TimeRep Timer::getTime() const
{
  if (myRunningFlag) {
    return myTotalTime + (getCurrentTime() - myStartTime);
  }
  else
    return myTotalTime;
}

TimeRep Timer::getLapTime() const
{
  if (!myRunningFlag) {
    Report::warning("[Timer::getLapTime] Timer is not running");
    return TimeRep();
  }

  return myLapTime;
}
 
TimeRep Timer::getCurrentTime() const
{
  double realTime, userTime, sysTime;

#ifdef SVR4
  struct timeval tv;

  gettimeofday(&tv, NULL);
  realTime = (double)tv.tv_sec + (double)tv.tv_usec/1000000.;

  struct tms time;

  times(&time);
  userTime = (double)time.tms_utime/(double)HZ;
  sysTime  = (double)time.tms_stime/(double)HZ;  

#elif WIN32
  userTime = clock() / 1000.0; // don't know how to measure user time and sys time
//  userTime = 0; // don't know how to measure user time and sys time
  sysTime  = 0; // this is not a unix system. 
  realTime = (double)timeGetTime() / 1000.0;
#else
  struct timeval tv;

  gettimeofday(&tv, NULL);
  realTime = (double)tv.tv_sec + (double)tv.tv_usec/1000000.;

  struct rusage usage;

  getrusage(RUSAGE_SELF, &usage);
  userTime = (double) usage.ru_utime.tv_sec +
             (double) usage.ru_utime.tv_usec / 1000000.;
  sysTime  = (double) usage.ru_stime.tv_sec +
             (double) usage.ru_stime.tv_usec / 1000000.;

#endif
 
  return TimeRep(realTime, userTime, sysTime);
}
