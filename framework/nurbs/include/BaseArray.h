/*
 * BaseArray.h
 *
 * Definition file for the classes BaseArray, Array1DOf and Array2DOf.
 * BaseArray is the base class for the latter classes. Array1DOf implements
 * a 1-D array, Array2DOf implements a 2-D array. 
 *
 * Copyright (C) 1995, Richard Baechler <baechler@iam.unibe.ch>
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
 *  $Id: BaseArray.h,v 1.5 1996/03/02 12:23:21 amann Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _BaseArray_H
#define _BaseArray_H

#include <stdlib.h> // NULL
#include "booga/base/Report.h"

/***********************************************************
  Constants
***********************************************************/

const int GROW_FACTOR = 10;

/***********************************************************
  Class BaseArray : Abstract base class for arrays
***********************************************************/

template <class T> class BaseArray
{
  public:
    BaseArray (void) {};
    virtual ~BaseArray (void) {};

    virtual int getDimension (void) = 0;
};

/***********************************************************
  Class Array1DOf : 1-D Array of object <T>
***********************************************************/

template <class T> class Array1DOf : public BaseArray<T>
{
  public:
    Array1DOf (void) : myItems (NULL), mySize (0), myCount (0), myFree (0) {}
    Array1DOf (int size);
    Array1DOf (const Array1DOf<T> &a);
    virtual ~Array1DOf (void);

    virtual int getDimension (void) { return 1; }

    virtual Array1DOf<T>& operator= (const Array1DOf<T> &a);
    virtual T& operator[] (int index);

    virtual void initSize (int size);
    virtual int  getSize (void) const { return mySize; };
    virtual int  getCount (void) const { return myCount; };
    virtual T    get (int index) const;
    virtual void set (int index, const T &item);

    virtual void prepend (const T &item) { insert (0, item); };
    virtual void append (const T &item) { insert (myCount, item); };
    virtual void insert (int index, const T &item);
    virtual void remove (int index);
    virtual void removeAll (void);

  private:
    T   *myItems;
    int mySize;
    int myCount;
    int myFree;
};

/***   Array1DOf : Constructor   **************************/

template <class T>
inline Array1DOf<T>::Array1DOf (int size)
{
  myItems = new T[size];
  mySize = size;
  myCount = size;
  myFree = size;
}

/***   Array1DOf : Copy-constructor   *********************/

template <class T>
inline Array1DOf<T>::Array1DOf (const Array1DOf<T> &a)
  : myItems (NULL)
{
  *this = a;
}

/***   ~Array1DOf : Destructor   **************************/

template <class T>
inline Array1DOf<T>::~Array1DOf (void)
{
  if (myItems != NULL)
    delete[] myItems;
}

/***   operator= : Assignment   ***************************/

template <class T>
inline Array1DOf<T>& Array1DOf<T>::operator= (const Array1DOf<T> &a)
{
  mySize = a.mySize;
  myCount = a.myCount;
  myFree = a.myFree;

  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  if (mySize)
  {
    myItems = new T[mySize];
    for (int x = 0; x < mySize; x++)
      myItems[x] = a.myItems[x];
  }

  return *this;
}

/***   operator[] : Get item by index   *******************/

template <class T>
inline T& Array1DOf<T>::operator[] (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array1DOf<T>::operator[]] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   initSize : Initialize with new size   **************/

template <class T>
inline void Array1DOf<T>::initSize (int size)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  myItems = new T[size];
  mySize = size;
  myCount = size;
  myFree = size;
}

/***   get : Get item by index   **************************/

template <class T>
inline T Array1DOf<T>::get (int index) const
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array1DOf<T>::getItem] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   set : Set item by index   **************************/

template <class T>
inline void Array1DOf<T>::set (int index, const T &item)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array1DOf<T>::setItem] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  myItems[i] = item;
}

/***   insert : Insert item at location   *****************/

