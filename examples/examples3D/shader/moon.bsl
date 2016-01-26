//
// $RCSfile: moon.bsl,v $
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
//  $Id: moon.bsl,v 1.2 1996/06/06 11:49:26 streit Exp $
// -----------------------------------------------------------------------------
//

surface moon(f = 2.27)
{
  // This shader first calculates a pseudorandom value to determine
  // in which of 7 different areas the point lies. Afterwards
  // the colors will be linearly interpolated between the
  // borders of the different areas, depending on the distance
  // to the borders.
  // 2.27 is a good frequency value for the unit sphere
  // for use with the chaos function.

  real f1, f2, f3, f4, f5, f6, threshold;
  color c1, c2, c3, c4, c5, c6;
  		
  f1 = .2;			// f1...f6 are the border values
  f2 = .24;                    // of the different areas.
  f3 = .319;
  f4 = .4766;
  f5 = .522;
  f6 = .6273;

  c1 = [.6,.6,.6];             // the colors of the different areas
  c2 = [.71,.71,.71];          // on the moon.
  c3 = [.79,.79,.79];
  c4 = [.85,.85,.85];
  c5 = [.91,.91,.91];
  c6 = [1,1,1];



  threshold = chaos(f*TPos, 6);

  if ((threshold < f1))
    Col = c1;
  else if (pulse(threshold, f1, f2))
    Col = mix(c1, c2, (threshold-f1)/(f2-f1));
  else if (pulse(threshold, f2, f3))
    Col = mix(c2, c3, (threshold-f2)/(f3-f2));
  else if (pulse(threshold, f3, f4))
    Col = mix(c3, c4, (threshold-f3)/(f4-f3));
  else if (pulse(threshold, f4, f5))
    Col = mix(c4, c5, (threshold-f4)/(f5-f4));
  else if (pulse(threshold, f5, f6))
    Col = mix(c5, c6, (threshold-f5)/(f6-f5));
  else
    Col = c6;
}
