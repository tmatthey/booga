/*
 * viewing.inc 
 *
 * Copyright (C) 1994-96, Bernhard Buehlmann <buehlmann@iam.unibe.ch>
 *                        University of Berne, Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified, and redistributed
 * provided that this copyright notice is preserved on all copies.
 *
 * You may not distribute this software, in whole or in part, as part of
 * any commercial product without the express consent of the authors.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose.  It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: viewing.inc,v 1.3 1997/05/26 13:45:21 matthey Exp $
 * -----------------------------------------------------------------------------
 */
#ifndef _viewing_bsdl3
#define _viewing_bsdl3
using 3D;

//
// Definition of the camera and the lightsource
//

camera {
  perspective {
//    eye [600,-450,00]; // spital
    eye [800,800,600];
    lookat [200, 0,150];
    resolution (60, 40);
  }
  background [.88,.85,.9];
};

pointLight   (1.0, [1,1,1]) { position [  400,   400,  1000]; radius 10;}

//pointLight   (0.3, [1,1,1]) { position [  0,1000,  2000]; radius 10;}
//pointLight   (0.3, [1,1,1]) { position [  1000,0, 2000]; radius 10;}
//pointLight   (0.3, [1,1,1]) { position [  1000,0,  2000]; radius 10;}
//pointLight   (0.3, [1,1,1]) { position [  0,0,  2000]; radius 10;}

ambientLight (0.3, [1,1,1]);

#endif
// _viewing_bsdl3
