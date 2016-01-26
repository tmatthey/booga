/*
 * File:    wx_ioterm.cc
 * Author:  Torsten Vogt, Mitarbeiter PI1 <vogt@pi2sun1>
 */

#include <wx.h>
#include "booga/wxwrapper/wxIOCon.h"
#include "booga/wxwrapper/wxIOSb.h"

static wxIostrbuf *iobuf = NULL;

wxIoConsole::wxIoConsole(wxFrame *parent, char *title, int x, int y, int width, int height, long style, char *name, int menu):
  wxFrame(parent, title, x, y, width, height, style, name)
{
  // Initialize child subwindow members.
  _tw   = NULL;
  _menu = menu;

  // Create a menu bar for the frame
  if (_menu) {
     wxMenuBar *menuBar3 = new wxMenuBar;
     wxMenu *menu1 = new wxMenu;
     menu1->Append(5, "Clear");
     menu1->Append(FRAMECLASS2_QUIT, "Close");
     menuBar3->Append(menu1, "File");
     wxMenu *menu2 = new wxMenu;
     menu2->Append(FRAMECLASS2_ABOUT, "About");
     menuBar3->Append(menu2, "Help");
     SetMenuBar(menuBar3);
  }

  // Create child subwindows.
  _tw = new wxTextWindow(this, 0, 0, 300, 300, 0, "_tw");
  _tw->SetEditable(FALSE);
  iobuf= new wxIostrbuf(1024,_tw);
  cout = iobuf;
  cerr = iobuf;
  cin  = iobuf;

  // Ensure the subwindows get resized o.k.
  OnSize(width, height);

  // Show the frame.
  Show(TRUE);
}

wxIoConsole::~wxIoConsole(void)
{
   if (iobuf) delete iobuf;
}

Bool wxIoConsole::OnClose(void)
{
  // Clean up any associated data here.
  return FALSE;
}

void wxIoConsole::OnSize(int w, int h)
{
  // Let default member handle sizing for only one subwindow.
  wxFrame::OnSize(w, h);
}

void FCAboutProc(wxFrame *fr) {
   wxMessageBox("\nI/O console (c) 1996 by Torsten Vogt\n\n"
		"wxWindows by Julian Smart\n\n"
		"Universitaet Mannheim\n"
		"Lehrstuhl Praktische Informatik I\n"
		"Seminargebaeude A5\n"
		"68131 Mannheim",
		"",wxOK,fr);
}

void wxIoConsole::Clear()
{
  _tw->Clear();
}

Bool wxIoConsole::isEmpty()
{
  return  (_tw->GetNumberOfLines());
}

void wxIoConsole::OnMenuCommand(int commandId)
{
  switch (commandId)
  {
    // Quit
    case FRAMECLASS2_QUIT:
    {
      // Close a window.    
      Show(FALSE);
//      delete this;
      break;
    }
    // About
    case 5:
      _tw->Clear();
	  break;

    case FRAMECLASS2_ABOUT:
    {
      FCAboutProc(this);
      break;
    }
  default:
    break;
  }
}


