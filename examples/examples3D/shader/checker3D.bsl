//
// $RCSfile: checker3D.bsl,v $
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
//  $Id: checker3D.bsl,v 1.1 1996/06/06 11:49:09 streit Exp $
// -----------------------------------------------------------------------------
//

surface checker3D(nx = 1, ny = 1, nz = 1,
//                  color cEven = [1,1,0], color cOdd = [0,0,1])
                  string 1sEven = "eroded.bsl", string sOdd = "marble.bsl")
{
  // this checker function uses the coordinates of the surface point
  // to directly calculate whether it lies in an even or in an odd field.
  // nx, ny and nz determine the number of divisions in each direction.
    
  if (mod(floor(nx*getx(TPos)) + floor(ny*gety(TPos)) + floor(nz*getz(TPos)), 2) == 0)
  shader(sOdd, sin(60));
//    Col = diffuse(cEven); 
  else
  shader(sOdd, 20, [1,.827,.678]);
//     Col = diffuse(cOdd);
}
