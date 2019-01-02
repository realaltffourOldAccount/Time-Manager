#pragma once
#include "../config.h"

#include "api/driver/API_driver.h"

#include <wx/wx.h>
#include <thread>

class NewDayDlg : public wxDialog {
   public:
    NewDayDlg(wxWindow *pID, API_driver *c_api);
    void CreateControls();

    void ShowData();

    Entry GetValue() { return *entry; }

   private:
    void OnCancel(wxCommandEvent &event);
    void OnCreate(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();

    wxPanel *mPanel = nullptr;
    wxStaticText *mIDText = nullptr;
    wxStaticText *mDateText = nullptr;
    wxStaticText *mStartTimeText = nullptr;
    wxStaticText *mExitTimeText = nullptr;

    wxTextCtrl *mIDVal = nullptr;
    wxTextCtrl *mDateVal = nullptr;
    wxTextCtrl *mStartTimeVal = nullptr;
    wxTextCtrl *mExitTimeVal = nullptr;
    wxCheckBox *mIsSchoolDay = nullptr;

    wxButton *mCancel = nullptr;
    wxButton *mCreate = nullptr;

    Entry *entry = nullptr;
    API_driver *c_api = nullptr;
    ;
};