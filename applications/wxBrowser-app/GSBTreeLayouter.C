/*
 * GSBTreeLayouter.C 
 *
 * Copyright (C) 1996, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: GSBTreeLayouter.C,v 1.10 1997/04/08 11:05:01 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 

#include "booga/base/TransMatrix2D.h"
#include "booga/object/Line2D.h"
#include "booga/object/List2D.h"
#include "booga/object/World2D.h"
#include "booga/glwrapper/GLConstantTexture2D.h"


#include "GSBTreeLayouter.h"
#include "GSBFastTraversal3D.h"
#include "GSBNodeTools.h"

//_____________________________________________________________________ GSBTreeLayouter

implementRTTI(GSBTreeLayouter, Operation3DTo2D);


GSBTreeLayouter::GSBTreeLayouter()
: myViewID(-1),
  myBorder(20),
  myDistanceToParents(50),
  myVertical(false)
{
  adoptTraversal(new GSBFastTraversal3D);
}


bool GSBTreeLayouter::doExecute()
{
  if (myViewID < 0)
    Report::error("[GSBTreeLayouter::generate] Layouter not initialized");

  traverse(getWorld());
  
  // clean up the mess we made
  garbageCollection();

  GSBTreeNode* headNode = dynamic_cast(GSBTreeNode, 
     (GSBNodeTools::getNode(getWorld()->getObjects(), myViewID)));
  if (headNode->getRepresentation() == NULL)
    Report::error("[GSBTreeLayouter::generate] Couldn't layout tree...");

  // get the tree, rotate it if necessary
  Object2D* tree = headNode->orphanRepresentation();
  if (myVertical) {
    TransMatrix2D tm = TransMatrix2D::makeRotateOrigin(-M_PI/2);
    tree->addTransform(tm);
  }
  
  World2D* result = new World2D;
  result->getObjects()->adoptObject(tree);
  adoptResult(result);

  return true;
}


Traversal::Result GSBTreeLayouter::visit(Object3D* obj)
{
  myNode = dynamic_cast(GSBTreeNode, GSBNodeTools::findNode(obj, myViewID));
  if (myNode) {
    if (GSBNodeTools::getNodeManager(obj)->isPruned() || (obj->countSubobject() == 0) ) {
      layoutLeaf(obj);
      return Traversal::PRUNE;
    } else {  
      attachParent(obj, join(obj));
      return Traversal::CONTINUE;
    }
  } else {
    // Oops, node seems to be missing.. strange..
    return Traversal::PRUNE;
  }
}


Traversal::Result GSBTreeLayouter::visit(Shared3D* obj)
{
  myNode = dynamic_cast(GSBTreeNode, GSBNodeTools::findNode(obj, myViewID));
  if (myNode) {
    if (GSBNodeTools::getNodeManager(obj)->isPruned() || (obj->countSubobject() == 0) ) {
      layoutLeaf(obj);
      return Traversal::PRUNE;
    }
    else {  
      attachParent(obj, join(obj));
      return Traversal::CONTINUE;
    }
  } else {
	// Oops, node seems to be missing.. strange..
    return Traversal::PRUNE;
  }
}


Real GSBTreeLayouter::offset(const Vector2D& pos, const Vector2D& a, const Vector2D& b)
{
  if (b.x() <= pos.x() || pos.x() + a.x() <= 0) {
    return 0;
  }
  Real d;
  Real t = b.x()*a.y() - b.y()*a.x();
  if (t > 0) 
    if (pos.x() < 0) 
      d = pos.x() * a.y()/a.x() - pos.y();
    else if (pos.x() > 0) 
      d = pos.x() * b.y()/b.x() - pos.y();
    else 
      d = -pos.y();
  else if (b.x() < pos.x() + a.x())
      d = b.y() - (pos.y() + (b.x() - pos.x()) * a.y()/a.x());
    else if (b.x() > pos.x() + a.x()) 
      d = ((a.x() + pos.x()) * b.y())/b.x() - (pos.y() + a.y());
    else
      d = b.y() - (pos.y() + a.y());
  return max((Real) 0, d);  
}


void GSBTreeLayouter::attachParent(Object3D* obj, Real vHeight)
{
  Real x = myBorder + myDistanceToParents;
  Real len1((myVertical) ? myNode->getWidth()  : myNode->getHeight() ),
       len2((myVertical) ? myNode->getHeight() : myNode->getWidth());

  Real y2 = (vHeight - len1)/2 - myBorder;
  Real y1 = y2 + len1 + 2*myBorder - vHeight;

  Vector2D offset(x + ((myVertical)
        ? myNode->getHeight() : myNode->getWidth()), y1);

  // generate representation of node:
  List2D* theRep = new List2D;
  Object2D* thisNodeRep = createRep(obj, myNode);
  theRep->adoptObject(thisNodeRep);
  
  BoundingRect bounds = thisNodeRep->getBounds();
  Vector2D startPos(bounds.getMaxX(), (bounds.getMaxY() - bounds.getMinY())/2);
  
  for(long i=0; i < obj->countSubobject(); i++) {
    GSBTreeNode* child = getChildNode(obj, i);
    Object2D* childRep = child->orphanRepresentation();
    offset += child->getRelPos();
    childRep->addTransform(TransMatrix2D::makeTranslate(offset));
    theRep->adoptObject(childRep);
		
    childRep->computeBounds();
    bounds = childRep->getBounds();
    Vector2D endPos = offset + Vector2D(0, (myVertical) ? child->getWidth()/2
        : child->getHeight()/2);
        theRep->adoptObject(new Line2D(startPos, endPos));
  }
  theRep->computeBounds();
  myNode->adoptRepresentation(theRep);
  
  // calculate resulting contour:
  myNode->contour().upper.head = 
        createPolyline(len2, 0, createPolyline(x, y1, myNode->contour().upper.head));
  myNode->contour().lower.head =
        createPolyline(len2, 0, createPolyline(x, y2, myNode->contour().lower.head));
}


void GSBTreeLayouter::layoutLeaf(Object3D* obj)
{
  Real len1((myVertical) ? myNode->getWidth()
        : myNode->getHeight()),
       len2((myVertical) ? myNode->getHeight()
        : myNode->getWidth());

  // define upper contour (just one line segment):
  myNode->contour().upper.tail = createPolyline(len2 + 2*myBorder, 0, 0);
  myNode->contour().upper.head = myNode->contour().upper.tail;

  // define lower contour (two line segments):
  myNode->contour().lower.tail = createPolyline(0, -len1 - 2*myBorder, 0);
  myNode->contour().lower.head = 
     createPolyline(len2 + 2*myBorder, 0, myNode->contour().lower.tail);
  
  // generate representation of leaf node:
  myNode->adoptRepresentation(createRep(obj, myNode));
}


Real GSBTreeLayouter::join(Object3D* obj)
{
  GSBTreeNode* child = getChildNode(obj, 0);
  Real sum, h, d;
  myNode->contour() = child->contour();
  
  sum = h = ((myVertical) 
              ? child->getWidth() : child->getHeight() ) 
		+ 2 * myBorder;
						
  for(long i = 1; i < obj->countSubobject(); i++) {
    child = getChildNode(obj, i);
    d = merge(&myNode->contour(), &child->contour());
    child->setRelPos(Vector2D(0, d + h));
    h = ((myVertical)
          ? child->getWidth() : child->getHeight() ) 
          + 2*myBorder;
    sum += d + h;   
  }
  return sum;
}


Real GSBTreeLayouter::merge(GSBPolygon* c1, GSBPolygon* c2)
{
  GSBPolyline* upper = c1->lower.head;
  GSBPolyline* lower = c2->upper.head;
  GSBPolyline* b;
  Vector2D offs(0,0);
  Real total = 0, d;
  
  while (lower && upper) {
    d = offset(offs, lower->offset, upper->offset);
    offs.y() += d;
    total += d;
    
    if ((offs.x() + lower->offset.x()) <= upper->offset.x()) {
      offs += lower->offset;
      lower = lower->link;
    } else {
      offs -= upper->offset;
      upper = upper->link;
    }
  }
  
  if (lower) {
    b = bridge(c1->upper.tail, Vector2D(0,0), lower, offs);
    c1->upper.tail = (b->link) ? c2->upper.tail : b;
    c1->lower.tail = c2->lower.tail;
  } else {
    b = bridge(c2->lower.tail, offs, upper, Vector2D(0,0));
    if (!b->link) c1->lower.tail = b;
  }
  c1->lower.head = c2->lower.head;
  return total;
}


GSBPolyline* GSBTreeLayouter::bridge(GSBPolyline* line1, Vector2D ofs1,
                                     GSBPolyline* line2, Vector2D ofs2)
{
  Real dx, dy;
  dx = ofs2.x() + line2->offset.x() - ofs1.x();
  if (line2->offset.x() == 0)
    dy = line2->offset.y();
  else
    dy = dx*line2->offset.y()/line2->offset.x();
  GSBPolyline* r = createPolyline(dx, dy, line2->link);
  line1->link = createPolyline(0, ofs2.y() + line2->offset.y() - dy - ofs1.y(), r);
  return r;
}


GSBPolyline* GSBTreeLayouter::createPolyline(Real dx, Real dy, GSBPolyline* link)
{
  GSBPolyline* newPolyline = new GSBPolyline(dx, dy, link);
  myMemory.append(newPolyline);
  return newPolyline;
}


GSBTreeNode* GSBTreeLayouter::getChildNode(Object3D* obj, long childNo)
{
  GSBTreeNode* child = dynamic_cast(GSBTreeNode, 
		GSBNodeTools::getNode(obj->getSubobject(childNo), myViewID));
  if (child == NULL)
    Report::error("[GSBTreeLayouter::getChild] Couldn't get child node!");
  return child;
}


void GSBTreeLayouter::garbageCollection()
{
  ListItr<GSBPolyline*> contours(myMemory);
  for(contours.first(); !contours.isDone(); contours.next()) {
    delete contours.curItem();
  }
  myMemory.removeAll();
}


Object2D* GSBTreeLayouter::createRep(Object3D* obj, GSBTreeNode* node)
{
  GSBNode2D* nodeRep = new GSBNode2D(node->getLabel(), 
        node->getWidth(), node->getHeight());
		
  if (myVertical) {
    TransMatrix2D tm = TransMatrix2D::makeRotateOrigin(M_PI/2);
    tm.translate(node->getHeight(), 0);
    nodeRep->setTransform(tm); 
  }
  markRep(obj, nodeRep);
  nodeRep->setRepresentWho(obj);
  nodeRep->computeBounds();
  return nodeRep;
}


void GSBTreeLayouter::markRep(Object3D* obj, GSBNode2D* rep)
{
  if (GSBNodeTools::getNodeManager(obj)->isMarked()) {
    GLConstantTexture2D* markedTexture = new GLConstantTexture2D;
    markedTexture->setColor(Color(.8, .0, .0));
    rep->appendTexture(markedTexture);
  } else {
    GLConstantTexture2D* unmarkedTexture = new GLConstantTexture2D;
    unmarkedTexture->setColor(Color(1, 1, 1));
    rep->appendTexture(unmarkedTexture);
  }
}

Traversal::Result GSBTreeLayouter::dispatch(Makeable* obj)
{
  tryAbstract(Shared3D, obj);
  tryAbstract(Object3D, obj);
  return Traversal::CONTINUE;
}
