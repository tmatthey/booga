/*
 * AbstractPixmap.C 
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
 *  $Id: AbstractPixmap.C,v 1.18 1997/09/19 07:13:50 buhlmann Exp $
 * -----------------------------------------------------------------------------
 */
#ifdef SVR4
#include <unistd.h>    // STDOUT_FILENO
#endif
#include <string.h>    // memcpy
#include <math.h>      // fabs
#include <strstream.h> // ostrstream

#include "booga/base/Report.h"
#include "booga/base/AbstractPixmap.h"

//_______________________________________________________________ AbstractPixmap

const RCString AbstractPixmap::MAGIC_NUMBER("BOOGA Pixmap Format");
const RCString AbstractPixmap::EXTENSION("pixi");

const int AbstractPixmap::MAX_USERCHANNELS = 32;
const int AbstractPixmap::MAX_SYSCHANNELS = 6;
const int AbstractPixmap::MAX_CHANNELS = MAX_USERCHANNELS+MAX_SYSCHANNELS;

AbstractPixmap::AbstractPixmap(int resX, int resY)
{
  myResX = resX;  myResY = resY;
  mySize = myResX * myResY;
  myCurrentPos = -1;
  myRangeMin = 0; myRangeMax = 1;

  myChannels = new float*[MAX_CHANNELS];
  for (int i=0; i<MAX_CHANNELS; i++)
    myChannels[i] = NULL;
}

AbstractPixmap::AbstractPixmap(const AbstractPixmap& pm)
{
  myChannels = new float*[MAX_CHANNELS];
  for (int i=0; i<MAX_CHANNELS; i++)
    myChannels[i] = NULL;
    
  assign(pm);
}

AbstractPixmap::~AbstractPixmap()
{
  for (int i=0; i<MAX_CHANNELS; i++)
    if (myChannels[i]) delete [] myChannels[i];
  delete [] myChannels;
}

void AbstractPixmap::setResolution(int resX, int resY)
{
  if (resX<=0 || resY<=0) {
    ostrstream os;
    os << "[AbstractPixmap::setResolution] illegal resolution ("
       << resX << ", " << resY << ") ignored";
    Report::recoverable(os);
    return;
  }

  myResX = resX;
  myResY = resY;
  mySize = myResX * myResY;
  
  for (int i=0; i<MAX_CHANNELS; i++)
    if (myChannels[i]) {
      delete [] myChannels[i];
      myChannels[i] = NULL;
    }
}

void AbstractPixmap::setRange(float min, float max)
{
  if ((max < min) || fabs(max-min) < EPSILON) {
    ostrstream os;
    os << "[AbstractPixmap::setRange] illegal range settings ("
       << min << ", " << max << ") ignored";
    Report::warning(os);
    return;
  }

  myRangeMin = min;
  myRangeMax = max;
}

void AbstractPixmap::clearColor(float c1, float c2, float c3)
{
  for (long p=0; p<mySize; p++) {
    setPosition(p);
    setColor(c1, c2, c3);
  }
}

void AbstractPixmap::clearColor(float value)
{
  for (long p=0; p<mySize; p++) {
    setPosition(p);
    setColor(value);
  }
}

void AbstractPixmap::clearColor(bool value)
{
  for (long p=0; p<mySize; p++) {
    setPosition(p);
    setColor(value);
  }
}

void AbstractPixmap::clearDepth(float depth)
{
  clearChannel(AbstractPixmap::DEPTH, depth);
}

void AbstractPixmap::clearAlpha(float alpha)
{
  clearChannel(AbstractPixmap::ALPHA, alpha);
}

