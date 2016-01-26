//
// $RCSfile: booga.bsl,v $
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
//  $Id: booga.bsl,v 1.2 1996/06/21 12:16:30 streit Exp $
// -----------------------------------------------------------------------------
//

surface booga(vector uP = [.06,.42,1], vector vP = [.325,.675,1])
{
  // this shader uses the "booga" pixmap as a mask. When the original
  // font is black, it will be evaluated as gold, otherwise the object
  // is transparent. uP and vP determine where the font is placed.
  
  real specPow, ctest;
  vector uv;
  
  specPow = 12;
  uP = [0.06,.42,1];
  vP = [0.325,.675,1];
  uv = getuv(TPos, uP, vP);
  ctest = texturemap("booga.ppm", uv);      // ctest will be black or white
  if (getx(ctest) > 0.4)                    // it is white
    Col = trace(WPos, RDir);                // -> transparent
  else
    Col = diffuse([1,.75, 0]) + .75 * specular([1,1,1], specPow);

}
