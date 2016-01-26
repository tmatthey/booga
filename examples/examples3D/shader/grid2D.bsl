//
// $RCSfile: grid2D.bsl,v $
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
//  $Id: grid2D.bsl,v 1.1 1996/06/06 11:49:22 streit Exp $
// -----------------------------------------------------------------------------
//

surface grid2D(nu = 10, nv = 5, delta = .1)
{
  // This shader implements a time-consuming way of wireframe rendering.
  // If the point lies on a u- or v-axis, it is not transparent.
  // If it lies outside one of these axis, it is partially transparent.
  // The width of the axis is 2*delta. nu and nv determine the number
  // of divisions in u- and v-direction.
  
  vector uP, vP, uv;
  uP = [0,1,1];
  vP = [0,1,1];

  uv = getuv(TPos, uP, vP);  
  if (pulse(frac(nu*getx(uv)), .5-delta, .5+delta) ||
      pulse(frac(nu*gety(uv)), .5-delta, .5+delta))
    Col = diffuse([.4,.2,.12]);
  else
    Col = mix(diffuse([1,1,1]), trace(WPos, RDir), .5);
}
