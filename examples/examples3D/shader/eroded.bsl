//
// $RCSfile: eroded.bsl,v $
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
//  $Id: eroded.bsl,v 1.1 1996/06/06 11:49:21 streit Exp $
// -----------------------------------------------------------------------------
//

surface eroded(f = 2, t1 = .45, t2 = .1)
{
  // This shader uses a pseudo-random number to decide
  // whether a point is transparent or not. 
  // 2 is a good frequency value for the unit sphere 
  // for use with the chaos function.
  // t1 is the threshold between the transparent
  // and the opaque areas. t2 is the width of the brown border.

  // intensity is the pseudo-random value.
  real intensity;
  real specPow = 15;
//  WNorm = faceforward(WNorm, RDir);

  // from marble...
  intensity = (0.5*sin(8*chaos(f*TPos, 6)) + 0.5) ^ .12;
  if (intensity > t1 + t2)      // just gold
    Col = diffuse([1,.75, 0]) + .75 * specular([1,1,1], specPow);
  else if (intensity > t1)      // brown-gold border
    Col = mix(diffuse([1,.75, 0]) + .75 * specular([1,1,1], specPow),
                [.4,.2,.12], 1 - smoothstep(intensity, t1, t1 + t2));
// warum geht wohl trace(WPos, RDir) nicht anstelle von [0,0,0]?
  else                          // transparent
    Col = trace(WPos, RDir);
}
