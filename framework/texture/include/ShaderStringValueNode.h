/*
 * ShaderStringValueNode.h
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
 *  $Id: ShaderStringValueNode.h,v 1.1 1996/04/18 14:31:29 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ShaderStringValueNode_H
#define _ShaderStringValueNode_H

#include "booga/texture/ShaderExpNode.h"

class ShaderStringValueNode : public ShaderExpNode {

public:
  ShaderStringValueNode(RCString* theString);
  virtual void print(bool indent);
  virtual void execute(Texture3DContext& context);
  virtual Value* evaluate(Texture3DContext& context);

private:
  RCString myValue;
  int myBlockDepth;
};

#endif



