/*
 * $RCSfile: JPEGReader.C,v $
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
 *  $Id: JPEGReader.C,v 1.5 1997/09/19 07:14:13 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>          // fdopen(), ...
#ifdef WIN32
#include <io.h>         // dup()
#elif SVR4
#include <unistd.h>
#endif
#include <sstream>

#ifdef HAVE_JPEG

#include <setjmp.h>
extern "C" {
#include <jpeglib.h>
}

#endif // HAVE_JPEG

#include "booga/base/Report.h"
#include "booga/pixmapOp/JPEGReader.h"
   
//____________________________________________________________________JPEGReader

implementInitExemplar(JPEGReader);

JPEGReader::JPEGReader(Exemplar anExemplar)
: ImageReader(anExemplar) 
{}

#ifdef HAVE_JPEG

/*
 * ERROR HANDLING:
 *
 * The JPEG library's standard error handler (jerror.c) is divided into
 * several "methods" which you can override individually.  This lets you
 * adjust the behavior without duplicating a lot of code, which you might
 * have to update with each future release.
 *
 * Our example here shows how to override the "error_exit" method so that
 * control is returned to the library's caller when a fatal error occurs,
 * rather than calling exit() as the standard error_exit method does.
 *
 * We use C's setjmp/longjmp facility to return control.  This means that the
 * routine which calls the JPEG library must first execute a setjmp() call to
 * establish the return point.  We want the replacement error_exit to do a
 * longjmp().  But we need to make the setjmp buffer accessible to the
 * error_exit routine.  To do this, we make a private extension of the
 * standard JPEG error handler object.  (If we were using C++, we'd say we
 * were making a subclass of the regular error handler.)
 *
 * Here's the extended error handler struct:
 */

struct JPEGErrorMgr {
  struct jpeg_error_mgr pub;	// "public" fields
  jmp_buf setjmp_buffer;	         // for return to caller
};

/*
 * Here's the routine that will replace the standard error_exit method:
 */

static void JPEGErrorExit(j_common_ptr cinfo)
{
  //
  // cinfo->err really points to a JPEGErrorMgr struct, so coerce pointer
  //
  JPEGErrorMgr* err = (JPEGErrorMgr*) cinfo->err;

  //
  // Always display the message (NO!!!).
  // We could postpone this until after returning, if we chose.
  //
  //  (*cinfo->err->output_message) (cinfo);

  //
  // Return control to the setjmp point.
  //
  longjmp(err->setjmp_buffer, 1);
}

#endif // HAVE_JPEG

AbstractPixmap* JPEGReader::read(const AbstractFile& ifs){
  FileFD fs(ifs,"rb");
  if (fs.bad()) {
    Report::warning("JPEGReader:can't open file");
    return NULL;
  }
  return read(fs);
}

