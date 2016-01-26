//
// $RCSfile: partOfTorus.bsl,v $
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
//  $Id: partOfTorus.bsl,v 1.1 1996/06/06 11:49:29 streit Exp $
// -----------------------------------------------------------------------------
//

surface partOfTorus(radius = 1)
{
  // This shader makes a torus totally transparant outside a 
  // certain distance from its center.

  WNorm = faceforward(WNorm, RDir);     // don't forget this line!
  if(sqrt((getx(TPos))^2+(gety(TPos)^2)) > radius )
      Col = trace(WPos, RDir);
  else
    shader("marble.bsl", 70, [.7,.7,.7]);
}
