/*
 * $RCSfile: PNGWriter.C,v $
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
 *  $Id: PNGWriter.C,v 1.12 1997/09/19 07:14:32 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#ifdef HAVE_PNG
#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#endif

#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PNGWriter.h"

//____________________________________________________________________ PNGWriter

implementRTTI(PNGWriter, Pixmap2DWriter);

PNGWriter::PNGWriter(const RCString& filename, Type traversalType)
  : Pixmap2DWriter(filename, traversalType) 
{}

bool PNGWriter::save(const AbstractFile& ofs, const Pixmap2D* pixi) const 
{
  FileFD fs(ofs,"wb");
  if (fs.bad()) {
    Report::warning("PNGWriter:can't open file\n");
    return false;
  }
  return save(fs,pixi);
}

bool PNGWriter::save(FILE* outfile, const Pixmap2D* pixi) const 
{
#ifdef HAVE_PNG



  // Create and initialize the png_struct with the default error handlers 
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL) {
    Report::warning("[PNGWriter::save] Could not initialize PNG library.");
    return false; 
  }
 
  // Allocate/initialize the memory for image information.  REQUIRED.
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    Report::warning("[PNGWriter::save] Could not allocate/initialize the memory for PNG image information.");
    return false; 
  }
 
  // Set error handling for setjmp/longjmp method of libpng error handling 
  if (setjmp(png_jmpbuf(png_ptr))) {
    // Free all of the memory associated with the png_ptr and info_ptr 
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    // If we get here, we had a problem writing the file 
    Report::warning("[PNGWriter::save] Could not open PNG image for writting.");
    return false; 
  }
 

  const AbstractPixmap* pm = pixi->getPixmap();
  int resX = pm->getResolutionX();
  int resY = pm->getResolutionY();
  bool didCut;
  unsigned char* ppmPicture = PixmapUtilities::createPPMPicture(didCut, pm);


  // Set up the input control if you are using standard C streams 
  png_init_io(png_ptr, outfile);
 
  png_set_IHDR(png_ptr, info_ptr, resX, resY,
	       8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
	       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
 
  png_set_gAMA(png_ptr, info_ptr, 1.0);
 
  png_textp text_ptr = (png_textp) png_malloc(png_ptr, (png_uint_32)sizeof(png_text) * 2);
 
  text_ptr[0].key = "Description";
  text_ptr[0].text = "ProtoMol PNG Writer";
  text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
#ifdef PNG_iTXt_SUPPORTED
  text_ptr[0].lang = NULL;
#endif
 
  text_ptr[1].key = "Software";
  text_ptr[1].text = "ProtoMol";
  text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
#ifdef PNG_iTXt_SUPPORTED
  text_ptr[1].lang = NULL;
#endif
 
  png_bytep* row_pointers = (png_bytep *) png_malloc(png_ptr, resY*sizeof(png_bytep));

  for (unsigned int y=0; y<resY; y++) {
    row_pointers[y] = &ppmPicture[y * resX * 3];
  }
 
  png_set_rows(png_ptr, info_ptr, row_pointers);
 
  // one-shot call to write the whole PNG file into memory 
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
 
  png_free(png_ptr, row_pointers);
  png_free(png_ptr, text_ptr);
 
  // clean up after the write and free any memory allocated - REQUIRED 
  png_destroy_write_struct(&png_ptr, (png_infopp)NULL);


  delete[] ppmPicture;  
  if (didCut)
    Report::warning("[PNGWriter::save] Pixel values adapted to range");
  
  return true;
#else
  
  return false;
   
#endif // HAVE_PNG

}
