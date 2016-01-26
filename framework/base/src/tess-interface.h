/*
 * tess-interface.h
 *
 * This code is in the public domain. Specifically, we give to the public
 * domain all rights for future licensing of the source code, all resale
 * rights, and all publishing rights.
 * 
 * UNC-CH GIVES NO WARRANTY, EXPRESSED OR IMPLIED, FOR THE SOFTWARE
 * AND/OR DOCUMENTATION PROVIDED, INCLUDING, WITHOUT LIMITATION, WARRANTY
 * OF MERCHANTABILITY AND WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE.
 *
 *                            - Atul Narkhede (narkhede@cs.unc.edu), 1995
 *
 * Orginal source code:
 *   ftp://ftp.cs.unc.edu/pub/users/narkhede/triangulation.tar.gz
 *
 * Reference:
 *   R. Seidel, 
 *   A simple and Fast Randomized Algorithm for Computing Trapezoidal 
 *   Decompositions and for Triangulating Polygons,
 *   Computational Geometry Theory & Applications, 1991.
 *
 * -----------------------------------------------------------------------------
 *  $Id: tess-interface.h,v 1.1 1996/01/18 18:15:23 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef __interface_h
#define __interface_h

#define TRUE  1
#define FALSE 0

extern int triangulate_polygon(int, int *, double (*)[2], int (*)[3]);
extern int is_point_inside_polygon(double *);

#endif /* __interface_h */
