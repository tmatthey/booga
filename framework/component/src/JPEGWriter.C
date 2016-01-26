/*
 * $RCSfile: JPEGWriter.C,v $
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
 *  $Id: JPEGWriter.C,v 1.2 1997/09/19 07:14:15 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
   
#include <fstream>

#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/JPEGWriter.h"
#ifdef HAVE_JPEG
extern "C" {
#include <jpeglib.h>
}
#endif // HAVE_JPEG

//____________________________________________________________________ JPEGWriter

implementRTTI(JPEGWriter, Pixmap2DWriter);

JPEGWriter::JPEGWriter(const RCString& filename, Type traversalType)
: Pixmap2DWriter(filename, traversalType) 
{
  myQuality = 75;
}

bool JPEGWriter::save(const AbstractFile& ofs, const Pixmap2D* pixi) const 
{
  FileFD fs(ofs,"wb");
  if (fs.bad()) {
    Report::warning("JPEGWriter:can't open file\n");
    return false;
  }
  return save(fs,pixi);
}
bool JPEGWriter::save(FILE* outfile, const Pixmap2D* pixi) const 
{
#ifdef HAVE_JPEG
  const AbstractPixmap* pm = pixi->getPixmap();
  int resX = pm->getResolutionX();
  int resY = pm->getResolutionY();
  bool didCut;
  unsigned char* JPEGPicture = PixmapUtilities::createPPMPicture(didCut, pm);

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  //  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */

  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);
  
  //ofs.close(); // We close ofs since we have to open the file
  //             // ourselves.
  
  // we have to open the file ourselves
  // maybe I should convert ofs to FILE
  
//   if ((outfile = fopen(myFilename.chars(), "wb")) == NULL) {
//     Report::warning("JPEGWriter:can't open file\n");
//     return false;
//     }
//  outfile = ofs.FILE();
    
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = resX; 	/* image width and height, in pixels */
  cinfo.image_height = resY;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */

  jpeg_set_defaults(&cinfo);

  jpeg_set_quality(&cinfo, myQuality, TRUE /* limit to baseline-JPEG values */);

  jpeg_start_compress(&cinfo, TRUE);

  row_stride = resX * 3;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = &JPEGPicture[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  if (didCut)
    Report::warning("[JPEGWriter::save] Pixel values adapted to range");
  delete JPEGPicture;
  return true;

#else
  
  return false;
   
#endif // HAVE_JPEG
}
