/*
 * TextureUtilities.C
 *
 * Copyright (C) 1996, Thomas <teuscher@iam.unibe.ch>
 *                     University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * Code fragments of Noise from Perlin and Skinner.
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
 *  $Id: TextureUtilities.C,v 1.4 1998/01/12 15:45:22 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include "booga/texture/TextureUtilities.h"
#include "booga/object/Ray3D.h"

#define MINX		-1000000
#define MINY		MINX
#define MINZ		MINX

#define SCURVE(a) ((a)*(a)*(3.0-2.0*(a)))
#define REALSCALE ( 2.0 / 65536.0 )
#define NREALSCALE ( 2.0 / 4096.0 )

#define Hash3d(a,b,c) hashTable[hashTable[hashTable[(a) & 0xfff] ^ ((b) & 0xfff)] ^ ((c) & 0xfff)]
#define Hash(a,b,c) (xtab[(xtab[(xtab[(a) & 0xff] ^ (b)) & 0xff] ^ (c)) & 0xff] & 0xff)

#define INCRSUM_org(m,s,x,y,z)	((s)*(rTable[m]*0.5		\
					+ rTable[m+1]*(x)	\
					+ rTable[m+2]*(y)	\
					+ rTable[m+3]*(z)))	\

#define INCRSUM(m,s,x,y,z)	((s)*(rTable[m]))

Real TextureUtilities::rTable[MAXSIZE];
short* TextureUtilities::hashTable;
Real TextureUtilities::power2[] = 
{
  0, 2/1-0.01, 2/1.5-0.01, 2/1.75-0.01, 2/1.875-0.01, 2/1.9375-0.01,
  2/1.969-0.01, 2/1.984-0.01, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

unsigned short TextureUtilities::xtab[256] =
{
  0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
  0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
  0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
  0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
  0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
  0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
  0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
  0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
  0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
  0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
  0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
  0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
  0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
  0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
  0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
  0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
  0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
  0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
  0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
  0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
  0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
  0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
  0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
  0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
  0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
  0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
  0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
  0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
  0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
  0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
  0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
  0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
};

void TextureUtilities::initTextureTable()
{
  int i, j, temp;

  srand48(123874L);
  hashTable = new short[4096];
  for (i = 0; i < 4096; i++)
    hashTable[i] = i;
  for (i = 4095; i > 0; i--) {
    j = (int)(drand48() * 4096);
    temp = hashTable[i];
    hashTable[i] = hashTable[j];
    hashTable[j] = temp;
  }
}

int TextureUtilities::Crc16(char* buf,int  count)
/*
 * Note that passing a Float to Crc16 and interpreting it as
 * an array of chars means that machines with different floating-point
 * representation schemes will evaluate Noise(point) differently.
 */
{
  register unsigned int crc = 0;

  while (count--)
    crc = (crc >> 8) ^ xtab[ (unsigned char) (crc ^ *buf++) ];

  return crc;
}

int TextureUtilities::R(Vector3D* v)
{
  Real scale = .12345;
  *v *= scale;

  return Crc16((char*) v, sizeof(Vector3D));
}

void TextureUtilities::initNoise()
{
  int i;
  Vector3D rp;

  initTextureTable();

  for (i = 0; i < MAXSIZE; i++) {
    rp = Vector3D((Real)i, (Real)i, (Real)i);
    rTable[i] = R(&rp)*REALSCALE - 1.0;
  }
}

//
// Robert Skinner`s Perlin-style "Noise" function
//
Real TextureUtilities::Noise3(Vector3D& point)
{
  register int	ix, iy, iz, jx, jy, jz;
  Real x, y, z;
  Real sx, sy, sz, tx, ty, tz;
  Real sum;
  short	m;

  /* ensures the values are positive. */
  x = point.x() - MINX; y = point.y() - MINY; z = point.z() - MINZ;

  /* its equivalent integer lattice point. */
  ix = (int)x; iy = (int)y; iz = (int)z;
  jx = ix+1; jy = iy + 1; jz = iz + 1;

  sx = SCURVE(x - ix); sy = SCURVE(y - iy); sz = SCURVE(z - iz);

  /* the complement values of sx,sy,sz */
  tx = 1.0 - sx; ty = 1.0 - sy; tz = 1.0 - sz;

  /*
   *  interpolate!
   */
  m = Hash3d( ix, iy, iz ) & 0xFF;
  sum = INCRSUM(m,(tx*ty*tz),(x-ix),(y-iy),(z-iz));

  m = Hash3d( jx, iy, iz ) & 0xFF;
  sum += INCRSUM(m,(sx*ty*tz),(x-jx),(y-iy),(z-iz));

  m = Hash3d( ix, jy, iz ) & 0xFF;
  sum += INCRSUM(m,(tx*sy*tz),(x-ix),(y-jy),(z-iz));

  m = Hash3d( jx, jy, iz ) & 0xFF;
  sum += INCRSUM(m,(sx*sy*tz),(x-jx),(y-jy),(z-iz));

  m = Hash3d( ix, iy, jz ) & 0xFF;
  sum += INCRSUM(m,(tx*ty*sz),(x-ix),(y-iy),(z-jz));

  m = Hash3d( jx, iy, jz ) & 0xFF;
  sum += INCRSUM(m,(sx*ty*sz),(x-jx),(y-iy),(z-jz));

  m = Hash3d( ix, jy, jz ) & 0xFF;
  sum += INCRSUM(m,(tx*sy*sz),(x-ix),(y-jy),(z-jz));

  m = Hash3d( jx, jy, jz ) & 0xFF;
  sum += INCRSUM(m,(sx*sy*sz),(x-jx),(y-jy),(z-jz));

//  if (sum<-1.0 || sum>1.0) printf("SUM=%0.4f ",sum);

  return sum/2 + 0.5;

  // noise() =  0 .. 1
}

