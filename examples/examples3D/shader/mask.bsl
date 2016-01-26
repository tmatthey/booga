//
// $RCSfile: mask.bsl,v $
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
//  $Id: mask.bsl,v 1.1 1996/06/06 11:49:25 streit Exp $
// -----------------------------------------------------------------------------
//

surface mask(string pixi = "earth.ppm",
             vector uP = [0,1,1], vector vP = [0,1,1])
{
  // This shader uses  a certain intensity value of a pixmap
  // as a mask to decide whether a point is transparent or not.
  // This is done by evaluating the pixmap color before
  // assigning it to a pixel value.
  // pixi is the name of the pixmap that serves as a mask.
  // uP and vP determine the area of the object to be covered.
  
  vector uv;
  color cTemp;
  
  uv = getuv(TPos, uP, vP);
  cTemp = texturemap(pixi, uv);

  // The point is transparent when the blue component of
  // its texture color is big and the red and green
  // components are small.
  if (getz(cTemp) > 150/255 && getx(cTemp)+gety(cTemp) < 10)
    Col = trace(WPos, RDir);
  else
    Col = diffuse(cTemp);
}