void AbstractPixmap::setPosition(int x, int y) const
{
  //
  // This method alters the *internal* state of the object only ->
  // logical const-ness of 'this' is casted away.
  //
  AbstractPixmap* This = (AbstractPixmap*) this;

  if (0>x || x>=This->myResX || 0>y || y>=This->myResY) {
    ostrstream os;
    os << "[AbstractPixmap::setPosition(int, int)] illegal pixmap position ("
       << x << ", " << y << ") ignored." 
       << " Range is x: [0, " << This->myResX 
       <<        "], y: [0, " << This->myResY << "]";
    Report::recoverable(os);
    return;
  } 

  This->myCurrentPos = x + y*This->myResX;
}

void AbstractPixmap::setPosition(long pos) const
{
  //
  // This method alters the *internal* state of the object only ->
  // logical const-ness of 'this' is casted away.
  //
  AbstractPixmap* This = (AbstractPixmap*) this;

  if (0>pos || pos>=This->mySize) {
    ostrstream os;
    os << "[AbstractPixmap::setPosition(long)] illegal pixmap position " 
       << pos << " ignored." 
       << " Range is [0, " << This->mySize << "]"; 
    Report::recoverable(os);
    return;
  }
  
  This->myCurrentPos = pos;
}

void AbstractPixmap::setDepth(float depth)
{
  setChannel(AbstractPixmap::DEPTH, depth);
}

void AbstractPixmap::getDepth(float& depth) const
{
  getChannel(AbstractPixmap::DEPTH, depth);
}

void AbstractPixmap::setAlpha(float alpha)
{
  setChannel(AbstractPixmap::ALPHA, alpha);
}

void AbstractPixmap::getAlpha(float& alpha) const
{
  getChannel(AbstractPixmap::ALPHA, alpha);
}

bool AbstractPixmap::getUnusedUserChannel(int& channel) const
{
  for(channel=0; channel < MAX_USERCHANNELS; channel++)
    if (!haveUserChannel(channel))
      return false;
  
  return true;
}
 
bool AbstractPixmap::haveUserChannel(int channel) const
{
  if (channel<0 || channel >= MAX_USERCHANNELS) {
    ostrstream os;
    os << "[AbstractPixmap::haveUserChannel] channel number "
       << channel << " is out of range." 
       << " Valid numbers are 0 to " << MAX_USERCHANNELS; 
    Report::recoverable(os);
    return false;
  }
  
  return haveChannel(channel+MAX_SYSCHANNELS);
}

void AbstractPixmap::clearUserChannel(int channel, float value)
{
  if (channel<0 || channel >= MAX_USERCHANNELS) {
    ostrstream os;
    os << "[AbstractPixmap::clearUserChannel] channel number "
       << channel << " is out of range." 
       << " Valid numbers are 0 to " << MAX_USERCHANNELS; 
    Report::recoverable(os);
    return;
  }

  clearChannel(channel+MAX_SYSCHANNELS, value);  
}

void AbstractPixmap::setUserChannel(int channel, float value)
{
  if (channel<0 || channel >= MAX_USERCHANNELS) {
    ostrstream os;
    os << "[AbstractPixmap::setUserChannel] channel number "
       << channel << " is out of range." 
       << " Valid numbers are 0 to " << MAX_USERCHANNELS; 
    Report::recoverable(os);
    return;
  }

  setChannel(channel+MAX_SYSCHANNELS, value);
}

void AbstractPixmap::getUserChannel(int channel, float& value) const
{
  if (channel<0 || channel >= MAX_USERCHANNELS) {
    ostrstream os;
    os << "[AbstractPixmap::getUserChannel] channel number "
       << channel << " is out of range." 
       << " Valid numbers are 0 to " << MAX_USERCHANNELS; 
    Report::recoverable(os);
    return;
  }

  getChannel(channel+MAX_SYSCHANNELS, value);
}