template <class T>
inline void Array1DOf<T>::insert (int index, const T &item)
{
  if (index < 0 || index > myCount)
    Report::error ("[Array1DOf<T>::insertItem] Index out of range");

  register int i;

  if (myCount == mySize)
  {
    int size = mySize + GROW_FACTOR;
    T   *items = new T[size];

    if (myItems != NULL)
    {
      for (i = 0; i < myFree; i++)
	items[i] = myItems[i];
      for (i = 0; i < myCount - myFree; i++)
	items[myFree+size-myCount+i] = myItems[myFree+mySize-myCount+i];
      delete[] myItems;
      myItems = NULL;
    }
    myItems = items;
    mySize = size;
  }

  if (index < myFree)
  {
    for (i = myFree - index - 1; i >= 0; i--)
      myItems[index+mySize-myCount+i] = myItems[index+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index + 1;
  myCount++;
  myItems[index] = item;
}

/***   remove : Remove item by index   ********************/

template <class T>
inline void Array1DOf<T>::remove (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array1DOf<T>::removeItem] Index out of range");

  register int i;

  if (index < myFree)
  {
    for (i = myFree - index - 2; i >= 0; i--)
      myItems[mySize-myCount+index+1+i] = myItems[index+1+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index;
  myCount--;
}

/***   removeAll : Remove all items   *********************/

template <class T>
inline void Array1DOf<T>::removeAll (void)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  mySize = 0;
  myCount = 0;
  myFree = 0;
}

/***********************************************************
  Class Array2DOf : 2-D Array of object <T>
***********************************************************/

template <class T> class Array2DOf : public BaseArray<T>
{
  public:
    Array2DOf (void) : myItems (NULL), mySize (0), myCount (0), myFree (0) {}
    Array2DOf (int sizeU, int sizeV);
    Array2DOf (const Array2DOf<T> &a);
    virtual ~Array2DOf (void);

    virtual int getDimension (void) { return 2; }

    virtual Array2DOf<T>& operator= (const Array2DOf<T> &a);
    virtual Array1DOf<T>& operator[] (int index);

    virtual Array1DOf<T>& getItems (int index) const;
    virtual void          setItems (int index, const Array1DOf<T> &item);

    virtual void initSize (int sizeU, int sizeV);
    virtual int  getSizeU (void) const { return mySize; };
    virtual int  getSizeV (void) const { return myItems[0].getSize (); };
    virtual int  getCountU (void) const { return myCount; };
    virtual int  getCountV (void) const { return myItems[0].getCount (); };
    virtual T    get (int uIndex, int vIndex) const;
    virtual void set (int uIndex, int vIndex, const T &item);

    virtual void prepend (const Array1DOf<T> &items) { insert (0, items); };
    virtual void append (const Array1DOf<T> &items) { insert (myCount, items); };
    virtual void insert (int index, const Array1DOf<T> &item);
    virtual void remove (int index);
    virtual void removeAll (void);

  private:
    Array1DOf<T> *myItems;
    int          mySize;
    int          myCount;
    int          myFree;
};

/***   Array2DOf : Constructor   **************************/

template <class T>
inline Array2DOf<T>::Array2DOf (int sizeU, int sizeV)
{
  myItems = new Array1DOf<T>[sizeU];
  for (int x = 0; x < sizeU; x++)
    myItems[x].initSize (sizeV);
  mySize = sizeU;
  myCount = sizeU;
  myFree = sizeU;
}

/***   Array2DOf : Copy-constructor   *********************/

template <class T>
inline Array2DOf<T>::Array2DOf (const Array2DOf<T> &a)
  : myItems (NULL)
{
  *this = a;
}

/***   ~Array2DOf : Destructor   **************************/

template <class T>
inline Array2DOf<T>::~Array2DOf (void)
{
  if (myItems != NULL)
    delete[] myItems;
}

/***   operator= : Assignment   ***************************/

template <class T>
inline Array2DOf<T>& Array2DOf<T>::operator= (const Array2DOf<T> &a)
{
  mySize = a.mySize;
  myCount = a.myCount;
  myFree = a.myFree;

  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  if (mySize)
  {
    myItems = new Array1DOf<T>[mySize];
    for (int x = 0; x < mySize; x++)
      myItems[x] = a.myItems[x];
  }

  return *this;
}

/***   operator[] : Get item by index   *******************/

template <class T>
inline Array1DOf<T>& Array2DOf<T>::operator[] (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array2DOf<T>::operator[]] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   getItems : Get items by index   ********************/

template <class T>
inline Array1DOf<T>& Array2DOf<T>::getItems (int index) const
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array2DOf<T>::getItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   setItems : Set items by index   ********************/

template <class T>
inline void Array2DOf<T>::setItems (int index, const Array1DOf<T> &item)
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array2DOf<T>::setItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  myItems[i] = item;
}

/***   initSize : Initialize with new size   **************/

template <class T>
inline void Array2DOf<T>::initSize (int sizeU, int sizeV)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  myItems = new Array1DOf<T>[sizeU];
  for (int x = 0; x < sizeU; x++)
    myItems[x].initSize (sizeV);
  mySize = sizeU;
  myCount = sizeU;
  myFree = sizeU;
}

