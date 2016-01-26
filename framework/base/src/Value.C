/*
 * Value.C 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
 *                        University of Berne, Switzerland
 * Portions Copyright (C) 1990, Jonathan P. Leech
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
 *  $Id: Value.C,v 1.9 1997/09/19 07:15:08 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */

#include <stdlib.h> //strtod
#include <stdio.h> // sscanf

#include "booga/base/Report.h"
#include "booga/base/Value.h"
#include "ValueMacros.h" 

//__________________________________________________________________ local const

// which value types do we know ?
//
static const int REAL     = 0;
static const int STRING   = 1;
static const int VECTOR3D = 2;
static const int VECTOR2D = 3;
static const int MATRIX3D = 4;
static const int MATRIX2D = 5;

// ... and a lot of combinations.
// 
// R : Real
// S : String
// V : Vector3D
// v : Vector2D
// M : TransMatrix3D
// m : TransMatrix2D
// 

#ifndef BITS
#define BITSPERBYTE    CHAR_BIT
#define BITS(type)     (BITSPERBYTE * sizeof(type))
#endif

static const int maxNoOfValues = BITS(int)/2;

#define encodeValues(type1,type2) ((1<<maxNoOfValues+(type1))+(1<<(type2)))
#define binaryType(value1,value2) encodeValues((value1).myType,(value2).myType)

// static const int UNKNOWN=0;

static const int RR=encodeValues(REAL,REAL);
static const int RS=encodeValues(REAL,STRING);
static const int RV=encodeValues(REAL,VECTOR3D);
static const int Rv=encodeValues(REAL,VECTOR2D);
// static const int RM=encodeValues(REAL,MATRIX3D);
// static const int Rm=encodeValues(REAL,MATRIX2D);
		    
static const int SR=encodeValues(STRING,REAL);
static const int SS=encodeValues(STRING,STRING);
static const int SV=encodeValues(STRING,VECTOR3D);
static const int Sv=encodeValues(STRING,VECTOR2D);
static const int SM=encodeValues(STRING,MATRIX3D);
static const int Sm=encodeValues(STRING,MATRIX2D);
		    
static const int VR=encodeValues(VECTOR3D,REAL);
static const int VS=encodeValues(VECTOR3D,STRING);
static const int VV=encodeValues(VECTOR3D,VECTOR3D);
// static const int Vv=encodeValues(VECTOR3D,VECTOR2D);
static const int VM=encodeValues(VECTOR3D,MATRIX3D);
// static const int Vm=encodeValues(VECTOR3D,MATRIX2D);
		    
static const int vR=encodeValues(VECTOR2D,REAL);
static const int vS=encodeValues(VECTOR2D,STRING);
// static const int vV=encodeValues(VECTOR2D,VECTOR3D);
static const int vv=encodeValues(VECTOR2D,VECTOR2D);
// static const int vM=encodeValues(VECTOR2D,MATRIX3D);
static const int vm=encodeValues(VECTOR2D,MATRIX2D);
		    
// static const int MR=encodeValues(MATRIX3D,REAL);
// static const int MS=encodeValues(MATRIX3D,STRING);
// static const int MV=encodeValues(MATRIX3D,VECTOR3D);
// static const int Mv=encodeValues(MATRIX3D,VECTOR2D);
static const int MM=encodeValues(MATRIX3D,MATRIX3D);
// static const int Mm=encodeValues(MATRIX3D,MATRIX2D);
		    
// static const int mR=encodeValues(MATRIX2D,REAL);
// static const int mS=encodeValues(MATRIX2D,STRING);
// static const int mV=encodeValues(MATRIX2D,VECTOR3D);
// static const int mv=encodeValues(MATRIX2D,VECTOR2D);
// static const int mM=encodeValues(MATRIX2D,MATRIX3D);
static const int mm=encodeValues(MATRIX2D,MATRIX2D);
		    
//________________________________________________________________________ Value

Value::Value(Real val)
: myType(REAL)
{ 
  realVal = val;
}

Value::Value(const char* str)
: myType(STRING)
{
  stringVal = new RCString(str);
}
      
Value::Value(const RCString& s)
: myType(STRING)
{
  stringVal = new RCString(s);
}

Value::Value(Real x, Real y, Real z)
: myType(VECTOR3D)
{
  vector3DVal = new Vector3D(x, y, z);
}

Value::Value(const Vector3D& vec)
: myType(VECTOR3D)
{
  vector3DVal = new Vector3D(vec);
}

Value::Value(Real x, Real y)
: myType(VECTOR2D)
{
  vector2DVal = new Vector2D(x, y);
}

