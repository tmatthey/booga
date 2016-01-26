/*
 * DynamicMatrix.h
 *
 * Definition file for the classes DynamicMatrix and SquareMatrix.
 * DynamicMatrix defines a dynamic nxm-Matrix, SquareMatrix defines
 * a dynamic nxn-Matrix.
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
 *  $Id: DynamicMatrix.h,v 1.4 1996/03/02 12:23:33 amann Exp $ 
 * -----------------------------------------------------------------------------
 */

#ifndef _DynamicMatrix_H
#define _DynamicMatrix_H

#include "booga/nurbs/BaseArray.h"

/********************************************************
  Class DynamicMatrix : Dynamic n x m -Matrix
********************************************************/

template <class T> class DynamicMatrix : public Array2DOf<T>
{
  public:
    DynamicMatrix (void) : Array2DOf<T> () {};
    DynamicMatrix (int uct, int vct) : Array2DOf<T> (uct, vct) {};
    DynamicMatrix (const DynamicMatrix<T>& a) { *this = a; };

    virtual DynamicMatrix<T> operator* (const DynamicMatrix<T>& a);

    virtual void transpose (void);
};

template <class T>
inline DynamicMatrix<T> DynamicMatrix<T>::operator* (const DynamicMatrix<T>& a)
{
  register int     x, y, z;
  int              n, m, k;
  DynamicMatrix<T> res;

  n = this->getCountU ();
  m = a.getCountV ();
  k = this->getCountV ();
  if (k == a.getCountU())
  {
    for (x = 0; x < n; x++)
    {
      for (y = 0; y < m; y++)
      {
	res.set (x, y, 0);
	for (z = 0; z < k; z++)
	  res[x][y] += this->get (x, z) * a.get (z, y);
      }
    }
  }
  return res;
}

template <class T>
inline void DynamicMatrix<T>::transpose (void)
{
  int uct = this->getCountU (), vct = this->getCountV ();

  DynamicMatrix<T> a (vct, uct);
  for (int x = 0; x < vct; x++)
    for (int y = 0; y < uct; y++)
      a.set (x, y, this->get(y, x));

  *this = a;
}

/********************************************************
  Class SquareMatrix : Dynamic n x n -matrix
********************************************************/

template <class T> class SquareMatrix : public DynamicMatrix<T>
{
  public:
    SquareMatrix (void) : DynamicMatrix<T> () {};
    SquareMatrix (int ct) : DynamicMatrix<T> (ct, ct) {};
    SquareMatrix (const SquareMatrix<T>& a) { *this = a; };

    virtual void initSize (int ct);
    virtual void inverse (void);
};

template <class T>
inline void SquareMatrix<T>::initSize (int ct)
{
  DynamicMatrix<T>::initSize (ct, ct);
}

template <class T>
inline void SquareMatrix<T>::inverse (void)
{
  register int i, j;
  int      uct = this->getCountU ();

  T *I = new T[uct*uct];  // Inverse of N
  T temp;			// Temp element for swapping

  for (i = 0; i < uct; i++)    	// Initialize
    for (j = 0; j < uct; j++)
      if (i == j)
	I[i*uct+j] = 1.0;
      else
	I[i*uct+j] = 0.0;

  int il;			// Largest pivot
  for (j = 0; j < uct; j++)     // Matrix inversion
  {
    il = j;			// Row with largest pivot candidate
    for (i = j + i; i < uct; i++) // Find largest pivot
      if (fabs(this->get(i, j)) > fabs(this->get(i, j)))
	il = i;

    if (il != j)		// Swap if necessary to put pivot on diagonal
    {
      for (i = 0; i < uct; i++) // Swap rows il and j in N and I
      {
	temp = this->get (il, i);
	this->set (il, i, this->get(j, i));
	this->set (j, i, temp);
	temp = I[il*uct+i];
	I[il*uct+i] = I[j*uct+i];
	I[j*uct+i] = temp;
      }
    }

    if (this->get(j, j) == 0.0)
      Report::error ("[SquareMatrix<T>::inverse] Matrix is singular, can't inverse");

    temp = this->get (j, j);		// Scale row j to get a unit diagonal
    for (i = 0; i < uct; i++)
    {
      (*this)[j][i] /= temp;
      I[j*uct+i] /= temp;
    }

    for (i = 0; i < uct; i++)	// Eliminate off-diagonal elements
    {
      if (i != j)
      {
		temp = this->get (i, j);
		for (int k = 0; k < uct; k++)
        {
		 I[i*uct+k] -= temp * I[j*uct+k];
		 (*this)[i][k] -= temp * this->get (j, k);
		}
      }
    }
  } // End of matrix inversion

  for (i = 0; i < uct; i++)	// Set matrix to inverse
    for (j = 0; j < uct; j++)
      this->set (i, j, I[i*uct+j]);
      
  delete [] I;
}

#endif