/*
 * File format for Pixmap:
 * 
 * Description                  Example
 * -----------------------------------------------------------------------------
 * - Magic Number          :    BOOGA Pixmap ('AbstractPixmap::MAGIC_NUMBER')
 * - Comment(s)            :    # Comment to the end of the line
 * - Width/Height (int)    :    as ASCII 
 * - Range Min/Max (float) :    as ASCII
 * - channels              :    "alpha" "depth" channel-numbers (0-MAX_CHANNEL)
 * - binary color (rgb)    :    color        repeat width*height times
 * - binary alpha (if any) :    alpha        repeat width*height times
 * - binary depth (if any) :    depth        repeat width*height times
 * - binary user channels  :    user-channel repeat width*height times
 *
 */
bool AbstractPixmap::save(const RCString& fileName, const RCString& comment) const
{
  ofstream ofs;

  if (fileName.isEmpty())
    ofs.rdbuf()->attach(STDOUT_FILENO);
  else
    ofs.open(fileName.chars());

  if (ofs.bad()) {
    Report::warning("[AbstractPixmap::save] could not open file named \"" + fileName + "\"");
    return false;
  }

  return save(ofs, comment);
}

bool AbstractPixmap::save(ofstream& ofs, const RCString& comment) const
{ 
  //
  // Write header information.
  //
  ofs << AbstractPixmap::MAGIC_NUMBER << endl;         // Magic number
  ofs << "# This file contains an image in the BOOGA Format\n";
  if (!comment.isEmpty()) 
    ofs << comment << endl;	                     // Comment
  ofs << myResX << " " << myResY << endl;	            // Resolution of image
  ofs << myRangeMin << " " << myRangeMax << endl;        // Range of color values
  for (int i=0; i<MAX_CHANNELS; i++)     // User channels ?
    if (myChannels[i] != NULL)
      ofs << i << " ";
  ofs << endl;
  
  float* color = new float[3*mySize];
  long p;
  int c;
  bool didCut = false;
  //
  // Write image.
  //
  for (p=0; p<mySize; p++) {
    setPosition(p);
    getColor(color[3*p+0], color[3*p+1], color[3*p+2]);
    for (c=0; c<3; c++) {
      if (color[3*p+c] < myRangeMin) {
        color[3*p+c] = myRangeMin;
        didCut = true;
      } else if (color[3*p+c] > myRangeMax) {
        color[3*p+c] = myRangeMax;
        didCut = true;
      }
    }
  }
  ofs.write((const char*)color, 3*mySize*sizeof(float));
  delete [] color;
  
  if (didCut)
    Report::warning("[AbstractPixmap::save] Pixel values adapted to range");

  //
  // Write channels
  //
  for (int j=0; j<MAX_CHANNELS; j++)
    if (myChannels[j] != NULL) 
      ofs.write((const char *)myChannels[j], mySize*sizeof(float));
  
  if (ofs.bad()) {
    Report::warning("[AbstractPixmap::save] an error occured while writing Pixmap");
    return false;
  }

  return true;
}

bool AbstractPixmap::load(const RCString& fileName)
{
  ifstream ifs;
#ifndef WIN32 // STDIN not supported on WIN32 platforms
  if (fileName.isEmpty())
    ifs.rdbuf()->attach(STDIN_FILENO);
  else
#endif
    ifs.open(fileName.chars());

  if (ifs.bad()) {
    Report::warning("[AbstractPixmap::load] could not open file named \"" + fileName + "\"");
    return false;
  }

  return load(ifs);
}

