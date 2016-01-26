/*
 * $RCSfile: GIFReader.C,v $
 *
 * +-------------------------------------------------------------------+ 
 * | Copyright 1990, 1991, 1993 David Koblas.		        | 
 * |   Permission to use, copy, modify, and distribute this software   | 
 * |   and its documentation for any purpose and without fee is hereby | 
 * |   granted, provided that the above copyright notice appear in all | 
 * |   copies and that both that copyright notice and this permission  | 
 * |   notice appear in supporting documentation.  This software is    | 
 * |   provided "as is" without express or implied warranty.	        | 
 * +-------------------------------------------------------------------+
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: GIFReader.C,v 1.2 1997/09/19 07:14:05 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>          // FILE, fseek, ...
#ifdef WIN32
#include <io.h>         // dup()
#elif SVR4
#include <unistd.h>     // dup()
#endif
#include <string.h>         // strncmp
#include <sstream>      // std::stringstream

#include "booga/pixmapOp/GIFReader.h"
//_____________________________________________________________ Static functions

#define MAXCOLORMAPSIZE 256

#define CM_RED		0
#define CM_GREEN	         1
#define CM_BLUE		2

#define	MAX_LWZ_BITS	12

#define INTERLACE		0x40
#define LOCALCOLORMAP	0x80

#define BitSet(byte, bit)	        (((byte) & (bit)) == (bit))
#define ReadOK(file,buffer,len)    (fread(buffer, len, 1, file) != 0)
#define LM_to_uint(a,b)            (((b)<<8)|(a))

static int ZeroDataBlock = false;

static int GetDataBlock(FILE* fd, unsigned char* buf)
{
  unsigned char count;

  if (!ReadOK(fd, &count, 1)) {
    return -1;
  }
  ZeroDataBlock = count == 0;

  if ((count != 0) && (!ReadOK(fd, buf, count))) {
    return -1;
  }
  return count;
}

static int GetCode(FILE* fd, int code_size, int flag)
{
  static unsigned char buf[280];
  static int curbit, lastbit, done, last_byte;
  int i, j, ret;
  unsigned char count;

  if (flag) {
    curbit = 0;
    lastbit = 0;
    done = false;
    return 0;
  }

  if ((curbit + code_size) >= lastbit) {
    if (done) {
      if (curbit >= lastbit)
        Report::recoverable("[GIFReader (GetCode)] ran off the end of my bits");
      return -1;
    }
    
    buf[0] = buf[last_byte - 2];
    buf[1] = buf[last_byte - 1];

    if ((count = GetDataBlock(fd, &buf[2])) == 0)
      done = true;

    last_byte = 2 + count;
    curbit = (curbit - lastbit) + 16;
    lastbit = (2 + count) * 8;
  }

  ret = 0;
  for (i = curbit, j = 0; j < code_size; ++i, ++j)
    ret |= ((buf[i / 8] & (1 << (i % 8))) != 0) << j;

  curbit += code_size;

  return ret;
}

static int LWZReadByte(FILE* fd, int flag, int input_code_size)
{
  static int fresh = false;
  int code, incode;
  static int code_size, set_code_size;
  static int max_code, max_code_size;
  static int firstcode, oldcode;
  static int clear_code, end_code;
  static int table[2][(1 << MAX_LWZ_BITS)];
  static int stack[(1 << (MAX_LWZ_BITS)) * 2], *sp;
  register int i;

  if (flag) {
    set_code_size = input_code_size;
    code_size = set_code_size + 1;
    clear_code = 1 << set_code_size;
    end_code = clear_code + 1;
    max_code_size = 2 * clear_code;
    max_code = clear_code + 2;

    GetCode(fd, 0, true);

    fresh = true;

    for (i = 0; i < clear_code; ++i) {
      table[0][i] = 0;
      table[1][i] = i;
    }

    for (; i < (1 << MAX_LWZ_BITS); ++i)
      table[0][i] = table[1][0] = 0;

    sp = stack;

    return 0;
  } 
  else if (fresh) {
    fresh = false;
    do {
      firstcode = oldcode = GetCode(fd, code_size, false);
    } while (firstcode == clear_code);
    return firstcode;
  }
  if (sp > stack)
    return *--sp;

  while ((code = GetCode(fd, code_size, false)) >= 0) {
    if (code == clear_code) {
      for (i = 0; i < clear_code; ++i) {
        table[0][i] = 0;
        table[1][i] = i;
      }
      for (; i < (1 << MAX_LWZ_BITS); ++i)
        table[0][i] = table[1][i] = 0;
      code_size = set_code_size + 1;
      max_code_size = 2 * clear_code;
      max_code = clear_code + 2;
      sp = stack;
      firstcode = oldcode = GetCode(fd, code_size, false);
      return firstcode;
    } 
    else if (code == end_code) {
      int count;
      unsigned char buf[260];

      if (ZeroDataBlock)
        return -2;

        while ((count = GetDataBlock(fd, buf)) > 0);

        if (count != 0) {
	/*
	   pm_message("missing EOD in data stream (common occurence)");
	 */
        }
      return -2;
    }
    incode = code;

    if (code >= max_code) {
      *sp++ = firstcode;
      code = oldcode;
    }
    while (code >= clear_code) {
      *sp++ = table[1][code];
      if (code == table[0][code]) {
        Report::recoverable("[GIFReader (LWZReadByte)] circular table entry BIG ERROR");
      }
      code = table[0][code];
    }

    *sp++ = firstcode = table[1][code];

    if ((code = max_code) < (1 << MAX_LWZ_BITS)) {
      table[0][code] = oldcode;
      table[1][code] = firstcode;
      ++max_code;
      if ((max_code >= max_code_size) &&
          (max_code_size < (1 << MAX_LWZ_BITS))) {
        max_code_size *= 2;
        ++code_size;
      }
    }
    oldcode = incode;

    if (sp > stack)
      return *--sp;
  }
  return code;
}