Value::Value(const Vector2D& vec)
: myType(VECTOR2D)
{
  vector2DVal = new Vector2D(vec);
}

Value::Value(const TransMatrix3D& tmat)
: myType(MATRIX3D)
{
  matrix3DVal = new TransMatrix3D(tmat);
}

Value::Value(const TransMatrix2D& tmat)
: myType(MATRIX2D)
{
  matrix2DVal = new TransMatrix2D(tmat);
}

Value::Value(const Value& v)
: myType(v.myType)
{
  switch (v.myType) {
    case REAL     : realVal = v.realVal;                             break;
    case STRING   : stringVal = new RCString(*v.stringVal);          break;
    case VECTOR3D : vector3DVal = new Vector3D(*v.vector3DVal);      break;
    case VECTOR2D : vector2DVal = new Vector2D(*v.vector2DVal);      break;
    case MATRIX3D : matrix3DVal = new TransMatrix3D(*v.matrix3DVal); break;
    case MATRIX2D : matrix2DVal = new TransMatrix2D(*v.matrix2DVal); break;
    default:
      Report::error("[Value::Value(const Value&)] unknown operand type");
  }
}

Value::~Value()
{
  switch (myType) {
    case STRING   : delete stringVal;   break;
    case VECTOR3D : delete vector3DVal; break;
    case VECTOR2D : delete vector2DVal; break;
    case MATRIX3D : delete matrix3DVal; break;
    case MATRIX2D : delete matrix2DVal; break;
    default: break;
  }
}

//__________________________________________________________________ Assignments

Value& Value::operator=(const Value& v)
{
  if (this == &v)
    return *this;

  switch (myType) {
    case STRING   : delete stringVal;   break;
    case VECTOR3D : delete vector3DVal; break;
    case VECTOR2D : delete vector2DVal; break;
    case MATRIX3D : delete matrix3DVal; break;
    case MATRIX2D : delete matrix2DVal; break;
    default: break;
  }  

  myType = v.myType;

  switch (v.myType) {
    case REAL     : realVal = v.realVal;                             break;
    case STRING   : stringVal = new RCString(*v.stringVal);          break;
    case VECTOR3D : vector3DVal = new Vector3D(*v.vector3DVal);      break;
    case VECTOR2D : vector2DVal = new Vector2D(*v.vector2DVal);      break;
    case MATRIX3D : matrix3DVal = new TransMatrix3D(*v.matrix3DVal); break;
    case MATRIX2D : matrix2DVal = new TransMatrix2D(*v.matrix2DVal); break;
    default:
      Report::error("[Value::Value(const Value&)] unknown operand type");
  }  

  return *this;
}
 
Value& Value::operator+=(const Value& v)
{
  *this = *this + v;
  return *this;
}

Value& Value::operator-=(const Value& v)
{
 *this = *this - v;
 return *this;
}

Value& Value::operator*=(const Value& v)
{
  *this = *this * v;
  return *this;
}

Value& Value::operator/=(const Value& v)
{
  *this = *this / v;
  return *this;
}

Value& Value::operator^=(const Value& v)
{
  *this = *this ^ v;
  return *this;
}

Value& Value::operator%=(const Value& v)
{
  *this = *this % v;
  return *this;
}

//______________________________________________________________ Type conversion

Value::operator int() const
{
  switch (myType) {
    case REAL:
      return !equal(realVal, 0);
    case STRING:
      return !stringVal->isEmpty();
    case VECTOR3D:
      return !vector3DVal->zero();
    case VECTOR2D:
      return !vector2DVal->zero();
    case MATRIX3D:
      return !matrix3DVal->zero();
    case MATRIX2D:
      return !matrix2DVal->zero();
    default:
      Report::error("[Value::operator int] unknown operand type");
  }
  return 0;
}

Value::operator Real() const
{
  switch (myType) {
    case REAL:  return realVal;
    case STRING: {
      Real retval;
      char* ptr;

      retval = strtod(stringVal->chars(), &ptr);
      if (*ptr == '\0')
        return retval;
      else 
        Report::error("[Value::operator Real()] can't convert string '" +
	  	      *stringVal + "' to Real");
    } break;
    case VECTOR3D:
      Report::error("[Value::operator Real()] can't convert Vector3D '" +
	  	    (RCString)*this + "' to Real");
      break;
    case VECTOR2D:
      Report::error("[Value::operator Real()] can't convert Vector2D '" +
	  	    (RCString)*this + "' to Real");
      break;
    case MATRIX3D:
      Report::error("[Value::operator Real()] can't convert TransMatrix3D '" +
	  	    (RCString)*this + "' to Real");
      break;
    case MATRIX2D:
      Report::error("[Value::operator Real()] can't convert TransMatrix2D '" +
	  	    (RCString)*this + "' to Real");
      break;
    default:
      Report::error("[Value::operator Real()] unknown operand type");
  }

  return 0;
}

