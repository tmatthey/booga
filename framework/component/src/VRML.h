/*
 * $RCSfile: VRML.h,v $ 
 *
 * Copyright (C) 1996, Beat Liechti <liechti@isbe.ch>
 *                     Ingenieurschule Bern, Switzerland
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
 *  $Id: VRML.h,v 1.2 1996/08/01 12:01:30 streit Exp $
 * -----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------*
 *  vrml.h
 *           
 * Project: SICS DIVE
 * Copyright: SICS
 * Implemented by: Emmanuel Frécon and Olof Hagsand
 *
 *---------------------------------------------------------------------------*/

#ifndef _VRML_H
#define _VRML_H

/* Text justification */
enum VRML_justification {
  VRML_LEFT,
  VRML_CENTER,
  VRML_RIGHT
};
typedef enum VRML_justification VRML_justification_t;

/* Parts of cones and cylinder */
#define VRML_SIDES  (1L<<0)
#define VRML_BOTTOM (1L<<1)
#define VRML_TOP    (1L<<2)
#define VRML_ALL    (VRML_SIDES | VRML_BOTTOM | VRML_TOP)

/* Font family */
enum VRML_font_family {
  VRML_SERIF,
  VRML_SANS,
  VRML_TYPEWRITER
};
typedef enum VRML_font_family VRML_font_family_t;

/* Font styles */
#define VRML_NONE   (1L<<0)
#define VRML_BOLD   (1L<<1)
#define VRML_ITALIC (1L<<2)

/* Bindings */
enum VRML_binding {
  VRML_DEFAULT,
  VRML_OVERALL,
  VRML_PER_PART,
  VRML_PER_PART_INDEXED,
  VRML_PER_FACE,
  VRML_PER_FACE_INDEXED,
  VRML_PER_VERTEX,
  VRML_PER_VERTEX_INDEXED
};
typedef enum VRML_binding VRML_binding_t;

/* Culling */
enum VRML_culling {
  VRML_ON,
  VRML_OFF,
  VRML_AUTO
};
typedef enum VRML_culling VRML_culling_t;

/* vertex ordering */
enum VRML_vertex_ordering {
  VRML_UNKNOWN_ORDERING,
  VRML_CLOCKWISE,
  VRML_COUNTERCLOCKWISE
};
typedef enum VRML_vertex_ordering VRML_vertex_ordering_t;

/* Shape Type */
enum VRML_shape_type {
  VRML_UNKNOWN_SHAPE_TYPE,
  VRML_SOLID
};
typedef enum VRML_shape_type VRML_shape_type_t;

/* Face type */
enum VRML_face_type {
  VRML_UNKNOWN_FACE_TYPE,
  VRML_CONVEX
};
typedef enum VRML_face_type VRML_face_type_t;

/* Wrap */
enum VRML_wrap {
  VRML_REPEAT,
  VRML_CLAMP
};
typedef enum VRML_wrap VRML_wrap_t;


#endif
