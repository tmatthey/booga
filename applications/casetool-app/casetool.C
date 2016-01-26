/*
 * casetool.C 
 *
 * Copyright (C) 1994-96, Thomas Wenger
 *                        Thomas von Siebenthal
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
 *  $Id: casetool.C,v 1.14 1996/10/30 15:31:15 amann Exp $
 * -----------------------------------------------------------------------------
 */
 


#ifdef HAVE_OPENGL

//#include "booga/component/ConfigurationHandlers.h"
#include "booga/glwrapper/GLViewer2D.h"

#include <stddef.h>
#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "booga/object/World2D.h"

#include "CTParser.h"

#include "booga/component/PSWriter2D.h"
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/base/Vector2D.h"
#include "booga/object/Camera2D.h"
#include "booga/object/Line2D.h"
#include "TextBox2D.h"
#include "booga/component/PrintWorld2D.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/Rasterizer.h"
#include "booga/component/BSDL2DParser.h"
#include "CTParserInit.h"
#include "CTUMRenderer2D.h"
#include "CTCPPRenderer2D.h"
#include "booga/object/ConstantTexture2D.h"
#include "booga/glwrapper/GLConstantTexture2D.h"
#include "booga/pixmapOp/ImageReaders.h"

//_____________________________________________________________________ Globals

RCString filename;
bool flags[256];
RCString options[256];

//__________________________________________________________________ Initialiser
 
static void parseCmdLine(int argc, char* argv[]);
static void usage(const RCString& name);

//__________________________________________________________________ Applikation

