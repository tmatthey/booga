/*
 * $RCSfile: MInteractionObject.C,v $
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: MInteractionObject.C,v 1.2 1996/08/07 16:15:00 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
/*
 * GNU compiler has a pretty bad handling of templates...
 */
#if defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)
// Only compile this file if either not GNU compiler running,
// or, in case of GNU compiler, files is included from header.

#include "booga/base/Exemplar.h"

#ifdef TEMPLATE_IN_HEADER
# define INLINE inline
#else
# include "booga/object/MInteractionObject.h"
# define INLINE
#endif  // TEMPLATE_IN_HEADER


template <class TProxy, class TInteractioObject, class TPath, class TWorld>
INLINE MInteractionObject<TProxy, TInteractioObject, TPath, TWorld>
::MInteractionObject(Exemplar exemplar)
: TProxy(exemplar) {}

#undef INLINE  
#endif // defined( TEMPLATE_IS_INCLUDE_FROM_H) || !defined(TEMPLATE_IN_HEADER)

