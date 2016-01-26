/*
 * $RCSfile: Grid3D.h,v $ 
 *
 * Copyright (C) 1994-96, Stephan Amann <amann@iam.unibe.ch>
 *                        Christoph Streit <streit@iam.unibe.ch>
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
 *  $Id: Grid3D.h,v 1.10 1996/10/04 09:46:40 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Grid3D_H
#define _Grid3D_H

#include "booga/object/Aggregate3D.h"

//_______________________________________________________________________ Grid3D

class Grid3D : public Aggregate3D {
declareRTTI(Grid3D);
// enable RTTI support

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Grid3D(int sizeX=1, int sizeY=1, int sizeZ=1);
  Grid3D(Exemplar);
  Grid3D(const Grid3D&); 

public:
  virtual ~Grid3D(); 

private:
  Grid3D& operator=(const Grid3D& list);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class Grid3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  Vector3D getResolution() const;
  void setResolution(const Vector3D& res);
  void setResolution(int x, int y, int z);
  
private:
  List<long>& getCellList(int x, int y, int z);
  void initCells();
  bool intersectCell(int* pos, int da, Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Aggregate3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual void adoptObject(Object3D* newObject);
  virtual int orphanObject(const Object3D* object);
  virtual int replaceObject(const Object3D* from, Object3D* to);

private:
  virtual Aggregate3D* makeEmpty() const;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object3D
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Object3D* copy() const;
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Object<>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  virtual bool doIntersect(Ray3D& ray);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class Makeable
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
  virtual RCString getKeyword() const;
  virtual List<Value*>* createParameters();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My private types
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  class Mailbox {
  public:
    Mailbox();
    Mailbox(const Mailbox& mbox);
    ~Mailbox();
 
    void setSize(long size);
 
    void setLastRay(long objNr, unsigned long rayID);
    unsigned long getLastRay(long objNr) const;
    
    void setCell(long objNr, int pos[3]);
    int getCell(long objNr, int index) const;
    
    void setDist(long objNr, Real dist);
    Real getDist(long objNr) const;

    void setBoundsDist(long objNr, Real dist);
    Real getBoundsDist(long objNr) const;
  
    void setTolerance(long objNr, Real tolerance);
    Real getTolerance(long objNr) const;
    
    void setHit(long objNr, Primitive3D* obj);
    Primitive3D* getHit(long objNr) const;
 
  private:
    struct Entry {
      unsigned long myLastRay;	// last tested ray
      int myCell[3];	         // grid coordinates of intersection point
      Real myDist;
      Real myBoundsDist;
      Real myTolerance;
      Primitive3D* myHit;
    }* myEntry;
    long mySize;
  };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  int myDimension[3];        // dimensions of grid
  Real myExtension[3];       // size of the voxels
  bool myAreCellsValid;      // are cell correctly initialized ?
  List<long>* myCells;       // the cells
  TransMatrix3D myToUnit;    // matrix to transform grid to unit cube
  Mailbox myMBox;            // store future hits
  BoundingBox mySubBounds;   // store the boundingbox without local transformation (tm)
};

//______________________________________________________________ inlines

inline List<long>& Grid3D::getCellList(int x, int y, int z)
{
  return myCells[z*myDimension[0]*myDimension[1] + 
                 y*myDimension[0] + x];
}

 
inline void Grid3D::Mailbox::setLastRay(long objNr, unsigned long rayID)
{
  myEntry[objNr].myLastRay = rayID;
}
 
inline unsigned long Grid3D::Mailbox::getLastRay(long objNr) const
{
  return myEntry[objNr].myLastRay;
}
 
inline void Grid3D::Mailbox::setCell(long objNr, int pos[3])
{
  myEntry[objNr].myCell[0] = pos[0];
  myEntry[objNr].myCell[1] = pos[1];
  myEntry[objNr].myCell[2] = pos[2];
}
 
inline int Grid3D::Mailbox::getCell(long objNr, int index) const
{
  return myEntry[objNr].myCell[index];
}
   
inline void Grid3D::Mailbox::setDist(long objNr, Real dist)
{
  myEntry[objNr].myDist = dist;
}
 
inline Real Grid3D::Mailbox::getDist(long objNr) const
{
  return myEntry[objNr].myDist;
}

inline void Grid3D::Mailbox::setBoundsDist(long objNr, Real dist)
{
  myEntry[objNr].myBoundsDist = dist;
}
 
inline Real Grid3D::Mailbox::getBoundsDist(long objNr) const
{
  return myEntry[objNr].myBoundsDist;
}
        
inline void Grid3D::Mailbox::setTolerance(long objNr, Real tolerance)
{
  myEntry[objNr].myTolerance = tolerance;
}
 
inline Real Grid3D::Mailbox::getTolerance(long objNr) const
{
  return myEntry[objNr].myTolerance;
}
 
inline void Grid3D::Mailbox::setHit(long objNr, Primitive3D* obj)
{
  myEntry[objNr].myHit = obj;
}
 
inline Primitive3D* Grid3D::Mailbox::getHit(long objNr) const
{
  return myEntry[objNr].myHit;
}
 
#endif // _Grid3D_H
