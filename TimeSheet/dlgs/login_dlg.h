#pragma once
#include "../config.h"

#include <wx/wx.h>

class LoginDlg : public wxFrame {
   public:
    LoginDlg(wxWindow* pID);

    void CreateControls();

    string GetPass();
    string GetUser();

   private:
    void OnLoginBtn(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();

    wxPanel* mPanel = nullptr;
    wxStaticText* mUserText = nullptr;
    wxStaticText* mPassText = nullptr;
    wxTextCtrl* mUserBox = nullptr;
    wxTextCtrl* mPassBox = nullptr;
    wxButton* mLoginBtn = nullptr;
};