//
// Vector-valued "Noise"
//
Vector3D TextureUtilities::DNoise3(Vector3D& point)
{
  Real result_x,result_y,result_z;
  register int ix, iy, iz, jx, jy, jz;
  Real x, y, z;
  Real s;
  Real sx, sy, sz, tx, ty, tz;
  short	m;

  /* ensures the values are positive. */
  x = point.x() - MINX; y = point.y() - MINY; z = point.z() - MINZ;

  /* its equivalent integer lattice point. */
  ix = (int)x; iy = (int)y; iz = (int)z;
  jx = ix+1; jy = iy + 1; jz = iz + 1;

  sx = SCURVE(x - ix); sy = SCURVE(y - iy); sz = SCURVE(z - iz);

  /* the complement values of sx,sy,sz */
  tx = 1.0 - sx; ty = 1.0 - sy; tz = 1.0 - sz;

  /*
   *  interpolate!
   */
  m = Hash3d( ix, iy, iz ) & 0xFF;
  //px = x-ix;  py = y-iy;  pz = z-iz;
  s = tx*ty*tz;
  result_x = INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y = INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z = INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( jx, iy, iz ) & 0xFF;
  //px = x-jx;
  s = sx*ty*tz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( jx, jy, iz ) & 0xFF;
  //py = y-jy;
  s = sx*sy*tz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( ix, jy, iz ) & 0xFF;
  //px = x-ix;
  s = tx*sy*tz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( ix, jy, jz ) & 0xFF;
  //pz = z-jz;
  s = tx*sy*sz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( jx, jy, jz ) & 0xFF;
  //px = x-jx;
  s = sx*sy*sz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( jx, iy, jz ) & 0xFF;
  //py = y-iy;
  s = sx*ty*sz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);

  m = Hash3d( ix, iy, jz ) & 0xFF;
  //px = x-ix;
  s = tx*ty*sz;
  result_x += INCRSUM(m,s,0,0,0 /* px,py,pz */);
  result_y += INCRSUM(m+4,s,0,0,0 /* px,py,pz */);
  result_z += INCRSUM(m+8,s,0,0,0 /* px,py,pz */);
	
  result_x = result_x / 2 + 0.5;        // scale into the range
  result_y = result_y / 2 + 0.5;        // of 0..1 !
  result_z = result_z / 2 + 0.5;

  return Vector3D(result_x,result_y,result_z);
}

Real TextureUtilities::Chaos(Vector3D vec, int octaves)
{
  Real s, t;
  int n = octaves;

  s = 1.0;
  t = 0.;

  while (octaves--) {
    t += Noise3(vec) * s;
    s *= 0.5;
    vec *= 2.;
  }

  return power2[n]*t/2;

  // chaos() = 0..1
}

void TextureUtilities::evaluateTextureAttributes(RCString name, Vector3D point,
                                                 Texture3DContext& context)
{
  if (name == "Col")
    context.setColor(point);
  else
  if (name == "Illum")
    context.setIllumination(point);
  else
  if (name == "LDir")
    context.setLightDirection(point);
  else
  if (name == "Eye")
    context.setIncidencePosition(point);
  else  
//  if (name == "RDir")
//    context.getIncidenceRay()->setDirection(point);
//  else  
  if (name == "WPos")
    context.setPositionWCS(point);
  else
  if (name == "WNorm")
    context.setNormalWCS(point);
  else
  if (name == "OPos")
    context.setPositionOCS(point);
  else
  if (name == "ONorm")
    context.setNormalOCS(point);
  else
  if (name == "TPos")
    context.setPositionTCS(point);
  else
  if (name == "TNorm")
    context.setNormalTCS(point);
}

