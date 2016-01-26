//
// $RCSfile: partOfSphere.bsl,v $
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
//  $Id: partOfSphere.bsl,v 1.1 1996/06/06 11:49:28 streit Exp $
// -----------------------------------------------------------------------------
//

surface partOfSphere(vector uP = [0,1,1], vector vP = [0,1,1])
{
  // This shader makes a sphere totally transparant on a segment
  // that can be determined by the parameters uP and vP.
  // This is done by first calculating the sphere's parameterization
  // and then deciding whether the incident ray has to be sent
  // further on or not.

  vector uv;

  uv = getuv(TPos, uP, vP);  
  WNorm = faceforward(WNorm, RDir);     // don't forget this line!
  if((getx(uv) == -1) || (gety(uv) == -1))
   shader("marble.bsl", 1.25);
  else
    Col = trace(WPos, RDir);
}
