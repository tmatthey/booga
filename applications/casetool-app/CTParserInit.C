/*
 * $RCSfile: CTParserInit.C,v $
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
 *  $Id: CTParserInit.C,v 1.1 1996/10/30 15:31:38 amann Exp $
 * -----------------------------------------------------------------------------
 */

#include "CTClassDescription2D.h"
#include "CTOperationDescription.h"
#include "CTClassDescription2DAttributes.h"
#include "CTOperationDescriptionAttr.h"
#include "TextBox2D.h"
#include "TextBox2DAttr.h"

#include "booga/component/BSDLParser.h"
#include "booga/component/BSDLParserInit.h"
#include "CTParserInit.h"

//___________________________________________________________ Global Namespace

void initCTParserGlobalNS()
{
  initBSDLParserGlobalNS();
}

//_______________________________________________________________ Namespace 2D

void initCTParser2DNS()
{
  initBSDLParser2DNS();

  registerParserExemplar("2D", ctClass, CTClassDescription2D);
  registerParserAttribute("2D", ctOrigin, ctClass, CTClassDescription2DAttrOrigin);
  registerParserAttribute("2D", ctWidth, ctClass, CTClassDescription2DAttrWidth);
  registerParserAttribute("2D", ctTemplate, ctClass, CTClassDescription2DAttrTemplate);
  registerParserAttribute("2D", ctAbstract, ctClass, CTClassDescription2DAttrAbstract);
  registerParserAttribute("2D", ctAttribute, ctClass, CTClassDescription2DAttrAttribute);
  registerParserAttribute("2D", ctBase, ctClass, CTClassDescription2DAttrBase);
  registerParserExemplar("2D", ctOperation, CTOperationDescription);
  registerParserAttribute("2D", ctVirtual, ctOperation, CTOperationDescriptionAttrVirtual);
  registerParserAttribute("2D", ctParameter, ctOperation, CTOperationDescriptionAttrParameter);

  registerParserExemplar("2D", textbox, TextBox2D);
  registerParserAttribute("2D", textline, textbox, TextBox2DAttrText);
}

