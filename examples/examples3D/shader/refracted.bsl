//
// $RCSfile: refracted.bsl,v $
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
//  $Id: refracted.bsl,v 1.1 1996/06/06 11:49:32 streit Exp $
// -----------------------------------------------------------------------------
//

surface refracted(ratio = .5, f1 = .1, f2 = 3, color col = [1,1,1])
{
  // This shader creates a pseudorandom refraction index
  // for the surface by sending the incident ray further on
  // in a slightly disturbed direction. The calculation of
  // this disturbed direction is done using the bump function.
  // ratio is the opacity of the object. f1 and f2 are the frequencies
  // for the bump funcion. col is the default surface color.
  
  real specPow = 30;
  color cSpec = [1,1,1];
  
  Col = mix(diffuse(col), trace(WPos, RDir+bump(f1, f2)), ratio) +
        specular(cSpec, specPow);
}

