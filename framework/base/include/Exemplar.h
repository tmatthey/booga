/*
 * Exemplar.h 
 *
 * An instance of class Exemplar is used in the parameter list of
 * a constructors to notify the creation of an exemplar (prototype).
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Exemplar.h,v 1.2 1995/04/21 12:32:23 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Exemplar_H
# define _Exemplar_H

//______________________________________________________________________ Exemplar

class Exemplar { 
public: 
  Exemplar() {} 
};

static Exemplar anExemplar;

#endif // _Exemplar_H
