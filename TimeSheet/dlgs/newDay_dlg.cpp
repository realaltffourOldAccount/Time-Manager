#include "newDay_dlg.h"

NewDayDlg::NewDayDlg(wxWindow *pID, API_driver *api)
    : wxDialog(pID, ID_NEW_DAY_DLG_MAIN, NEW_DAY_DLG_T, wxDefaultPosition,
               wxSize(NEW_DAY_DLG_W, NEW_DAY_DLG_H)) {
    c_api = api;

    CreateControls();
    ShowData();

    SetMinSize(GetSize());
    SetMaxSize(GetSize());
    Center();
}

void NewDayDlg::CreateControls() {
#pragma region Creation of Controls
    mPanel = new wxPanel(this, ID_NEW_DAY_DLG_PANEL);

    mIDText = new wxStaticText(mPanel, wxID_ANY, "ID:");
    mDateText = new wxStaticText(mPanel, wxID_ANY, "Date:");
    mStartTimeText = new wxStaticText(mPanel, wxID_ANY, "Start Time:");
    mExitTimeText = new wxStaticText(mPanel, wxID_ANY, "Expected Exit Time:");

    mIDVal = new wxTextCtrl(mPanel, ID_NEW_DAY_DLG_ID);
    mIDVal->SetEditable(false);
    mDateVal = new wxTextCtrl(mPanel, ID_NEW_DAY_DLG_DATE);
    mDateVal->SetEditable(false);
    mStartTimeVal = new wxTextCtrl(mPanel, ID_NEW_DAY_DLG_START_TIME);
    mStartTimeVal->SetEditable(false);
    mExitTimeVal = new wxTextCtrl(mPanel, ID_NEW_DAY_DLG_EXIT_TIME);
    mIsSchoolDay =
        new wxCheckBox(mPanel, ID_NEW_DAY_DLG_SCHOOL_DAY, "Is School Day");

    mCancel = new wxButton(mPanel, ID_NEW_DAY_DLG_CANCEL_BTN, "Cancel");
    mCreate = new wxButton(mPanel, ID_NEW_DAY_DLG_CREATE_BTN, "Create");

#pragma endregion

#pragma region Size of Controls

    mIDText->SetPosition(wxPoint(105, 9));
    mDateText->SetPosition(wxPoint(93, 35));
    mStartTimeText->SetPosition(wxPoint(71, 61));
    mExitTimeText->SetPosition(wxPoint(25, 87));

    mIDVal->SetSize(wxSize(199, 20));
    mIDVal->SetPosition(wxPoint(132, 6));

    mDateVal->SetSize(wxSize(199, 20));
    mDateVal->SetPosition(wxPoint(132, 32));

    mStartTimeVal->SetSize(wxSize(199, 20));
    mStartTimeVal->SetPosition(wxPoint(132, 58));

    mExitTimeVal->SetSize(wxSize(199, 20));
    mExitTimeVal->SetPosition(wxPoint(132, 84));

    mIsSchoolDay->SetPosition(wxPoint(132, 106));

    mCancel->SetSize(wxSize(75, 23));
    mCancel->SetPosition(wxPoint(256, 129));

    mCreate->SetSize(wxSize(118, 23));
    mCreate->SetPosition(wxPoint(132, 129));

#pragma endregion
}

void NewDayDlg::ShowData() {
    auto db = *c_api->DB()->GetDataBase();
    if (db._TotalDays >= 0)
        mIDVal->SetValue(to_string(db._TotalDays + 1));
    else
        mIDVal->SetValue(to_string(1));  // always show negative as 1

    Date today_comp;
    auto today = wxDateTime::Now();
    today_comp.set(today.GetDay(), today.GetMonth() + 1, today.GetYear());

    mDateVal->SetValue(today_comp.get());

    Time_PAM timerStart;
    auto timerStart_val = wxDateTime::Now();
    timerStart.add(timerStart_val.GetHour(), timerStart_val.GetMinute());

    mStartTimeVal->SetValue(timerStart.get());
}

void NewDayDlg::OnCancel(wxCommandEvent &event) {
    this->Close();
    this->SetReturnCode(wxID_CANCEL);
}

void NewDayDlg::OnCreate(wxCommandEvent &event) {
    entry = new Entry;
    entry->_ID = atoi(mIDVal->GetValue());
    entry->_date.set(mDateVal->GetValue().ToStdString());
    entry->_EnterTime.set(mStartTimeVal->GetValue().ToStdString());
    entry->_ExitTime.set(mExitTimeVal->GetValue().ToStdString());
    entry->_isSchool = mIsSchoolDay->GetValue();

    *entry = CalcEntry(*entry);

    this->Close();
    this->SetReturnCode(wxID_OK);
}

wxBEGIN_EVENT_TABLE(NewDayDlg, wxDialog)

    EVT_BUTTON(ID_NEW_DAY_DLG_CREATE_BTN, NewDayDlg::OnCreate)
        EVT_BUTTON(ID_NEW_DAY_DLG_CANCEL_BTN, NewDayDlg::OnCancel)

            wxEND_EVENT_TABLE()