/***   get : Get item by index   **************************/

template <class T>
inline T Array2DOf<T>::get (int uIndex, int vIndex) const
{
  if (uIndex < 0 || uIndex >= myCount)
    Report::error ("[Array2DOf<T>::getItem] Index out of range");

  int i = uIndex < myFree ? uIndex : uIndex + mySize - myCount;
  return myItems[i].get (vIndex);
}

/***   set : Set item by index   **************************/

template <class T>
inline void Array2DOf<T>::set (int uIndex, int vIndex, const T &item)
{
  if (uIndex < 0 || uIndex >= myCount)
    Report::error ("[Array2DOf<T>::setItem] Index out of range");

  int i = uIndex < myFree ? uIndex : uIndex + mySize - myCount;
  myItems[i].set (vIndex, item);
}

/***   insert : Insert items at location   ****************/

template <class T>
inline void Array2DOf<T>::insert (int index, const Array1DOf<T> &item)
{
  if (index < 0 || index > myCount)
    Report::error ("[Array2DOf<T>::insertItems] Index out of range");
  if (myCount > 0 && item.getCount() != myItems[0].getCount())
    Report::error ("[Array2DOf<T>::insertItems] Wrong number of <T> to insert");

  register int i;

  if (myCount == mySize)
  {
    int          size = mySize + GROW_FACTOR;
    Array1DOf<T> *items = new Array1DOf<T>[size];

    if (myItems != NULL)
    {
      for (i = 0; i < myFree; i++)
	items[i] = myItems[i];
      for (i = 0; i < myCount - myFree; i++)
	items[myFree+size-myCount+i] = myItems[myFree+mySize-myCount+i];
      delete[] myItems;
      myItems = NULL;
    }
    myItems = items;
    mySize = size;
  }

  if (index < myFree)
  {
    for (i = myFree - index - 1; i >= 0; i--)
      myItems[index+mySize-myCount+i] = myItems[index+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index + 1;
  myCount++;
  myItems[index] = item;
}

/***   remove : Remove items by index   *******************/

template <class T>
inline void Array2DOf<T>::remove (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array2DOf<T>::removeItems] Index out of range");

  register int i;

  if (index < myFree)
  {
    for (i = myFree - index - 2; i >= 0; i--)
      myItems[mySize-myCount+index+1+i] = myItems[index+1+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index;
  myCount--;
}

/***   removeAll : Remove all items   *********************/

template <class T>
inline void Array2DOf<T>::removeAll (void)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  mySize = 0;
  myCount = 0;
  myFree = 0;
}

/***********************************************************
  Class Array3DOf : 3-D Array of object <T>
***********************************************************/

template <class T> class Array3DOf : public BaseArray<T>
{
  public:
    Array3DOf (void) : myItems (NULL), mySize (0), myCount (0), myFree (0) {};
    Array3DOf (int sizeX, int sizeY, int sizeZ);
    Array3DOf (const Array3DOf<T> &a);
    virtual ~Array3DOf (void);

    virtual int getDimension (void) { return 3; }

    virtual Array3DOf<T>& operator= (const Array3DOf<T> &a);
    virtual Array2DOf<T>& operator[] (int index);

    virtual Array2DOf<T>& getItems (int index) const;
    virtual void          setItems (int index, const Array2DOf<T> &item);

    virtual void initSize (int sizeX, int sizeY, int sizeZ);
    virtual int  getSizeX (void) const { return mySize; };
    virtual int  getSizeY (void) const { return myItems[0].getSizeU (); };
    virtual int  getSizeZ (void) const { return myItems[0].getSizeV (); };
    virtual int  getCountX (void) const { return myCount; };
    virtual int  getCountY (void) const { return myItems[0].getCountU (); };
    virtual int  getCountZ (void) const { return myItems[0].getCountV (); };
    virtual T    get (int indexX, int indexY, int indexZ) const;
    virtual void set (int indexX, int indexY, int indexZ, const T &item);

    virtual void prepend (const Array2DOf<T> &items) { insert (0, items); };
    virtual void append (const Array2DOf<T> &items) { insert (myCount, items); };
    virtual void insert (int index, const Array2DOf<T> &item);
    virtual void remove (int index);
    virtual void removeAll (void);

  private:
    Array2DOf<T> *myItems;
    int          mySize;
    int          myCount;
    int          myFree;
};

/***   Array3DOf : Constructor   **************************/

template <class T>
inline Array3DOf<T>::Array3DOf (int sizeX, int sizeY, int sizeZ)
{
  myItems = new Array2DOf<T>[sizeX];
  for (int x = 0; x < sizeX; x++)
    myItems[x].initSize (sizeY, sizeZ);
  mySize = sizeX;
  myCount = sizeX;
  myFree = sizeX;
}

/***   Array3DOf : Copy-constructor   *********************/

template <class T>
inline Array3DOf<T>::Array3DOf (const Array3DOf<T> &a)
  : myItems (NULL)
{
  *this = a;
}

/***   ~Array3DOf : Destructor   **************************/

template <class T>
inline Array3DOf<T>::~Array3DOf (void)
{
  if (myItems != NULL)
    delete[] myItems;
}

/***   operator= : Assignment   ***************************/

template <class T>
inline Array3DOf<T>& Array3DOf<T>::operator= (const Array3DOf<T> &a)
{
  mySize = a.mySize;
  myCount = a.myCount;
  myFree = a.myFree;

  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  if (mySize)
  {
    myItems = new Array2DOf<T>[mySize];
    for (int x = 0; x < mySize; x++)
      myItems[x] = a.myItems[x];
  }

  return *this;
}

/***   operator[] : Get item by index   *******************/

template <class T>
inline Array2DOf<T>& Array3DOf<T>::operator[] (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array3DOf<T>::operator[]] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   getItems : Get items by index   ********************/

template <class T>
inline Array2DOf<T>& Array3DOf<T>::getItems (int index) const
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array3DOf<T>::getItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   setItems : Set items by index   ********************/

template <class T>
inline void Array3DOf<T>::setItems (int index, const Array2DOf<T> &item)
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array3DOf<T>::setItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  myItems[i] = item;
}

/***   initSize : Initialize with new size   **************/

template <class T>
inline void Array3DOf<T>::initSize (int sizeX, int sizeY, int sizeZ)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  myItems = new Array2DOf<T>[sizeX];
  for (int x = 0; x < sizeX; x++)
    myItems[x].initSize (sizeY, sizeZ);
  mySize = sizeX;
  myCount = sizeX;
  myFree = sizeX;
}

