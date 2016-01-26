//
// $RCSfile: water.bsl,v $
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
//  $Id: water.bsl,v 1.2 1996/06/06 11:49:57 streit Exp $
// -----------------------------------------------------------------------------
//

surface water(f1 = .15, f2 = 10, color cSea = [.2,.2,.4])
{
  // f1 determines the grade of perturbation of the normal.
  // f2 determines how fast this perturbation changes.
  // cSea is the color of the sea (dark blue).
  
  real specPow = 150;
  color cSpec = [.8,.8,.8];

  WNorm += bump(f1, f2);
  Col = cSea + specular(cSpec, specPow);
}
