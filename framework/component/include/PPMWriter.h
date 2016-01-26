/*
 * $RCSfile: PPMWriter.h,v $
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: PPMWriter.h,v 1.5 1996/08/01 12:00:48 streit Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifndef _PPMWriter_H
#define _PPMWriter_H

#include "booga/component/Pixmap2DWriter.h"

//____________________________________________________________________ PPMWriter

class PPMWriter : public Pixmap2DWriter {
declareRTTI(PPMWriter);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  PPMWriter(const RCString& filename="", Type traversalType=FIRST);
  // PPMWriter(const PPMWriter&);          // Use default version.

public:
  // virtual ~PPMWriter();                 // Use default version.

private:
  PPMWriter& operator=(const PPMWriter&);  // No assignments.  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Pixmap2DWriter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  bool save(ofstream& ofs, const Pixmap2D* pixi) const;
};

#endif // _PPMWriter_H