int main(int argc, char* argv[])
{
  parseCmdLine(argc, argv);

  cout << "Using the following parameters:\n";
  cout << "    Filename: ";
  if (filename.length() <= 0) {
    cout << "STDIN";
    }
  else {
    cout << filename;
    };
  cout << "\n";
  cout << "    Options:  ";
  bool notFirst = false;
  for (int i=0; i < 256; i++) {
    if ((options[i].length() > 0) && (flags[i])) {
      if (notFirst) {
        cout << "              ";
        }
      else {
        notFirst = true;
        };
      cout << char(i) << ": " << options[i] << "\n";
      };
    };
  cout << "    Flags:    ";
  for (int i=0; i < 256; i++) {
    if ((flags[i]) && (options[i].length() == 0)) {
      cout << char(i) << " ";
      };
    };
  cout << "\n\n";

  // set filename for output
  RCString outfile;
  if (flags['O']) {
    outfile = options['O'];
    }
  else {
    outfile = "test";
    };

  World2D myWorld;

  if (strstr(filename.chars(), ".bsdl")) {
    initCTParserGlobalNS();
    initCTParser2DNS();
    BSDL2DParser parser;
    parser.setFilename(filename);
    parser.execute(&myWorld);   
  } else {
    // Parse the C++ Input  
    CTParser TestParser;
   
    cout << "BEGIN PARSING ... ";  

    // checks flags and set several parameters
    TestParser.setCppParameters("");  
    if (flags['i']) {
      TestParser.addCppParameters("-I/home/fcg/BOOGA/workspaces/app-dev/shared_src/framework/include");
      };
    if (flags['I']) {
      RCString tmp;
      tmp = "-I" + options['I'];
      TestParser.addCppParameters(tmp);
      };
    if (flags['d']) {
      TestParser.debugScanner(true);
      TestParser.debugParser(true);
      }
    else {
      TestParser.debugScanner(false);
      TestParser.debugParser(false);
      };
    if (flags['v']) {
      Report::setDebug(true);
      TestParser.verboseOutput(true);
      }
    else {
      TestParser.verboseOutput(false);
      Report::setDebug(false);
      };

    TestParser.setFilename(filename);
    TestParser.execute(&myWorld);

    cout << "ENDED PARSING\n";  
  }
  
  // Display the parsed stuff
 
  cout << "BEGIN OF RENDERER(s) ... ";
 
  if (flags['U']) {
    cout << "UM Renderer ... ";
    CTUMRenderer2D myRenderer;
    myRenderer.execute(&myWorld);
    }
  else {
    if (flags['C']) {
      cout << " C++ Renderer ... ";
      CTCPPRenderer2D myCppRenderer(outfile + ".cpp");
      myCppRenderer.execute(&myWorld);
      };
    };    
  cout << "ENDED RENDERER(s)\n";

  Texture2D* BlackGLTexture = new GLConstantTexture2D(Color(0,0,0));
  Texture2D* BlackTexture = new ConstantTexture2D(Color(0,0,0));

  // add a footer and a border if rendered with UM
  if (flags['U']) {
    // border around the graphic
    Vector2D myOffset(20, 20); 
    Vector2D lowerleft = myWorld.getObjects()->getBounds().getMin() - myOffset;
    Vector2D upperright =  myWorld.getObjects()->getBounds().getMax() + myOffset;
    // lower left  to  upper left
    Line2D* myLine = new Line2D(lowerleft, Vector2D(lowerleft.x(), upperright.y()));
    myLine->appendTexture(BlackTexture->copy());
    myLine->appendTexture(BlackGLTexture->copy());
    myWorld.getObjects()->adoptObject(myLine);
    // upper left  to  upper right
    myLine = new Line2D(Vector2D(lowerleft.x(), upperright.y()), upperright);
    myLine->appendTexture(BlackTexture->copy());
    myLine->appendTexture(BlackGLTexture->copy());
    myWorld.getObjects()->adoptObject(myLine);
    // upper right  to  lower right
    myLine = new Line2D(upperright, Vector2D(upperright.x(), lowerleft.y()));
    myLine->appendTexture(BlackTexture->copy());
    myLine->appendTexture(BlackGLTexture->copy());
    myWorld.getObjects()->adoptObject(myLine);
    // lower right  to  lower left
    myLine = new Line2D(Vector2D(upperright.x(), lowerleft.y()), lowerleft);
    myLine->appendTexture(BlackTexture->copy());
    myLine->appendTexture(BlackGLTexture->copy());
    myWorld.getObjects()->adoptObject(myLine);

    // add comments to the bottom of the graphic
    //tm *myActualTime;
    //tm = localtime(time());
    List<RCString> myTextLines;
    time_t seconds;
    seconds = time(&seconds);
    tm* currentTime;
    currentTime = localtime(&seconds);
    ostrstream os;
    os << "CASETOOL, Filename: " << filename << ", Date: ";
    // the number for the month is 1 to small -> increment by one
    os << currentTime->tm_mday << "." << (currentTime->tm_mon + 1) << "." << currentTime->tm_year;
    os << ", Time: " << currentTime->tm_hour << ":";
    // correct leading 0 when minutes have only one and not the needed 2 digits
    if (currentTime->tm_min < 10) {
      os << "0";
      };
    os << currentTime->tm_min << ", User: " << getlogin();
    RCString footer(os);
    myTextLines.append(footer);
    TextBox2D* myTextBox = new TextBox2D(myTextLines); 
    myTextBox->setPosition(Vector2D(lowerleft.x(), lowerleft.y() - myTextBox->calculateHeight() ));
    myTextBox->setWidth(upperright.x() - lowerleft.x());
    myTextBox->appendTexture(BlackTexture->copy());
    myTextBox->appendTexture(BlackGLTexture->copy());
    myWorld.getObjects()->adoptObject(myTextBox);
 
    myWorld.getObjects()->computeBounds();
    
    };

  delete BlackGLTexture;
  delete BlackTexture;

  // PrintWorld
  if(flags['w']) {
    PrintWorld2D myPrinter;
    myPrinter.incLevel();
    myPrinter.incLevel();
    myPrinter.incLevel();
    myPrinter.incLevel();
    myPrinter.execute(&myWorld);
    };
    
  // prepare camera and viewing when needed
  Camera2D* myCamera;
  Viewing2D* myViewing;
  
  if (flags['b'] || flags['g'] || flags['p']) {
    // output to bitmap or glviewer
    int myBorder = 15;
    int size;
    Vector2D ll = myWorld.getObjects()->getBounds().getMin() - Vector2D(myBorder,myBorder);
    Vector2D ur = myWorld.getObjects()->getBounds().getMax() + Vector2D(myBorder,myBorder);
    Real dx = ur.x()-ll.x();
    Real dy = ur.y()-ll.y();
      
    myCamera = new Camera2D;
    myCamera->setBackground(Color(1,1,1));
    myViewing = myCamera->getViewing();

    // scale to a specified window
    if (flags['s'] || flags['S']){
      if (flags['s']) {
        size = 777;
        }
      else {
        size = atoi(options['S'].chars());
        };
   
    cout << "Size: " << size << "\n";
    
      // display centered in a window of size * size pixels
      if (dx > dy) {
        // center landscape in square 
        myViewing->setWindow(Vector2D(ll.x(), ll.y()-(dx-dy)/2),
                             Vector2D(dx, dx));
        }
      else {
        // center portrait in square
        myViewing->setWindow(Vector2D(ll.x()-(dy-dx)/2, ll.y()),
                             Vector2D(dy, dy));
        };
      myViewing->setResolution(size, size);
      }
    else {
      myViewing->setWindow(ll, Vector2D(dx, dy) );
      // display pixel by pixel
      //myViewing->setResolution(int (dx) + 2*myBorder,
      //                         int (dy) + 2*myBorder);
 
      myViewing->setResolution(int(dx), int(dy));

      };
    myWorld.getObjects()->adoptObject(myCamera);  
    };

  // Bitmap
  if (flags['b']) {
    cout << "STARTED PPM OUTPUT ... ";
    cout.flush();
    World2D* generatedPixmap = NULL;
    Rasterizer rasterizer;
    generatedPixmap = rasterizer.execute(&myWorld);
    // Write image(s)
    PPMWriter myPPMWriter(outfile + ".ppm");
    myPPMWriter.execute(generatedPixmap);
    delete generatedPixmap;
    cout << "ENDED PPM OUTPUT\n";
    };

  // Postscript
  if (flags['p']) {
    cout << "STARTED PS OUTPUT ... ";
    cout.flush();
    cout << "\n\nPS Viewing Details:\n";
    cout << "  Resolution: " << myViewing->getResolutionX() << " x " << myViewing->getResolutionY() << "\n";
    cout << "  Window Origin: " << myViewing->getWindowOrigin() << " Size: " << myViewing->getWindowSize() << "\n\n";
    PSWriter2D myPSWriter(outfile + ".ps");
    myPSWriter.execute(&myWorld);
    cout << "ENDED PS OUTPUT\n";
    };

  //  Start GL displaying of scene
  // has to be at the end of the program !!!
  if (flags['g']) {
    cout << "STARTED GL VIEWER ... \n\n";
    cout.flush();
    GLViewer2D viewer;
    viewer.execute(&myWorld);
    cout << "ENDED GL VIEWER\n";
    };
  
  cout << "\n\n";

  return 0;
} // end of main



