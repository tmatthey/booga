/*
 * Timer.h 
 *
 * Time your algorithms!
 *
 * 0     5     10    15    20    25    30    35    40    45    50 seconds
 * |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
 *       ^        ^        ^           ^                      ^
 *       |        |        |           |                      |
 * |<--------------------------->|     |     |<--------->|    |
 * start |        |        |   stop    |     start     stop   |      
 *       |        |        |           |                      |
 *       | getTime()=>12s  |    getTime()=>25s         getTime()=>35s
 *       |                 |
 *       |                 |
 *     lap();            lap();
 * getLapTime()=>5s  getLapTime()=>15s
 *
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
 *  $Id: Timer.h,v 1.6 1995/10/06 14:06:28 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Timer_H
#define  _Timer_H

class ostream;

//_____________________________________________________________________ TimerRep

class TimeRep {
friend class Timer;
public:
  TimeRep();
  // TimeRep(const TimeRep&);             // Use default version.
  TimeRep(double realTime, double userTime, double sysTime);
  // ~TimeRep();                          // Use default version.
  // TimeRep& operator=(const TimeRep&);  // Use default version.

  double getRealTime() const;
  double getUserTime() const;
  double getSysTime() const;
  double getProcessTime() const; // User & Sys

  TimeRep operator+(const TimeRep& time) const;
  TimeRep operator-(const TimeRep& time) const;

  friend ostream& operator<<(ostream& os, const TimeRep& time);

private:
  double myRealTime;
  double myUserTime;
  double mySysTime;

private:
  void setTimes(double realTime = 0.0,
                double userTime = 0.0, 
                double sysTime  = 0.0);
};

//______________________________________________________________ INLINE TimerRep

inline double TimeRep::getRealTime() const 
{ 
  return myRealTime; 
}

inline double TimeRep::getUserTime() const 
{ 
  return myUserTime; 
}

inline double TimeRep::getSysTime() const 
{ 
  return mySysTime;  
}

inline double TimeRep::getProcessTime() const
{
  return myUserTime + mySysTime;
}

//________________________________________________________________________ Timer

class Timer {
public:
  Timer();
  // Time(const Time&);             // Use default version.
  // ~Time();                       // Use default version.
  // Time& operator=(const Time&);  // Use default version.

  void start();
  void stop();
  void lap();
  void reset();

  TimeRep getTime() const;
  TimeRep getLapTime() const;
       
private:
  int myRunningFlag;
  TimeRep myStartTime;
  TimeRep myTotalTime;
  TimeRep myLastLapTime;
  TimeRep myLapTime;

private:
  TimeRep getCurrentTime() const;
};

#endif // _Timer_H
