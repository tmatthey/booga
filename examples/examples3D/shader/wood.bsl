//
// $RCSfile: wood.bsl,v $
//
// Copyright (C) 1996, Thomas Teuscher<teuscher@iam.unibe.ch>
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
//  $Id: wood.bsl,v 1.2 1996/06/06 11:49:57 streit Exp $
// -----------------------------------------------------------------------------
//

surface wood(age = 2, freq = 3, color lightwood = [.4,.24,.14],
                                color darkwood = [.15,.03,.015])
{
  // age is the number of rings in the unit cube.
  // 1 is a good frequency value for the unit cube.
  // lightwood and darkwood determine the color of the wood and the rings.
  // These colors will be used to interpolate the final color.
  
  real specPow = 20;
  color specCol = [1,1,1];
  real x,y,r;             // used to determine in which "year ring" we are.
  vector temp;
  real f1, f2;            // used for bump mapping.
  temp = TPos + [noise(freq*TPos),                // disturb the current
                 noise(freq*(TPos+[7,7,7])),      // position (just in
                 0];                              // the x-y-plane).
                 
  x = getx(temp);         // we suppose our "original tree" to be standing
  y = gety(temp);         // upward, i.e. parallel to the z-axis. 
  r = sqrt(x*x + y*y); // calculate the radius of the ring on which we are.
  r *= age;               // involve the age.
  r += noise([r,r,r]);    // disturb the radius to get varying ring widths.
  r = mod(r,1);           // fit r into the interval [0..1]
  
  // r will be growing "smoothly" from 0 to 1 in the interval [0..0.8],
  // rest 1 in[0.8..0.83 and fall rapidly down to 0 in [0.83..1].
  r = smoothstep(0,0.8,r) - smoothstep(.83,1,r);
  
  Col = mix(lightwood, darkwood, r);  // interpolation according to r.
  f1 = .125;
  f2 = 80;
  WNorm += bump(f1,f2);        // give some structure to the surface.
  WNorm = normalize(WNorm);
  Col = diffuse(Col) + (0.3*r  + 0.7) * specular(Col, specPow);
  Col *= 4;
}
