/*
 * color.inc
 *
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
 *                     University of Berne, Switzerland
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
 *  $Id: color.inc,v 1.3 1997/05/26 13:45:14 matthey Exp $
 * -----------------------------------------------------------------------------
 */
#ifndef _color_inc
#define _color_inc
  
define white          whitted { ambient [.05,.05,.05]; diffuse [.9,.9,.9]; }
define black          whitted { ambient [.2,.2,.2];diffuse [0,0,0]; }
define red            whitted { ambient [.2,.2,.2];diffuse [.4,.1,.1]; }
define yellow         whitted { ambient [.2,.2,.2];diffuse [1,1,0]; }
//define green          whitted { ambient [.2,.2,.2];diffuse [.2,.5,.2]; }
define green2         whitted { ambient [.2,.2,.2];diffuse [.3,.6,.2]; }
define brown          whitted { ambient [.2,.2,.2];diffuse [.3,.2,.2]; }
define brown2         whitted { ambient [.2,.2,.2];diffuse [.6,.5,.5]; }
define blue           whitted { ambient [.2,.2,.2];diffuse [.3,.2,.9]; }
define grey           whitted { ambient [.2,.2,.2];diffuse [.7,.7,.7]; }
define metall         whitted { diffuse [.9,.9,.95];}// specular [1,1,1]; specpow 20;};
define metall_s       whitted { diffuse [.7,.65,.1];}// specular [1,1,1]; specpow 40;};
define metall_hib     whitted { diffuse [150/255,157/255,181/255];}// specular [1,1,1]; specpow 40;};
define rot            whitted { ambient [.1,.1,.1]; diffuse [.8,.3,.1];}// specular [1,1,1]; specpow 50;};
define blau           whitted { diffuse [.4,.4,.9];}// specular [1,1,1]; specpow 50;};
define blau_hib       whitted { diffuse [10/255,51/255,76/255];}// specular [1,1,1]; specpow 50;};
define pneu           whitted { diffuse [.01,.01,.01];}// specular [.3,.3,.3]; specpow 3;};
define braun          whitted { ambient [.1,.1,.1];  diffuse [10/255,117/255,125/255];}// specular [.9,.8,0]; specpow 3;}
define green          whitted { ambient [.1,.3,.1]; diffuse [42/255,94/255,73/255];}// specular [.9,.9,.9]; specpow 20;}
define dachGreen      whitted { ambient [.1,.3,.25]; diffuse [170/255,204/255,196/255];}// specular [.9,.9,.9]; specpow 20;}
define asphalt        whitted { ambient [.1,.1,.1]; diffuse [.3,.3,.3];}// specpow 2;}
define weiss          whitted { ambient [.7,.7,.7]; diffuse [1,1,1];};
define ground         whitted { ambient [.1,.1,.1]; diffuse [.6,.6,.6];};
define sandstein      whitted { ambient [.3,.2,.25]; diffuse [220/255,200/255,170/255];}
define sandsteinWeiss whitted { ambient [.4,.4,.4]; diffuse [220/255,210/255,200/255];}
define darkGreen      whitted { ambient [.4,.4,.4]; diffuse [90/255,150/255,70/255];}
define darkGreen2     whitted { ambient [.4,.4,.4]; diffuse [90/255,180/255,120/255];}
define gold           whitted { ambient [.4,.4,.4]; diffuse [230/255,220/255,40/255];}//specpow 30; specular [1,1,1];}
define glasDunkel     whitted { ambient [.1,.1,.1]; diffuse [60/255,90/255,80/255];}
define dachRot        whitted { ambient [.1,.1,.1]; diffuse [180/255,115/255,97/255];}
define dachSchuetz    whitted { ambient [.15,.1,.1];diffuse [.25,.15,.15]; }
define dachIam        whitted { ambient [.21,.2,.2];diffuse [.35,.33,.3]; }
define gruenDunkel    whitted { ambient [.1,.3,.1]; diffuse [.3,.5,.3];}// specular [.9,.9,.9]; specpow 20;}
define gruenHell      whitted { ambient [.1,.7,.1]; diffuse [.3,.6,.1];}// specular [.9,.9,.9]; specpow 20;}
define gruenSpiegel   whitted { ambient [.3,.3,.3]; diffuse [.6,.6,.3];}// reflectivity .7;}
//define gruenSpiegel whitted { ambient [.3,.3,.3]; diffuse [.6,.1,.1]; specular [.9,.9,.9]; specpow 20;reflectivity .7;}
define beton          whitted { ambient [.3,.3,.3]; diffuse [.9,.95,.9];}// specular [.9,.9,.9]; specpow 20;}
define orange         whitted { ambient [.3,.3,.3]; diffuse [.9,.6,.1];}// specular [.9,.9,.9]; specpow 20;}
//define textureWall    polygonmapper( "brickyellow.jpg",0.1,0.1,0){
//                        ambient [199/255,172/255, 92/255]*.5;
//                      }
define textureWall sandstein;
#endif
// _color_inc

