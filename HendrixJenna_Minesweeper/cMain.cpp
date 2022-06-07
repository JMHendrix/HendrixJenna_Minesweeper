#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper - Jenna", wxPoint(30,30), wxSize(800,600))
{

	btn = new wxButton*[nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	mineField = new int[nFieldWidth * nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);


	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++) {
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			mineField[y*nFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}



cMain::~cMain() {
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt) {
	//get coordinate of button in array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int numMines = 30;
		while (numMines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (mineField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				mineField[ry * nFieldWidth + rx] = -1;
				numMines--;
			}
		}
		bFirstClick = false;

	}

	//disable button, no need to press again
	btn[y * nFieldWidth + x]->Enable(false);

	//check if player hit mine
	if (mineField[y*nFieldWidth + x] == -1) {
		wxMessageBox("BOOOOM!! - Game Over :(");

		//reset game
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++) {
			for (int y = 0; y < nFieldHeight; y++) {
				mineField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else {
		//count neighbor mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight) {
					if (mineField[(y + j) * nFieldWidth + (x + i)] == -1) {
						mine_count++;

					}
				}
			}

			//update buttons label to show mine count if mine_count > 0;
			if (mine_count > 0) {
				btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));

			}
		}
	}
	evt.Skip();
}
