/*
 * Nurbs3DTypes.h
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
 *  $Id: Nurbs3DTypes.h,v 1.3 1996/01/12 16:09:51 streit Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Nurbs3DTypes_H
# define _Nurbs3DTypes_H

#include "booga/base/PrimitiveTypes.h"
#include "booga/base/Vector3D.h"
#include "booga/base/Vector4D.h"
#include "booga/nurbs/BaseArray.h"
#include "booga/nurbs/DynamicMatrix.h"

//______________________________________________________________________ TYPEDEF

typedef Array1DOf<Real> RealArr1D;
typedef Array2DOf<Real> RealArr2D;

typedef Array1DOf<Real> KnotArray;
typedef Array1DOf<int>  IndexArray;

typedef Array1DOf<Vector3D> PtArray1D;
typedef Array2DOf<Vector3D> PtArray2D;
typedef Array1DOf<Real>     WtArray1D;
typedef Array2DOf<Real>     WtArray2D;

typedef Array1DOf<Vector4D> Vec4DArr1D;
typedef Array2DOf<Vector4D> Vec4DArr2D;
typedef Array4DOf<Vector4D> Vec4DArr4D;

typedef SquareMatrix<Real>  RealMatrix;

//_________________________________________________________________ Nurbs3DTypes

class Nurbs3DTypes {
public:
  enum EObject { None = 1, Curve, Surface };
  enum EEvaluation { Unknown, BasisFuns, CornerCut, DeBoor };
  enum EInterpolation { ChordLength = 1, Centripetal };
};

#endif // _Nurbs3DTypes_H