/***   get : Get item by index   **************************/

template <class T>
inline T Array3DOf<T>::get (int indexX, int indexY, int indexZ) const
{
  if (indexX < 0 || indexX >= myCount)
    Report::error ("[Array3DOf<T>::getItem] Index out of range");

  int i = indexX < myFree ? indexX : indexX + mySize - myCount;
  return myItems[i].get (indexY, indexZ);
}

/***   set : Set item by index   **************************/

template <class T>
inline void Array3DOf<T>::set (int indexX, int indexY, int indexZ, const T &item)
{
  if (indexX < 0 || indexX >= myCount)
    Report::error ("[Array3DOf<T>::setItem] Index out of range");

  int i = indexX < myFree ? indexX : indexX + mySize - myCount;
  myItems[i].set (indexY, indexZ, item);
}

/***   insert : Insert items at location   ****************/

template <class T>
inline void Array3DOf<T>::insert (int index, const Array2DOf<T> &item)
{
  if (index < 0 || index > myCount)
    Report::error ("[Array3DOf<T>::insertItems] Index out of range");
  if (myCount > 0 && item.getCountU() != myItems[0].getCountU() && item.getCountV() != myItems[0].getCountV())
    Report::error ("[Array3DOf<T>::insertItems] Wrong number of <T> to insert");

  register int i;

  if (myCount == mySize)
  {
    int          size = mySize + GROW_FACTOR;
    Array2DOf<T> *items = new Array2DOf<T>[size];

    if (myItems != NULL)
    {
      for (i = 0; i < myFree; i++)
	items[i] = myItems[i];
      for (i = 0; i < myCount - myFree; i++)
	items[myFree+size-myCount+i] = myItems[myFree+mySize-myCount+i];
      delete[] myItems;
      myItems = NULL;
    }
    myItems = items;
    mySize = size;
  }

  if (index < myFree)
  {
    for (i = myFree - index - 1; i >= 0; i--)
      myItems[index+mySize-myCount+i] = myItems[index+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index + 1;
  myCount++;
  myItems[index] = item;
}

/***   remove : Remove items by index   *******************/

template <class T>
inline void Array3DOf<T>::remove (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array3DOf<T>::removeItems] Index out of range");

  register int i;

  if (index < myFree)
  {
    for (i = myFree - index - 2; i >= 0; i--)
      myItems[mySize-myCount+index+1+i] = myItems[index+1+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index;
  myCount--;
}

/***   removeAll : Remove all items   *********************/

template <class T>
inline void Array3DOf<T>::removeAll (void)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  mySize = 0;
  myCount = 0;
  myFree = 0;
}

/***********************************************************
  Class Array4DOf : 4-D Array of object <T>
***********************************************************/

template <class T> class Array4DOf : public BaseArray<T>
{
  public:
    Array4DOf (void) : myItems (NULL), mySize (0), myCount (0), myFree (0) {}
    Array4DOf (int sizeX, int sizeY, int sizeZ, int sizeW);
    Array4DOf (const Array4DOf<T> &a);
    virtual ~Array4DOf (void);

    virtual int getDimension (void) { return 4; }

    virtual Array4DOf<T>& operator= (const Array4DOf<T> &a);
    virtual Array3DOf<T>& operator[] (int index);

    virtual Array3DOf<T>& getItems (int index) const;
    virtual void          setItems (int index, const Array3DOf<T> &item);

    virtual void initSize (int sizeX, int sizeY, int sizeZ, int sizeW);
    virtual int  getSizeX (void) const { return mySize; };
    virtual int  getSizeY (void) const { return myItems[0].getSizeX (); };
    virtual int  getSizeZ (void) const { return myItems[0].getSizeY (); };
    virtual int  getSizeW (void) const { return myItems[0].getSizeZ (); };
    virtual int  getCountX (void) const { return myCount; };
    virtual int  getCountY (void) const { return myItems[0].getCountX (); };
    virtual int  getCountZ (void) const { return myItems[0].getCountY (); };
    virtual int  getCountW (void) const { return myItems[0].getCountZ (); };
    virtual T    get (int indexX, int indexY, int indexZ, int indexW) const;
    virtual void set (int indexX, int indexY, int indexZ, int indexW, const T &item);

    virtual void prepend (const Array3DOf<T> &items) { insert (0, items); };
    virtual void append (const Array3DOf<T> &items) { insert (myCount, items); };
    virtual void insert (int index, const Array3DOf<T> &item);
    virtual void remove (int index);
    virtual void removeAll (void);

  private:
    Array3DOf<T> *myItems;
    int          mySize;
    int          myCount;
    int          myFree;
};

/***   Array4DOf : Constructor   **************************/

template <class T>
inline Array4DOf<T>::Array4DOf (int sizeX, int sizeY, int sizeZ, int sizeW)
{
  myItems = new Array3DOf<T>[sizeX];
  for (int x = 0; x < sizeX; x++)
    myItems[x].initSize (sizeY, sizeZ, sizeW);
  mySize = sizeX;
  myCount = sizeX;
  myFree = sizeX;
}

/***   Array4DOf : Copy-constructor   *********************/

template <class T>
inline Array4DOf<T>::Array4DOf (const Array4DOf<T> &a)
  : myItems (NULL)
{
  *this = a;
}

/***   ~Array4DOf : Destructor   **************************/

template <class T>
inline Array4DOf<T>::~Array4DOf (void)
{
  if (myItems != NULL)
    delete[] myItems;
}

/***   operator= : Assignment   ***************************/

template <class T>
inline Array4DOf<T>& Array4DOf<T>::operator= (const Array4DOf<T> &a)
{
  mySize = a.mySize;
  myCount = a.myCount;
  myFree = a.myFree;

  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  if (mySize)
  {
    myItems = new Array3DOf<T>[mySize];
    for (int x = 0; x < mySize; x++)
      myItems[x] = a.myItems[x];
  }

  return *this;
}

/***   operator[] : Get item by index   *******************/

template <class T>
inline Array3DOf<T>& Array4DOf<T>::operator[] (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array4DOf<T>::operator[]] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   getItems : Get items by index   ********************/

template <class T>
inline Array3DOf<T>& Array4DOf<T>::getItems (int index) const
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array4DOf<T>::getItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  return myItems[i];
}

/***   setItems : Set items by index   ********************/

template <class T>
inline void Array4DOf<T>::setItems (int index, const Array3DOf<T> &item)
{
  if (index < 0 || index >= mySize)
    Report::error ("[Array4DOf<T>::setItems] Index out of range");

  int i = index < myFree ? index : index + mySize - myCount;
  myItems[i] = item;
}

/***   initSize : Initialize with new size   **************/

template <class T>
inline void Array4DOf<T>::initSize (int sizeX, int sizeY, int sizeZ, int sizeW)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  myItems = new Array3DOf<T>[sizeX];
  for (int x = 0; x < sizeX; x++)
    myItems[x].initSize (sizeY, sizeZ, sizeW);
  mySize = sizeX;
  myCount = sizeX;
  myFree = sizeX;
}

