/*
 * CTAttributeDescription.C
 *
 * Copyright (C) 1994-96, Thomas Wenger <wenger@iam.unibe.ch>
 *                        Thomas von Siebenthal <siebenth@iam.unibe.ch>
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
 *  $Id: CTAttributeDescription.C,v 1.6 1996/09/10 13:27:21 siebenth Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "CTAttributeDescription.h"

//_______________________________________________________ CTAttributeDescription


CTAttributeDescription::CTAttributeDescription () {
  myView = Unspecified;
  myAssociation = NULL;
};

CTAttributeDescription::CTEView CTAttributeDescription::getView() {
  return myView;
};

void CTAttributeDescription::setView(CTAttributeDescription::CTEView View) {
  myView = View;
};

CTClassDescription2D* CTAttributeDescription::getAssociation() {
  return myAssociation;
};

void CTAttributeDescription::setAssociation(CTClassDescription2D* Association) {
  myAssociation = Association;
};  

bool CTAttributeDescription::getIsTemplate () {
  return myIsTemplate;
};

void CTAttributeDescription::setIsTemplate (bool IsTemplate) {
  myIsTemplate = IsTemplate;
};
