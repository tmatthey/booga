/* $Id: shade.h,v 1.3 1997/06/20 02:28:40 brianp Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  2.3
 * Copyright (C) 1995-1997  Brian Paul
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


/*
 * $Log: shade.h,v $
 * Revision 1.3  1997/06/20 02:28:40  brianp
 * changed color components from GLfixed to GLubyte
 *
 * Revision 1.2  1997/05/23 03:01:18  brianp
 * commented out a few const keywords because IRIX cc chokes on them
 *
 * Revision 1.1  1997/04/01 04:10:06  brianp
 * Initial revision
 *
 */


#ifndef SHADE_H
#define SHADE_H


#include "booga/glosmesa/types.h"


extern void gl_color_shade_vertices( GLcontext *ctx,
                                     GLuint side,
                                     GLuint n,
                                     /*const*/ GLfloat vertex[][4],
                                     /*const*/ GLfloat normal[][3],
                                     GLubyte color[][4] );


extern void gl_color_shade_vertices_fast( GLcontext *ctx,
                                          GLuint side,
                                          GLuint n,
                                          /*const*/ GLfloat normal[][3],
                                          GLubyte color[][4] );


extern void gl_index_shade_vertices( GLcontext *ctx,
                                     GLuint side,
                                     GLuint n,
                                     GLfloat vertex[][4],
                                     GLfloat normal[][3],
                                     GLuint indexResult[] );

#endif

