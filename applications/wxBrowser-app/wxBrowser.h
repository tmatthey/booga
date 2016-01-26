/*
 * wxBrowser.h
 *
 * Copyright (C) 1995, Pascal Habegger <habegger@iam.unibe.ch>
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
 *  $Id: wxBrowser.h,v 1.7 1997/04/08 11:05:46 habegger Exp $
 * -----------------------------------------------------------------------------
 */
 
#ifndef _wxBrowser_H
#define _wxBrowser_H

#include "wx.h"


//_____________________________________________________________________  myApp


class GSBApp : public wxApp {
public:
  wxFrame *OnInit();
};


class GSBwxPanel;
class GSBwxListBox;


class GSBwxAppFrame : public wxFrame {
public:
  GSBwxPanel* panel;
  wxListBox* listbox;
  GSBwxAppFrame(wxFrame *frame, char *title, int x, int y, int w, int h);
  void OnMenuCommand(int id);
  void OnSize(int, int);
  Bool OnClose();
};


class GSBwxListBox : public wxListBox {
public:
  GSBwxListBox(wxPanel* parent, wxFunction func, char* label, Bool multiple_selection, 
  int x, int y, int width, int height, int n, char* choices[], long style, char* name) :
    wxListBox(parent, func, label, multiple_selection, x, y, width, height, n, choices, style, name) {};
  GSBwxListBox(wxPanel* parent)
    : wxListBox(parent, (wxFunction) 0, "", wxSINGLE, -1, -1, -1, -1) {};
  void OnEvent(wxMouseEvent&);
};


class GSBwxPanel : public wxPanel {
public :
  GSBwxPanel(wxWindow* parent, int x = -1, int y = -1, int width = -1, int height = -1, long style = 0,
  char* name = "panel")
    : wxPanel(parent, x, y, width, height, style, name) {};
  void OnSize(int, int);
  void OnEvent(wxMouseEvent& event);
  void OnDefaultAction(wxItem* item);
};


//______________________________________________________________________ INLINES

extern GSBwxAppFrame* GSBMainframe;

#endif // _wxBrowser_H
