/*
 * AnimationFunction.h
 *
 * To model the motion function of action and to compute the actual 
 * value for a given frame.
 *
 * Copyright (C) 1996, Thierry Matthey <matthey@iam.unibe.ch>
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
 *  $Id: AnimationFunction.h,v 1.3 1996/11/13 09:38:01 collison Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _AnimationFunction_H
#define _AnimationFunction_H

#include "booga/base/PrimitiveTypes.h"

// ____________________________________________________________________ AnimationFunction

class AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // AnimationFunction();

  // AnimationFunction(const AnimationFunction&);          // Use default version.

public:
  virtual ~AnimationFunction();
  virtual AnimationFunction* copy() const=0;
  virtual RCString getKeyword() const=0;

private:  
  AnimationFunction& operator=(const AnimationFunction&);  // No assignments.
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// New methods of class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  // to set the parameters of the motion function
  void setParameters(Real start, Real end, Real step);

  // to get the parameters
  Real getStart() const;
  Real getEnd() const;
  Real getStep() const;

  // to compute the value of the motion function
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame) = 0;

protected:
  // a linear transforamtion defined from [startFrame, endframe] to [start, end].
  // computes the value with this transformation for a given framevalue
  // cosiders the possibility of stepwise or linear defintion of the transforamtion   
  Real AFTransformation(Real startFrame, Real endFrame, Real frame);
    		       
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// My data members
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
  Real myStart;
  Real myEnd;
  Real myStep;
};

//______________________________________________________________________ INLINES

inline Real AnimationFunction::getStart() const
{
  return myStart;
}

inline Real AnimationFunction::getEnd() const
{
  return myEnd;
}

inline Real AnimationFunction::getStep() const
{
  return myStep;
}

// ____________________________________________________________________ AFConst

class AFConst : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFConst(Real start, Real end, Real step);
  // AFConst(const AFConst&);          // Use default version.

public:

  virtual AnimationFunction* copy() const;
  virtual RCString getKeyword() const;
    // virtual ~AFConst();                // Use default version.

private:  
  AFConst& operator=(const AFConst&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0  
//
//
// start ---*---------------------------------------------------------*---
//
//
//  0.0  
//
//         0.0                                                       1.0
//       
       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFId

class AFId : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFId(Real start, Real end, Real step);
  // AFId(const AFId&);          // Use default version.

public:
  virtual AnimationFunction* copy() const;
  virtual RCString getKeyword() const;
  // virtual ~AFId();                // Use default version.

private:  
  AFId& operator=(const AFId&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                                                         ---*---
//                                                      --------
//                                              --------
//                                      --------
//                              --------         
//                      --------  
//              --------    
//  0.0  ---*---
//
//         0.0                                                     1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFSin

class AFSin : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFSin(Real start, Real end, Real step);
  // AFSin(const AFSin&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFSin();                // Use default version.

private:  
  AFSin& operator=(const AFSin&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//           
//  1.0       --        --         --                   --        --
//           -  -      -  -      -                     -  -      -  -
//            
//  0.0  ---*    -    *    -    *                          *    -    *---
//
//                -  -      -  -                            -  -
// -1.0            --        --                              --
//         0.0       0.1       0.2                        0.9       1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFSaw

class AFSaw : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFSaw(Real start, Real end, Real step);
  // AFSaw(const AFSaw&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFSaw();                // Use default version.

private:  
  AFSaw& operator=(const AFSaw&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                                                         --- 
//                                                      --------
//                                              --------
//                                      --------
//                              --------         
//                      --------  
//              --------    
//  0.0  ---*---                                                   *---
//
//         0.0                                                    1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFStep

class AFStep : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFStep(Real start, Real end, Real step);
  // AFStep(const AFStep&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFStep();                // Use default version.

private:  
  AFStep& operator=(const AFStep&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                                 *---------------------------*--        
//
//
//
//
//
//
//  0.0  ---*---------------------------                            
//
//         0.0                         0.5                         1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFPulse

class AFPulse : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFPulse(Real start, Real end, Real step);
  // AFPulse(const AFPulse&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFPulse();                // Use default version.

private:  
  AFPulse& operator=(const AFPulse&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                   *---------------------------        
//
//
//
//
//
//
//  0.0  ---*-------------                            *-------------*---
//
//         0.0           0.25                        0.75          1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFSmoothStep

class AFSmoothStep : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFSmoothStep(Real start, Real end, Real step);
  // AFSmoothStep(const AFSmoothStep&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFSmoothStep();                // Use default version.

private:  
  AFSmoothStep& operator=(const AFSmoothStep&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                                                     -------*---
//                                                 ---------
//                                          -------
//                                      ----
//                                  ----         
//                          -------  
//                  ---------    
//  0.0  ---*-------
//
//         0.0                                                     1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

// ____________________________________________________________________ AFTriangle

class AFTriangle : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFTriangle(Real start, Real end, Real step);
  // AFTriangle(const AFTriangle&);          // Use default version.

public:
  virtual AnimationFunction* copy() const;
  virtual RCString getKeyword() const;
  // virtual ~AFTriangle();                // Use default version.

private:  
  AFTriangle& operator=(const AFTriangle&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0                                -*-
//                                 ----   ----
//                             ----           ----
//                         ----                   ----
//                     ----                           ----         
//                 ----                                   ----
//             ----                                           ----
//  0.0  ---*--                                                   --*---
//
//         0.0                                                     1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

class AFSqrt : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFSqrt(Real start, Real end, Real step);
  // AFSqrt(const AFSqrt&);          // Use default version.

public:
  virtual AnimationFunction* copy() const;
  virtual RCString getKeyword() const;
  // virtual ~AFSqrt();                // Use default version.

private:  
  AFSqrt& operator=(const AFSqrt&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0 ---*--------                                       --------*---
//                  ------                           ------                     
//                        -----                 -----                              
//                             ---           ---                                 
//                                --       --                                       
//                                  --   --                        
//                                    - -   
//  0.0                                *
//
//         0.0                        0.5                         1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};

class AFQuad : public AnimationFunction {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructors, destructors, assignment
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
  AFQuad(Real start, Real end, Real step);
  // AFQuad(const AFQuad&);          // Use default version.

public:
  virtual RCString getKeyword() const;
  virtual AnimationFunction* copy() const;
  // virtual ~AFQuad();                // Use default version.

private:  
  AFQuad& operator=(const AFQuad&);  // No assignments.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// From class AnimationFunction
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  1.0 ---*                                                       *---
//          -                                                     -
//           --                                                 --
//             --                                             --
//               ----                                     ----        
//                   ------                         ------  
//                         -------           -------   
//  0.0                           -----*-----
//
//         0.0                        0.5                         1.0
//       
public:
  virtual Real computeValue(Real startFrame, Real endFrame, Real frame);
};


#endif // _AnimationFunction_H

