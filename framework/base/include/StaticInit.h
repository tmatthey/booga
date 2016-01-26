/*
 * StaticInit.h 
 *
 * Provide macros to ensure initialization of static data.
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
 *  $Id: StaticInit.h,v 1.9 1995/09/28 13:09:53 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _StaticInit_H
# define _StaticInit_H

//_______________________________________________________ Handling of Exemplars

#define declareInitExemplar(className)         \
class className##Init {                        \
public:                                        \
  className##Init();                           \
  ~##className##Init();                        \
private:                                       \
  static int ourInitCount;                     \
  static className##* ourExemplar;             \
};                                             \
static className##Init the##className##Init

#define useInitExemplar(className)             \
friend class className##Init

#define implementInitExemplar(className)       \
int className##Init::ourInitCount;             \
className##* className##Init::ourExemplar;     \
className##Init::className##Init()             \
{                                              \
  if (ourInitCount++ == 0)                     \
    ourExemplar = new className##(anExemplar); \
}                                              \
className##Init::~##className##Init()          \
{                                              \
  if (--ourInitCount == 0)                     \
    delete ourExemplar;                        \
}

//___________________________________________________________________ Init Class


//_________________________________________________________________ Init Statics

#define declareInitStatics(className)          \
class className##Init {                        \
public:                                        \
  className##Init();                           \
  ~##className##Init();                        \
private:                                       \
  static int ourInitCount;                     \
};                                             \
static className##Init the##className##Init

#define implementInitStatics(className)        \
int className##Init::ourInitCount;             \
className##Init::className##Init()             \
{                                              \
  if (ourInitCount++ == 0)                     \
    className##::initClass();                  \
}                                              \
className##Init::~##className##Init()          \
{                                              \
  if (--ourInitCount == 0) {                   \
    /* T::exitClass() */                       \
  }                                            \
}

//___________________________________________________ Template version 



#endif // _StaticInit_H
