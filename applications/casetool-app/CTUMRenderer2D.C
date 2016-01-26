/*
 * CTUMRenderer2D.C
 *
 * Copyright (C) 1994-96, Thomas Wenger
 *                        Thomas von Siebenthal
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
 * for any purpose.  It is provided solely as is.
 *
 * -----------------------------------------------------------------------------
 *  $Id: CTUMRenderer2D.C,v 1.28 1996/12/04 09:15:15 wenger Exp $
 * -----------------------------------------------------------------------------
 */
   
#include <math.h>
#include "booga/base/RCString.h"
#include "booga/base/List.h"
#include "booga/object/Object2D.h"
#include "booga/object/Shared2D.h"
#include "booga/object/Line2D.h"
#include "booga/component/CollectShared2D.h"
#include "CTUMRenderer2D.h"
#include "TextBox2D.h"
#include "booga/object/Text2D.h"
#include "CTAttributeDescription.h"
#include "booga/object/ConstantTexture2D.h"
#include "booga/glwrapper/GLConstantTexture2D.h"

//_________________________________________________________________ CTUMRenderer2D

implementRTTI(CTUMRenderer2D, Operation2D);



CTUMRenderer2D::CTUMRenderer2D()
{
  // Option Flags for rendering:
  myViewsIsVisible = true;
  myOperationsIsVisible = true;
  myAttributesIsVisible = true;
  myOperationDetailsIsVisible = true;
  myPositioningIsEnabled = true;

  // constants for this class:
  FONT_HEIGHT_CLASSNAME = 14;       // titleline with classname
  FONT_HEIGHT_STANDARD = 10;        // all the normal text
  TEXTBOX_STANDARD_WIDTH = 300;     // fixed width of the boxes
  TEMPLATE_PARAMETER_BOXWIDTH_FACTOR = 0.6; // to be multiplied with TEXTBOX_STANDARD_WIDTH
  TEXTBOX_STANDARD_LINELENGTH = int(TEXTBOX_STANDARD_WIDTH*0.16); // number of character per line
  STANDARD_ARROW_LENGTH = 15;       // length of an arrow-wing
  ARROW_ALPHA = 0.4;                // opening of the arrows

  // prepare the textures:
  BlueGLTexture = new GLConstantTexture2D(Color(0,0,1));
  BlueTexture = new ConstantTexture2D(Color(0,0,1));
  RedGLTexture = new GLConstantTexture2D(Color(1,0,0));
  RedTexture = new ConstantTexture2D(Color(1,0,0));
  GreenGLTexture = new GLConstantTexture2D(Color(.2,.8,.3));
  GreenTexture = new ConstantTexture2D(Color(.2,.8,.3));
  BlackGLTexture = new GLConstantTexture2D(Color(0,0,0));
  BlackTexture = new ConstantTexture2D(Color(0,0,0));
  WhiteGLTexture = new GLConstantTexture2D(Color(1,1,1));
  WhiteTexture = new ConstantTexture2D(Color(1,1,1));

  CTUMRenderer2DClean();            // Init of the member variables
}


void CTUMRenderer2D::CTUMRenderer2DClean()
{
  // Init of the data members:
  myBodyMaxHeight = 0;
  myNumberOfClasses = 0;
  myNumberOfActualClass = 0;
  myClassesPerRow = 0;
  myClassesPerColumn = 0;
  myClassGridDx = 0;
  myClassGridDy = 0;
}  

void CTUMRenderer2D::setViewsIsVisible(bool isOn)
{
  myViewsIsVisible = isOn;
}
void CTUMRenderer2D::setOperationsIsVisible(bool isOn)
{
  myOperationsIsVisible = isOn;
}
void CTUMRenderer2D::setAttributesIsVisible(bool isOn)
{
  myAttributesIsVisible = isOn;
}
void CTUMRenderer2D::setOperationDetailsIsVisible(bool isOn)
{
  myOperationDetailsIsVisible = isOn;
}

