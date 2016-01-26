
/*
 * rasterize.C 
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
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: rasterdemo.C,v 1.7 1996/02/23 10:17:32 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifdef HAVE_SRGP
extern "C" {
#include <srgp.h>
}
#include "booga/base/Configuration.h"
#include "booga/base/Vector2D.h"
#include "booga/base/TransMatrix2D.h"
#include "booga/base/LineRasterizer.h"
#include "booga/base/ConicRasterizer.h"

int main()
{
  // 
  //  Setup world.
  // -----------------------------------------------------------
  // Configuration::setOption(Name("Report.ErrorStream.Filename"),Name("/dev/console"));
  // Configuration::setOption(Name("Report.ErrorStream"),Name("file"));
  Configuration::setOption(Name("Report.ErrorStream"),Name("cerr"));

  int width  = 600;
  int height = 600;
  int centerX = width/2;
  int centerY = height/2;
  int x, y;

  SRGP_begin("Rasterizer Demo", width, height, 1, 0);
  SRGP_setInputMode(LOCATOR, EVENT);
 
  LineRasterizer lr;
  register int i;

  for (i=0; i<width; i+=10) {
    for (lr.init(0, i, i, height); !lr.isDone(); lr.next()) {
      lr.getPixel(x, y);
      SRGP_pointCoord(x, y);
    }

    for (lr.init(i, height, width, height-i); !lr.isDone(); lr.next()) {
      lr.getPixel(x, y);
      SRGP_pointCoord(x, y);
    }

    for (lr.init(width, height-i, width-i, 0); !lr.isDone(); lr.next()) {
      lr.getPixel(x, y);
      SRGP_pointCoord(x, y);
    }

    for (lr.init(width-i, 0, 0, i); !lr.isDone(); lr.next()) {
      lr.getPixel(x, y);
      SRGP_pointCoord(x, y);
    }
  }
  
  ConicRasterizer cr;
  TransMatrix2D m;
  Vector2D p, q;  
  Vector2D center(centerX, centerY);
   
  for (i=0; i<180; i+=45) {
    m = TransMatrix2D::makeRotateOrigin(dtor(i));
    p = Vector2D(width/3, 0)*m + center;
    q = Vector2D(0, height/6)*m + center;
    
    for (cr.initEllipse(centerX, centerY, (int)p.x(), (int)p.y(), (int)q.x(), (int)q.y()); 
	 !cr.isDone(); cr.next()) {
      cr.getPixel(x, y);
      SRGP_pointCoord(x, y); 
    }
  }
  
  for (i=height/6; i>0; i-=10) {
    for (cr.initCircle(centerX, centerY, i); !cr.isDone(); cr.next()) {
      cr.getPixel(x, y);
      SRGP_pointCoord(x, y); 
    }
  }
  
  SRGP_waitEvent(-1);
  SRGP_end();

  return 1;
}

#else // HAVE_SRGP

#include <stream.h>

int main ()
{
  cerr << "This application needs the Simple Raster Graphics Package\n" 
       << "(SRGP). When compiling this application your site was \n"
       << "configured not to use SRGP.\n\n";
}

#endif // HAVE_SRGP
