/*
 * $RCSfile: MFile.h,v $
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
 *  $Id: MFile.h,v 1.6 1996/09/13 08:04:55 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _MFile_H
#define _MFile_H

#include "booga/base/RCString.h"

//_____________________________________________________________________ MFile

template <class TObject, class TProxy, class TFile,
          class TAggregate, class TWorld, class TParser>
class MFile : public TProxy {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // MFile();                         // Use default version.
  MFile(const RCString& name);
  MFile(Exemplar);
  // MFile(const MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>&);
  // Use default version.

public:
  // virtual ~MFile();                // Use default version.

private:
  MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>& 
    operator=(const MFile<TObject, TProxy, TFile, TAggregate, TWorld, TParser>&);    
  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class MFile<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  void setFilename(const RCString& name);
  RCString getFilename() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TProxy
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual TObject* createSubject() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class TObject
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual TObject* copy() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
 virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  RCString myFilename;
};

/*
 * GNU compiler has a pretty bad handling of templates...
 */
#ifdef TEMPLATE_IN_HEADER
#define TEMPLATE_IS_INCLUDE_FROM_H
#include "../component/src/MFile.C"
#endif // TEMPLATE_IN_HEADER

#endif // _MFile_H