Value::operator RCString() const
{
  char tmp[256];
  switch (myType) {
    case REAL:
      sprintf(tmp,"%g", realVal);
      return RCString(tmp);
    case STRING:
      return *stringVal;
    case VECTOR3D: {
      std::stringstream os;
      os << *vector3DVal;
      return RCString(os);
    } 
    case VECTOR2D: {
      std::stringstream os;
      os << *vector2DVal;
      return RCString(os);
    } 
    case MATRIX3D: {
      std::stringstream os;
      os << *matrix3DVal;
      return RCString(os);
    } 
    case MATRIX2D: {
      std::stringstream os;
      os << *matrix2DVal;
      return RCString(os);
    } 
    default:
      Report::error("[Value::operator RCString()] unknown operand type");
  }

  return RCString();      
}

Value::operator Vector3D() const
{
  switch (myType) {
    case REAL:
      Report::error("[Value::operator Vector3D()] can't convert Real " +
	  	      (RCString)*this + " to Vector3D");
      break;
    case STRING:
      Report::error("[Value::operator Vector3D()] can't convert String '" +
	  	      (RCString)*this + "' to Vector3D");
      break;
    case VECTOR3D:
      return *vector3DVal;
    case VECTOR2D: 
      Report::error("[Value::operator Vector3D()] can't convert Vector2D '" +
	  	      (RCString)*this + "' to Vector3D");
      break;
    case MATRIX3D:
      Report::error("[Value::operator Vector3D()] can't convert TransMatrix3D '" +
	  	      (RCString)*this + "' to Vector3D");
      break;
    case MATRIX2D:
      Report::error("[Value::operator Vector3D()] can't convert TransMatrix2D '" +
	  	      (RCString)*this + "' to Vector3D");
      break;
    default:
      Report::error("[Value::operator Vector3D()] unknown operand type");
  }
  
  return Vector3D();  
}

Value::operator Vector2D() const
{
  switch (myType) {
    case REAL:
      Report::error("[Value::operator Vector2D()] can't convert Real " +
	  	      (RCString)*this + " to Vector2D");
      break;
    case STRING:
      Report::error("[Value::operator Vector2D()] can't convert String '" +
	  	      (RCString)*this + "' to Vector2D");
      break;
    case VECTOR3D: 
      Report::error("[Value::operator Vector2D()] can't convert Vector3D '" +
	  	      (RCString)*this + "' to Vector2D");
      break;
    case VECTOR2D:
      return *vector2DVal;
    case MATRIX3D:
      Report::error("[Value::operator Vector2D()] can't convert TransMatrix3D '" +
	  	      (RCString)*this + "' to Vector2D");
      break;
    case MATRIX2D:
      Report::error("[Value::operator Vector2D()] can't convert TransMatrix2D '" +
	  	      (RCString)*this + "' to Vector2D");
      break;
    default:
      Report::error("[Value::operator Vector2D()] unknown operand type");
  }
  
  return Vector2D();  
}

Value::operator TransMatrix3D() const
{
  switch (myType) {
    case REAL:
      Report::error("[Value::operator TransMatrix3D()] can't convert Real " +
	  	      (RCString)*this + " to TransMatrix3D");
      break;
    case STRING:
      Report::error("[Value::operator TransMatrix3D()] can't convert String '" +
	  	      (RCString)*this + "' to TransMatrix3D");
      break;
    case VECTOR3D:
      Report::error("[Value::operator TransMatrix3D()] can't convert Vector3D '" +
	  	      (RCString)*this + "' to TransMatrix3D");
      break;
    case VECTOR2D:
      Report::error("[Value::operator TransMatrix3D()] can't convert Vector2D '" +
	  	      (RCString)*this + "' to TransMatrix3D");
      break;
    case MATRIX3D:
      return *matrix3DVal;
    case MATRIX2D:
      Report::error("[Value::operator TransMatrix3D()] can't convert TransMatrix2D '" +
	  	      (RCString)*this + "' to TransMatrix3D");
      break;
    default:
      Report::error("[Value::operator TransMatrix3D()] unknown operand type");
  }  

  return TransMatrix3D();
}

