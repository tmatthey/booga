/*
 * $RCSfile: TextBox2DAttr.C,v $
 *
 * Copyright (C) 1996, Mister Nobody <nobody@iam.unibe.ch>
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
 *  $Id: TextBox2DAttr.C,v 1.1 1996/10/30 15:31:46 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/Value.h"
#include "booga/base/Report.h"
#include "TextBox2D.h"
#include "TextBox2DAttr.h"

//_____________________________________________________ TextBox2DAttr

implementRTTI(TextBox2DAttr, ObjectAttr);

//_____________________________________________ TextBox2DAttrText

implementRTTI(TextBox2DAttrText, TextBox2DAttr);

TextBox2DAttrText::TextBox2DAttrText(RCString text)
: myText(text)
{}

Makeable* TextBox2DAttrText::make(RCString& errMsg, const List<Value*>* parameters) const
{
  checkParameterNumber(1);
  getParameter(1, RCString, text);

  return new TextBox2DAttrText(text);
}

void TextBox2DAttrText::setAttribute(TextBox2D* textbox) const
{
  textbox->addTextLine(myText);
}