static int DoExtension(FILE* fd, int label)
{
  static char buf[256];
  //const char* str;

  /* struct {
    int transparent;
    int delayTime;
    int inputFlag;
    int disposal;
  }; */ 
  //Gif89 = {  -1, -1, -1, 0 };

  switch (label) {
    case 0x01:			// Plain Text Extension 
        //str = "Plain Text Extension";
	break;
    case 0xff:			// Application Extension 
        //str = "Application Extension";
	break;
    case 0xfe:			// Comment Extension 
        //str = "Comment Extension";
	while (GetDataBlock(fd, (unsigned char *) buf) != 0);
	return false;
    case 0xf9:			// Graphic Control Extension
        //str = "Graphic Control Extension";
	(void) GetDataBlock(fd, (unsigned char *) buf);
	//Gif89.disposal = (buf[0] >> 2) & 0x7;
	//Gif89.inputFlag = (buf[0] >> 1) & 0x1;
	//Gif89.delayTime = LM_to_uint(buf[1], buf[2]);
	//if ((buf[0] & 0x1) != 0)
	//    Gif89.transparent = buf[3];

	while (GetDataBlock(fd, (unsigned char *) buf) != 0);
	return false;
    default:
        //str = buf;
	sprintf(buf, "UNKNOWN (0x%02x)", label);
	break;
    }

    while (GetDataBlock(fd, (unsigned char *) buf) != 0);

    return false;
}

static int ReadColorMap(FILE* fd, 
                        int number, 
                        unsigned char buffer[3][MAXCOLORMAPSIZE], 
                        int* gray)
{
  unsigned char rgb[3];

  for (int i = 0; i < number; ++i) {
    if (!ReadOK(fd, rgb, sizeof(rgb))) {
      Report::recoverable("[GIFReader (ReadColorMap)] bad colormap");
      return 1;
    }

    buffer[CM_RED][i]   = rgb[0];
    buffer[CM_GREEN][i] = rgb[1];
    buffer[CM_BLUE][i]  = rgb[2];
  }

  *gray = 0;

  return 0;
}

