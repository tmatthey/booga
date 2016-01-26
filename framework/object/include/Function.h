/*
 * Function.h 
 *
 * Copyright (C) 1994, Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: Function.h,v 1.2 1995/04/21 12:32:28 amann Exp $
 * -----------------------------------------------------------------------------
 */

#ifndef _Function_H
#define _Function_H

#include "booga/object/Makeable.h"

//_____________________________________________________________________ Function

class Function : public Makeable {
declareRTTI(Function); 
// enable RTTI support
protected:
  Function() {}
};

//__________________________________________________________________ FunctionSin

class FunctionSin : public Function {
declareRTTI(FunctionSin);
// enable RTTI support
public:
  FunctionSin(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//__________________________________________________________________ FunctionCos

class FunctionCos : public Function {
declareRTTI(FunctionCos);
// enable RTTI support
public:
  FunctionCos(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//__________________________________________________________________ FunctionTan

class FunctionTan : public Function {
declareRTTI(FunctionTan);
// enable RTTI support
public:
  FunctionTan(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//_________________________________________________________________ FunctionASin

class FunctionASin : public Function {
declareRTTI(FunctionASin);
// enable RTTI support
public:
  FunctionASin(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//_________________________________________________________________ FunctionACos

class FunctionACos : public Function {
declareRTTI(FunctionACos);
// enable RTTI support
public:
  FunctionACos(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//_________________________________________________________________ FunctionATan

class FunctionATan : public Function {
declareRTTI(FunctionATan);
// enable RTTI support
public:
  FunctionATan(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//_________________________________________________________________ FunctionRand

class FunctionRand : public Function {
declareRTTI(FunctionRand);
// enable RTTI support
public:
  FunctionRand(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//_________________________________________________________________ FunctionSqrt

class FunctionSqrt : public Function {
declareRTTI(FunctionSqrt);
// enable RTTI support
public:
  FunctionSqrt(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//__________________________________________________________________ FunctionPow

class FunctionPow : public Function {
declareRTTI(FunctionPow);
// enable RTTI support
public:
  FunctionPow(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//__________________________________________________________________ FunctionExp

class FunctionExp : public Function {
declareRTTI(FunctionExp);
// enable RTTI support
public:
  FunctionExp(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//__________________________________________________________________ FunctionLog

class FunctionLog : public Function {
declareRTTI(FunctionLog);
// enable RTTI support
public:
  FunctionLog(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

//___________________________________________________________________ FunctionLn

class FunctionLn : public Function {
declareRTTI(FunctionLn);
// enable RTTI support
public:
  FunctionLn(Exemplar) {}
  virtual Makeable* make(RCString& errMsg, const List<Value*>* parameters) const;
};

#endif // _Function_H
