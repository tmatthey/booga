//
// $RCSfile: planet.bsl,v $
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
//  $Id: planet.bsl,v 1.2 1996/06/06 11:49:32 streit Exp $
// -----------------------------------------------------------------------------
//

surface planet(f = 2.27)
{
  // This shader first calculates a pseudorandom value to determine
  // in which of 8 different areas the point lies. Afterwards
  // the colors will be linearly interpolated between the
  // borders of the different areas, depending on the distance
  // to the borders.
  // 2.27 is a good frequency value for the unit sphere
  // for use with the chaos function.

  real f1, f2, f3, f4, f5, f6, f7, threshold, specPow;
  color c1, c2, c3, c4, c5, c6, c7, cSpec;
  		
  f1 = .2;			// f1...f7 are the border values
  f2 = .53;			// of the different areas.
  f3 = .55;
  f4 = .59;
  f5 = .67;
  f6 = .72;
  f7 = .79;
  specPow = 1.4;

  c1 = [.255,.412,.982];	// the sea
  c2 = 1.5*c1;	        	// brighter sea
  c3 = [0,.9,0];		// greenlands
  c4 = [0,.7,.3];               // forests
  c5 = [.647,.165,.165];	// sandylands
  c6 = [.83,.83,.83];		// stones, mountains
  c7 = [1,1,1];			// snow
  cSpec = [.4,.4,0];            // specular light, yellow like the sun

  threshold = (chaos(f*TPos, 6));

  if (threshold<f1)				    
    Col = c1;                                       // just the seacolor
  else if (pulse(threshold, f1, f2))                // linear interpolation
    Col = mix(c1, c2, (threshold-f1)/(f2-f1));	    // between c1 and c2, ...
  else if (pulse(threshold, f2, f3))
    Col = mix(c2, c3, (threshold-f2)/(f3-f2));	    // ... c2 and c3
  else if (pulse(threshold, f3, f4))
    Col = mix(c3, c4, (threshold-f3)/(f4-f3));	    // ... c3 and c4
  else if (pulse(threshold, f4, f5))
    Col = mix(c4, c5, (threshold-f4)/(f5-f4));	    // ... c4 and c5
  else if (pulse(threshold, f5, f6))
    Col = mix(c5, c6, (threshold-f5)/(f6-f5));	    // ... c5 and c6
  else if (pulse(threshold, f6, f7))
    Col = mix(c6, c7, (threshold-f6)/(f7-f6));	    // ... c6 and c7
  else
    Col = c7;					    // just snow

  Col = diffuse(Col)+specular(cSpec, specPow);
}
