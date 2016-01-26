//
// $RCSfile: texturemap.bsl,v $
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
//  $Id: texturemap.bsl,v 1.1 1996/06/06 11:49:55 streit Exp $
// -----------------------------------------------------------------------------
//

surface texturemap(string pixi = "allee.pixi",
                   vector uP = [0,1,1],
                   vector vP = [0,1,1])
{
  vector uv;
  uv = getuv(TPos, uP, vP);
  if(getx(uv) != -1 && gety(uv) != -1) 
    Col = diffuse(texturemap(pixi, uv));
}