static AbstractPixmap* ReadImage(FILE* fd, 
                                 AbstractPixmap* adoptPrototype,
                                 int width, int height, 
                                 unsigned char cmap[3][MAXCOLORMAPSIZE],
                                 int interlace, int ignore)
{
  //
  // Initialize the compression routines.
  //
  unsigned char c;
  
  if (!ReadOK(fd, &c, 1)) {
    Report::recoverable("[GIFReader (ReadImage)] EOF / read error on image data");
    delete adoptPrototype;
    return NULL;
  }

  if (LWZReadByte(fd, true, c) < 0) {
    Report::recoverable("[GIFReader (ReadImage)] error reading image");
    delete adoptPrototype;
    return NULL;
  }

  //
  // If this is an "uninteresting picture" ignore it.
  //
  if (ignore) {
    while (LWZReadByte(fd, false, c) >= 0);
    delete adoptPrototype;
    return NULL;
  }

  //
  // We have an image! Read it and create a pixi.
  //
  AbstractPixmap* image = adoptPrototype;
  image->setResolution(width, height);

  int cmapIndex;
  int xpos = 0, ypos = 0, pass = 0;
  
  while ((cmapIndex = LWZReadByte(fd, false, c)) >= 0) {
    image->setPosition(xpos, height-ypos-1);
    image->setColor(cmap[CM_RED][cmapIndex]   / 255., 
                    cmap[CM_GREEN][cmapIndex] / 255., 
                    cmap[CM_BLUE][cmapIndex]  / 255.);

    ++xpos;
    if (xpos == width) {
       xpos = 0;
       if (interlace) {
	switch (pass) {
           case 0:
           case 1:
	    ypos += 8;
	    break;
           case 2:
	    ypos += 4;
	    break;
           case 3:
	    ypos += 2;
	    break;
         }

         if (ypos >= height) {
	  ++pass;
	  switch (pass) {
	    case 1:
               ypos = 4;
               break;
	    case 2:
               ypos = 2;
               break;
	    case 3:
               ypos = 1;
               break;
	    default:
               goto fini;
           }
         }
       } 
       else {
        ++ypos;
      }
    }
    if (ypos >= height)
      break;
  }

fini:

  return image;
}
                                 
//____________________________________________________________________ GIFReader

implementInitExemplar(GIFReader);

GIFReader::GIFReader(Exemplar anExemplar)
: ImageReader(anExemplar) 
{}

AbstractPixmap* GIFReader::read(const AbstractFile& ifs){
  FileFD fs(ifs,"rb");
  if (fs.bad()) {
    Report::warning("GIFReader:can't open file");
    return NULL;
  }
  return read(fs);
}


