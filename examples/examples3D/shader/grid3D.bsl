//
// $RCSfile: grid3D.bsl,v $
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
//  $Id: grid3D.bsl,v 1.1 1996/06/06 11:49:23 streit Exp $
// -----------------------------------------------------------------------------
//

surface grid3D(nx, ny, nz, delta = .2)
{
  real x, y, z;
  x = getx(TPos);
  y = gety(TPos);
  z = getz(TPos);
  
  if (pulse(abs(frac(nz*z)), .5 - delta, .5 + delta))
    Col = diffuse([.8,.8,.8]);
  else
    if (pulse(abs(frac(ny*y)), .5 - delta, .5 + delta))
      Col = diffuse([.8,.8,.8]);
    else
      if (pulse(abs(frac(nx*x)), .5 - delta, .5 + delta))      
        Col = diffuse([.8,.8,.8]);      
      else
        Col = diffuse([1,1,0]);    
}
