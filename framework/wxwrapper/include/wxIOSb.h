#ifndef __WX_IOSB_H__
#define __WX_IOSB_H__

#include <iostream.h>
#include <wx.h>

////////////////////////////////////////////////////////
//
//  

class wxIostrbuf: public streambuf {

  public:
    wxIostrbuf(const int lngbuf = 1024, wxTextWindow *tw=0);
    ~wxIostrbuf();

  private:
    char         *pbuffer,*gbuffer;
    wxTextWindow *_tw;
    int          _lngbuf;
    
    int          overflow(int c),
                 underflow(),
                 sync();
    void         writen( long n );
};

#endif
