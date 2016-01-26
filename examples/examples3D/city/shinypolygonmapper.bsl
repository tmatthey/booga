//
// $RCSfile: shinypolygonmapper.bsl,v $
//
// A simple mapping of a bitmap on a polygon. With shiny
//
// Every face (point with normal) of a object is turned into the xy-plane.
// The rotation is defined by the normal vector and [0,0,1] with the cross
// product. The rotation axis is lying in the xy-plane and the rotation 
// angle is defined by dot product of the normal and [0,0,1].
//
// Copyright (C) 1996, Thierry Matthey<teuscher@iam.unibe.ch>
//                     University of Berne, Switzerland
//
// All rights reserved.
//
// This software may be freely copied, modified, and redistributed
// provided that this copyright notice is preserved on all copies.
//
// You may not distribute this software, in whole or in part, as part of
// any commercial product without the express consent of the authors.
//
// There is no warranty or other guarantee of fitness of this software
// for any purpose.  It is provided solely "as is".
//
// -----------------------------------------------------------------------------
//  $Id: shinypolygonmapper.bsl,v 1.2 1997/01/17 12:02:34 matthey Exp $
// -----------------------------------------------------------------------------
//

surface shinypolygonmapper(string filename,  // filename of the bitmap
                           nx = 1,           // x-ratio of the bitmap
                           ny = 1,           // y-ratio of the bitmap
                           beta = 0)         // rotation angle of the bitmap 
{
  vector uv;       // texture cooridnates
  vector n;        // normal vector of the object
  real sinAlpha;   // sin value of rotation angle
  real cosAlpha;   // cos value of rotation angle 
  vector w;        // rotation axis
  real ux;         // x-value of the rotation axis
  real uy;         // y-value of the rotation axis
                  
  real x;          
  real y;

  real specPow = 50;
  color cSpec = [1,1,1];
  real ratio = .2;
  real cosAlphaLight;
  vector normal;
  
  n      = getnormal(OPos);  // get the normal of the object
  normal = getnormal(WPos);
  
  //
  // using Heckbert's method to compute reflected ray direction
  // R = I + 2*c1*N, where
  //    I  = incident direction (unit)
  //    N  = plane normal (unit)
  //    c1 = cos (-I*N) (= cosAlpha)
  //

  cosAlphaLight = -RDir^normal;
  
//  if (cosAlphaLight < 0) {
//    //
//    // Hit the 'backside' of a surface -- flip the normal.
//    //
//    cosAlphaLight = -cosAlphaLight;
//    normal = -normal;
//  }
  w = [gety(n),-getx(n),0];
  if (length(w) < 0.0001)
    w = [1,0,0];
  else
    w = normalize(w);
    
  ux = getx(w);
  uy = gety(w);
  
  cosAlpha = getz(n);             // values of the rotation angle
  sinAlpha = sin(acos (getz(n)));
  
  
  // 3D-rotation of the normal vector into the plane which is parallel to the xy-plane
  x = [ux*ux + cosAlpha*(1- ux*ux), ux*uy*(1 - cosAlpha),uy*sinAlpha] ^ OPos;
  y = [ux*uy*(1 - cosAlpha), uy*uy + cosAlpha*(1 - uy*uy), - ux*sinAlpha] ^ OPos;

  // scale, rotate and repeat the bitmap
  uv = [mod((x * cos(beta) - y * sin(beta)) * nx,1),
        mod((x * sin(beta) + y * cos(beta)) * ny,1), 0];

  
  if (filename != "")
    Col = mix(sdiffuse(texturemap(filename, uv)), trace(WPos, RDir+2*cosAlphaLight*normal), ratio) +sspecular(cSpec, specPow);

}
