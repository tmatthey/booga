/*
 * $RCSfile: PSWriter2D.C,v $
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
 *  $Id: PSWriter2D.C,v 1.16 1997/09/19 07:14:36 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <unistd.h>
#endif
#include "booga/base/AbstractPixmap.h"
#include "booga/base/PixmapUtilities.h"
#include "booga/object/Transform2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/Text2D.h"
#include "booga/object/Circle2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/Collector2DFor.h"
#include "booga/component/PSWriter2D.h"

//___________________________________________________________________ PSWriter2D

implementRTTI(PSWriter2D, Operation2D);

PSWriter2D::PSWriter2D(const RCString& filename)
: myFilename(filename)
{
  myCamera = NULL;
  myHasAdoptedCamera = false;
}

void PSWriter2D::adoptCamera(Camera2D* camera)
{
  if (camera == NULL) {
    Report::warning("[PSWriter2D::adoptCamera] NULL pointer passed");
    return;
  }
    
  if (myCamera != NULL && myCamera != camera)
    delete myCamera;

  myCamera = camera; 
  myHasAdoptedCamera = true;
}

void PSWriter2D::deleteCamera()
{
  if (myCamera != NULL) {
    delete myCamera;
    myCamera = NULL;
  }
  myHasAdoptedCamera = false;
}

bool PSWriter2D::preprocessing()
{
  if (!Operation2D::preprocessing())
    return false;

  if (!myHasAdoptedCamera) {
    //
    // Collect all cameras in the world.
    //  
    Collector2DFor<Camera2D> camCollector;
    camCollector.execute(getWorld());
  
    //
    // Look for first camera in world, that is switched on.
    //
    for (camCollector.first(); !camCollector.isDone(); camCollector.next())
      if (camCollector.getObject()->isOn()) {
        if (myCamera != NULL)
          delete myCamera;
        myCamera = camCollector.createTransformedObject(); 
    }
  }

  if (myCamera == NULL) {
    Report::recoverable("[PSWriter2D::preprocessing] no camera available");
    return false;
  }
  
  //
  // If myFilename is empty, we try to open stdout for writing
  //
  if (myFilename.isEmpty()) {
    myOfs.tie(&std::cout);//->attach(STDOUT_FILENO);
    if (myOfs.bad()) {
      Report::recoverable("[PSWriter2D::preprocessing] could not attach to stdout");
      return false;
    }
  } else {  // filename is not empty, so we have to open a regular file:
    //
    // try to open file and save image
    //
    myOfs.open(myFilename.chars());
    if (myOfs.bad()) {
      Report::recoverable("[PSWriter2D::preprocessing] could not open file named " + myFilename);
      return false;
    }
  }
  
  printPostScriptHeader();
  return true;
}

bool PSWriter2D::postprocessing()
{
  printPostScriptFooter();
  return Operation2D::postprocessing();
}

Traversal::Result PSWriter2D::visit(Pixmap2D* pixi)
{
  const TransMatrix2D&  trans = getTraversal()->getPath()->getLastTransform().getTransMatrix();
  const AbstractPixmap* image = pixi->getPixmap();

  int resX = image->getResolutionX();
  int resY = image->getResolutionY();
 
  bool didCut;
  unsigned char* ppmPicture = PixmapUtilities::createPPMPicture(didCut, image);

  if (didCut)
    Report::warning("[PSWriter2D::visit(Pixmap2D)] Pixel values adapted to range");

  myOfs << "\n"
           "% define string to hold a scanline's worth of data\n"
           "/pix " << (int)((resX*3*8+7)/8) << " string def\n"
           "\n"
           "gsave\n"
           "[" << trans(0, 0) << " " << trans(0, 1) <<
           " " << trans(1, 0) << " " << trans(1, 1) <<
           " " << trans(2, 0) << " " << trans(2, 1) << 
           "] concat   % Transformation matrix\n"
           << resX << " " << resY << " scale\n"
           "\n"
           << resX << " " << resY << " 8       % dimensions of data\n"
           "[" << resX << " 0 0 " << -resY << " 0 " << resY 
           << "]  % transform to dot\n"
           
           "{currentfile pix readhexstring pop}\n"
           "false 3 colorimage\n"
           ; // end of myOfs << ....

  myOfs << std::hex; // Set to hex output

  int j=0;
  for (int i=0; i<3*resX*resY; i++,j++) {
    if (j%20 == 0) {  // 20 bytes per line
      myOfs << "\n";
      j = 0;
    }
    
    if (i%(3*resX) == 0) {  // new line after each row
      myOfs << "\n\n";
      j = 0;
    }
    
    if (ppmPicture[i] <= 0xF)  
      myOfs << "0";
    myOfs << (int)ppmPicture[i] << " ";      
  }
  
  myOfs << std::dec; // Set to dec output

  myOfs << "\n"
           "\n"
           "grestore\n"
           "\n"
           ; // end of myOfs << ....

  delete ppmPicture;

  return Traversal::CONTINUE;
}

Traversal::Result PSWriter2D::visit(Line2D* line)
{
  Vector2D from = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       line->getFrom());
  Vector2D to   = getTraversal()->getPath()->getLastTransform().transformAsPoint(
		       line->getTo());

  //
  // Viewing transformation.
  //
  from = myCamera->getViewing()->transformWorld2Screen(from);
  to   = myCamera->getViewing()->transformWorld2Screen(to);

  myOfs << from.x() << " " << from.y() << " m" << std::endl;
  myOfs << to.x()   << " " << to.y()   << " e" << std::endl;

  return Traversal::CONTINUE;
}

Traversal::Result PSWriter2D::visit(Text2D*)
{
//  const TransMatrix2D&  trans = myTraversal->getPath()->getLastTransform().getTransMatrix();
//  Vector2D start = myCamera->getViewing()->transformWorld2Screen(Vector2D(0,0));
//  Vector2D height = myCamera->getViewing()->transformWorld2Screen(Vector2D(0, text->getHeight()));
//
//  myOfs << "gsave /Times-Roman findfont " << height.y() << " scalefont setfont\n"
//           "[" << trans(0, 0) << " " << trans(0, 1) <<
//           " " << trans(1, 0) << " " << trans(1, 1) <<
//           " " << trans(2, 0) << " " << trans(2, 1) << 
//           "] concat   % Transformation matrix\n"
//       << start.x() << " " << start.y() << " moveto\n" 
//       << " (" << text->getText() << ") " 
//        << "show grestore\n";
//
  return Traversal::UNKNOWN;
}

Traversal::Result PSWriter2D::visit(Circle2D* circle)
{
  const TransMatrix2D&  trans = getTraversal()->getPath()->getLastTransform().getTransMatrix();

  myOfs  << circle->getCenter().x() << " " 
         << circle->getCenter().y() << " "
         << circle->getRadius() << " 0 360 "
         << "[" << trans(0, 0) << " " << trans(0, 1) <<
         " " << trans(1, 0) << " " << trans(1, 1) <<
         " " << trans(2, 0) << " " << trans(2, 1) << 
         "] c\n"
         ; // end of myOfs << ....

  return Traversal::CONTINUE;
}

void PSWriter2D::printPostScriptHeader()
{
  int xRes = myCamera->getViewing()->getResolutionX();
  int yRes = myCamera->getViewing()->getResolutionY();
  
  Vector2D winOrig = myCamera->getViewing()->getWindowOrigin();
  Vector2D winSize = myCamera->getViewing()->getWindowSize();
  Vector2D offset  = Vector2D(0,0) - winOrig;
 
  myOfs << "%!PS-Adobe-2.0 EPSF-2.0\n"
           "%%Title: " << myFilename << "\n"
           "%%Creator: BOOGA : Berne's Object Oriented Graphics Architecture\n"
           "%%Orientation: Portrait\n"
           "%%BoundingBox: " 
           << winOrig.x() << " " << winOrig.y() << " "
           << winOrig.x()+winSize.x() << " " 
           << winOrig.y()+winSize.y() << "\n"
           "%%Pages: 1\n" 
           "%%DocumentFonts:\n" 
           "%%EndComments\n"
           "%%EndProlog\n"
           "%%Page: 1 1\n"
           "\n"
           "% remember original state\n"
           "/origstate save def\n"
           "\n"
           "% build a temporary dictionary\n"
           "20 dict begin\n"
           "\n"
           "% some settings\n"
           ".5 setlinewidth\n"
           "1 setlinejoin\n"
           "1 setlinecap\n"
           "\n"
           "%some definitions\n"
           "/m /moveto load def                           % moveto\n"
           "/d { lineto currentpoint stroke moveto } def  % draw line\n"
           "/e { lineto currentpoint stroke } def         % endpoint of line\n"
           "/c { /matr exch def            % store matrix\n"
           "     gsave matr concat         % set transformation\n"
           "     arc                       % draw circle\n"
           "     matr matrix invertmatrix  % create inverse matrix\n"
           "     concat stroke             % draw line in original context\n"
           "     grestore } def   % circle with transf\n"
           "\n"
           "% define clipping path\n"
           "newpath\n"
           << winOrig.x() << " " << winOrig.y() << " m\n"
           << winOrig.x() << " " << winOrig.y()+winSize.y() << " lineto\n"
           << winOrig.x()+winSize.x() << " " << winOrig.y()+winSize.y() << " lineto\n"
           << winOrig.x()+winSize.x() << " " << winOrig.y() << " lineto\n"
           "closepath clip\n"
           "newpath\n"
           "\n"
           "% Global Positioning\n"
           << offset.x() << " " << offset.y() << " translate\n"
           << ((Real)xRes)/winSize.x() << " " << ((Real)yRes)/winSize.y() << " scale\n"
           "\n"
           "% define space for color conversions\n"
           "/grays 72 string def  % space for gray scale line\n"
           "/npixls 0 def\n"
           "/rgbindx 0 def\n"
           "\n"
           "% define 'colorimage' if it isn't defined\n"
           "/colorimage where   % do we know about 'colorimage'?\n"
           "  { pop }           % yes: pop off the 'dict' returned\n"
           "  {                 % no:  define one\n"
           "    /colortogray {  % define an RGB->I function\n"
           "      /rgbdata exch store    % call input 'rgbdata'\n"
           "      rgbdata length 3 idiv\n"
           "      /npixls exch store\n"
           "      /rgbindx 0 store\n"
           "      0 1 npixls 1 sub {\n"
           "        grays exch\n"
           "        rgbdata rgbindx       get 20 mul    % Red\n"
           "        rgbdata rgbindx 1 add get 32 mul    % Green\n"
           "        rgbdata rgbindx 2 add get 12 mul    % Blue\n"
           "        add add 64 idiv      % I = .5G + .31R + .18B\n"
           "        put\n"
           "        /rgbindx rgbindx 3 add store\n"
           "      } for\n"
           "      grays 0 npixls getinterval\n"
           "    } bind def\n"
           "\n"
           "    % Utility procedure for colorimage operator.\n"
           "    % This procedure takes two procedures off the\n"
           "    % stack and merges them into a single procedure.\n"
           "\n"
           "    /mergeprocs { % def\n"
           "      dup length\n"
           "      3 -1 roll\n"
           "      dup\n"
           "      length\n"
           "      dup\n"
           "      5 1 roll\n"
           "      3 -1 roll\n"
           "      add\n"
           "      array cvx\n"
           "      dup\n"
           "      3 -1 roll\n"
           "      0 exch\n"
           "      putinterval\n"
           "      dup\n"
           "      4 2 roll\n"
           "      putinterval\n"
           "    } bind def\n"
           "\n"
           "    /colorimage { % def\n"
           "      pop pop     % remove 'false 3' operands\n"
           "      {colortogray} mergeprocs\n"
           "      image\n"
           "    } bind def\n"
           "  } ifelse          % end of 'false' case\n"
           "\n"
           ; // end of myOfs << ....
}

void PSWriter2D::printPostScriptFooter()
{
  myOfs << "showpage\n"
           "% stop using temporary dictionary\n"
           "end\n"
           "\n"
           "% restore original state\n"
           "origstate restore\n"
           "\n"
           "%Trailer\n"
           "\n"
           ; // end of myOfs << ...
}

Traversal::Result PSWriter2D::dispatch(Makeable* obj)
{
  tryConcrete(Line2D,   obj);
  tryConcrete(Text2D,   obj);
  tryConcrete(Circle2D, obj);
  tryConcrete(Pixmap2D, obj);

  return Traversal::UNKNOWN; // Perform decomposition if unknown object.
}
