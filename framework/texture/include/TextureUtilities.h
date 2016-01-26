/*
 * TextureUtilities.h
 *
 * Copyright (C) 1995-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
 *                        Thomas Teuscher <teuscher@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * Code fragments of Noise from Perlin  and Skinner
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
 *  $Id: TextureUtilities.h,v 1.3 1996/04/18 14:31:50 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _TextureUtilities_H
#define _TextureUtilities_H

#include "booga/base/Vector3D.h"
#include "booga/base/RCString.h"
#include "booga/object/Texture3DContext.h"
#include "booga/base/AbstractPixmap.h"

#define simplefloor(x) ((double)((long)(x)-((x)<0.0)))

#define floor(x) ((tempdoub=(x))<0.0?((long)tempdoub)-1L:(long)tempdoub)

#define MAXSIZE 267 

/*
 * Iteration over all Lightsources of a certain type
 * 
 * Texture3DContext context has to be defined and at least
 * the corresponding light sources have to be set in context.
 * 
 * Example: (Matte.C)
 *
 *  Color ambientIllumination(0,0,0);
 *  forEachLight(AmbientLight,ambLight) {
 *    ambLight->getIllumination(context);
 *    ambientIllumination += context.getIllumination();
 *  }
 *
 */
#define forEachLight(type,light)                                     \
  const List<type*>* the##type##List = context.get##type##Sources(); \
  type* light;                                                       \
  long light##Nr;                                                    \
  if (the##type##List != NULL)                                       \
    for (light##Nr=0;                                                \
         light##Nr<the##type##List->count() &&                       \
         (light=the##type##List->item(light##Nr));                   \
         light##Nr++) 

//__________________________________________________________________ TextureUtilities

class TextureUtilities  {
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // TextureUtilities();                               // Use default version.
private:
  // TextureUtilities(const TextureUtilities&);             // Use default version.

public:
  // virtual ~TextureUtilities();                      // Use default version.

private:
  // TextureUtilities& operator=(const TextureUtilities&);  // Use default version.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Attributes of class TextureUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  static Real rTable[MAXSIZE];
  static short*	hashTable;
  static Real power2[];
  static unsigned short xtab[256];
  static Real tempdoub;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Methods of class TextureUtilities
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

private:
  static void initTextureTable();
  static int Crc16(char* buf, int count);
  static int R(Vector3D* v);

public:
  static void initNoise();
  static Real Noise3(Vector3D& vec);     
  static Vector3D DNoise3(Vector3D& vec);
  static Real Chaos(Vector3D vec, int octaves);
  
  static void evaluateTextureAttributes(RCString name, Vector3D point,
                                        Texture3DContext& context);

  static Vector3D calculateTexelValue(AbstractPixmap* pm, Real x, Real y, Real aaDistance);

private:
  static Real ip(Real x);  // cubic interpolation
};
#endif // _TextureUtilities_H