void CTUMRenderer2D::setmyPositioningIsEnabled(bool isEnabled)
{
  myPositioningIsEnabled = isEnabled;
}
 
bool CTUMRenderer2D::doExecute()
{
  //before each apply the variable init is redone:
  CTUMRenderer2DClean();
        
  // 1. do the body:
  myRenderingStatus = DoingBodies;
  traverse(getWorld());
  
  // 2. do the positioning:
  // put the bodies into a square-grid:
  myRenderingStatus = DoingPositioning;
  int NumberPerRowForSquare = int(ceil(sqrt(myNumberOfClasses)));
  myClassesPerRow = NumberPerRowForSquare;
  myClassesPerColumn = NumberPerRowForSquare;     
  // calculate the spacing between the bodies:
  myClassGridDx = TEXTBOX_STANDARD_WIDTH*2.0;
  myClassGridDy = myBodyMaxHeight*1.5;
  traverse(getWorld());
  
  // 3. do the connectors:
  myRenderingStatus = DoingConnectors;
  traverse(getWorld());
  
  getWorld()->getObjects()->computeBounds();

  return true;       // result for doExecute
}

 
void CTUMRenderer2D::doBodies(CTClassDescription2D* obj)
{
  // one more class (classes have to be counted for the positioning:
  myNumberOfClasses++;


  // prepare TextBox for Template Parameters:
  List<RCString> textTemplateParameters;
  textTemplateParameters.append(obj->getTemplateParameters());
  TextBox2D* textBoxTemplateParameters = new TextBox2D(textTemplateParameters);  
  textBoxTemplateParameters->setFontHeight(FONT_HEIGHT_STANDARD);
  textBoxTemplateParameters->setWidth(TEXTBOX_STANDARD_WIDTH*TEMPLATE_PARAMETER_BOXWIDTH_FACTOR);
  textBoxTemplateParameters->wrapText(int(TEXTBOX_STANDARD_LINELENGTH/2));
  Real textBoxTemplateParametersHeight=0;  
  // if we have template parameters then we are higher:
  if (obj->getIsTemplate())
    textBoxTemplateParametersHeight = textBoxTemplateParameters->calculateHeight();
  
  
  // prepare TextBox for ClassName:
  // Text and box for the class name have to be generated manually
  // without textbox, because the template box interferes in the 
  // upper right corner:
  // prepare the graphical text for the classname:
  Text2D* textClassName = new Text2D(obj->getName());
  textClassName->setHeight(FONT_HEIGHT_CLASSNAME);
  textClassName->computeBounds();
  Vector2D textClassNameDiagonal = Vector2D(textClassName->getBounds().getMax()-textClassName->getBounds().getMin());
  Real textClassNameHeight = textClassNameDiagonal.y();
  Real textClassNameWidth = textClassNameDiagonal.x();
  // prepare the graphical text for the word "abstract":
  Text2D* textAbstract = new Text2D("abstract");
  textAbstract->setHeight(FONT_HEIGHT_STANDARD);
  textAbstract->computeBounds();
  Vector2D textAbstractDiagonal = Vector2D(textAbstract->getBounds().getMax()-textAbstract->getBounds().getMin());
  Real textAbstractHeight = textAbstractDiagonal.y();
  // calculate the corners of the box:
  //      UL -------- UR1  
  //       |                 UR2
  //       |                  |
  //      LL ----------------LR
  Vector2D LL(0,0),LR(TEXTBOX_STANDARD_WIDTH,0),UL,UR1,UR2;
  if (obj->getIsAbstract())
  {
    UL = Vector2D(0,2*textClassNameHeight+1*textAbstractHeight);
    UR1 = UR2 = Vector2D(TEXTBOX_STANDARD_WIDTH,2*textClassNameHeight+1*textAbstractHeight);
  }
  else
  {
    UL = Vector2D(0,2*textClassNameHeight);
    UR1 = UR2 = Vector2D(TEXTBOX_STANDARD_WIDTH,2*textClassNameHeight);
  }
  // if we have a templateparameterbox, the UR1 and UR2 are not the same:
  if (obj->getIsTemplate())
  {
    UR1 -= Vector2D(TEXTBOX_STANDARD_WIDTH*(1-TEMPLATE_PARAMETER_BOXWIDTH_FACTOR),0);
    UR2 -= Vector2D(0,textBoxTemplateParametersHeight/2);
  }
  // let's compose all to handmade "textbox":
  List2D* textBoxClassName = new List2D;
  textBoxClassName->adoptObject(new Line2D(UL,UR1));
  textBoxClassName->adoptObject(new Line2D(UR2,LR));
  textBoxClassName->adoptObject(new Line2D(LR,LL));
  textBoxClassName->adoptObject(new Line2D(LL,UL));
  //  do the positioning of the text:
  // if we have templateparameters, the Classname is left aligned otherwise centered:
  if (obj->getIsTemplate())
    textClassName->addTransform(TransMatrix2D::makeTranslate(UL+Vector2D(10,-(1.5*textClassNameHeight))));
  else
    textClassName->addTransform(TransMatrix2D::makeTranslate(UL+Vector2D((TEXTBOX_STANDARD_WIDTH-textClassNameWidth)/2,-(1.5*textClassNameHeight))));
  textBoxClassName->adoptObject(textClassName);
  if (obj->getIsAbstract())
  {
    textAbstract->addTransform(TransMatrix2D::makeTranslate(Vector2D(0.5*TEXTBOX_STANDARD_WIDTH,0.7*textAbstractHeight)));
    textBoxClassName->adoptObject(textAbstract);
  }
  Real textBoxClassNameHeight = UL.y();


  // prepare TextBox for Attributes:
  // example:  #name: type = initvalue
  List<RCString> textAttributes;
  RCString aTextLine;
  if (myAttributesIsVisible)
  {
    for (long i=obj->getAttributeIndexMin(); i<=obj->getAttributeIndexMax(); i++)
    {
      CTAttributeDescription anAttribute;
      anAttribute = obj->getAttributeByIndex(i);
      // check if it is a normal variable or an associated class:
      if (anAttribute.getAssociation() == NULL)      
      {
        aTextLine = "";
        if (myViewsIsVisible)
        {
          // begin with the view sign:
          switch (anAttribute.getView())
          {
            case CTAttributeDescription::Private:   aTextLine += "-"; break;
            case CTAttributeDescription::Public:    aTextLine += "+"; break;
            case CTAttributeDescription::Protected: aTextLine += "#"; break;
            default:                                aTextLine += "";
         }  
        }         
        // append name:
        aTextLine += anAttribute.getName();
        // append type if there:
        if (anAttribute.getType() != "")
          aTextLine = aTextLine + ": " + anAttribute.getType();
        // append init value if there:
        if (anAttribute.getInitValue() != "") 
          aTextLine += " = " + anAttribute.getInitValue();
        // this attribute is completed, so append to all attributes:
        textAttributes.append(aTextLine);   
      }
    }
  }
  TextBox2D* textBoxAttributes = new TextBox2D(textAttributes);
  textBoxAttributes->setFontHeight(FONT_HEIGHT_STANDARD);
  textBoxAttributes->setWidth(TEXTBOX_STANDARD_WIDTH);
  textBoxAttributes->wrapText(TEXTBOX_STANDARD_LINELENGTH);

  // prepare TextBox for Operations:
  // example: #name(para1: type = init, para2: type = init): returntype {abstract}
  List<RCString> textOperations;
  if (myOperationsIsVisible)
  {
    for (long i=obj->getOperationIndexMin(); i<=obj->getOperationIndexMax(); i++)
    {
      CTOperationDescription anOperation;
      anOperation = obj->getOperationByIndex(i);
      // begin with the view sign:
      aTextLine = "";
      if (myViewsIsVisible)
      {
        // begin with the view sign:
        switch (anOperation.getView())
        {
          case CTAttributeDescription::Private:   aTextLine += "-"; break;
          case CTAttributeDescription::Public:    aTextLine += "+"; break;
          case CTAttributeDescription::Protected: aTextLine += "#"; break;
          default:                                aTextLine += "";
        }  
      }         
      // append operation name:
      aTextLine += anOperation.getName();

      if (myOperationDetailsIsVisible)
      {
        aTextLine += "(";

        // do all the parameters of the operation:
        CTVariableDescription aParameter;

        if (anOperation.getParameterIndexMin()<=anOperation.getParameterIndexMax())
        {
          for (long j=anOperation.getParameterIndexMin(); j<=anOperation.getParameterIndexMax(); j++)
          {
            aParameter = anOperation.getParameterByIndex(j);
            // if not the first parameter, then append a comma:
            if (j != anOperation.getParameterIndexMin())
              aTextLine += ", ";
            // append parameter name:
            aTextLine += aParameter.getName();
            // append type if there:
            if (aParameter.getType() != "")
              aTextLine += ": " + aParameter.getType();
            // append init value if there:
            if (aParameter.getInitValue() != "")
              aTextLine += " = " + aParameter.getInitValue();
          }
        }  
        aTextLine = aTextLine + ")";
        // append return type if there:
        if (anOperation.getReturnType() != "")
          aTextLine += ": " + anOperation.getReturnType();
        // append the mark {abstract} if opeartion really is:
        if (anOperation.getIsAbstract())
          aTextLine += " {abstract}";
      }          
      textOperations.append(aTextLine);
    }
  }
  TextBox2D* textBoxOperations = new TextBox2D(textOperations);
  textBoxOperations->setFontHeight(FONT_HEIGHT_STANDARD);
  textBoxOperations->setWidth(TEXTBOX_STANDARD_WIDTH);
  textBoxOperations->wrapText(TEXTBOX_STANDARD_LINELENGTH);

  // assemble the TextBoxes to one class-body:
  Real textBoxAttributesHeight=0, textBoxOperationsHeight=0;
  // if there are attributes or operations then both boxes are drawn:
  if ((textAttributes.size()>0) || (textOperations.size()>0))
  {
    textBoxAttributesHeight = textBoxAttributes->calculateHeight();
    textBoxOperationsHeight = textBoxOperations->calculateHeight();
  }
  // put the boxes to the right relative postion in relation to origin:
  textBoxAttributes->addTransform(TransMatrix2D::makeTranslate(0,textBoxOperationsHeight));
  textBoxClassName->addTransform(TransMatrix2D::makeTranslate(0,textBoxOperationsHeight+textBoxAttributesHeight));
  textBoxTemplateParameters->addTransform(TransMatrix2D::makeTranslate(TEXTBOX_STANDARD_WIDTH
                       *TEMPLATE_PARAMETER_BOXWIDTH_FACTOR,textBoxOperationsHeight+textBoxAttributesHeight
                       +textBoxClassNameHeight-textBoxTemplateParametersHeight/2));
 
  List2D* aBody = new List2D;
  aBody->appendTexture(BlackTexture);
  aBody->appendTexture(BlackGLTexture);
  aBody->adoptObject(textBoxClassName);
  // if there are no attributes nor operations then ommit both boxes:
  if ((textAttributes.size()>0) || (textOperations.size()>0))
  {
    aBody->adoptObject(textBoxAttributes);
    aBody->adoptObject(textBoxOperations);
  }
  // append Template Parameters Box, if needed:
  if (obj->getIsTemplate())
    aBody->adoptObject(textBoxTemplateParameters);
  obj->adoptBody(aBody);
  obj->setWidth(TEXTBOX_STANDARD_WIDTH);
  Real bodyActualHeight = textBoxClassNameHeight+textBoxAttributesHeight
                +textBoxOperationsHeight /*+textBoxTemplateParametersHeight*/;
  if (bodyActualHeight>myBodyMaxHeight)
   myBodyMaxHeight = bodyActualHeight;
  obj->setHeight(bodyActualHeight);
}