/***   get : Get item by index   **************************/

template <class T>
inline T Array4DOf<T>::get (int indexX, int indexY, int indexZ, int indexW) const
{
  if (indexX < 0 || indexX >= myCount)
    Report::error ("[Array4DOf<T>::getItem] Index out of range");

  int i = indexX < myFree ? indexX : indexX + mySize - myCount;
  return myItems[i].get (indexY, indexZ, indexW);
}

/***   set : Set item by index   **************************/

template <class T>
inline void Array4DOf<T>::set (int indexX, int indexY, int indexZ, int indexW, const T &item)
{
  if (indexX < 0 || indexX >= myCount)
    Report::error ("[Array4DOf<T>::setItem] Index out of range");

  int i = indexX < myFree ? indexX : indexX + mySize - myCount;
  myItems[i].set (indexY, indexZ, indexW, item);
}

/***   insert : Insert items at location   ****************/

template <class T>
inline void Array4DOf<T>::insert (int index, const Array3DOf<T> &item)
{
  if (index < 0 || index > myCount)
    Report::error ("[Array4DOf<T>::insertItems] Index out of range");
  if (myCount > 0 && item.getCountX() != myItems[0].getCountX() 
      && item.getCountY() != myItems[0].getCountY() && item.getCountZ() != myItems[0].getCountZ())
    Report::error ("[Array4DOf<T>::insertItems] Wrong number of <T> to insert");

  register int i;

  if (myCount == mySize)
  {
    int          size = mySize + GROW_FACTOR;
    Array3DOf<T> *items = new Array3DOf<T>[size];

    if (myItems != NULL)
    {
      for (i = 0; i < myFree; i++)
	items[i] = myItems[i];
      for (i = 0; i < myCount - myFree; i++)
	items[myFree+size-myCount+i] = myItems[myFree+mySize-myCount+i];
      delete[] myItems;
      myItems = NULL;
    }
    myItems = items;
    mySize = size;
  }

  if (index < myFree)
  {
    for (i = myFree - index - 1; i >= 0; i--)
      myItems[index+mySize-myCount+i] = myItems[index+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index + 1;
  myCount++;
  myItems[index] = item;
}

/***   remove : Remove items by index   *******************/

template <class T>
inline void Array4DOf<T>::remove (int index)
{
  if (index < 0 || index >= myCount)
    Report::error ("[Array4DOf<T>::removeItems] Index out of range");

  register int i;

  if (index < myFree)
  {
    for (i = myFree - index - 2; i >= 0; i--)
      myItems[mySize-myCount+index+1+i] = myItems[index+1+i];
  }
  else if (index > myFree)
  {
    for (i = 0; i < index - myFree; i++)
      myItems[myFree+i] = myItems[myFree+mySize-myCount+i];
  }
  myFree = index;
  myCount--;
}

/***   removeAll : Remove all items   *********************/

template <class T>
inline void Array4DOf<T>::removeAll (void)
{
  if (myItems != NULL)
  {
    delete[] myItems;
    myItems = NULL;
  }
  mySize = 0;
  myCount = 0;
  myFree = 0;
}

#endif
