#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	//array of button ptrs
	wxButton **btn;
	int* mineField = nullptr; 
	bool bFirstClick = true;  //if true, populate the mine field

	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

