/*  -*- c++ -*-  */
#ifndef _FDSTREAM_H
#define _FDSTREAM_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "booga/base/RCString.h"

struct AbstractFile {
  int fd;
  RCString filename;
  AbstractFile():fd(0),filename(""){}
  AbstractFile(int fd_):fd(fd_),filename(""){}
  AbstractFile(RCString name):fd(0),filename(name){}
  AbstractFile(const char* name):fd(0),filename(name){}
  void attach(RCString name){fd=0;filename= name;}
  void attach(const char* name){fd=0;filename= name;}
  void attach(int fd_){fd=fd_;filename="";}
  int tellg() const {return (filename.isEmpty()?1:0);}
};

class FileFD {
  FILE* file;
  bool  cl;
public:
  FileFD(const AbstractFile& af, const char* attr):file(NULL),cl(false){
    if(af.filename.isEmpty()){
      if(STDOUT_FILENO){
	file = stdout;
      }
      else if(STDIN_FILENO){
	file = stdin;
      }
      else if(STDERR_FILENO){
	file = stderr;
      }
    }
    else {
      file = fopen(af.filename.chars(),attr);
      cl = true;
    }
  }
  bool bad() const{return file == NULL;}
  operator FILE*()const{return file;}
  ~FileFD(){
    if(cl && file != NULL)
    {
      if (fseek(file, 0, SEEK_CUR) != -1 && errno != EBADF)
	fclose(file);
    }
    file = NULL;
  }
};

class FileSTDIn {
  std::istream *is;
  bool  cl;
public:
  FileSTDIn(const AbstractFile& af, std::ios::openmode mode = std::ios::in):is(NULL),cl(false){
    if(af.filename.isEmpty()){
      if(STDIN_FILENO){
	is = &std::cin;
      }
    }
    else {
      is = new std::ifstream(af.filename.chars(),mode);
      if(is->bad()){
	delete is;
	is = NULL;
      }
      cl = (is != NULL);
    }
  }
  bool bad() const{return (is == NULL || is->bad());}
  operator std::istream& ()const{return *is;}
  ~FileSTDIn(){
    if(cl && is != NULL)
      delete is;
  }

};

class FileSTDOut {
  std::ostream *os;
  bool  cl;
public:
  FileSTDOut(const AbstractFile& af, std::ios::openmode mode = std::ios::out | std::ios::trunc):os(NULL),cl(false){
    if(af.filename.isEmpty()){
      if(STDOUT_FILENO){
	os = &std::cout;
      }
      else if(STDERR_FILENO){
	os = &std::cerr;
      }
    }
    else {
      os = new std::ofstream(af.filename.chars(),mode);
      if(os->bad()){
	delete os;
	os = NULL;
      }
      cl = (os != NULL);
    }
  }
  bool bad() const{return (os == NULL || os->bad());}
  operator std::ostream& ()const{return *os;}
  ~FileSTDOut(){
    if(cl && os != NULL)
      delete os;
  }
};

#endif /*_FDSTREAM_H*/