bool AbstractPixmap::load(ifstream& ifs)
{
  const int MAX_LINE_LENGTH = 5 * MAX_CHANNELS;
  char line[MAX_LINE_LENGTH];

  //
  // First check if we really got a pixi.
  //
  ifs.getline(line, MAX_LINE_LENGTH);
  if (RCString(line) != AbstractPixmap::MAGIC_NUMBER)
    return false;

  //
  // Jup... we've got a pixi type image
  // -> Read Header Information.
  //
  char comment;			// First : read comment
  ifs.get(comment);
  while (comment == '#') {
    ifs.getline(line, MAX_LINE_LENGTH);
    ifs.get(comment);
  }
  ifs.putback(comment);

  //   
  // Read and set image resolution.
  //
  char newline;
  int resX, resY;		        
  ifs >> resX >> resY;
  ifs.get(newline);
  setResolution(resX, resY);
  
  //   
  // Read and set image range.
  //
  float rangeMin, rangeMax;		        
  ifs >> rangeMin >> rangeMax;
  ifs.get(newline);
  setRange(rangeMin, rangeMax);

  //
  // Read line defining kind and number of channels.
  //
  ifs.getline(line, MAX_LINE_LENGTH);
  List<RCString>* tokens = RCString(line).createTokens(" \n");

  // Test which channels are necessary
  bool needChannel[MAX_CHANNELS];
  for (int i=0; i<MAX_CHANNELS; i++)
    needChannel[i] = false;
  int channel;
  long count = tokens->count();
  for (long curToken=0; curToken<count; curToken++) {
    channel = (int)atof(tokens->item(curToken).chars());
    needChannel[channel] = true;
  }
  delete tokens;

  if (ifs.bad()) {
    Report::recoverable("[AbstractPixmap::load] an error occured while reading a Pixmap");
    return false;
  }

  //
  // Read image.
  //
  float* color = new float[3*mySize];
  ifs.read((char*)color, 3*mySize*sizeof(float));
  for (long p=0; p<mySize; p++) {
    setPosition(p);
    setColor(color[3*p+0], color[3*p+1], color[3*p+2]);
  }
  delete [] color;
  
  //
  // Read channels
  //   
  for (int j=0; j<MAX_CHANNELS; j++) 
    if (needChannel[j]) {
      myChannels[j] = new float[mySize];
      ifs.read((char *)myChannels[j], mySize*sizeof(float));
    } 
    
  if (ifs.bad()) {
    Report::warning("[AbstractPixmap::load] an error occured while reading a Pixmap");
    return false;
  }

  return true;
}

void AbstractPixmap::assign(const AbstractPixmap& pm)
{
  //
  // Delete user channels if necessary.
  //
  for (int i=0; i<MAX_CHANNELS; i++)
    if (myChannels[i]) {
      delete [] myChannels[i];
      myChannels[i] = NULL;
    }
    
  myResX = pm.myResX;
  myResY = pm.myResY;
  mySize = pm.mySize;
  
  myRangeMin = pm.myRangeMin;
  myRangeMax = pm.myRangeMax;

  //
  // Copy user channels if needed.
  //
  for (int j=0; j<MAX_CHANNELS; j++)
    if (pm.myChannels[j] != NULL) {
      myChannels[j] = new float[mySize];
      memcpy(myChannels[j], pm.myChannels[j], mySize);
    } 
  
  myCurrentPos = -1;
}

void AbstractPixmap::clearChannel(int channel, float value)
{
  if (myChannels[channel] == NULL)
    myChannels[channel] = new float[mySize];
  
  for (long i=0; i<mySize; i++)
    myChannels[channel][i] = value;
}

void AbstractPixmap::setChannel(int channel, float value)
{
  if (myCurrentPos < 0) {
    Report::recoverable("[AbstractPixmap::setChannel] use setPosition first");
    return;
  }
  
  if (myChannels[channel] == NULL) {
    myChannels[channel] = new float[mySize];
    clearChannel(channel);
  }
  
  myChannels[channel][myCurrentPos] = value;
}

void AbstractPixmap::getChannel(int channel, float& value) const
{
  if (myCurrentPos < 0) {
    Report::recoverable("[AbstractPixmap::setChannel] use setPosition first");
    return;
  }

  if (myChannels[channel] == NULL) {
    //
    // This method alters the *internal* state of the object only ->
    // logical const-ness of 'this' is casted away.
    //
    AbstractPixmap* This = (AbstractPixmap*) this;

    This->myChannels[channel] = new float[This->mySize];
    This->clearChannel(channel);
  }
  
  value = myChannels[channel][myCurrentPos];
}

 
