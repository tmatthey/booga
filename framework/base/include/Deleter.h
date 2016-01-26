/*
 * Deleter.h
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Deleter.h,v 1.5 1997/09/19 07:35:20 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Deleter_H
#define _Deleter_H

//_____________________________________________________________________ Deleter

template <class TLetter>
class Deleter {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Deleter(TLetter* letter);
  // Deleter();                         // No default constructor.
  
private:
  Deleter(const Deleter<TLetter>&);              // No copies.

public:
  ~Deleter();

private:
  Deleter<TLetter>& operator=(const Deleter<TLetter>&);   // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Deleter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  TLetter* operator->();
  operator TLetter&();
  
private:
  // void* operator new(size_t);           // No dynamic construction.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  TLetter* myLetter;
};

//______________________________________________________________________ INLINES

template <class TLetter>
inline Deleter<TLetter>::Deleter(TLetter* letter)
{
  myLetter = letter;
}

template <class TLetter>
inline Deleter<TLetter>::~Deleter()
{
  delete myLetter;
}

template <class TLetter>
inline TLetter* Deleter<TLetter>::operator->()
{
  return myLetter;
}

template <class TLetter>
inline Deleter<TLetter>::operator TLetter&()
{ 
  return *myLetter;
}

#endif // _Deleter_H

