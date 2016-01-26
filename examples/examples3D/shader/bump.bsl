//
// $RCSfile: bump.bsl,v $
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
//  $Id: bump.bsl,v 1.1 1996/06/06 11:49:08 streit Exp $
// -----------------------------------------------------------------------------
//

surface bump(f1 = .5, f2 = 5)
{
  WNorm += bump(f1, f2);
}