Vector3D TextureUtilities::calculateTexelValue(AbstractPixmap* pm, Real x,
                                               Real y, Real aaDistance)
{
  Real r,g,b;
  float rt,gt,bt;
  r = b = g = 0;
  Real fx = frac(x);
  Real fy = frac(y);
  
  if (fx < 0.5-aaDistance ) {    // left part of Texel
    if (fy < 0.5-aaDistance) {   // lower left part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition((int)x, max(0, (int)y-1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy)) * (1.0-ip(fabs(0.5-fx))) * rt; 
      g += ip(fabs(0.5-fy)) * (1.0-ip(fabs(0.5-fx))) * gt;
      b += ip(fabs(0.5-fy)) * (1.0-ip(fabs(0.5-fx))) * bt;

      pm->setPosition(max(0, (int)x-1), (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * bt;

      pm->setPosition(max(0, (int)x-1), max(0, (int)y-1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * bt;

      return Vector3D(r,g,b);
    }    // end of lower left part of Texel
    
    else if (fy > 0.5+aaDistance) {    // upper left part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx)))* gt;
      b += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition((int)x, min(pm->getResolutionY()-1, (int)y+1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * rt; 
      g += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * gt;
      b += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * bt;

      pm->setPosition(max(0, (int)x-1), (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * bt;

      pm->setPosition(max(0, (int)x-1), min(pm->getResolutionY()-1, (int)y+1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * bt;

      return Vector3D(r,g,b);
    }    // end of upper left part of Texel
    
    else {    // mid left part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fx))) * gt;
      b += (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition(max(0, (int)x-1), (int)y);
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fx)) * bt;

      return Vector3D(r,g,b);
    }    // end of mid left part of Texel   
  }    //  end of left part of Texel
  
  else if (fx > 0.5+aaDistance) {    // right part of Texel
    if (fy < 0.5-aaDistance) {    // lower right part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition((int)x, max(0, (int)y-1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * rt; 
      g += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * gt;
      b += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * bt;

      pm->setPosition(min(pm->getResolutionX()-1, (int)x+1), (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * bt;

      pm->setPosition(min(pm->getResolutionX()-1, (int)x+1), max(0, (int)y-1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * bt;

      return Vector3D(r,g,b);
    }    // end of lower right part of Texel
    
    else if (fy > 0.5+aaDistance) {    // upper right part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition((int)x, min(pm->getResolutionY()-1, (int)y+1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * rt; 
      g += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * gt;
      b += ip(fabs(0.5-fy))* (1.0-ip(fabs(0.5-fx))) * bt;

      pm->setPosition(min(pm->getResolutionX()-1, (int)x+1), (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * ip(fabs(0.5-fx)) * bt;

      pm->setPosition(min(pm->getResolutionX()-1, (int)x+1), min(pm->getResolutionY()-1, (int)y+1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fy))* ip(fabs(0.5-fx)) * bt;

      return Vector3D(r,g,b);
    }    // end of upper right part of Texel
    
    else {    // mid right part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fx))) * rt; 
      g += (1.0-ip(fabs(0.5-fx))) * gt;
      b += (1.0-ip(fabs(0.5-fx))) * bt;
      
      pm->setPosition(min(pm->getResolutionX()-1, (int)x+1), (int)y);
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fx)) * rt; 
      g += ip(fabs(0.5-fx)) * gt;
      b += ip(fabs(0.5-fx)) * bt;      

      return Vector3D(r,g,b);
    }    // end of mid right part of Texel
  }    // end of right part of Texel
  
  else {    // mid part of Texel
    if (fy < 0.5-aaDistance) {    // lower mid part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * bt;
      
      pm->setPosition((int)x, max(0, pm->getResolutionY()-1,(int)y-1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* rt; 
      g += ip(fabs(0.5-fy))* gt;
      b += ip(fabs(0.5-fy))* bt;

      return Vector3D(r,g,b);
    }    // end of lower mid part of Texel
    
    else if (fy > 0.5+aaDistance) {    // upper mid part of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);
      r += (1.0-ip(fabs(0.5-fy))) * rt; 
      g += (1.0-ip(fabs(0.5-fy))) * gt;
      b += (1.0-ip(fabs(0.5-fy))) * bt;
      
      pm->setPosition((int)x, min(pm->getResolutionY()-1,(int)y+1));
      pm->getColor(rt,gt,bt);
      r += ip(fabs(0.5-fy))* rt; 
      g += ip(fabs(0.5-fy))* gt;
      b += ip(fabs(0.5-fy))* bt;

      return Vector3D(r,g,b);
    }    // end of upper mid part of Texel
    
    else {    // center of Texel
      pm->setPosition((int)x, (int)y);
      pm->getColor(rt,gt,bt);

      return Vector3D(rt,gt,bt);
    }    // end of center of Texel
  }    // end of mid part of Texel
}

Real TextureUtilities::ip(Real x)
{
  return x * x * (3 - 2 * x);
}