AbstractPixmap* GIFReader::read(FILE* fd)
{
  char buf[16];     // Buffer for read operations.
  //  FILE* fd;         // Source file.

  //
  // In this application we want to open the input file before doing anything 
  // else.
  // VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
  // requires it in order to read binary files.
  //
  //   if ((fd = fdopen(dup(ifs.fd()), "rb")) == NULL) {
  //     return NULL;
  //   }

  fseek(fd, 0, 0); // Ajust position to the beginning of the file.

  //
  // Read header information.
  // --------------------------------------------
  //
  
  if (!ReadOK(fd, buf, 6)) {
    fclose(fd);
    return NULL;
  }

  if (strncmp(buf, "GIF", 3) != 0) {
    fclose(fd);
    return NULL;
  }

  //
  // Check GIF version number: 87a or 89a area allowed.
  //
  char version[4];
  strncpy(version, buf + 3, 3);
  version[3] = '\0';

  if ((strcmp(version, "87a") != 0) && (strcmp(version, "89a") != 0)) {
    Report::recoverable("[GIFReader::read] bad version number, not '87a' or '89a'");
    fclose(fd);
    return NULL;
  }
    
  //
  // Read screen description.
  //
  if (!ReadOK(fd, buf, 7)) {
    Report::recoverable("[GIFReader::read] failed to read screen descriptor");
    fclose(fd);
    return NULL;
  }

  struct GifScreen {
    unsigned int Width;
    unsigned int Height;
    unsigned char ColorMap[3][MAXCOLORMAPSIZE];
    unsigned int BitPixel;
    unsigned int ColorResolution;
    unsigned int Background;
    unsigned int AspectRatio;
    int GrayScale;
  };
  GifScreen gifScreen;

  gifScreen.Width = LM_to_uint(buf[0], buf[1]);
  gifScreen.Height = LM_to_uint(buf[2], buf[3]);
  gifScreen.BitPixel = 2 << (buf[4] & 0x07);
  gifScreen.ColorResolution = (((buf[4] & 0x70) >> 3) + 1);
  gifScreen.Background = buf[5];
  gifScreen.AspectRatio = buf[6];

  //
  // Get the colormap.
  //
  if (BitSet(buf[4], LOCALCOLORMAP)) {	// Global Colormap
    if (ReadColorMap(fd, gifScreen.BitPixel, 
                         gifScreen.ColorMap,
                        &gifScreen.GrayScale)) {
      Report::recoverable("[GIFReader::read] error reading global colormap");
      fclose(fd);
      return NULL;
    }
  }

  //
  // Start reading the image.
  // --------------------------------------------
  //
  
  char c;
  int imageCount = 0;
  int imageNumber = 1;
  AbstractPixmap* pm = NULL;

  do {
    if (!ReadOK(fd, &c, 1)) {
      Report::recoverable("[GIFReader::read] EOF / read error on image data");
      fclose(fd);
      return NULL;
    }

    if (c == ';') {		// GIF terminator 
      if (imageCount < imageNumber) {
        std::stringstream os;
        os << "[GIFReader::read] only " << imageCount 
           << " image" << ((imageCount > 1) ? "s" : "") << " found in file";
        Report::recoverable(os);
        fclose(fd);
        return NULL;
      }
    }
	
    if (c == '!') {		// Extension 
      if (!ReadOK(fd, &c, 1)) {
        Report::recoverable("[GIFReader::read] OF / read error on extention function code");
        fclose(fd);
        return NULL;
      }
      DoExtension(fd, c);
      continue;
    }
	
    if (c != ',') {		// Not a valid start character 
      continue;
    }

    ++imageCount;

    if (!ReadOK(fd, buf, 9)) {
      Report::recoverable("[GIFReader::read] couldn't read left/top/width/height");
      fclose(fd);
      return NULL;
    }
    
    int useGlobalColormap = !BitSet(buf[8], LOCALCOLORMAP);

    int bitPixel = 1 << ((buf[8] & 0x07) + 1);

    if (!useGlobalColormap) {
      int grayScale;
      unsigned char localColorMap[3][MAXCOLORMAPSIZE];

      if (ReadColorMap(fd, bitPixel, localColorMap, &grayScale)) {
        Report::recoverable("[GIFReader::read] error reading local colormap");
        fclose(fd);
        return NULL;
      }

      pm = ReadImage(fd, 
                     MPixmapExemplar::createPixmap(1,1),
                     LM_to_uint(buf[4], buf[5]), // width
                     LM_to_uint(buf[6], buf[7]), // height
                     localColorMap,
		   BitSet(buf[8], INTERLACE),  // interlace
		   imageCount != imageNumber); // only read last image
    } 
    else {
      pm = ReadImage(fd, 
                     MPixmapExemplar::createPixmap(1,1),
                     LM_to_uint(buf[4], buf[5]), // width
                     LM_to_uint(buf[6], buf[7]), // height
                     gifScreen.ColorMap,
		   BitSet(buf[8], INTERLACE),  // interlace
		   imageCount != imageNumber); // only read last image
    }
  } while (pm == NULL);
 
  fclose(fd);

  return pm;
}

