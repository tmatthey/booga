//
// $RCSfile: checker2D.bsl,v $
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
//  $Id: checker2D.bsl,v 1.1 1996/06/06 11:49:09 streit Exp $
// -----------------------------------------------------------------------------
//

surface checker2D(nu = 8, nv = 4,
                  color cEven = [0,.8,0], color cOdd = [1,0,0])
{
  // this checker function first calculates the (u,v)-parameterization
  // of the object with two part spherical mapping.
  // Then the calculated values are used to determine whether
  // the point lies in an even or in an odd field.
  // nu and nv determine the number of divisions in u- and v-direction.

  real u, v;
  vector uP, vP, uv;        // parameters to calculate (u,v)

  uP = [0,1,1];             // cover the whole object once in u-direction
  vP = [0,1,1];             // cover the whole object once in v-direction
  uv = getuv(TPos, uP, vP); // use the texture position
  
  if (mod(floor(nu*getx(uv))+floor(nv*gety(uv)), 2) == 0)
    Col = diffuse(cEven); 
  else
    Col = diffuse(cOdd);
}