// ---------------------- useful utilities ----------------------------

void parseCmdLine(int argc, char* argv[])
{
  // reset all flags to false
  for (int i=0; i < 256; i++) {
    flags[i] = false;
    options[i] = "";
    };

  int i = 1;
  // analyse every argument of the command line
  while (i <  argc) {
    RCString flagString("");
    // analyse flags if first char is a -
    if (argv[i][0] == '-') {
      flagString = argv[i];
      // parameters -O, -S and -I demand 1 parameter
      // and have to be the only flag after the -
      if ((flagString.length() == 2) &&
          ((argv[i][1] == 'O') || (argv[i][1] == 'S') || (argv[i][1] == 'I'))) {
        if ((i+1) < argc) {
          flags[argv[i][1]] = true;
          if (argv[i][1] == 'I') {
            ostrstream os;
            os << options[argv[i][1]];
            if (options[argv[i][1]].length() > 0) {
              os << " ";
              };
            os << argv[i+1];
            RCString tmp(os);
            options[argv[i][1]] = tmp.chars();
            }
          else {
            options[argv[i][1]] = argv[i+1];
            };
          i++;  // skip flag
          i++;  // skip option
          }
        else {
          ostrstream os;
          os << "[casetool:parseCmdLine]: Parameter " << argv[i];
          os << " needs one additional parameter, but there's none\n";
          Report::error(os);
          };      
        }    
      else {
        // h: Check Help flag
        if (strchr(flagString.chars(), 'h') != NULL) {
          usage(argv[0]);
          exit(0);       
          };
        // d: Check Debug flag 
        if (strchr(flagString.chars(), 'd') != NULL) {
          flags['d'] = true;
          };
        // v: Check Verbose flag 
        if (strchr(flagString.chars(), 'v') != NULL) {
          flags['v'] = true;
          };
        // i: Check Include flag 
        if (strchr(flagString.chars(), 'i') != NULL) {
          flags['i'] = true;
          };
        // Check Output Flags (may be used together)
        // if Bitmap or Postscript Output is choosen
        // I disable the GL Viewer. This one can be
        // reabled with the additional option g
        // p: PS File Output
        if (strchr(flagString.chars(), 'p') != NULL) {
          flags['p'] = true;
          };
        // b: PPM File Output
       if (strchr(flagString.chars(), 'b') != NULL) {
          flags['b'] = true;
          };
        // g: GL Viewer (default)
        if (strchr(flagString.chars(), 'g') != NULL) {
          flags['g'] = true;
          };
        // w: Check PrintOfWorld Flag
        if (strchr(flagString.chars(), 'w') != NULL) {
          flags['w'] = true;
          };
        // s: Check Scaling Flag
        if (strchr(flagString.chars(), 's') != NULL) {
          flags['s'] = true;
          };
        // Check Renderer Flags (only one at a time)
        // C: C++ Renderer
        if (strchr(flagString.chars(), 'C') != NULL) {
          flags['C'] = true;
          flags['U'] = false;
          // no display, postscript or bitmap output possible
          flags['g'] = false;
          flags['b'] = false;
          flags['p'] = false; 
          }
        // U: UM Renderer (default)
        else {
          flags['U'] = true;
          flags['C'] = false;
          }
        i++; // skip to next flag
        };
      }
    else {
      filename = argv[i];
      i++; // skip filename to next parameter
      };
    }; // end while
    
    // check for a renderer
    if ((flags['C'] == false) && (flags['U'] == false)) {
      flags['U'] = true;
      };
      
    // check for a output device
    if ((flags['C'] == false) && (flags['p'] == false) && 
        (flags['b'] == false) && (flags['g'] == false)) {
      flags['g'] = true;
      };
      
    // check scaling flag
    if ((flags['s'] == false) && (flags['S'] == false)) {
      flags['s'] = true;
      };
          
} // end parseCmdLine