void CTUMRenderer2D::doPositioning(CTClassDescription2D* obj)
{
  myNumberOfActualClass++;

  if (myPositioningIsEnabled) {
  // get the rendered body:
  List2D* aBody = obj->getBody();

  Real PosX =  0 + ((myNumberOfActualClass-1) % myClassesPerRow) * myClassGridDx;
  Real PosY =  0 + floor((myNumberOfActualClass-1) / (myClassesPerColumn)) * myClassGridDy;

  obj->setOrigin(Vector2D(PosX,PosY));
  aBody->addTransform(TransMatrix2D::makeTranslate(PosX,PosY));
  obj->adoptBody(aBody);
  }
  generateDockingPoints(obj);
}


void CTUMRenderer2D::doConnectors(CTClassDescription2D* obj)
{

  List2D* connectors = new List2D;
  CTBaseclassDescription aBaseclass;
  Vector2D connectorTail;
  Vector2D connectorHead;
  Vector2D arrow;

  // connectors for aBaseclasses:
  for (long i=obj->getBaseclassIndexMin(); i<=obj->getBaseclassIndexMax(); i++)
  {
    aBaseclass = obj->getBaseclassByIndex(i);
    getNearestDockingPoints(obj,aBaseclass.getBaseclass(),connectorTail,connectorHead);

    arrow = connectorTail-connectorHead;
    arrow = arrow/arrow.length()*STANDARD_ARROW_LENGTH;

    Line2D* arrowL = new Line2D(Vector2D(0,0),arrow);
    Line2D* arrowR = new Line2D(Vector2D(0,0),arrow);

    arrowL->addTransform(TransMatrix2D::makeRotateOrigin(ARROW_ALPHA));
    arrowR->addTransform(TransMatrix2D::makeRotateOrigin(-ARROW_ALPHA));

    arrowL->addTransform(TransMatrix2D::makeTranslate(connectorHead));
    arrowR->addTransform(TransMatrix2D::makeTranslate(connectorHead));

    Line2D* aLine = new Line2D(connectorTail,connectorHead);

    arrowL->appendTexture(BlueTexture);
    arrowL->appendTexture(BlueGLTexture);
    arrowR->appendTexture(BlueTexture);
    arrowR->appendTexture(BlueGLTexture);
    aLine->appendTexture(BlueTexture);
    aLine->appendTexture(BlueGLTexture);

    connectors->adoptObject(arrowL);
    connectors->adoptObject(arrowR);

    connectors->adoptObject(aLine);
  }


  // connectors for Associations:

  CTAttributeDescription Attribute;

  for (long i=obj->getAttributeIndexMin(); i<=obj->getAttributeIndexMax(); i++)
  {
    Attribute = obj->getAttributeByIndex(i);
    // check if it is a normal variable or an associated class:
    if (Attribute.getAssociation() != NULL)
    {
      getNearestDockingPoints(obj,Attribute.getAssociation(),connectorTail,connectorHead);
      Line2D* aLine = new Line2D(connectorTail,connectorHead);
      aLine->appendTexture(GreenTexture);
      aLine->appendTexture(GreenGLTexture);
      connectors->adoptObject(aLine);
      // add the name of the association at the connector near the tail of the line:
      Text2D* aTextLine = new Text2D(Attribute.getName());
      aTextLine->setHeight(FONT_HEIGHT_STANDARD);
      Vector2D posForName = connectorTail+(connectorHead-connectorTail)*1/4;
      aTextLine->addTransform(TransMatrix2D::makeTranslate(posForName));
      aTextLine->appendTexture(GreenTexture);
      aTextLine->appendTexture(GreenGLTexture);
      connectors->adoptObject(aTextLine);
    }
  }
  obj->adoptConnectors(connectors);
}

