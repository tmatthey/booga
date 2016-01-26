/*
 * $RCSfile: ColorTypes.C,v $ 
 *
 * Copyright (C) 1994-96, Christoph Streit <streit@iam.unibe.ch>
 *                        Stephan Amann <amann@iam.unibe.ch>
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
 *  $Id: ColorTypes.C,v 1.3 1996/08/30 08:16:10 streit Exp $
 * -----------------------------------------------------------------------------
 */
 
#include "booga/base/ColorTypes.h"

//__________________________________________________________________________ RGB

void RGB::setValue(float c1, float c2, float c3)
{
  setRed(c1);
  setGreen(c2);
  setBlue(c3);
}

void RGB::setValue(float value)
{
  setRed(value);
  setGreen(value);
  setBlue(value);
}

void RGB::setValue(bool value)
{
  if (value == false)
    setValue((float)0.0);
  else
    setValue((float)1.0);
}

void RGB::getValue(float& c1, float& c2, float& c3) const
{
  c1 = getRed();
  c2 = getGreen();
  c3 = getBlue();
}

void RGB::getValue(float& value) const
{
  value = brightness();
}

void RGB::getValue(bool& value) const
{
  if (brightness() <= 0.5)
    value = false;
  else
    value = true;
}

//______________________________________________________________________ RGBChar

void RGBChar::setValue(float c1, float c2, float c3)
{
  if (c1 < 0)
    myRed = 0;
  else if (c1 > 1)
    myRed = 255;
  else
    myRed = (unsigned char)(c1 * 255);

  if (c2 < 0)
    myGreen = 0;
  else if (c2 > 1)
    myGreen = 255;
  else
    myGreen = (unsigned char)(c2 * 255);

  if (c3 < 0)
    myBlue = 0;
  else if (c3 > 1)
    myBlue = 255;
  else
    myBlue = (unsigned char)(c3 * 255);
}

void RGBChar::setValue(float value)
{
  if (value < 0)
    myRed = myGreen = myBlue = 0;
  else if (value > 1)
    myRed = myGreen = myBlue = 255;
  else
    myRed = myGreen = myBlue = (unsigned char)(value * 255);
}

void RGBChar::setValue(bool value)
{
  if (value == false)
    myRed = myGreen = myBlue = 0;
  else
    myRed = myGreen = myBlue = 255;
}

void RGBChar::getValue(float& c1, float& c2, float& c3) const
{
  c1 = myRed   / 255.0;
  c2 = myGreen / 255.0;
  c3 = myBlue  / 255.0;
}

void RGBChar::getValue(float& value) const
{
  value = (0.59*myRed + 0.3*myGreen + 0.11*myBlue) / 255.0;
}

void RGBChar::getValue(bool& value) const
{
  float grey = (0.59*myRed + 0.3*myGreen + 0.11*myBlue) / 255.0;
  if (grey <= 0.5)
    value = false;
  else
    value = true;
}

//_________________________________________________________________________ Grey

void Grey::setValue(float c1, float c2, float c3)
{
  myValue = Color(c1, c2, c3).brightness();
}

void Grey::setValue(float value)
{
  myValue = value;
}

void Grey::setValue(bool value)
{
  if (value == false)
    myValue = 0;
  else
    myValue = 1;
}

void Grey::getValue(float& c1, float& c2, float& c3) const
{
  c1 = c2 = c3 = myValue;
}

void Grey::getValue(float& value) const
{
  value = myValue;
}

void Grey::getValue(bool& value) const
{
  if (myValue <= 0.5)
    value = false;
  else
    value = true;
}

//___________________________________________________________________________ BW

void BW::setValue(float c1, float c2, float c3)
{
  setValue(Color(c1, c2, c3).brightness());
}

void BW::setValue(float value)
{
  if (value <= 0.5)
    myValue = false;
  else
    myValue = true;
}

void BW::setValue(bool value)
{
  myValue = value;
}

void BW::getValue(float& c1, float& c2, float& c3) const
{
  if (myValue == false)
    c1 = c2 = c3 = 0.0;
  else
    c1 = c2 = c3 = 1.0;
}

void BW::getValue(float& value) const
{
  if (myValue == false)
    value = 0;
  else
    value = 1;
}

void BW::getValue(bool& value) const
{
  value = myValue;
}
