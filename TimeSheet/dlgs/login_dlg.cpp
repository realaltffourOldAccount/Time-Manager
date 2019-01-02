#include "login_dlg.h"

#include "dashboard_dlg.h"

LoginDlg::LoginDlg(wxWindow *pID)
    : wxFrame(pID, ID_LOGIN_DLG_MAIN, LOGIN_DLG_T, wxDefaultPosition,
              wxSize(LOGIN_DLG_W, LOGIN_DLG_H),
              wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX) {
    CreateControls();

    SetMinSize(GetSize());
    SetMaxSize(GetSize());
    Center();
}

void LoginDlg::CreateControls() {
    mPanel = new wxPanel(this, ID_LOGIN_DLG_PANEL);
    mUserText = new wxStaticText(mPanel, wxID_ANY, "User: ");
    mPassText = new wxStaticText(mPanel, wxID_ANY, "Pass: ");

    mUserBox = new wxTextCtrl(mPanel, ID_LOGIN_DLG_USER_BOX);
    mPassBox = new wxTextCtrl(mPanel, ID_LOGIN_DLG_PASS_BOX, "",
                              wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    mLoginBtn = new wxButton(mPanel, ID_LOGIN_DLG_LOGIN_BTN, "Login");
    mLoginBtn->SetDefault();

    wxBoxSizer *mSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mUserField = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *mPassField = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags;
    flags.Center();

    mUserField->Add(mUserText, 0, wxALIGN_CENTER);
    mUserField->AddSpacer(4);
    mUserField->Add(mUserBox, 0, wxALIGN_CENTER);

    mPassField->Add(mPassText, 0, wxALIGN_CENTER);
    mPassField->AddSpacer(4);
    mPassField->Add(mPassBox, 0, wxALIGN_CENTER);

    mSizer->Add(mUserField, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 50);
    mSizer->Add(mPassField, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 50);
    mSizer->Add(mLoginBtn, 0, wxALIGN_CENTER, 25);

    mSizer->SetSizeHints(this);
    this->SetSizer(mSizer);
}

string LoginDlg::GetPass() { return mPassBox->GetValue().ToStdString(); }

string LoginDlg::GetUser() { return mUserBox->GetValue().ToStdString(); }

void LoginDlg::OnLoginBtn(wxCommandEvent &event) {
    if (GetPass() == "" || GetUser() == "") return;

    this->Show(false);
    DashBoard *dsh = new DashBoard(nullptr, GetUser(), GetPass());
    dsh->Show();

    this->Close(true);
}

wxBEGIN_EVENT_TABLE(LoginDlg, wxFrame)

    EVT_BUTTON(ID_LOGIN_DLG_LOGIN_BTN, LoginDlg::OnLoginBtn)

        wxEND_EVENT_TABLE()