Value::operator TransMatrix2D() const
{
  switch (myType) {
    case REAL:
      Report::error("[Value::operator TransMatrix2D()] can't convert Real " +
	  	      (RCString)*this + " to TransMatrix2D");
      break;
    case STRING:
      Report::error("[Value::operator TransMatrix2D()] can't convert String '" +
	  	      (RCString)*this + "' to TransMatrix2D");
      break;
    case VECTOR3D:
      Report::error("[Value::operator TransMatrix2D()] can't convert Vector3D '" +
	  	      (RCString)*this + "' to TransMatrix2D");
      break;
    case VECTOR2D:
      Report::error("[Value::operator TransMatrix2D()] can't convert Vector2D '" +
	  	      (RCString)*this + "' to TransMatrix2D");
      break;
    case MATRIX3D:
      Report::error("[Value::operator TransMatrix2D()] can't convert TransMatrix2D '" +
	  	      (RCString)*this + "' to TransMatrix2D");
      break;
    case MATRIX2D:
      return *matrix2DVal;
    default:
      Report::error("[Value::operator TransMatrix2D()] unknown operand type");
  }  

  return TransMatrix2D();
}

int Value::toReal(Real& x) const
{
  switch (myType) {
    case REAL:
      x = realVal;
      return 1;
    case STRING: {
      Real retval;
      char* ptr;

      retval = strtod(stringVal->chars(), &ptr);
      if (*ptr == '\0') {
        x = retval;
        return 1;
      }
    } break;
    default:
      break;
  }

  return 0;
}

int Value::toRCString(RCString& s) const
{
  s = (RCString)*this;
  return 1;
}

int Value::toVector3D(Vector3D& vec) const
{
  switch (myType) {
    case VECTOR3D:
      vec = *vector3DVal;
      return 1;
    case STRING: {
      double x, y, z;
      sscanf (stringVal->chars(), "[%lf,%lf,%lf]", &x, &y, &z);
      Vector3D retval((Real)x, (Real)y, (Real)z);
      vec = retval;
      return 1;}
    default:
      break;
  }

  return 0;
}

int Value::toVector2D(Vector2D& vec) const
{
  switch (myType) {
    case VECTOR2D:
      vec = *vector2DVal;
      return 1;
    case STRING: {
      double x, y;
      sscanf (stringVal->chars(), "[%lf,%lf]", &x, &y);
      Vector2D retval((Real)x, (Real)y);
      vec = retval;
      return 1;}
    default:
      break;
  }

  return 0;
}

int Value::toTransMatrix3D(TransMatrix3D& tmat) const
{
  if (myType == MATRIX3D) {
    tmat = *matrix3DVal;
    return 1;
  }
  return 0;
}

int Value::toTransMatrix2D(TransMatrix2D& tmat) const
{
  if (myType == MATRIX2D) {
    tmat = *matrix2DVal;
    return 1;
  }
  return 0;
}

//_________________________________________________________ Arithmetic operators

Value Value::operator-() const
{
  switch (myType) {
    case REAL:   
      return Value(-realVal);
    case VECTOR3D: 
      return Value(-*vector3DVal);
    case VECTOR2D: 
      return Value(-*vector2DVal);
    case MATRIX3D:
      Report::error("[Value::operator-] unary - not valid for TransMatrix3D");
    case MATRIX2D:
      Report::error("[Value::operator-] unary - not valid for TransMatrix2D");
    default:     
      Report::error("[Value::operator-] unknown operand type");
  }
      
  return *this;
}

Value Value::operator^(const Value& v) const
{  
  switch (binaryType(*this, v)) {
    case RR: 
      return Value(pow(realVal, v.realVal));
    case RS:
      return Value(pow(realVal, (Real) v));
    VV(^); vv(^);
    DefaultError(^);
  }
}

Value Value::operator%(const Value& v) const
{
  switch (binaryType(*this, v)) {
    case RR: 
      return Value(fmod(realVal, v.realVal));
    case RS: 
      return Value(fmod(realVal, (Real) v));
    DefaultError(%);
  }
}

Value Value::operator!() const
{
  switch (myType) {
    case REAL: 
      return Value(!realVal);
    case STRING: 
      return Value(stringVal->isEmpty());
    case VECTOR3D:
      return Value(vector3DVal->zero());
    case VECTOR2D:
      return Value(vector2DVal->zero());
    case MATRIX3D:
      return Value(matrix3DVal->zero());
    case MATRIX2D:
      return Value(matrix2DVal->zero());
    default:   
      Report::error("[Value::operator!] unknown operand type");
  }
  return *this;
}

