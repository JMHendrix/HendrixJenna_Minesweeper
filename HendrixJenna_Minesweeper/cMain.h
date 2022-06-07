#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxButton *button1 = nullptr;
	wxTextCtrl *textCtrl1 = nullptr;
	wxListBox *listBox1 = nullptr;

};

