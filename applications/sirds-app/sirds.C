/*
 * $RCSfile: sirds.C,v $
 *
 * Copyright (C) 1996, Lorenz Ammon <ammon@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: sirds.C,v 1.1 1996/08/16 13:10:57 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <string.h>  // strcmp()
#include <stdlib.h>  // atoi()

#include "booga/base/Statistic.h"
#include "booga/base/StatisticUtilities.h"
#include "booga/pixmapOp/ImageReaders.h"
#include "booga/component/BSDL3DParser.h"
#include "booga/component/BSDLParserInit.h"
#include "booga/component/PPMWriter.h"
#include "booga/component/PrintWorld3D.h"
#include "booga/component/SirdsRenderer.h"

static void usage(char* name);

int main(int argc, char* argv[])
{

  initBSDLParserGlobalNS();
  initBSDLParser3DNS();

  RCString sirdsRCS, artefactsRCS, bsdlRCS, patternRCS;
  AbstractPixmap *patternPixmap = NULL;

  // Arguments

  // Files
  char *bsdlFileName= NULL;
  char *sirdsFileName= NULL;
  char *patternFileName= NULL;
  char *artefactsFileName= NULL;
    
  // Switches
  bool verbose= false;   // Ausgabe von Debug-Informationen ? ... nein
  bool removal= false;   // Artefakt-Removal durchfuehren ?  ... nein
  
  // Parameter fuer SirdsRenderer-Algorithmus
  Real distanceToImagePlane= 40;   // Abstand des Augenmittelpunktes zur Bildeben in cm
  int dpi= 108;   // Dots Per Inch
  Real eyeSeparation= 6.4;   // Augenabstand in cm
  Real mu= 0.5;

  // Parameter fuer den ArtefactRemoval-Algorithmus
  int artefactsWindowSize= 5;   //  Maximale Artefaktbreite
  int artefactsDepthDelta= 10;   // Maximale Tiefe auf die sich der Artefakt erstrecken darf
  int artefactsPerWindow= 3;   // Anzahl Punkte im Raum, die einen Artefakt ausmachen        
  Real enlargeViewVolumeBy= 0.0;   // Erwieitert das Viewvolume, das auf Artefakte untersucht wird 
  int maxArtefactsTests= 7;   //  Maximale Anzahl Versuche, in einer Zeile eine Artefaktewertung  ... 
  int artefactsToAccept= 0;   //  ... zu erreichen, die den hier angegebenen Wert nicht uebersteigt 
  int colourIndexStep= 2;   // Sprung im Muster in Pixeln nach negativem Artefaktetest


  // Parse arguments
  if ((argc == 2 && !strcmp(argv[1], "-h")) || argc>32) {
    usage(argv[0]);
    exit(0);
  }
   
  bsdlFileName = argv[1];
   
  int cur = 2;
    
  while (cur<argc && argv[cur][0]=='-') {
 
    if (!strcmp(argv[cur],"-o")) {
      sirdsFileName = argv[++cur];
      cur++;
      continue;
    }
    
    if (!strcmp(argv[cur],"-p")){
      patternFileName = argv[++cur];
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-af")){
      artefactsFileName = argv[++cur];
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-v")){
      verbose = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-ar")){
      removal = true;
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-D")) {
      distanceToImagePlane = atof(argv[++cur]);
      cur++;
      continue;
    }
  
    if (!strcmp(argv[cur],"-d")) {
      dpi = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-E")) {
      eyeSeparation = atof(argv[++cur]);
      cur++;
      continue;
    }
  
    if (!strcmp(argv[cur],"-m")) {
      mu = atof(argv[++cur]);
      cur++;
      continue;
    }
  
    if (!strcmp(argv[cur],"-aws")) {
      artefactsWindowSize = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-apw")) {
      artefactsPerWindow = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-add")) {
      artefactsDepthDelta = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-ata")) {
      artefactsToAccept = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-amt")) {
      maxArtefactsTests = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-aps")) {
      colourIndexStep = atoi(argv[++cur]);
      cur++;
      continue;
    }

    if (!strcmp(argv[cur],"-aevv")) {
      enlargeViewVolumeBy = atof(argv[++cur]);
      cur++;
      continue;
    }
  





    break;
    
  }  
        
   
  if (bsdlFileName != NULL) {   // BSDL-Inputfilename  angegeben ?
    bsdlRCS= bsdlFileName;     // ... dann in RCString ueberfuehren
  }

  if (sirdsFileName != NULL) {   // Ausgabename angegeben ?
    sirdsRCS= sirdsFileName;   // ... dann in RCString ueberfuehren
  }

  //
  // Read scene
  //
  
  World3D* world3D = new World3D;
  BSDL3DParser parser;
  parser.setFilename(bsdlRCS);
  
  setExecTime(parser.execute(world3D), "rendersirds: 1: Parsing");
  
  //
  // Print scene
  //
  //if (verbose) {
  //  PrintWorld3D printer(std::cerr);
  //  printer.execute(world3D);
  //}

  //
  // set arguments
  //
 
  SirdsRenderer rendersirds;   // SirdsRenderer initialisieren
  
  rendersirds.setVerbose(verbose);
  rendersirds.setArtefactsRemoval(removal);
  
  rendersirds.setDistanceToImagePlane(distanceToImagePlane);
  rendersirds.setDpi(dpi);
  rendersirds.setEyeSeparation(eyeSeparation);
  rendersirds.setMu(mu);
   
  rendersirds.setArtefactsWindowSize(artefactsWindowSize);
  rendersirds.setArtefactsDepthDelta(artefactsDepthDelta);
  rendersirds.setArtefactsPerWindow(artefactsPerWindow);
  rendersirds.setEnlargeViewVolumeBy(enlargeViewVolumeBy);
  rendersirds.setMaxArtefactsTests(maxArtefactsTests);
  rendersirds.setArtefactsToAccept(artefactsToAccept);
  rendersirds.setArtefactsPixelStep(colourIndexStep);




  if (artefactsFileName != NULL) {   // Artefakt-Filename angegeben ?
    artefactsRCS= artefactsFileName;   // In RCString ueberfuehren
    rendersirds.setArtefactsFileName(artefactsRCS);   // Die Angabe eines Artefakt-Filenames
    // veranlasst die Berechnung des Artefakt-Bildes
  }
  
  if (patternFileName != NULL) {   // Muster-Filename angegeben ?
    AbstractPixmap* pixi = ImageReader::createPixmap(patternFileName);
    
    if (pixi == NULL) {
      Report::recoverable("[sirds] could not read the pixmap " 
                          + RCString(patternFileName)
                          + ". Writing random dots");
    } 
    else {
      rendersirds.setPatternPixmap(pixi);   // Die Uebrgabe eines Musters veranlasst den Renderer
      // das Bild mit diesem Muster zu ueberziehen 
    }
  }
   
  //
  // Process scene
  //
     
  World2D* world2D;
  setExecTime(world2D=rendersirds.execute(world3D), "rendersirds: 2: Rendering");   // Render 

  //
  // Write image(s)
  //
  PPMWriter writer(sirdsRCS);
  setExecTime(writer.execute(world2D), "rendersirds: 3: Writing output");

  delete world3D;
  delete world2D;
  if (patternFileName != NULL) delete patternPixmap;
  //
  // Write out statistics
  //
  Statistic::print();

  return 0;
}

void usage(char* name)
{
  std::cerr << "Usage: " << name << " <BSDL input file> [options]\n";
  std::cerr << " where options:\n";
  std::cerr << "         -o outfile       : Generated SIRDS (PPM output file)\n";
  std::cerr << "         -p patternfile   : Colourfy SIRDS with pattern\n";
  std::cerr << "         -af artifactfile : Compute artefacts (PPM output file)\n";
  std::cerr << "         -v               : Display information while running (verbose)\n";
  std::cerr << "         -ar              : Do artefact removal\n";
  std::cerr << "         -D float         : Distance to the image plane (in cm)\n";
  std::cerr << "         -d int           : Dots per inch used to print or view the SIRDS\n";
  std::cerr << "         -E float         : Distance between the eyes (eye separation in cm)\n";
  std::cerr << "         -m float         : Indicates the view volumes's depth to be rendered (mu)\n";
  std::cerr << "         -aws int         : Maximum artefact size (in pixel)\n";
  std::cerr << "         -apw int         : Number of artefact pixels needed for an artefact\n";
  std::cerr << "         -add int         : Number of depth levels allowed in an artefact\n";
  std::cerr << "         -ata int         : Artefacts value to accept without artefact removal\n";
  std::cerr << "         -amt int         : Maximum number of tests while artefact removal\n";
  std::cerr << "         -aps int         : Step that much pixels in pattern while artefact removal\n";
  std::cerr << "         -aevv float      : Enlarge view volume by\n";
}