Traversal::Result CTUMRenderer2D::visit(CTClassDescription2D* obj)
{

   // do the rendering of the class:
   // prepare the body:   *********************************************
   if (myRenderingStatus == DoingBodies) 
     doBodies(obj);   
      
   // prepare the positions: **********************************************
   if (myRenderingStatus == DoingPositioning)
     doPositioning(obj);
   
   // prepare the connectors: ********************************************
   if (myRenderingStatus == DoingConnectors)
     doConnectors(obj);
   
   return Traversal::CONTINUE;
}


// Methods to manage the Dockingpoints:
void CTUMRenderer2D::generateDockingPoints(CTClassDescription2D* theClass)
{
  Real width = theClass->getWidth();
  Real height = theClass->getHeight();
  Vector2D origin = theClass->getOrigin();
  
  Vector2D vecWidth = Vector2D(width,0);
  Vector2D vecHeight = Vector2D(0,height);
  // make shure there are no docking points:  
  theClass->getDockingPoints()->removeAll();
  // the left side:
  theClass->getDockingPoints()->append(origin+vecHeight/4);
  theClass->getDockingPoints()->append(origin+vecHeight*3/4);
  // the upper side:
  theClass->getDockingPoints()->append(origin+vecHeight+vecWidth/4);
  if (!theClass->getIsTemplate())
    theClass->getDockingPoints()->append(origin+vecHeight+vecWidth*3/4);
  // the lower side:
  theClass->getDockingPoints()->append(origin+vecWidth/4);
  theClass->getDockingPoints()->append(origin+vecWidth*3/4);
  // the right side:
  theClass->getDockingPoints()->append(origin+vecWidth+vecHeight/4);
  if (!theClass->getIsTemplate())
    theClass->getDockingPoints()->append(origin+vecWidth+vecHeight*3/4);
  // the center of all sides (last found is preferred and we like center:)
  theClass->getDockingPoints()->append(origin+vecWidth+vecHeight/2);
  theClass->getDockingPoints()->append(origin+vecHeight/2);
  theClass->getDockingPoints()->append(origin+vecHeight+vecWidth/2);
  theClass->getDockingPoints()->append(origin+vecWidth/2);
}  

