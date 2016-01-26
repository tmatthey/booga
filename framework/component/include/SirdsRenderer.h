/*
 * $RCSfile: SirdsRenderer.h,v $
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
 *  $Id: SirdsRenderer.h,v 1.1 1996/08/16 13:10:58 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _SirdsRenderer_H
#define _SirdsRenderer_H

#include "booga/component/PixmapRenderer.h"

//____________________________________________________________________ SirdsRenderer

typedef  int SirdsResolution;
typedef  Real ColourIndex; 
struct ColourListElement { 
  SirdsResolution left;
  SirdsResolution right;
  ColourIndex  colourIndex;
};
        
typedef ColourListElement *ColourList;

class SirdsRenderer : public PixmapRenderer {
declareRTTI(SirdsRenderer);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  SirdsRenderer();
 
private:
  SirdsRenderer(const SirdsRenderer&);             // No copies.

public:
  // virtual ~SirdsRenderer();                     // Use default version.

private:
  SirdsRenderer& operator=(const SirdsRenderer&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class SirdsRenderer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

public:
   void setVerbose( bool verbose);
   void setArtefactsRemoval(bool removal);
   
   void setDistanceToImagePlane( Real distanceToImagePlane);
   void setDpi(int dpi);
   void setEyeSeparation(Real eyeSeparation);
   void setMu(Real mu);
   
   void setArtefactsWindowSize(int artefactsWindowSizeCont);
   void setArtefactsDepthDelta(int artefactsDepthDelta);
   void setArtefactsPerWindow(int artefactsPerWindow);
   void setEnlargeViewVolumeBy(Real enlargeViewVolumeBy);
   void setMaxArtefactsTests(int maxArtefactsTest);
   void setArtefactsToAccept(unsigned long int artefactsToAccept);
   void setArtefactsPixelStep( Real colourIndexStep);
   
   void setArtefactsFileName(const RCString& artefactsFilename);
   
   void setPatternPixmap(AbstractPixmap *patternPixmap);
   
   SirdsResolution getResolutionX( void );
   SirdsResolution getResolutionY( void );
    
protected:
   void spreadColour( SirdsResolution, ColourIndex, ColourList);
   void initArtefact();
   bool getTestBoundaries( int &minDeltaX, int &maxDeltaX, int xLeft, int xRight);
   unsigned long artefactCount( ColourList colourList, bool writeToFile, SirdsResolution y);
   unsigned long artefactRemoval( ColourList colourList, 
                                  ColourIndex &colourIndexOriginal,SirdsResolution spreadAt, SirdsResolution lineY);
   void colourLine(ColourList colourList, SirdsResolution lineY, bool doRemoval);        
                                
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Component<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
protected:
  virtual bool doExecute();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

protected:

// Switches
   bool verbose;   // Debug Informationen ausgeben
   bool colouring;   // Einfaerben mit Muster oder schwarz-weiss
   bool artefacts;   // Artefaktebild schreiben
   bool removal;   // Artefakte entfernen
  
// Parameter fuer SirdsRenderer-Algorithmus
   Real distanceToImagePlane;   // Abstand des Augenmittelpunktes zur Bildeben in cm
   int dpi;   // Dots Per Inch
   Real eyeSeparation;   // Augenabstand in cm
   Real mu;

// Parameter fuer den ArtefactRemoval-Algorithmus
   int artefactsWindowSizeCont;   //  Maximale Artefaktbreite
   int artefactsDepthDelta;   // Maximale Tiefe auf die sich der Artefakt erstrecken darf
   int artefactsPerWindow;   // Anzahl Punkte im Raum, die einen Artefakt ausmachen        
   Real enlargeViewVolumeBy;   // Erwieitert das Viewvolume, das auf Artefakte untersucht wird 
   int maxArtefactsTests;   //  Maximale Anzahl Versuche, in einer Zeile eine Artefaktewertung  ... 
   unsigned long int artefactsToAccept;   //  ... zu erreichen, die den hier angegebenen Wert nicht uebersteigt 
   ColourIndex colourIndexStep;   // Sprung im Muster in Pixeln nach negativem Artefaktetest

// Daten aus dem globalen Scope des urspruenglichen ANSI-C-Programmes
   // Bilder
   SirdsResolution xResolution, yResolution;   // Aufloesung des Ausgabebildes
   SirdsResolution patternXRes, patternYRes;  // Aufloesung des Musters
   AbstractPixmap *artefactsPixmap;   // Artefakte-Ausgabe-Pixmap
   const AbstractPixmap *patternPixmap;   // Pixap des Musters fuer das Einfaerben
   RCString artefactsFileName;
  
  // SirdsAlgorithmus
   SirdsResolution backClippingPlaneSeparation;  // Abstand korrespondierender Punke auf der  ...
   SirdsResolution frontClippingPlaneSeparation;   // ... hinteren, vorderen ClippingEbene
   int depthLevels;   // Anzahl moeglicher Tiefenstufen im Ausgabebild
   
   //  ArtefactRemoval-ALgorithmus
   int artefactsTestDepthLevels;    // Anzahl Tiefenstufen im erweiterten Viewvolume
   int artefactsWindowSize;   // Fenstergroesse fuer ebene Artefakte (2*WindowSizeCont) 
   SirdsResolution halveFarestSeparation;
   SirdsResolution halveNearestSeparation;
   
   //  Anker der Datenstrukturen des ArtefactRemoval-Algorithmus
   int *artefactsTestLine;
   int *artefactsTestLineCont;
   int **artefactsWindow;

};

#endif // _SirdsRenderer_H

