#ifndef _base_inc
#define _base_inc

using 3D;

pointLight (1, [1,1,1]) {    // Point light with intensity 1 
                             // and color [1,1,1] (white)
  position [0,0,100];
}
ambientLight (0.3, [1,1,1]);

define col_el phong  {ambient [.2,.2,.2];
                      diffuse [.2,.2,.2];
                      specpow 30;
                      specular [1,1,1];}

define col_c phong  {ambient [.4,.2,.2];
                   diffuse [.6,.2,.2];
                   specpow 30;
                   specular [1,1,1];}

define col_h phong  {ambient [.2,.2,.4];
                   diffuse [.2,.2,.6];
                   specpow 30;
                   specular [1,1,1];}

define col_cc phong  {ambient [.4,.2,.2];
                   diffuse [.7,.3,.3];
                   specpow 30;
                   specular [1,1,1];}

define col_hh phong  {ambient [.2,.2,.4];
                   diffuse [.3,.3,.7];
                   specpow 30;
                   specular [1,1,1];}

define col_o phong  {ambient [.4,.4,.4];
                   diffuse [.6,.6,.6];
                   specpow 30;
                   specular [1,1,1];}

const rEl 0.15;     // Electron
const rC 0.66140; // C
const rH 0.30394; // H
const rO 0.66140; // O
const rBond 0.23; // Bond
const rBond15 0.23*1.375; // Bond
const rBond2 0.23*1.75; // Bond
const rBond3 0.23*2.5; // Bond

define el     sphere(rEl,[0,0,0]){col_el;};
define atom_c sphere(rC,[0,0,0]){col_c;};
define atom_h sphere(rH,[0,0,0]){col_h;};
define atom_o sphere(rO,[0,0,0]){col_o;};

define bond_cc cylinder(rBond,[0,0,0],[2*rCC,0,0]){col_cc;};
define bond_cc15 cylinder(rBond15,[0,0,0],[2*rCC,0,0]){col_cc;};
define bond_cc2 cylinder(rBond2,[0,0,0],[2*rCC,0,0]){col_cc;};
define bond_cc3 cylinder(rBond3,[0,0,0],[2*rCC,0,0]){col_cc;};
define bond_ch list {cylinder(rBond,[0,0,0],[rCH,0,0]){col_hh;};
                     cylinder(rBond,[rCH,0,0],[2*rCH,0,0]){col_cc;};}
define bond_hc list {cylinder(rBond,[0,0,0],[rCH,0,0]){col_cc;};
                     cylinder(rBond,[rCH,0,0],[2*rCH,0,0]){col_hh;};}
define bond_hh list {cylinder(rBond,[0,0,0],[2*rHH,0,0]){col_hh;};}


#endif // _base_inc