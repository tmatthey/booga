/*
 * ShaderExpNode.h
 *
 * Copyright (C) 1995 Thomas Teuscher <teuscher@iam.unibe.ch>
 *                    University of Berne Switzerland
 *
 * All rights reserved.
 *
 * This software may be freely copied, modified and redistributed
 * provided that this copyright note be preserved on all copies.
 * 
 * You may not distribute this software, in whole or in part, as part
 * of any commercial product without the express consent of the author.
 *
 * There is no warranty or other guarantee of fitness of this software
 * for any purpose. It is provided solely "as is".
 *
 * -----------------------------------------------------------------------------
 *  $Id: ShaderExpNode.h,v 1.3 1996/04/18 14:30:55 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderExpNode_H
#define _ShaderExpNode_H

#include "booga/texture/ShaderNode.h"

class ShaderExpNode : public ShaderNode {

public:
  virtual Value* evaluate(Texture3DContext& context) = 0;
  // for the expressions we need to use the virtual method evaluate instead
  // of execute because execute has no return value
};

#endif

