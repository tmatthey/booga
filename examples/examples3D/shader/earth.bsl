//
// $RCSfile: earth.bsl,v $
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
//  $Id: earth.bsl,v 1.1 1996/06/06 11:49:15 streit Exp $
// -----------------------------------------------------------------------------
//

surface earth(vector uParam = [0,1,1], vector vParam = [0,1,1])
{
  vector uv;
   
  uv = getuv(TPos, uParam, vParam);
  Col = diffuse(texturemap("earth.ppm", uv));
}
