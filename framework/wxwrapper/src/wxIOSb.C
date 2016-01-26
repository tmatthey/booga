#include <stdlib.h>
#include <iostream>
#include <wx.h>
#include "booga/wxwrapper/wxIOSb.h"

////////////////////////////////////////////////////////
//
//  

#define PBR 4

wxIostrbuf::wxIostrbuf(const int lngbuf, wxTextWindow *tw): _tw(tw), _lngbuf(lngbuf) {
  
   if  ((pbuffer = (new char[lngbuf])) != NULL) {
      setp(pbuffer, pbuffer + lngbuf);
   }
   
   if ((gbuffer = new char[lngbuf + PBR]) != NULL) {
      setg(gbuffer + PBR, gbuffer + PBR, gbuffer + PBR);
   }
      
   if (!pbuffer || !gbuffer) { 
      cerr << "[WXIOSTRBUF::CONSTR: Cannot create puffer!" << endl; exit(1); 
   }
   if (!_tw) {
      cerr << "[WXIOSTRBUF::CONSTR: No text-window!"       << endl; exit(1); 
   }

   sync();
}

wxIostrbuf::~wxIostrbuf() {
   delete[] pbuffer;
   delete[] gbuffer;
   pbuffer = gbuffer = 0;
}

////////////////////////////////////////////////////////


////////////////////////////////////////////////////////

int wxIostrbuf::sync() {

   int count = out_waiting();
   if (count) {
      writen(count);
   }
   return streambuf::sync();
}

////////////////////////////////////////////////////////

int wxIostrbuf::overflow(int) {

   int count = out_waiting();
   if (count) {
      writen(count);
   }
//   return streambuf::overflow();
   return 0;
}

int wxIostrbuf::underflow() {
  
   char *p = gbuffer + PBR;
   char *pp;
   char *line = new char[_lngbuf];

   if (gptr()<egptr()) return *gptr();

   if (line) {
      _tw->GetLineText(_tw->GetNumberOfLines(), line);
   } else 
     line = "";
   
   pp=wxGetTextFromUser(line, "", "", _tw, -1,-1, TRUE);
   
   if (pp && *pp!=0) {
      while (*pp && p<(gbuffer+_lngbuf+PBR-1)) {
         *p=*pp; p++; pp++;
      }
   } else {
     *p=0; 
     p++; 
   }

   *p='\n'; p++;
   setg(gbuffer + PBR, gbuffer + PBR, p);
   delete[] line;
   
   return *gptr();
}

void wxIostrbuf::writen( long cnt ) {
  
   char *str = (char*)pbase();
   
   for (int i=0; i<cnt; i++) {
      if (_tw) *_tw << *str;
      else cerr << *str;
      str++;
   }
   pbump(-cnt);
}
