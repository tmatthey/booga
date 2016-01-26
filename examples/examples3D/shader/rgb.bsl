//
// $RCSfile: rgb.bsl,v $
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
//  $Id: rgb.bsl,v 1.2 1996/06/06 11:49:33 streit Exp $
// -----------------------------------------------------------------------------
//

surface rgb(scale = 1)
{

//  if(getx(TPos) * gety(TPos) * getz(TPos) != 0)
//    Col = trace(WPos, RDir);
//  else
    Col = TPos/scale;
}

