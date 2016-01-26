/*
 * $RCSfile: PPMWriter.C,v $
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
 *  $Id: PPMWriter.C,v 1.12 1997/09/19 07:14:32 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#include <fstream>

#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PPMWriter.h"

//____________________________________________________________________ PPMWriter

implementRTTI(PPMWriter, Pixmap2DWriter);

PPMWriter::PPMWriter(const RCString& filename, Type traversalType)
: Pixmap2DWriter(filename, traversalType) 
{}

bool PPMWriter::save(const AbstractFile& ofs, const Pixmap2D* pixi) const 
{
  FileSTDOut fs(ofs);
  if (fs.bad()) {
    Report::warning("PPMWriter:can't open file\n");
    return false;
  }
  return save(fs,pixi);
}

bool PPMWriter::save(std::ostream& ofs, const Pixmap2D* pixi) const 
{
  const AbstractPixmap* pm = pixi->getPixmap();
  int resX = pm->getResolutionX();
  int resY = pm->getResolutionY();
  
  // 
  // Write out header information for ppm file
  //
  ofs << "P6" << std::endl;
  ofs << resX << " " << resY << std::endl;
  ofs << "255" << std::endl;

  bool didCut;
  unsigned char* ppmPicture = PixmapUtilities::createPPMPicture(didCut, pm);

#ifdef WIN32
  ofs.rdbuf().setmode( filebuf::binary ); // set to binary, else 10 will become 13-10
#endif  

  ofs.write(reinterpret_cast<char*>(ppmPicture), 3*resX*resY*sizeof(unsigned char));
  delete[] ppmPicture;
  
  if (didCut)
    Report::warning("[PPMWriter::save] Pixel values adapted to range");

  if (ofs.bad()) {
    Report::warning("[PPMWriter::save] something went wrong writing .ppm file");
    return false;
  }
  
  return true;
}
