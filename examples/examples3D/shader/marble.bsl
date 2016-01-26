//
// $RCSfile: marble.bsl,v $
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
//  $Id: marble.bsl,v 1.2 1996/06/06 11:49:24 streit Exp $
// -----------------------------------------------------------------------------
//

surface marble(f = 5, color c1 = [.6,.8,.9], color c2 = [0,0,0])
{
  // This shader uses a pseudorandom value to determine
  // the mix ratio between the stone color and the "vein" color.
  // 5 is a good frequency value for the unit sphere.
  // c1 is the default color of marble (grey-blue).
  // c2 is the color of the "veins".
 
  real ratio;        // ratio be used to interpolate between c1 and c2
  real specPow = 14;
  color cSpec = [1,1,1];

  ratio = (.5*sin(8*chaos(f*TPos, 6))+.5)^.12; // try and error...
  Col = mix(c2, c1, ratio);
  Col = diffuse(Col)+.6*specular(cSpec, specPow);
}
