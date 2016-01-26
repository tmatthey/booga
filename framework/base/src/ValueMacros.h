/*
 * ValueMacros.h 
 *
 * Macro definition for generic operator generation in Value.C
 *
 * Copyright (C) 1994, Christoph Streit <streit@iam.unibe.ch>
 *                     Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ValueMacros.h,v 1.2 1995/04/21 12:36:58 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _ValueMacros_H
# define _ValueMacros_H

//
// xy    : combine object of type x with object of type y
// x_y2z : combine object of type x with object of type z
//         after casting it from y to z
//

#define RR(op) case RR: return Value( realVal op  v.realVal   )
#define RS(op) case RS: return Value( realVal op *v.stringVal )
#define RV(op) case RV: return Value( realVal op *v.vector3DVal )
#define Rv(op) case Rv: return Value( realVal op *v.vector2DVal )
#define RM(op) case RM: return Value( realVal op *v.matrix3DVal )
#define Rm(op) case Rm: return Value( realVal op *v.matrix2DVal )
#define R_S2R(op) case RS: return Value( realVal op (Real) v  )

#define SR(op) case SR: return Value( *stringVal op  v.realVal   )
#define SS(op) case SS: return Value( *stringVal op *v.stringVal )
#define SV(op) case SV: return Value( *stringVal op *v.vector3DVal )
#define Sv(op) case Sv: return Value( *stringVal op *v.vector2DVal )
#define SM(op) case SM: return Value( *stringVal op *v.matrix3DVal )
#define Sm(op) case Sm: return Value( *stringVal op *v.matrix2DVal )
#define S_R2S(op) case SR: return Value( *stringVal op (RCString) v )
#define S_V2S(op) case SV: return Value( *stringVal op (RCString) v )
#define S_v2S(op) case Sv: return Value( *stringVal op (RCString) v )
#define S_M2S(op) case SM: return Value( *stringVal op (RCString) v )
#define S_m2S(op) case Sm: return Value( *stringVal op (RCString) v )

#define VR(op) case VR: return Value( *vector3DVal op  v.realVal   )
#define VS(op) case VS: return Value( *vector3DVal op *v.stringVal )
#define VV(op) case VV: return Value( *vector3DVal op *v.vector3DVal )
#define Vv(op) case Vv: return Value( *vector3DVal op *v.vector2DVal )
#define VM(op) case VM: return Value( *vector3DVal op *v.matrix3DVal )
#define Vm(op) case Vm: return Value( *vector3DVal op *v.matrix2DVal )
#define V_S2R(op) case VS: return Value( *vector3DVal op (Real) v )

#define vR(op) case vR: return Value( *vector2DVal op  v.realVal   )
#define vS(op) case vS: return Value( *vector2DVal op *v.stringVal )
#define vV(op) case vV: return Value( *vector2DVal op *v.vector3DVal )
#define vv(op) case vv: return Value( *vector2DVal op *v.vector2DVal )
#define vM(op) case vM: return Value( *vector2DVal op *v.matrix3DVal )
#define vm(op) case vm: return Value( *vector2DVal op *v.matrix2DVal )
#define v_S2R(op) case vS: return Value( *vector2DVal op (Real) v )

#define MR(op) case MR: return Value( *matrix3DVal op  v.realVal   )
#define MS(op) case MS: return Value( *matrix3DVal op *v.stringVal )
#define MV(op) case MV: return Value( *matrix3DVal op *v.vector3DVal )
#define Mv(op) case Mv: return Value( *matrix3DVal op *v.vector2DVal )
#define MM(op) case MM: return Value( *matrix3DVal op *v.matrix3DVal )
#define Mm(op) case Mm: return Value( *matrix3DVal op *v.matrix2DVal )
#define M_S2R(op) case MS: return Value( *matrix3DVal op (Real) v )

#define mR(op) case mR: return Value( *matrix2DVal op  v.realVal   )
#define mS(op) case mS: return Value( *matrix2DVal op *v.stringVal )
#define mV(op) case mV: return Value( *matrix2DVal op *v.vector3DVal )
#define mv(op) case mv: return Value( *matrix2DVal op *v.vector2DVal )
#define mM(op) case mM: return Value( *matrix2DVal op *v.matrix3DVal )
#define mm(op) case mm: return Value( *matrix2DVal op *v.matrix2DVal )
#define m_S2R(op) case mS: return Value( *matrix2DVal op (Real) v )

#define Default(op)      default: return Value( (Real)*this op (Real)v )
#define DefaultError(op) default: Value::error(RCString(#op), *this, v); return Value();

#define GenerateOp2(op,V1,V2) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op);  \
}}

#define GenerateOp3(op,V1,V2,V3) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op);  \
}}

#define GenerateOp4(op,V1,V2,V3,V4) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op);  \
}}

#define GenerateOp5(op,V1,V2,V3,V4,V5) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op);  \
}}

#define GenerateOp6(op,V1,V2,V3,V4,V5,V6) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op);  \
}}

#define GenerateOp7(op,V1,V2,V3,V4,V5,V6,V7) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op);  \
}}

#define GenerateOp7(op,V1,V2,V3,V4,V5,V6,V7) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op);  \
}}

#define GenerateOp8(op,V1,V2,V3,V4,V5,V6,V7,V8) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op);  \
}}

#define GenerateOp9(op,V1,V2,V3,V4,V5,V6,V7,V8,V9) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
}}

#define GenerateOp10(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op);  \
}}

#define GenerateOp11(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op);  \
}}

#define GenerateOp12(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op); V12(op);  \
}}

#define GenerateOp13(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op); V12(op); V13(op);  \
}}

#define GenerateOp14(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op); V12(op); V13(op); V14(op);  \
}}

#define GenerateOp15(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14,V15) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op); V12(op); V13(op); V14(op); V15(op);  \
}}

#define GenerateOp16(op,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14,V15,V16) \
Value Value::operator op (const Value& v) const { switch (binaryType(*this, v)) { \
  V1(op); V2(op); V3(op); V4(op); V5(op); V6(op); V7(op); V8(op); V9(op); \
  V10(op); V11(op); V12(op); V13(op); V14(op); V15(op); V16(op);  \
}}

#endif // _ValueMacros_H