Value Value::operator[](const Value& theIndex) const
{
  switch (myType) {
    case REAL:
      Report::error("[Value::operator[] ] no index operation for Reals");
      break;
    case STRING:
      return Value(RCString((*stringVal)[(int)Real(theIndex)],1));
    case VECTOR3D:
      return Value((*vector3DVal)[(int)Real(theIndex)]);
    case VECTOR2D:
      return Value((*vector2DVal)[(int)Real(theIndex)]);
    case MATRIX3D:
      Report::error("[Value::operator[] ] no index operation for TransMatrix3D");
      break;
    case MATRIX2D:
      Report::error("[Value::operator[] ] no index operation for TransMatrix2D");
      break;
    default:
      break;
  }
  return Value();
}

/*
 * Generic creation of several binary operators using the macros definied in
 * ValueMacros.h, e.g.
 *
 *    GenerateOp2(+, RR, DefaultError); 
 *
 * will create the operator+ limited to Real numbers (RR). For other value
 * arguments like String or Vectors, we will get a runtime error.
 */

GenerateOp11 (+,  
	      RR, R_S2R, 
	      S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S,
	      VV, 
	      vv,
	      DefaultError);
GenerateOp5 (-,  
	     RR, R_S2R, 
	     VV, 
	     vv,
	     DefaultError);
GenerateOp14 (*,  
	      RR, R_S2R, RV, Rv,
	      VR, V_S2R, VV, VM,
	      vR, v_S2R, vm,
	      MM, 
	      mm,
	      DefaultError);
GenerateOp7 (/,  
	     RR, R_S2R, 
	     VR, V_S2R, 
	     vR, v_S2R,
	     DefaultError);
GenerateOp3 (&&, 
	     RR, R_S2R, 
	     DefaultError);
GenerateOp3 (||, 
	     RR, R_S2R, 
	     DefaultError);
GenerateOp13 (==, 
	      RR, R_S2R, 
	      S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S,
	      VV, 
	      vv,
	      MM, 
	      mm,
	      DefaultError);
GenerateOp13 (!=, 
	      RR, R_S2R, 
	      S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S,
	      VV, 
	      vv,
	      MM, 
	      mm,
	      DefaultError);
GenerateOp9 (<,  
	     RR, R_S2R, 
	     S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S, 
	     DefaultError);
GenerateOp9 (<=, 
	     RR, R_S2R, 
	     S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S,
	     DefaultError);
GenerateOp9 (>,  
	     RR, R_S2R, 
	     S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S, 
	     DefaultError);
GenerateOp9 (>=, 
	     RR, R_S2R, 
	     S_R2S, SS, S_V2S, S_v2S, S_M2S, S_m2S,
	     DefaultError);

//_______________________________________________________________ Static members

/*
 * Generates error messages in the following form:
 *
 *   [operator op] operands type1 and type2 are incompatible!
 */
void Value::error(const RCString& op, const Value& arg1, const Value& arg2)
{
  RCString operand1;
  RCString operand2;
  
  switch (arg1.myType) {
    case REAL:     operand1 = "Real";          break;
    case STRING:   operand1 = "String";        break;
    case VECTOR3D: operand1 = "Vector3D";      break;
    case VECTOR2D: operand1 = "Vector2D";      break;
    case MATRIX3D: operand1 = "TransMatrix3D"; break;
    case MATRIX2D: operand1 = "TransMatrix2D"; break;
    default:       operand1 = "UNKNOWN";
  }

  switch (arg2.myType) {
    case REAL:     operand2 = "Real";          break;
    case STRING:   operand2 = "String";        break;
    case VECTOR3D: operand2 = "Vector3D";      break;
    case VECTOR2D: operand2 = "Vector2D";      break;
    case MATRIX3D: operand2 = "TransMatrix3D"; break;
    case MATRIX2D: operand2 = "TransMatrix2D"; break;
    default:       operand2 = "UNKNOWN";
  }

  Report::error("[Value::operator" + op + "] operands " +
                operand1 + " and " + operand2 + " are incompatible");
}

//______________________________________________________________________ Friends

std::ostream& operator<<(std::ostream& os, const Value& v)
{
  switch(v.myType) {
    case REAL:
      os << v.realVal; break;
    case STRING:
      os << *v.stringVal; break;
    case VECTOR3D:
      os << *v.vector3DVal; break;
    case VECTOR2D:
      os << *v.vector2DVal; break;
    case MATRIX3D:
      os << *v.matrix3DVal; break;
    case MATRIX2D:
      os << *v.matrix2DVal; break;
    default:
      Report::error("[operator<<(ostream&, const Value&)] unknown operand type");
  }
 
  return os;
}
