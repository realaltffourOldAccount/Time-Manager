#pragma once
#include "../config.h"

#include "api/driver/API_driver.h"

#include <wx/wx.h>
#include <wx/grid.h>
#include <thread>

class TimeSheetView : public wxPanel
{
public:
	TimeSheetView(wxWindow* pID, API_driver *api, wxSize size);
	void CreateControls();

	void ShowData();

private:
	API_driver *c_api = nullptr;

	wxGrid *mGrid = nullptr;
private:
	enum {
		ID_PANEL,
		ID_GRID
	};
};
