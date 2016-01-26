/*
 * $RCSfile: SirdsRenderer.C,v $
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
 *  $Id: SirdsRenderer.C,v 1.2 1996/09/13 12:04:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include <sstream>  // std::stringstream
#include "booga/base/Statistic.h"
#include "booga/base/PixmapOf.h"
#include "booga/object/Camera3D.h"
#include "booga/object/Primitive3D.h"
#include "booga/object/Path3D.h"
#include "booga/object/Ray3D.h"
#include "booga/object/Ray3DFactory.h"
#include "booga/object/Viewing3D.h"
#include "booga/object/Pixmap2D.h"
#include "booga/component/PPMWriter.h"
#include "booga/base/RCString.h"
#include "booga/component/SirdsRenderer.h"
#include <math.h>   // drand48

//____________________________________________________________________ SirdsRenderer

implementRTTI(SirdsRenderer, PixmapRenderer);

SirdsRenderer::SirdsRenderer()
{
   verbose= false;   // ohne Debug-Information
   colouring= false;   // nur schwarz-weiss
   artefacts= false;   // Kein Artefakte-Bild speichern
   removal= false;  // Kein Artefact-Removal

   distanceToImagePlane = 40;   // Abstand des Augenmittelpunktes zur Bildeben in cm
   dpi = 108;   // Dots Per Inch
   eyeSeparation = 6.4;   // Augenabstand in cm
   mu = 0.5;

   artefactsWindowSizeCont = 5;   //  Maximale Artefaktbreite
   artefactsDepthDelta =10;   // Maximale Tiefe ueber die sich der Artefakt erstrecken darf
   artefactsPerWindow = 3;   // Anzahl Punkte im Raum, die einen Artefakt ausmachen        
   enlargeViewVolumeBy = 0.0;   // Erwieitert das Viewvolume, das auf Artefakte untersucht wird 
   maxArtefactsTests = 7;   //  Maximale Anzahl Versuche, in einer Zeile eine Artefaktewertung  ... 
   artefactsToAccept = 0;   //  ... zu erreichen, die den hier angegebenen Wert nicht uebersteigt 
   colourIndexStep= 2;   // Sprung im Muster in Pixeln nach positivem Artefaktetest

   artefactsFileName =("artefacts.ppm");   // Name des Artefakten-AusgabeBildes

}

// Die ganze Punktemenge gleicher Farbe von x mit colourIndex einfaerben 

void SirdsRenderer::spreadColour( SirdsResolution x, ColourIndex colourIndex, ColourList colourList)
{
    SirdsResolution xi;
	
       for (xi= x; colourList[xi].right != xi; xi= colourList[xi].right)
          colourList[xi].colourIndex = colourIndex;
          colourList[xi].colourIndex = colourIndex;

       for (xi= x; colourList[xi].left != xi; xi= colourList[xi].left)
         colourList[xi].colourIndex = colourIndex;
         colourList[xi].colourIndex = colourIndex;
}


// Datenstrukturen fuer Artefakte allozieren, Parametergrenzen ueberpruefen und
// verwendete Groessen ableiten

void SirdsRenderer::initArtefact()
{

// Parametergrenzen testen

   if (artefactsDepthDelta < 0)
      artefactsDepthDelta = 1;

   if (artefactsWindowSizeCont < 0)
      artefactsWindowSizeCont= 1;

   if (artefactsPerWindow > artefactsWindowSizeCont)
      artefactsPerWindow = artefactsWindowSizeCont;

// Verwendete Groessen aus den Parametern ableiten 

   artefactsWindowSize= 2 * artefactsWindowSizeCont;	

   halveFarestSeparation = (SirdsResolution) (ceil( (1 + enlargeViewVolumeBy) *
                                            backClippingPlaneSeparation / 2.0));
   halveNearestSeparation = (SirdsResolution) (floor( (1 - enlargeViewVolumeBy) * 
                                            frontClippingPlaneSeparation / 2.0));

   artefactsTestDepthLevels= 2*halveFarestSeparation - 2*halveNearestSeparation +1;

    if (artefactsDepthDelta >= artefactsTestDepthLevels) 
       artefactsDepthDelta = artefactsTestDepthLevels -1;

// Datenstrukturen fuer Artefaktebehandlung allozieren und initialisieren

   artefactsWindow= new int* [artefactsWindowSize];
   for (int i=0; i < artefactsWindowSize; i++) {
      artefactsWindow[i]= new int [artefactsTestDepthLevels];
      for (int j=0; j < (artefactsTestDepthLevels); j++)
         (artefactsWindow[i])[j] = 0;
   }
	
   artefactsTestLine= new int [artefactsTestDepthLevels];
   for (int k=0; k < (artefactsTestDepthLevels); k++)
      artefactsTestLine[k]= 0;

   artefactsTestLineCont= new int [artefactsTestDepthLevels];
   for (int j=0; j < (artefactsTestDepthLevels); j++)
       artefactsTestLineCont[j]= 0;

}


// Minimal und maximal moeglicher Abstand zwischen korrespondierenden Bilpunkten eines bestimmten
// Sehstrahls bestimmen

bool SirdsRenderer::getTestBoundaries( int &minDeltaX, int &maxDeltaX, int xLeft, int xRight)
{

// Moegliche Abstaende nur durch ViewVolume begrenzt

   minDeltaX = halveNearestSeparation;
   maxDeltaX = halveFarestSeparation;

   if ( ((xLeft + halveFarestSeparation) <= (xResolution -1)) &&
         (xRight >= halveFarestSeparation) )
      return true;


// Moegliche Abstaende nicht im ViewVolume

   if ( ((xLeft + halveNearestSeparation) > (xResolution -1)) || (xRight < halveNearestSeparation) )
      return false;


// Moegliche Abstaende durch linken oder rechten Bildrand begrenzt

   if ( (xLeft + halveFarestSeparation) > (xResolution -1) ) 
      maxDeltaX = xResolution -1 - xLeft;
  
   if ( (xRight < halveFarestSeparation) && (xRight < maxDeltaX) ) 
      maxDeltaX = xRight;

   return true;

}


// Die Summe der Artefakte-Strafpunkte der Zeile colourList bestimmen
// Die gefundenen Artefakte in das Artefakte-Bild schreiben, falls dies writeToFile fordert
// Details sind in der Dokumentation nachzulesen

unsigned long int SirdsRenderer::artefactCount( ColourList colourList, 
                                                 bool writeToFile, SirdsResolution y)
{
   Real x;   // Position des bearbeiteten Sehstarhls
   SirdsResolution xLeft, xRight;  
   int deltaX, minDeltaX, maxDeltaX;
   ColourIndex colourIndexDelta;
   ColourIndex colourIndexLeft, colourIndexRight;

   int artefactsWindowPosition = 0;
   int artefactsWindowPosCont = artefactsWindowSizeCont -1;
   int artefactsInTestLine = 0;
   int artefactsInTestLineCont = 0;
   int artefactDepthLineIndex = 0;
   unsigned long int artefactsInScanLine= 0;   //Aufsummierte Artefakte-Strafpunkte der Zeile


   for (x=0; x <= xResolution -1; x= x + 0.5) {   
   
      for (int i= 0 ; i < artefactsTestDepthLevels; i++) {   
      
         if ( (artefactsWindow[artefactsWindowPosition])[i] != 0) {
            artefactsTestLine[i] -= 1;
            artefactsInTestLine -= 1;
         }

         if ( (artefactsWindow[artefactsWindowPosCont])[i] != 0 ) {
            artefactsTestLineCont[i] -= 1;
            artefactsInTestLineCont -= 1;
         }

         (artefactsWindow[artefactsWindowPosition])[i] = 0;

      }
			

      if (x == (SirdsResolution) x)
         xLeft =  xRight = (SirdsResolution) x;
      else {
         xLeft = (SirdsResolution) x;
         xRight = xLeft + 1;
      }
		
      if (getTestBoundaries (minDeltaX, maxDeltaX, xLeft, xRight)) {
			
         for (deltaX= minDeltaX; deltaX <= maxDeltaX; deltaX++) {
				
            if ( ((colourIndexLeft = colourList[xRight - deltaX].colourIndex) >= 0) &&
   		  ((colourIndexRight = colourList[xLeft + deltaX].colourIndex) >= 0) ) {
 
               colourIndexDelta = fabs (colourIndexRight - colourIndexLeft);
				
               if ( ((colourIndexDelta < 0.5 ) || (colourIndexDelta > (patternXRes-0.5)) ) && 
                    ( colourList[xRight-deltaX].right != (xLeft + deltaX) ) ) {

                  artefactDepthLineIndex= ( ((xLeft != xRight) ? 2*deltaX -1 : 2*deltaX) - 
                                             2*halveNearestSeparation); 

                  (artefactsWindow[artefactsWindowPosition])[artefactDepthLineIndex]= 1;

                   artefactsTestLine[artefactDepthLineIndex] += 1;
                   artefactsInTestLine += 1;
                   artefactsTestLineCont[artefactDepthLineIndex] += 1;
                   artefactsInTestLineCont += 1;
						
                   if (writeToFile){
                     float depth= 0.3+(0.7/(artefactsTestDepthLevels -1)*artefactDepthLineIndex);                         
                     artefactsPixmap->setPosition((int) (2*x),y);
                     artefactsPixmap->setColor(depth);
 
                   }
               }
            }

         }

      }



      if (artefactsInTestLine >= artefactsPerWindow) {

         int sum = 0;
         int i= 1;
			
         if (xLeft == xRight)
            i= 0;

         for (int j=0; j < 3; j++) {
            sum = sum + artefactsTestLine[i];
            i++;
            sum = sum +	(int) floor(0.5*artefactsTestLine[i]) ;
            i++;
         }


         do {
            if (sum >= artefactsPerWindow)
               artefactsInScanLine++;

            sum = sum - (int) floor(artefactsTestLine[i-6] + (0.5*artefactsTestLine[i+1-6]) );
            sum = sum + artefactsTestLine[i];
            i++;
            if (i < artefactsTestDepthLevels)
               sum = sum + (int) floor(0.5*artefactsTestLine[i]);
            i++;
         }
         while (i < artefactsTestDepthLevels);

         if (sum >= artefactsPerWindow)
            artefactsInScanLine++;
	
      }

      if (artefactsInTestLineCont >= artefactsPerWindow) {

         int sum = 0;
         int i;

         for (i=0; i < artefactsDepthDelta; i++)
            sum = sum + artefactsTestLineCont[i];

         do {
	
            if (sum >= artefactsPerWindow)
               artefactsInScanLine++;
		
            sum = sum - artefactsTestLineCont[i-artefactsDepthDelta];
            sum = sum + artefactsTestLineCont[i];
            i++;
         }
         while (i < artefactsTestDepthLevels);

         if (sum >= artefactsPerWindow)
         artefactsInScanLine++;
	
      }


      artefactsWindowPosition= (artefactsWindowPosition +1) % artefactsWindowSize;
      artefactsWindowPosCont= (artefactsWindowPosCont +1) % artefactsWindowSize;
   }

   return artefactsInScanLine;
}	



// Waehle fuer die bei spreadAt einzufaerbende Punktemenge gleicher Farbe eine Farbe, die moeglichts wenig
// Artefakte erzeugt und faerbe diese Menge damit ein.

unsigned long int SirdsRenderer::artefactRemoval( ColourList colourList,
                                                  ColourIndex &colourIndexOriginal, 
                                                  SirdsResolution spreadAt, SirdsResolution lineY)
{

     static SirdsResolution actualY=0;
     static unsigned long int actualArtefactsToAccept= artefactsToAccept;

   unsigned long int minArtefacts;   // Minimale Anzahl Artefakte-Strafpunkte der Zeile nach den bisherigen Versuchen
   unsigned long int artefacts;   // Artefakte-Strafpunkte des aktuellen Versuchs
   ColourIndex colourIndex;   // Farbe des aktuellen Versuchs
   ColourIndex minArtefactsColourIndex;  // Farbe mit der bisher minimalen Anzahl Artefakte-Strafpunkte

     if ( lineY != actualY ) {
         actualY = lineY;
         actualArtefactsToAccept = artefactsToAccept;
     }


   minArtefacts= artefactCount(colourList, false, 0);   // Momentane Anzahl Artefakte-Strafpunkte ist bei Beginn minimal
   minArtefactsColourIndex= colourIndexOriginal;	// zugehoerige Farbe

   if (minArtefacts > actualArtefactsToAccept) {   // Zuviele Strafpunkte ?

      int i= 1;   // Ja -> suche eine bessere Farbe
      do {

        // Eine benachbarte Musterfarbe waehlen	...		
			
         colourIndex= colourIndexOriginal +
                        ( ( (drand48() >= 0.5) ? 1 : -1 ) * (i * colourIndexStep) );

         if (colourIndex >= patternXRes)
            colourIndex= colourIndex - patternXRes;
         if (colourIndex < 0)
            colourIndex= colourIndex + patternXRes;

         spreadColour(spreadAt, colourIndex, colourList);   // ... und die Punktemenge geleicher Farbe bei spreadAt damit einfaerben

         artefacts= artefactCount(colourList, false, 0);   // Anzahl Strafpunkte dieses Versuchs ermitteln

         // War dieser Versuch besser als alle bisherigen

         if (artefacts < minArtefacts) {   // Ja
           minArtefacts= artefacts;   // Strafpunkte des aktuellen Versuchs sind neues Minimum
           minArtefactsColourIndex= colourIndex;   // zugehoerige Frabe
         }

         i++;   // naechtse Farbe untersuchen ...
         
      // ... es sei denn die maximale Anzahl Versuche wurde Ausgeschoepft oder das aktuelle Strafpunkte-Minimum ist akzeptierbar 
	
      } while ( (minArtefacts > actualArtefactsToAccept) && (i <= maxArtefactsTests) );
		
      if (minArtefacts > artefactsToAccept) {
         actualArtefactsToAccept = minArtefacts;  
         spreadColour(spreadAt, minArtefactsColourIndex, colourList);
      }
   }

   colourIndexOriginal= minArtefactsColourIndex;   // Rueckgabe der veraenderten Farbe ...
   return minArtefacts;   // ... und der Artefaktestrafpunkte der dieser Farbe
				
}



// Faerbe eine Zeile mit dem vorgegebenen Muster patternPixmap ein. Das Muster wird von der Zeilenmitte aus
// gleichzeitig nach links und nach rechts verbreitet. Wenn doRemoval gesetzt ist, wird ein Artefakt-Removal
// durchgefuehrt

void SirdsRenderer::colourLine(ColourList colourList, SirdsResolution lineY, bool doRemoval)
{

   // Beginne in der Mitte

    SirdsResolution xr= xResolution /2;   // rechter Startunkt fuer das Einfaerben
    SirdsResolution xl= xr-1;  // linker Startpunkt fuer das Einfaerben

    ColourIndex newPixelIndexDelta  = (ColourIndex) (xResolution / (backClippingPlaneSeparation-depthLevels));
    ColourIndex colourIndexr, colourIndexl;
    Real deltaX;

   // Faerbe den rechten Startpunkt mit dem linken Rand des Musters 
    colourIndexr= 0;
    spreadColour( xr, colourIndexr, colourList);   // Faerbe die ganze PunkteMenge gleicher Farbe ein

   // Faerbe den linken Startpunkt mit dem rechten Rand des Musters 
    colourIndexl= (patternXRes -1);
    spreadColour( xl, colourIndexl, colourList);   // Faerbe die ganze PunkteMenge gleicher Farbe ein


   // schiebe den rechten Startpunkt nach rechts, den linken nach links 
    xr++;
    if (xl>0)
        xl--;

   while (xr < xResolution) {   // Solange der rechte Startpunkt nicht den rechten Bidrand erreicht

      if (colourList[xr].colourIndex < 0) {   // Ist der rechte Startpunkt noch ohne Farbe ?


          // Bestimme dem Muster entsprechend eine Farbe ... 
          
          
          deltaX = colourList[xr-1].right - (xr-1);
          if (deltaX > 0) {
             colourIndexr= (colourList[xr-1].colourIndex + (patternXRes/deltaX));
             if (colourIndexr >= patternXRes)
                colourIndexr = colourIndexr - patternXRes;
          }
          else {
             colourIndexr= (colourList[xr-1].colourIndex + newPixelIndexDelta);
             if (colourIndexr >= patternXRes)
                colourIndexr = colourIndexr - patternXRes;
          }
 
          spreadColour( xr, colourIndexr, colourList);   // ... und faerbe die ganze Punktemenge gleicher Farbe so ein

          if (doRemoval) {   // Falls verlangt fuehre einen Artefakt-Removal durch
             artefactRemoval(colourList, colourIndexr, xr, lineY);
          }

      }



      // wie oben, nur fuer den linken Startpunkt
      
      if (colourList[xl].colourIndex < 0) {
	 
        deltaX = (xl+1) - colourList[xl+1].left;
        if (deltaX > 0) {
            colourIndexl= (colourList[xl+1].colourIndex - (patternXRes/deltaX));
            if (colourIndexl < 0)
               colourIndexl = colourIndexl + patternXRes;
         }
         else {
            colourIndexl= (colourList[xl+1].colourIndex -newPixelIndexDelta);
                if (colourIndexl < 0)
                    colourIndexl = colourIndexl + patternXRes;
         }

         spreadColour( xl, colourIndexl, colourList);

         if (doRemoval) {
            artefactRemoval(colourList, colourIndexl, xl, lineY);
         }

     }

   // schiebe den linken Startpunkt weiter nach links, den rechten weiter nach rechts		 
     xr++;
     if (xl>0)  // der linke Startpunkt erreicht den linken Bildrand immer bevor der rechte Startpunkt den rechten Bidrand erreicht
        xl--;
   }

}



bool SirdsRenderer::doExecute()
{
// Ohne Einfaerben mit einem Muster macht ein Artefact-Removal keinen Sinn

  if (!colouring) {
     removal= false;
     artefacts= false;
  }


  // Werte der aktiven View auslesen 

  Vector3D eyeWcs = getCamera()->getViewing()->getEye();   // Augenmittelpunkt
  Vector3D lookAtWcs = getCamera()->getViewing()->getLookat();   // Point of Interest
  Vector3D upWcs = getCamera()->getViewing()->getUp();   // wo ist im Bild oben ?
  Real fovHView = getCamera()->getViewing()->getHFov();   // Horizontaler Sichtwinkel
  Real fovVView = getCamera()->getViewing()->getVFov();   // Vertikaler Sichtwinkel


  // Bild-Koordinatensystem bestimmen
  
  Vector3D imageCenterWcs = eyeWcs + 0.5*(lookAtWcs - eyeWcs);   // Ursprung
  Vector3D imageZDirectionWcs = (lookAtWcs - eyeWcs).normalized();   // Bildtiefe-Richtung
  Vector3D imageXDirectionWcs =  (upWcs * imageZDirectionWcs).normalized();   // Bildbreite-Richtung
  Vector3D imageYDirectionWcs = (imageZDirectionWcs * imageXDirectionWcs).normalized();   // Bildhoehe-Richtung
  
  
  // Koordinatentransformation WCS nach ICS berechnen 
  
  TransMatrix3D tm3WcsToIcs;   // Transformationsmatrix der Koordinatentransformation WCS -> ICS
  tm3WcsToIcs.getIdentity();
  
  tm3WcsToIcs.translate( -imageCenterWcs);   // Verschiebung des ICS in den Ursprungs des WCS
    
  TransMatrix3D csRotation( imageXDirectionWcs[0], imageYDirectionWcs[0], imageZDirectionWcs[0], 
                             imageXDirectionWcs[1], imageYDirectionWcs[1], imageZDirectionWcs[1],
                             imageXDirectionWcs[2], imageYDirectionWcs[2], imageZDirectionWcs[2]);  // Bsiswechselmatrix WCS,ICS
  tm3WcsToIcs = tm3WcsToIcs * csRotation;   // Basiswechsel nach Verschiebung ausfuehren
  
  Real distanceToImagePlaneWu = ((lookAtWcs - eyeWcs).length()) / 2.0;   // Abstand des Augpunktes zur Bildebene in WU
  Real scaleFactor = distanceToImagePlane / distanceToImagePlaneWu;   
  tm3WcsToIcs.scale(scaleFactor,scaleFactor,scaleFactor);   // Abstand zum Bild auf Vorgabe in cm skalieren
  
  Transform3D t3WcsToIcs (tm3WcsToIcs);   // Koordinatentransformation als 3D-Transformation speichern


  // Die ganze Welt in das ICS transformieren und skalieren
   
  Object3D* objListWorld = getWorld()->getObjects();
  for (long i=0; i < objListWorld->countSubobject(); i++) 
    objListWorld->getSubobject(i)->addTransform(t3WcsToIcs);
  objListWorld->computeBounds();


  // Bildparameter bestimmen

  Real imageWidth = 2 * distanceToImagePlane * tan(fovHView / 2.0);   // Bildbreite nach Sichtwinkel und Abstand zum Bild
  Real imageHeight = 2 * distanceToImagePlane * tan(fovVView / 2.0);  // Bildhoehe nach Sichtwinkel und Abstand zum Bild
  xResolution = (int) (rint(imageWidth / 2.54 * dpi));   // Bild-X-Aufloesung nach dpi
  yResolution = (int) (rint(imageHeight / 2.54 * dpi));   // Bild-Y-Aufloesung nach dpi
  Real pixelWidth = imageWidth / xResolution;   // Pixelausdehnung in X-Richtung
  Real pixelHeight = imageHeight / yResolution;   // Pixelausdehnung in Y-Richtung


  // Ausgabe Pixmap initialisieren
  
  delete myPixmap;
  myPixmap = createPixmap(xResolution, yResolution); 
  myPixmap->clearColor(0, 0, 0);
  
  if( (xResolution < 10) || (yResolution < 3) ) {
     Report::recoverable("[SirdsRenderer::doExecute] Image size too small. Nothing rendered !");
     TransMatrix3D invTm3WcsToIcs= t3WcsToIcs.getInvTransMatrix(); 
     objListWorld = getWorld()->getObjects();
     for (long i=0; i < objListWorld->countSubobject(); i++) 
        objListWorld->getSubobject(i)->addTransform(invTm3WcsToIcs);
     objListWorld->computeBounds();

     return false;;
  }

  // Artefakte Pixmap initialisieren
  if (artefacts) { 
     artefactsPixmap = new PixmapOf<RGB> (2*xResolution -1, yResolution);
     artefactsPixmap->clearColor(0.0F);
  }

  // Augenpositionen festlegen
  
//  Vector3D eye(0, 0, -distanceToImagePlane);   // Augenmittelpunkt
  Vector3D eyeLeft(eyeSeparation/2.0, 0, -distanceToImagePlane);   // Linkes Auge 
  Vector3D eyeRight(-eyeSeparation/2.0, 0, -distanceToImagePlane);   // Rechtes Auge


  // kanonische Basis des Bildes

  Vector3D imageXDirection(1,0,0);   // kanonisch
  Vector3D imageYDirection(0,1,0);   // kanonisch
//  Vector3D imageZDirection(0,0,1);   // kanonisch   


  // Bildgeometrie und Lage im Raum
  Vector3D imageCenter(0,0,0);   // Bildmitte liegt im Ursprung des kanonischen Koordinatensystems
  Vector3D pixelXDelta = pixelWidth * imageXDirection;   // Pixelbreite als Vektor
  Vector3D pixelYDelta = pixelHeight * imageYDirection;   // Pixelhoehe als Vektor
  Vector3D lowerLeftCorner = imageCenter + (imageWidth/2.0 * imageXDirection) - (pixelXDelta / 2.0) -
                                (imageHeight/2.0 * imageYDirection) + (pixelYDelta / 2.0);   // Bildecke oben links
  Real backClippingPlaneZ= distanceToImagePlane + (mu * distanceToImagePlane / 2.0);   // Hintere Clipping-Ebene
  Real frontClippingPlaneZ= backClippingPlaneZ - (mu * distanceToImagePlane);  // vordere Clipping-Ebene 
  backClippingPlaneSeparation = (SirdsResolution) rint( (eyeSeparation * backClippingPlaneZ) /
                                      (distanceToImagePlane + backClippingPlaneZ) / 2.54 * dpi );
  frontClippingPlaneSeparation = (SirdsResolution) rint( (eyeSeparation * frontClippingPlaneZ) /
                                      (distanceToImagePlane + frontClippingPlaneZ) /2.54 * dpi);                                     
  depthLevels= backClippingPlaneSeparation - frontClippingPlaneSeparation +1;

 
  // Parameter fuer den Sirds-Algorithmus
  
  int xRight, y;  // (xRight,yResolution-y)-Pixeladresse im Bild
  int xLeft;   // xLeft ist der zu xRight korrespondierende linke Bildpunkt
  Real xLeftIcs;  // das selbe in Bildkoordinaten
  Ray3D *rayRight = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(1,0,0));   // Sehstrahl fuer das rechte Auge
  Vector3D actualImagePixel;   // wo schaut das rechte Auge hin ?    
  Vector3D hitPointOnObject;   // Schnittpunkt des rechten Sehstrahls mit der Welt 
  Ray3D *rayLeft = Ray3DFactory::createRay(Vector3D(0,0,0), Vector3D(1,0,0));   // Sehstrahl fuer das linke Auge
  Real t;   // Strahlen-Parameter
  bool verdeckt;   // Objektpunkt fuer das linke Auge verdeckt ?
  bool hitFrontClippingPlane;   // liegt der Schnittpunkt auf der vorderen Clipping Ebene

  ColourList colourList = new ColourListElement[xResolution];   // Punktemengen gleicher Farbe
  bool *hitsLeft = new bool[xResolution];   // bereits getroffene linke Bildpunkte


  if (artefacts || removal)   // Falls Artefakte untersucht werden, initialisiere die verwendeten Datenstrukturen 
     initArtefact();

  // Ausgabe von Kontrollwerten
  if(verbose) {
     std::stringstream tos;
     tos << "\n\n\nParameter des Sirds-Algorithmus:";
     tos << "\nxResolution: " << xResolution << ",   yResolution: " << yResolution;
     tos << "\nmu: " << mu << ",   dpi: " << dpi << ",   eyeSeparation: " << eyeSeparation;
     tos << ",   distanceToImagePlane: " << distanceToImagePlane; 
     tos << "\nbackClippingPlaneSeparation: " << backClippingPlaneSeparation << ",   frontClippingplaneSeparation: " << frontClippingPlaneSeparation;
     tos << ",   depthLevels: " << depthLevels;

     if(artefacts || removal) {
        if (artefacts) tos << "\n\nArtefaktebild wird erzeugt:";
        else tos << "\n\nArtefakte sind definiert durch:";
        tos << "\nartefactswWindowSize: " << artefactsWindowSizeCont << ",   artefactsPerWindow: " << artefactsPerWindow;
        tos << "\nartefactsDepthDelta: " << artefactsDepthDelta << ",   enlargeViewVolumeBy: " << enlargeViewVolumeBy;
        tos << "\nartefactsTestDepthLevels: " << artefactsTestDepthLevels;
        tos << "\nartefactsFileName: " << artefactsFileName.chars();
     }
     if(removal) {
        tos << "\n\nArtefactRemoval wird durchgefuehrt:";
        tos << "\nartefactsToAccept: " << artefactsToAccept << ",   artefactsPixelStep: " << colourIndexStep;
        tos << "\nmaxArtefactsTests: " << maxArtefactsTests;
     }


     if(colouring) {
        tos << "\n\nFaerbe Bild mit Muster ein:";
        tos << "\npatternXRes: " << patternXRes << ",   patternYRes: " << patternYRes;
     }
     
     tos << "\n\n\nVerschiedene interne Werte:";
     tos << "\nlookAtWcs: " << lookAtWcs << ",   eyeWcs: " << eyeWcs <<  ",   upWcs: " << upWcs << "\n" ;
     tos << "imageCenterWcs: " << imageCenterWcs << ",   imageXDirectionWcs: " << imageXDirectionWcs << "\n" ;
     tos << "imageYDirectionWcs: " << imageYDirectionWcs << ",   imageZDirectionWcs: " << imageZDirectionWcs << "\n";
     tos << "distanceToImagePlane: " << distanceToImagePlane << ",   distanceToImagePlaneWu: " << distanceToImagePlaneWu << "\n";
     tos << "ImageWidth: " << imageWidth << ",   ImageHeight: " << imageHeight;
     tos << "LowerLeftCorner: " << lowerLeftCorner << "\n";
     tos << "BackClippingPlane: " << backClippingPlaneZ << ",   FrontClippingPlane: " << frontClippingPlaneZ << "\n" ;
     tos << "ImageX: " << imageXDirectionWcs << ",   ImageXTrans: " << t3WcsToIcs.transformAsVector(imageXDirectionWcs);

     tos << "\n\n\n";
     Report::debug(tos);
  }
 
  // Sirds-Algorithmus

  for (y=0; y < yResolution; y++) {   // Fuer jede Zeile des Bildes
    
    actualImagePixel = lowerLeftCorner + (y * pixelYDelta);   // Beginne mit dem ersten Pixel der Zeile
 
    // zu Beginn wurde noch kein linker Bildpunkt getroffen
 
    for (int i=0; i < xResolution; i++)
          hitsLeft[i] = false;
  
    for (xRight=0; xRight < xResolution; xRight++) {   // Fuer jedes Pixel der Zeile von links nach rechts
      
      // Jeder Punkt hat noch keine spezielle Farbe und keinen rechten Nachfolger
                                  
           colourList[xRight].colourIndex= -100.0;
           colourList[xRight].right = xRight;

      // rechter Sehstrahl erzeugen
       
      rayRight->reset();   // Sehstrahl in Ausgangszustand vesetzten
      rayRight->setOrigin(eyeRight);   // Sehstrahl des rechten Auges ...
      rayRight->setDirection(actualImagePixel - eyeRight);  // ... durch das aktuelle Bildpixel
      
      // Die Welt mit dem Sehstrahl des rechten Auges schneiden
      
      hitFrontClippingPlane = false;
      
      if (getWorld()->getObjects()->intersect(*rayRight) &&   // Es wurde ein Objekt getroffen
          ((rayRight->getPath()) != NULL)) {

         // Liegt der Schnittpunkt hinter der hinteren Clipping Ebene ?

         if ( ((hitPointOnObject = ( rayRight->getHitPoint())).z() )  > backClippingPlaneZ ) {   //  dahinter
           
            // hitPointOnObject ist Durchstosspunkt mit der hinteren Clipping Ebene

            t= ( backClippingPlaneZ -(rayRight->getOrigin().z() )) / ((rayRight->getDirection()).z());
            hitPointOnObject = (rayRight->getOrigin()) + (t * (rayRight->getDirection()));              

         }

         // Liegt der Schnittpunkt vor der vorderen Clipping Ebene ?

         if ( (hitPointOnObject.z()) < frontClippingPlaneZ ) {   //  davor
           
            // hitPointOnObject ist Durchstosspunkt mit der vorderen Clipping Ebene

             t= ( frontClippingPlaneZ - ((rayRight->getOrigin()).z()) ) / ((rayRight->getDirection()).z());
             hitPointOnObject = (rayRight->getOrigin()) + (t * (rayRight->getDirection()));  
             hitFrontClippingPlane = true;         
 
         }
      }
      else {   // kein Objekt getroffen
        
        // hitPointOnObject ist Durchstosspunkt mit der hinteren Clipping Ebene
 
        t= ( backClippingPlaneZ - ((rayRight->getOrigin()).z()) ) / ((rayRight->getDirection()).z());
        hitPointOnObject = (rayRight->getOrigin()) + (t * (rayRight->getDirection()));
      }
        

      // Um zu erkennen, ob der Schnittpunkt hitpointOnObject fuer das linke Auge verdeckt ist,
      // wird der Sehstrahl von diesem Schnittpunkt zum linken Auge mit der Welt geschnitten,
      // falls der linke Bildpunkt nicht bereits zuvor einmal getroffen wurde und hitPointOnObject
      // schon deshalb verdeckt ist
  
      rayLeft->reset();   // Sehstrahl in Ausgangszustand vesetzten
      rayLeft->setDirection(eyeLeft - hitPointOnObject);  //  Sehstrahl zum linken Auge ...
      rayLeft->setOrigin(hitPointOnObject + ( 0.01 * (rayLeft->getDirection()) ) );   // ... vom Schnittpunkt aus
      
      // zu xRight korrespondierender linker Bildpunkt xLeft berechnen
        
      t=  (-((rayLeft->getOrigin()).z())) / ((rayLeft->getDirection()).z());
      xLeftIcs= ( (rayLeft->getOrigin()) + (t * (rayLeft->getDirection())) ).x();
      xLeft = (int) (  rint( (lowerLeftCorner.x() - xLeftIcs) / pixelWidth) );


      if (xLeft < 0)   // Linker Bildpunkt nicht im Bild ist wie verdeckt
         verdeckt = true;
      else
         verdeckt = hitsLeft[xLeft];   // Linker Bildpunkt war dieses schon mal -> verdeckt       

      if ( (verdeckt == false) && (hitFrontClippingPlane == false) ) {   // xLeft war zuvor noch nie linker Bildpunkt
                                                                        // Schnittpunkt nicht auf FrontClippingPlane
         // Welt schneiden
  
         if (getWorld()->getObjects()->intersect(*rayLeft) &&   // Es wurde ein Objekt getroffen
            ((rayLeft->getPath()) != NULL)) {
              
            // Liegt der Schnittpunkt mit dem Objekt vor dem linken Auge ?
                
            if ( ((rayLeft->getHitPoint()).z()) > (eyeLeft.z()) ) {   // davor
              
              // hitPointOnObject ist fuer das linke Auge verdeckt
          
              verdeckt= true;
            }
         }
      }
      
      
      // Ist der Objektpunkt fuer das linke Auge verdeckt ?
      
      if (verdeckt) {   // verdeckt
      
         // hitPointOnObject ist fuer das linke Auge verdeckt
          
         colourList[xRight].left= xRight;   // Startpunkt einer neuen Punktemenge gleicher Farbe          

      }
      else {   // nicht verdeckt
      
          colourList[xRight].left = xLeft;   // left und right sind in der selben Punktemenge ...
          colourList[xLeft].right = xRight;   // ... gleicher Farbe
          hitsLeft[xLeft] = true;   // linker Punkt als bereits getroffen markieren

      }

      // naechstes Pixel
      
      actualImagePixel = actualImagePixel - pixelXDelta;   

     }


    // Muster auf die aktuelle Zeile des Bildes aufbringen

    if (!colouring) {   // Farbig oder schwarz/weiss ?
  
       // ein Schwarz-Weiss-Zufallsmuster
       int x;
       
       for (x = 0; x < xResolution; x++) {
          if (colourList[x].left == x)
             colourList[x].colourIndex = (int) (drand48() +0.7);
          else
             colourList[x].colourIndex = colourList[colourList[x].left].colourIndex;
       }
    
       for (x = 0; x < xResolution; x++) {
          if (colourList[x].colourIndex == 0) {
             myPixmap->setPosition(x,y); 
             myPixmap->setColor(0,0,0);
          }
          else {
             myPixmap->setPosition(x,y); 
             myPixmap->setColor(1,1,1);
          }
       }
 
     }   
     else {   // farbiges Muster
    
       /* Den Punktemengen gleicher Farbe eine Farbe im magischen Bild zuordnen
          und die aktuelle Zeile des magischen Bildes so einfaerben*/
 
        colourLine(colourList, y, false);

        if (removal) {
           if ( artefactCount(colourList, false, y) > artefactsToAccept ) {
               for (SirdsResolution xd = 0; xd < xResolution; xd++)  
                  colourList[xd].colourIndex= -100.0;
               colourLine(colourList, y, true);
           }
        }


    /* Die berechnete Zeile des magischen Bildes speichern */
	 
      SirdsResolution x,xp;
      SirdsResolution yp= y % patternYRes;
      ColourIndex colourIndex;
      ColourIndex fracPart=1;
      float r1, g1, b1, r2, g2, b2;

      for (x=0; x < xResolution; x++) {

         colourIndex = colourList[x].colourIndex;

         xp= (SirdsResolution) colourIndex;
         fracPart= colourIndex -xp;

         patternPixmap->setPosition(xp % patternXRes,yp);
         patternPixmap->getColor(r1,g1,b1);
         patternPixmap->setPosition( (xp +1) % patternXRes, yp);
         patternPixmap->getColor(r2,g2,b2);

         myPixmap->setPosition(x,y);            
         myPixmap->setColor( (1 - fracPart) * r1 +  fracPart*r2,
                                            (1 - fracPart) * g1 +  fracPart*g2,
                                            (1 - fracPart) * b1 +  fracPart*b2);
         
      }
    }


    // Progress indicator     

      if (verbose && !artefacts) {
        if ( (y % 10) == 0 ){
           std::stringstream os;
           os << "Zeile " << y;
           Report::debug(os);
        }
      }
      if (artefacts && verbose) {
        std::stringstream os;
        os << "Zeile " << y << " enthaelt "  <<  artefactCount(colourList, true, y) <<"  Artefakte";
        Report::debug(os);        
      }
      if (artefacts && !verbose) {
         std::stringstream os;
         artefactCount(colourList, true, y);
         Report::debug(os);
      }
   }
      
  // Artefakte Pixmap schreiben
  if (artefacts) {
     Pixmap2D *artefactsPixmap2D = new Pixmap2D(artefactsPixmap);  
     World2D *artefactsPixmapWorld = new World2D;
     artefactsPixmapWorld->getObjects()->adoptObject(artefactsPixmap2D);
     PPMWriter artefactsPixmapWriter(artefactsFileName);
     artefactsPixmapWriter.execute(artefactsPixmapWorld);  
     delete artefactsPixmapWorld;
  }
  
  // Die ganze Welt in den Anfangszustand zuruecktransformieren
   
  TransMatrix3D invTm3WcsToIcs = t3WcsToIcs.getInvTransMatrix(); 
   
  objListWorld = getWorld()->getObjects();
  for (long j=0; j < objListWorld->countSubobject(); j++) 
    objListWorld->getSubobject(j)->addTransform(invTm3WcsToIcs);
  objListWorld->computeBounds();
  
  
  // Speicher freigeben
  
  delete rayRight;
  delete rayLeft;
  if (artefacts || removal){
     delete [] artefactsTestLine;
     delete [] artefactsTestLineCont;
     for (int i=0; i < artefactsWindowSize; i++)
        delete [] (artefactsWindow[i]);
     delete [] artefactsWindow;
  }
  delete [] colourList;
  delete [] hitsLeft;
 
  return true;
}


