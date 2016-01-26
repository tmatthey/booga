/*
 * File:    wx_ioterm.h
 * Author:  Torsten Vogt, Mitarbeiter PI1 <vogt@pi2sun1>
 */

#ifndef _INC_WX_IOTERM_H
#define _INC_WX_IOTERM_H

/*
 * Forward declarations of all top-level window classes.
 */

class wxIoConsole;
class wxFrame;
class wxIoConsole: public wxFrame
{
 private:
 protected:
 public:
  // Subwindows for reference within the program.
  wxTextWindow *_tw;
  int          _menu;

  // Constructor and destructor
  wxIoConsole(wxFrame *parent, char *title, int x, int y, int width, int height, long style=wxSDI|wxDEFAULT_FRAME, char *name="", int menu=TRUE);
  ~wxIoConsole(void);

 Bool OnClose(void);
 void OnSize(int w, int h);
 void OnMenuCommand(int commandId);
 void Clear();
 Bool isEmpty(); 
};

/* Menu identifiers
 */

#define FRAMECLASS2_FILE  1
#define FRAMECLASS2_QUIT  2
#define FRAMECLASS2_HELP  3
#define FRAMECLASS2_ABOUT 4

#endif /* mutual exclusion */