AbstractPixmap* JPEGReader::read(FILE* infile)
{
#ifdef HAVE_JPEG

  //  FILE* infile;		// source file
  AbstractPixmap* pm = NULL;

  //
  // In this application we want to open the input file before doing anything 
  // else, so that the setjmp() error recovery below can assume the file is open.
  // VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
  // requires it in order to read binary files.
  //
  //  if ((infile = fdopen(dup(ifs.fd()), "rb")) == NULL) {
  //    return NULL;
  //  }
  //  fseek(infile, 0, 0); // Ajust position to the beginning of the file.

  //
  // Step 1: allocate and initialize JPEG decompression object */
  // -------
  //

  // This struct contains the JPEG decompression parameters and pointers to
  // working space (which is allocated as needed by the JPEG library).
  //
  struct jpeg_decompress_struct cinfo;
  struct JPEGErrorMgr jerr; // We use our private extension JPEG error handler.

  //
  // We set up the normal JPEG error routines, then override error_exit.
  //
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = JPEGErrorExit;
  
  //
  // Establish the setjmp return context for JPEGErrorExit to use.
  //
  if (setjmp(jerr.setjmp_buffer)) {
    //
    // If we get here, the JPEG code has signaled an error.
    // We need to clean up the JPEG object, close the input file, and return.
    //
    jpeg_destroy_decompress(&cinfo);
    if (pm != NULL)
      delete pm;
    //fclose(infile);

    return NULL;
  }
  
  //
  // Now we can initialize the JPEG decompression object. 
  //
  jpeg_create_decompress(&cinfo);

  //
  // Step 2: specify data source (eg, a file) 
  // -------
  //

  jpeg_stdio_src(&cinfo, infile);

  //
  // Step 3: read file parameters with jpeg_read_header() 
  // -------
  //
  
  (void) jpeg_read_header(&cinfo, TRUE);
  // We can ignore the return value from jpeg_read_header since
  //   (a) suspension is not possible with the stdio data source, and
  //   (b) we passed TRUE to reject a tables-only JPEG file as an error.
  // See libjpeg.doc for more info.

  //
  // Step 4: set parameters for decompression
  // -------

  // In this example, we don't need to change any of the defaults set by
  // jpeg_read_header(), so we do nothing here.

  //
  // Step 5: Start decompressor
  // -------
  //
  
  jpeg_start_decompress(&cinfo);

  //
  // 1 or 3 color components are allowd...
  //
  if (cinfo.jpeg_color_space != JCS_GRAYSCALE &&
      cinfo.jpeg_color_space != JCS_RGB       &&
      cinfo.jpeg_color_space != JCS_YCbCr) {
    Report::recoverable("[JPEGReader::read] color space model of jpeg image not supported");
    jpeg_destroy_decompress(&cinfo);
    //fclose(infile);

    return NULL;
  }
       
  //
  // JSAMPLEs per row in output buffer == physical row width in output buffer
  //
  int rowStride = cinfo.output_width * cinfo.output_components;
  pm = MPixmapExemplar::createPixmap(cinfo.output_width, cinfo.output_height);
 
  //
  // Make a one-row-high sample array that will go away when done with image */
  //
  JSAMPARRAY buffer;
  buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, rowStride, 1);

  //
  // Step 6: while (scan lines remain to be read) 
  // -------   jpeg_read_scanlines(...); 
  //
  
  //  
  // Here we use the library's state variable cinfo.output_scanline as the
  // loop counter, so that we don't have to keep track ourselves.
  //
  int i;
  int x = 0, y = cinfo.output_height - 1; // indicates position within pixi.
  
  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);

    //
    // Store data to the pixi.
    //
    for (i=0; i<rowStride; i += cinfo.output_components, x++) {
      pm->setPosition(x, y);
        
      //
      // JPEG image of type greyscale
      //
      if (cinfo.output_components == 1) 
         pm->setColor((*buffer)[i]/255.0F);
      //
      // JPEG image of type rgb
      //
      else if (cinfo.output_components == 3) 
         pm->setColor((*buffer)[i]/255.0, 
                      (*buffer)[i+1]/255.0, 
                      (*buffer)[i+2]/255.0);
    }

    y--;   // Next scanline.
    x = 0;
  }

  //
  // Step 7: Finish decompression
  // -------
  //

  (void) jpeg_finish_decompress(&cinfo);
  // We can ignore the return value since suspension is not possible
  // with the stdio data source.

  //
  // Step 8: Release JPEG decompression object 
  // -------
  //

  jpeg_destroy_decompress(&cinfo);

  // After finish_decompress, we can close the input file.
  // Here we postpone it until after no more JPEG errors are possible,
  // so as to simplify the setjmp error logic above.  (Actually, I don't
  // think that jpeg_destroy can do an error exit, but why assume anything...)
  //
  //fclose(infile);

  //
  // At this point you may want to check to see whether any corrupt-data
  // warnings occurred (test whether jerr.pub.num_warnings is nonzero).
  //
  if (jerr.pub.num_warnings > 0) {
    std::stringstream os;
    os << "[JPEGReader::read] " 
       << jerr.pub.num_warnings
       << " corrupt-data warnings occurred while reading a jpeg image";
    Report::warning(os);
  }

  return pm;
  
#else
  
  return NULL;
   
#endif // HAVE_JPEG
} 
