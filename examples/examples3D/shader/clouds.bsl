//
// $RCSfile: clouds.bsl,v $
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
//  $Id: clouds.bsl,v 1.2 1996/06/06 11:49:11 streit Exp $
// -----------------------------------------------------------------------------
//

surface clouds(justclouds = 0, f = .65, cloudyness = .6)
{
  // This shader first calculates a pseudorandom value to determine
  // if a point lies under the clouds or not. If so, the color
  // of the clouds will be calculated by interpolating between c1 an c2.
  // The darker the clouds are, the more transparent they will be.
  // justclouds is a boolean determining whether the groundcolor
  // has to be overwritten or not.
  // .65 is a good frequency value for the unit sphere
  // for use with the chaos function.
  // cloudyness determines the amount of clouds. 0 => uncovered, 1 => covered

  real cloudy, intensity, thres, smooth;
  color c1, c2, c3;		// colors of the different areas.

  c1 = [.6,.6,.6];
  c2 = [1,1,1];
  c3 = [.055,.152,.982];	// blue like the sea...

  intensity = chaos(f * TPos, 6);

  if (justclouds == 1)                // can be used if Col 
    Col = c3;                         // is not set yet.. 

  cloudy = 1 - cloudyness;
  thres = (intensity - cloudy) / (1 - cloudy);
  if (thres > 0) {                    // i.e. intensity > cloudy
    smooth = smoothstep(thres, -cloudy, .9);  // brighten up
    Col = mix(mix(c1, c2, smooth), Col, 1-1.2*smooth);
  }
}