// Set-Funktionen
void SirdsRenderer::setVerbose( bool v)
{
  verbose= v;
}

void SirdsRenderer::setArtefactsRemoval(bool r)
{
  removal= r;
}

void SirdsRenderer::setDistanceToImagePlane( Real d)
{
  distanceToImagePlane= d;
}

void SirdsRenderer::setDpi(int d)
{
  dpi= d;
}

void SirdsRenderer::setEyeSeparation(Real e)
{
  eyeSeparation= e;
}

void SirdsRenderer::setMu(Real m)
{
  mu= m;
}

void SirdsRenderer::setArtefactsWindowSize(int a)
{
  artefactsWindowSizeCont=a;
}

void SirdsRenderer::setArtefactsDepthDelta(int a)
{
  artefactsDepthDelta= a;
}

void SirdsRenderer::setArtefactsPerWindow(int a)
{
  artefactsPerWindow= a;
}

void SirdsRenderer::setEnlargeViewVolumeBy(Real e)
{
  enlargeViewVolumeBy= e;
}

void SirdsRenderer::setMaxArtefactsTests(int m)
{
  maxArtefactsTests= m;
}

void SirdsRenderer::setArtefactsToAccept(unsigned long int a)
{
  artefactsToAccept= a;
}

void SirdsRenderer::setArtefactsPixelStep( ColourIndex c)
{
  colourIndexStep= c;
}

void SirdsRenderer::setArtefactsFileName(const RCString& a)
{
  artefactsFileName= a;
  artefacts= true;
}

void SirdsRenderer::setPatternPixmap(AbstractPixmap *p)
{
  patternPixmap= p;
  patternXRes= patternPixmap->getResolutionX();
  patternYRes= patternPixmap->getResolutionY();
  if ( (patternXRes > 5) && (patternYRes > 5) )
    colouring= true;
  else
    Report::recoverable("SirdsRenderer::setPatternPixmap: Pattern too small. Writing random dots !");       
}

SirdsResolution SirdsRenderer::getResolutionX( void ) 
{
  return xResolution;
}

SirdsResolution SirdsRenderer::getResolutionY( void ) {
return yResolution;
}