long CTUMRenderer2D::getDockingPointIndexMin(CTClassDescription2D* /* theClass */) 
{ 
  return 0; 
};

long CTUMRenderer2D::getDockingPointIndexMax(CTClassDescription2D* theClass) 
{
  return (theClass->getDockingPoints()->count() - 1);
};

Vector2D CTUMRenderer2D::getDockingPointByIndex(CTClassDescription2D* theClass, long index) const
{
  return theClass->getDockingPoints()->item(index);
};
  
void CTUMRenderer2D::getNearestDockingPoints(CTClassDescription2D* thisClass, CTClassDescription2D* otherClass, Vector2D &thisPoint, Vector2D &otherPoint)
{
  Vector2D ownDocking=Vector2D(0,0), otherDocking=Vector2D(0,0);
  Real distance=0, actualDistance=9e9;
  
  for (int i=getDockingPointIndexMin(thisClass); i<=getDockingPointIndexMax(thisClass); i++)
  {
    for (int j=getDockingPointIndexMin(otherClass); j<=getDockingPointIndexMax(otherClass); j++)
    {
       ownDocking = getDockingPointByIndex(thisClass,i);
       otherDocking = getDockingPointByIndex(otherClass,j);
       distance = (ownDocking-otherDocking).length();
       if (distance<=actualDistance)
       {
         thisPoint = ownDocking;
         otherPoint = otherDocking;
         actualDistance = distance;
       }         
    }
  }
};
 
Traversal::Result CTUMRenderer2D::dispatch(Makeable* obj)
{
  tryConcrete(CTClassDescription2D, obj);
  
  //
  // Create decomposition for objects other than triangles.
  //
  return Traversal::UNKNOWN;
}
