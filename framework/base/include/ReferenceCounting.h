/*
 * ReferenceCounting.h
 *
 * Base classes for reference counting. 
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
 * -----------------------------------------------------------------------------
 *  $Id: ReferenceCounting.h,v 1.2 1995/04/21 12:35:06 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ReferenceCounting_H
# define _ReferenceCounting_H

//_____________________________________________________________________ RCLetter

class RCLetter {
friend class RCEnvelope;

protected:
  RCLetter();
  virtual ~RCLetter();
  
  virtual RCLetter* rcCopy() const = 0;
  // Every derived class has to provide a copy method to create 
  // a copy of itself (see the RCEnvelope::rcMakeUnique method 
  // as an example for its use).
  void ref();
  int deref();

protected:
  int myRefCount;
};

inline RCLetter::RCLetter()
{
  myRefCount = 1;
}

inline void RCLetter::ref()
{
  ++myRefCount;
}

inline int RCLetter::deref()
{
  return --myRefCount;
}

//___________________________________________________________________ RCEnvelope

class RCEnvelope {
public:
  RCEnvelope(const RCEnvelope& envelope);
  virtual ~RCEnvelope();

  int rcIsShared() const;
  // Returns 1, if the letter of the envelope is not shared by others,
  //         0, otherwise.
  int rcCountReferences() const;
  // Returns the number of references, i.e. how many times is this 
  // letter shared.

protected:
  RCEnvelope(RCLetter* letter);
  void rcMakeUnique();
  // Ensures that the envelope owns a unique copy of the letter.
  void rcAssign(const RCEnvelope& envelope);
  // The assignment operator in a derived has to call the rcAssing 
  // method in order to handle reference counting.
  void rcRef();
  // Increment the ref count of the letter.
  void rcDeref();
  // Decrement the ref count of the letter, 
  // remove the letter if ref count == 0.

protected:
  RCLetter* myLetter;
};

inline RCEnvelope::RCEnvelope(RCLetter* letter)
{
  myLetter = letter;
}

inline void RCEnvelope::rcMakeUnique()
{
  if (myLetter->myRefCount > 1) {
    myLetter->deref();
    myLetter = myLetter->rcCopy();
  }
}

inline RCEnvelope::RCEnvelope(const RCEnvelope& envelope)
{
  myLetter = envelope.myLetter;
  myLetter->ref();
}

inline void RCEnvelope::rcRef()
{
  myLetter->ref();
}

inline void RCEnvelope::rcDeref()
{
  if (myLetter->deref() <= 0)
    delete myLetter;
}

inline int RCEnvelope::rcIsShared() const
{
  return (myLetter->myRefCount > 1);
}

inline int RCEnvelope::rcCountReferences() const
{
  return myLetter->myRefCount;
}

#endif // _ReferenceCounting_H