void usage(const RCString& name)
{
  cerr << "Usage: " << name << " [-hdigpbwCUs] [-S number] [-I includepath] [-O out-file] [in-file]\n";
  cerr << " where:\n";
  cerr << "  in-file  : (optional) filename of input\n";
  cerr << "  h        : (optional) shows this message\n";
  cerr << "  d        : (optional) enable debug messages of the parser\n";
  cerr << "  v        : (optional) enable the verbose messages\n";
  cerr << "  i        : (optional) enable the standard includes\n";
  cerr << "  g        : (default)  use the GL viewer\n";
  cerr << "  p        : (optional) use PS File output\n";
  cerr << "  b        : (optional) use PPM File output\n";
  cerr << "  w        : (optional) Print the World\n";
  cerr << "  C        : (optional) use the C++ Renderer\n";
  cerr << "  U        : (default)  use the UM Renderer\n";
  cerr << "  s        : (default)  scale to 777 * 777 pixel window\n";
  cerr << "  S nbr    : (optional) scale to nbr * nbr pixel window\n";
  cerr << "  I path   : (optional) use additional path for include files\n";
  cerr << "  O file   : (optional) use file for output files\n";  
  cerr << "\n";
}

#else // HAVE_OPENGL -----------------------------------------------------------

#include <stream.h>

int main ()
{
  cerr << "\nThis application needs the OpenGL graphics package.\n" 
       << "When compiling this application your site was \n"
       << "configured not to use OpenGL.\n\n";
}

#endif // HAVE_OPEN
