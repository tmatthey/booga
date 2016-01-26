/*
 * PPMReader.C
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
 *  $Id: PPMReader.C,v 1.2 1997/09/19 07:14:31 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <string.h>
#ifdef SVR4
#include <unistd.h>
#endif
#include <stdio.h>          // FILE, fseek, ...

#include "booga/pixmapOp/PPMReader.h"
   
//_____________________________________________________________________PPMReader

implementInitExemplar(PPMReader);

PPMReader::PPMReader(Exemplar anExemplar)
: ImageReader(anExemplar) 
{}

AbstractPixmap* PPMReader::read(const AbstractFile& ifs)
{
  FileSTDIn fs(ifs);
  if (fs.bad()) {
    Report::warning("PPMReader:can't open file");
    return NULL;
  }
  return read(fs);
}

AbstractPixmap* PPMReader::read(std::istream& ifs)
{

  char aChar;
  char line[256];
  line[0] = '1';
  line [1] = '\0';

  //
  // Check for correct PPM Header
  //
  ifs.getline(line,255);
  if (strncmp(line, "P6", 2)){
    return NULL;
  }  
  readComment(ifs);		// read over comment

  int resX, resY, maxVal;
  ifs >> resX;
  readComment(ifs);		// read over comment
  ifs >> resY;
  readComment(ifs);		// read over comment
  ifs >> maxVal;
  readComment(ifs);		// read over comment

  ifs.get(aChar);		         // read last EOL

  if (ifs.bad()) {
    Report::warning("[PPMReader::read] An error occured while reading a PPM file");
    return NULL;
  }

  AbstractPixmap* pm = MPixmapExemplar::createPixmap(resX, resY);
  float rangeMin = pm->getRangeMin();
  float rangeMax = pm->getRangeMax();
  
  unsigned char* ppmPicture = new unsigned char[3*resX*resY];
  ifs.read(reinterpret_cast<char*>(ppmPicture), 3*resX*resY*sizeof(unsigned char));
  
  long pos; 
  float factor;
  for (int x, y=resY-1; y>=0; y--)
    for (x=0; x<resX; x++) {
      pm->setPosition(x, y);
      pos = (resY-1-y)*resX+x;
      factor = (rangeMax-rangeMin)/(float)maxVal;
      pm->setColor((factor*(float)(ppmPicture[3*pos]))+rangeMin,
                   (factor*(float)(ppmPicture[3*pos+1]))+rangeMin,
                   (factor*(float)(ppmPicture[3*pos+2]))+rangeMin);
    }
  delete ppmPicture;
  
  if (ifs.bad()) {
    Report::warning("[PPMReader::read] an error occured while reading a PPM file");
    delete pm;
    return NULL;
  }

  return pm;
} 

void PPMReader::readComment(std::istream& ifs) const
{
  char aChar, line[256];
  ifs.get(aChar);		// read over comment
  while (aChar == '#') {
    ifs.getline(line, 255);
    ifs.get(aChar);
  }
  ifs.putback(aChar);
}



