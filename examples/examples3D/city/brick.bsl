//
// $RCSfile: brick.bsl,v $
//
// Copyright (C) 1996, Thierry Matthey<matthey@iam.unibe.ch>
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
//  $Id: brick.bsl,v 1.2 1997/01/17 12:02:09 matthey Exp $
// -----------------------------------------------------------------------------
//

surface brick(nx = 1, ny = 1, nz = 0,
              color cEven = [0.3,0.2,0.2], color cOdd = [1,.9,.9])
{
  // this brick function uses the coordinates of object

  real c, f, d, x, y;
  
  c = 0.2;     // between the bricks
  
  f = 3;       // ratio of the brick
     
  if (nx == 0) {          // which side ?
    x = gety(OPos) * ny;
    y = getz(OPos) * nz;
  }
  else if (ny == 0) {
    x = getz(OPos) * nz;
    y = getx(OPos) * nx;
  }
  else {
    x = getx(OPos) * nx; 
    y = gety(OPos) * ny;
  }
  
  if (mod(y,2) > 1)      // which brick ?
    d = 0.5;
  else
    d = 0;
    
  if ((pulse(mod(x/f - d,1),c/f, 1-c/f) * pulse(mod(y,1),c, 1-c)) > 0)
    Col = diffuse(cOdd); 
  else 
    Col = diffuse(cEven);
}
