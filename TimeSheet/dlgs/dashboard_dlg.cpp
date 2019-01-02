#include "dashboard_dlg.h"

DashBoard::DashBoard(wxWindow *pID, string user, string pass)
    : wxFrame(nullptr, ID_DASHBOARD_MAIN, DASHBOARD_DLG_T, wxDefaultPosition,
              wxSize(DASHBOARD_DLG_W, DASHBOARD_DLG_H)) {
    CreateControls();

    c_api = new API_driver();
    c_api->Init(mLogList);
    if (c_api->LoadDB(user, pass) && c_api->DB()->Loaded() == false) {
        wxMessageBox("Wrong Pass or User.\n Exiting . . .", "ERROR");
        c_api->DeInit();
        exit(1);
        return;
    }

    c_api->VerifyDB();
    c_api->DB()->ReCalc();
    SetTodayEntry();

    ShowData();

    GUILogic();
    mTabs = new wxNotebook(mPanel, ID_DASHBOARD_TAB_CONTROL, wxDefaultPosition,
                           wxDefaultSize, wxNB_TOP);
    mTabs->SetPosition(wxPoint(12, 12));
    mTabs->SetSize(wxSize(594 + 75, 575));
    mTimeSheetView =
        new TimeSheetView(mTabs, c_api, mTabs->GetClientSize() - wxSize(8, 29));
    mTabs->AddPage(mTimeSheetView, "TimeSheet View", true);

    SizeControls();
    SetMinSize(GetSize());
    SetMaxSize(GetSize());
    Center();
}

void DashBoard::CreateControls() {
#pragma region Declaration Of Controls
    mPanel = new wxPanel(this, ID_DASHBOARD_PANEL);

    mHours = new wxStaticText(mPanel, wxID_ANY, "");
    mLevel = new wxStaticText(mPanel, wxID_ANY, "");
    mFunnyText = new wxStaticText(mPanel, wxID_ANY, "");

    mSaveBtn = new wxButton(mPanel, ID_DASHBOARD_SAVE_BTN, "Save");

    mLogList = new wxListBox(mPanel, ID_DASHBOARD_LISTBOX);
    mEnterLog = new wxButton(mPanel, ID_DASHBOARD_COMMAND_BTN, ">");
    mCommand = new wxTextCtrl(mPanel, wxID_ANY);

    mProgressText =
        new wxStaticText(mPanel, wxID_ANY, "Progress For Next Level Up:");
    mProgressBar = new wxGauge(mPanel, ID_DASHBOARD_PROGRESS_BAR, 0);

    mTotalDays = new wxStaticText(mPanel, wxID_ANY, "Total Days:");
    mSchoolDays = new wxStaticText(mPanel, wxID_ANY, "SchoolDays:");
    mNonSchoolDays = new wxStaticText(mPanel, wxID_ANY, "Non-School Days:");
    mTotalTime = new wxStaticText(mPanel, wxID_ANY, "Total Time:");
    mTimeNWaisted =
        new wxStaticText(mPanel, wxID_ANY, "Total Time Not Waisted:");
    mTimeWaisted = new wxStaticText(mPanel, wxID_ANY, "Total Time Waisted:");
    mStudiesTime = new wxStaticText(mPanel, wxID_ANY, "Studies Time:");
    mCPTime = new wxStaticText(mPanel, wxID_ANY, "CP Time:");
    mSideProjTime = new wxStaticText(mPanel, wxID_ANY, "Side Proj Time:");
    mGamesTime = new wxStaticText(mPanel, wxID_ANY, "Games Time:");
    mExcerciseTime = new wxStaticText(mPanel, wxID_ANY, "Excercises Time:");

    mTotalDaysVal = new wxTextCtrl(mPanel, wxID_ANY);
    mTotalDaysVal->SetEditable(false);

    mSchoolDaysVal = new wxTextCtrl(mPanel, wxID_ANY);
    mSchoolDaysVal->SetEditable(false);

    mNonSchoolDaysVal = new wxTextCtrl(mPanel, wxID_ANY);
    mNonSchoolDaysVal->SetEditable(false);

    mTotalTimeVal = new wxTextCtrl(mPanel, wxID_ANY);
    mTotalTimeVal->SetEditable(false);

    mTotalTimeNWaistedVal = new wxTextCtrl(mPanel, wxID_ANY);
    mTotalTimeNWaistedVal->SetEditable(false);

    mTotalTimeWaistedVal = new wxTextCtrl(mPanel, wxID_ANY);
    mTotalTimeWaistedVal->SetEditable(false);

    mStudiesTimeVal = new wxTextCtrl(mPanel, wxID_ANY);
    mStudiesTimeVal->SetEditable(false);

    mCPTimeVal = new wxTextCtrl(mPanel, wxID_ANY);
    mCPTimeVal->SetEditable(false);

    mSideProjVal = new wxTextCtrl(mPanel, wxID_ANY);
    mSideProjVal->SetEditable(false);

    mGamesTimeVal = new wxTextCtrl(mPanel, wxID_ANY);
    mGamesTimeVal->SetEditable(false);

    mExcerciseVal = new wxTextCtrl(mPanel, wxID_ANY);
    mExcerciseVal->SetEditable(false);

    mTimerText = new wxStaticText(mPanel, wxID_ANY, "Timer:");
    mTimerVal = new wxTextCtrl(mPanel, wxID_ANY, "--:--:--", wxDefaultPosition,
                               wxDefaultSize, wxTE_CENTRE);
    mTimerVal->SetEditable(false);

    mStartedText = new wxStaticText(mPanel, wxID_ANY, "Started:");
    mStartedVal = new wxTextCtrl(mPanel, wxID_ANY, "--:--:--",
                                 wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
    mStartedVal->SetEditable(false);

    mStartTimer = new wxButton(mPanel, ID_DASHBOARD_START_TIMER, "Start");
    mEnterTime = new wxButton(mPanel, ID_DASHBOARD_ENTER_TIME, "Enter Time");

    mNewDay = new wxButton(mPanel, ID_DASHBOARD_NEW_DAY, "New Day Entry");

    mChoices = new wxComboBox(mPanel, wxID_ANY);
    mChoices->AppendString("Study");
    mChoices->AppendString("CP");
    mChoices->AppendString("Side Proj");
    mChoices->AppendString("Exercise");
    mChoices->AppendString("Games");
    mChoices->SetEditable(false);

    mTimer = new wxTimer(this, ID_DASHBOARD_TIMER);

    mStopTimer = new wxButton(mPanel, ID_DASHBOARD_STOP_TIMER, "Stop");
    mResetTimer = new wxButton(mPanel, ID_DASHBOARD_RESET_TIMER, "Reset");

    wxFont font1;
    font1.SetPointSize(15);
    mLevel->SetFont(font1);

    wxFont font;
    font.Bold();
    font.SetPointSize(24);
    mHours->SetFont(font);

    wxFont font2;
    font2.SetPointSize(8);
    mFunnyText->SetPosition(wxPoint(758, 96));

#pragma endregion
    ShowWithCurrentDay();
}

void DashBoard::SizeControls() {
#pragma region Controls Settings

    mMainSizer = new wxBoxSizer(wxHORIZONTAL);
    mLeftPane = new wxBoxSizer(wxVERTICAL);
    mRightPane = new wxBoxSizer(wxVERTICAL);
    mRightTopPane = new wxBoxSizer(wxVERTICAL);
    mRightBotPane = new wxBoxSizer(wxVERTICAL);

    mLeftPane->Add(mTabs, 0, wxEXPAND | wxLEFT, 5);
    mLeftPane->AddSpacer(4);
    mLeftPane->Add(mProgressText, 0, wxLEFT, 5);
    mLeftPane->AddSpacer(4);
    mLeftPane->Add(mProgressBar, 0, wxEXPAND | wxLEFT, 5);
    mLeftPane->AddSpacer(4);

    mRightTopPane->AddSpacer(25);
    mRightTopPane->Add(mHours, 0, wxCENTER | wxRIGHT | wxLEFT, 125);
    mRightTopPane->AddSpacer(5);
    mRightTopPane->Add(mLevel, 0, wxCENTER | wxRIGHT | wxLEFT, 125);
    mRightTopPane->AddSpacer(25);

#pragma region SummeryFields
    wxBoxSizer *mSummeryFields = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *mSummeryLeftFields = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mSummeryRightFields = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *mTotalDaysFields = new wxBoxSizer(wxHORIZONTAL);
    mTotalDaysFields->Add(mTotalDays, 0, wxCENTER, 0);
    mTotalDaysFields->Add(mTotalDaysVal, 0, wxCENTER, 0);

    wxBoxSizer *mSchoolDaysFields = new wxBoxSizer(wxHORIZONTAL);
    mSchoolDaysFields->Add(mSchoolDays, 0, wxCENTER, 0);
    mSchoolDaysFields->Add(mSchoolDaysVal, 0, wxCENTER, 0);

    wxBoxSizer *mNonSchoolDaysFields = new wxBoxSizer(wxHORIZONTAL);
    mNonSchoolDaysFields->Add(mNonSchoolDays, 0, wxCENTER, 0);
    mNonSchoolDaysFields->Add(mNonSchoolDaysVal, 0, wxCENTER, 0);

    wxBoxSizer *mTotalTimeFields = new wxBoxSizer(wxHORIZONTAL);
    mTotalTimeFields->Add(mTotalTime, 0, wxCENTER, 0);
    mTotalTimeFields->Add(mTotalTimeVal, 0, wxCENTER, 0);

    wxBoxSizer *mTotalTimeNWaistedFields = new wxBoxSizer(wxHORIZONTAL);
    mTotalTimeNWaistedFields->Add(mTimeNWaisted, 0, wxCENTER, 0);
    mTotalTimeNWaistedFields->Add(mTotalTimeNWaistedVal, 0, wxCENTER, 0);

    wxBoxSizer *mTotalTimeWaistedFields = new wxBoxSizer(wxHORIZONTAL);
    mTotalTimeWaistedFields->Add(mTimeWaisted, 0, wxCENTER, 0);
    mTotalTimeWaistedFields->Add(mTotalTimeWaistedVal, 0, wxCENTER, 0);

    mSummeryLeftFields->Add(mTotalDaysFields, 0, wxALIGN_RIGHT, 0);
    mSummeryLeftFields->Add(mSchoolDaysFields, 0, wxALIGN_RIGHT, 0);
    mSummeryLeftFields->Add(mNonSchoolDaysFields, 0, wxALIGN_RIGHT, 0);
    mSummeryLeftFields->Add(mTotalTimeFields, 0, wxALIGN_RIGHT, 0);
    mSummeryLeftFields->Add(mTotalTimeNWaistedFields, 0, wxALIGN_RIGHT, 0);
    mSummeryLeftFields->Add(mTotalTimeWaistedFields, 0, wxALIGN_RIGHT, 0);

    wxBoxSizer *mStudiedTimeFields = new wxBoxSizer(wxHORIZONTAL);
    mStudiedTimeFields->Add(mStudiesTime, 0, wxCENTER, 0);
    mStudiedTimeFields->Add(mStudiesTimeVal, 0, wxCENTER, 0);

    wxBoxSizer *mCPTimeFields = new wxBoxSizer(wxHORIZONTAL);
    mCPTimeFields->Add(mCPTime, 0, wxCENTER, 0);
    mCPTimeFields->Add(mCPTimeVal, 0, wxCENTER, 0);

    wxBoxSizer *mSideProjField = new wxBoxSizer(wxHORIZONTAL);
    mSideProjField->Add(mSideProjTime, 0, wxCENTER, 0);
    mSideProjField->Add(mSideProjVal, 0, wxCENTER, 0);

    wxBoxSizer *mGamesTimeField = new wxBoxSizer(wxHORIZONTAL);
    mGamesTimeField->Add(mGamesTime, 0, wxCENTER, 0);
    mGamesTimeField->Add(mGamesTimeVal, 0, wxCENTER, 0);

    wxBoxSizer *mExcerciseTimeField = new wxBoxSizer(wxHORIZONTAL);
    mExcerciseTimeField->Add(mExcerciseTime, 0, wxCENTER, 0);
    mExcerciseTimeField->Add(mExcerciseVal, 0, wxCENTER, 0);

    mSummeryRightFields->Add(mStudiedTimeFields, 0, wxALIGN_RIGHT, 0);
    mSummeryRightFields->Add(mCPTimeFields, 0, wxALIGN_RIGHT, 0);
    mSummeryRightFields->Add(mSideProjField, 0, wxALIGN_RIGHT, 0);
    mSummeryRightFields->Add(mGamesTimeField, 0, wxALIGN_RIGHT, 0);
    mSummeryRightFields->Add(mExcerciseTimeField, 0, wxALIGN_RIGHT, 0);

    mSummeryFields->Add(mSummeryLeftFields);
    mSummeryFields->AddSpacer(5);
    mSummeryFields->Add(mSummeryRightFields);
    mSummeryFields->AddSpacer(5);
#pragma endregion
#pragma region GeneralControls

    wxBoxSizer *mControls = new wxBoxSizer(wxHORIZONTAL);

    // First col //
    wxBoxSizer *mControlsColOne = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *mStartedFields = new wxBoxSizer(wxHORIZONTAL);
    mStartedFields->Add(mStartedText, 0, wxCENTER, 0);
    mStartedFields->Add(mStartedVal, 0, wxCENTER, 0);

    wxBoxSizer *mTimerFields = new wxBoxSizer(wxHORIZONTAL);
    mTimerFields->Add(mTimerText, 0, wxCENTER, 0);
    mTimerFields->Add(mTimerVal, 0, wxCENTER, 0);

    mControlsColOne->Add(mStartedFields, 0, wxALIGN_RIGHT, 0);
    mControlsColOne->Add(mTimerFields, 0, wxALIGN_RIGHT, 0);
    mControlsColOne->Add(mSaveBtn, 0, wxEXPAND | wxALIGN_RIGHT, 0);
    /////////////

    // Second Col //
    wxBoxSizer *mControlsColTwo = new wxBoxSizer(wxVERTICAL);

    mControlsColTwo->Add(mResetTimer, 0, wxEXPAND, 0);

    wxBoxSizer *mControlsTimerCtrls = new wxBoxSizer(wxHORIZONTAL);

    mControlsTimerCtrls->Add(mStartTimer);
    mControlsTimerCtrls->Add(mStopTimer);

    mControlsColTwo->Add(mControlsTimerCtrls);

    mControlsColTwo->Add(mNewDay, 0, wxEXPAND, 0);

    /////////////

    // Third Col //
    wxBoxSizer *mControlsColThree = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *mControlsEnterTime = new wxBoxSizer(wxVERTICAL);
    mControlsEnterTime->Add(mChoices, 0, wxEXPAND, 0);
    mControlsEnterTime->Add(mEnterTime, 0, wxEXPAND, 0);

    mControlsColThree->Add(mControlsEnterTime, 0, wxEXPAND | wxALIGN_BOTTOM, 0);

    /////////////

    mControls->Add(mControlsColOne, 0, wxEXPAND | wxALIGN_RIGHT, 0);
    mControls->Add(mControlsColTwo, 0, wxEXPAND | wxALIGN_CENTER, 0);
    mControls->Add(mControlsColThree, 0,
                   wxEXPAND | wxALIGN_RIGHT | wxALIGN_BOTTOM, 0);
#pragma endregion
#pragma region ConsoleArea

    wxBoxSizer *mConsoleSizer = new wxBoxSizer(wxVERTICAL);
    mConsoleSizer->Add(mLogList, 0, wxEXPAND, 0);

    wxFlexGridSizer *mEnterText = new wxFlexGridSizer(2, 4, 0);
    mEnterText->AddGrowableCol(0, 4);
    mEnterText->AddGrowableCol(1, 0);

    mEnterText->Add(mCommand, 0, wxEXPAND | wxCENTER, 0);
    mEnterText->Add(mEnterLog);

    mConsoleSizer->Add(mEnterText, 0, wxCENTER | wxEXPAND, 0);
#pragma endregion

    mRightTopPane->Add(mSummeryFields, 0, wxCENTER, 0);
    mRightTopPane->AddSpacer(15);
    mRightTopPane->Add(mControls, 0, wxCENTER, 0);

    mRightBotPane->Add(mConsoleSizer, 0, wxEXPAND | wxCENTER, 0);

    mRightPane->Add(mRightTopPane);
    mRightPane->AddSpacer(10);
    mRightPane->Add(mRightBotPane, 0, wxEXPAND | wxCENTER, 0);

    mMainSizer->Add(mLeftPane);
    mMainSizer->AddSpacer(4);
    mMainSizer->Add(mRightPane);

    mMainSizer->SetSizeHints(this);
    SetSizerAndFit(mMainSizer);

#pragma endregion
    Center();
}

void DashBoard::ShowData() {
    c_api->DB()->ReCalc();
    mHours->SetLabel(
        to_string(c_api->DB()->GetDataBase()->_TotalTimenotWaisted._hr));

    c_api->getRank()->calc();
    mLevel->SetLabel(c_api->getRank()->rank._name);

    mTotalDaysVal->SetValue(to_string(c_api->DB()->GetDataBase()->_TotalDays));
    mSchoolDaysVal->SetValue(
        to_string(c_api->DB()->GetDataBase()->_SchoolDays));
    mNonSchoolDaysVal->SetValue(
        to_string(c_api->DB()->GetDataBase()->_NonSchoolDays));

    auto db = *c_api->DB()->GetDataBase();

    mTotalTimeVal->SetValue(db._TotalTime.get());
    mTotalTimeNWaistedVal->SetValue(db._TotalTimenotWaisted.get());
    mTotalTimeWaistedVal->SetValue(db._TotalTimeWaisted.get());
    mStudiesTimeVal->SetValue(db._StudiedTime.get());
    mCPTimeVal->SetValue(db._CPTime.get());
    mSideProjVal->SetValue(db._SideProjTime.get());
    mGamesTimeVal->SetValue(db._GamesTime.get());
    mExcerciseVal->SetValue(db._ExerciseTime.get());

    mLevel->SetPosition(
        wxPoint((mHours->GetPosition().x + (mHours->GetSize().x) / 2) -
                    (mLevel->GetSize().x / 2),
                mHours->GetPosition().y + mHours->GetSize().y + 4));

    Rank nextRank =
        c_api->getRank()->_ranks[findInVec<Rank>(c_api->getRank()->_ranks,
                                                 c_api->getRank()->rank) +
                                 1];
    int range = nextRank._min - c_api->getRank()->rank._min;
    int finished_range =
        (atoi(mHours->GetLabel()) - c_api->getRank()->rank._min) * 1000;
    range *= 1000;
    mProgressBar->SetRange(range);
    mProgressBar->SetValue(finished_range);

    if (mTimeSheetView != nullptr) mTimeSheetView->ShowData();
}

void DashBoard::OnSaveBtn(wxCommandEvent &event) {
    if (c_api->DB()->Save()) {
        (*c_api->getLogSys()) << "[GUI] Save Succesfully !";
    } else {
        (*c_api->getLogSys()) << "[GUI] Could Save !";
    }
}

void DashBoard::OnEnterCommmand(wxCommandEvent &event) {}

void DashBoard::OnQuit(wxCloseEvent &event) {
    c_api->DeInit();
    exit(0);
}

void DashBoard::OnIDLE(wxIdleEvent &event) { GUILogic(); }

void DashBoard::OnResize(wxSizeEvent &event) { SizeControls(); }

void DashBoard::OnNewDay(wxCommandEvent &event) {
    NewDayDlg *dlg = new NewDayDlg(this, c_api);
    dlg->ShowModal();

    if (dlg->GetReturnCode() == wxID_OK) {
        c_api->DB()->AddEntry(dlg->GetValue());
        c_api->DB()->ReCalc();
        ShowData();
        GUILogic();
        mTodayEntry =
            &(*c_api->DB()
                   ->GetDataBase()
                   ->_entries)[c_api->DB()->GetDataBase()->_entries->size()];
    } else
        return;
}

void DashBoard::OnStartTimer(wxCommandEvent &event) {
    mTimer->Start(1000);
    mTimerStarted = true;
    mTimerVal->SetValue(time.get());

    Time_PAM timerStart;
    auto timerStart_val = wxDateTime::Now();
    timerStart.add(timerStart_val.GetHour(), timerStart_val.GetMinute());

    mStartedVal->SetValue(timerStart.get());
}

void DashBoard::OnStopTimer(wxCommandEvent &event) { mTimer->Stop(); }

void DashBoard::OnResetTimer(wxCommandEvent &event) {
    mTimer->Stop();
    mTimerStarted = false;
    mTimerVal->SetValue("--:--:--");
    time.reset();
    mStartedVal->SetValue("--:--:--");
}

void DashBoard::OnProgressTimer(wxTimerEvent &event) {
    time.addMilliSeconds(event.GetInterval());
    mTimerVal->SetValue(time.get());
}

void DashBoard::OnEndTimer(wxCommandEvent &event) {
    auto choice = mChoices->GetString(mChoices->GetSelection());
    Time time;
    time.set(mTimerVal->GetValue().ToStdString());
    OnResetTimer(event);

    if (choice == "Study") {
        // add time to studies
        mTodayEntry->_StudiedTime = mTodayEntry->_StudiedTime + time;
    } else if (choice == "CP") {
        // add time to cp
        mTodayEntry->_CPTime = mTodayEntry->_CPTime + time;
    } else if (choice == "Side Proj") {
        // add time to side proj
        mTodayEntry->_SideProjTime = mTodayEntry->_SideProjTime + time;
    } else if (choice == "Exercise") {
        // add time to exercise
        mTodayEntry->_ExerciseTime = mTodayEntry->_ExerciseTime + time;
    } else if (choice == "Games") {
        // add time to games
        mTodayEntry->_GamesTime = mTodayEntry->_GamesTime + time;
    }

    mTimer->Stop();
    mTimerStarted = false;
    mChoices->SetValue("");
    mTimerVal->SetValue("--:--:--");
    mStartedVal->SetValue("--:--:--");
    time.reset();
    mTimeSheetView->ShowData();
}

void DashBoard::OnDraw(wxPaintEvent &event) {}

void DashBoard::ShowWithCurrentDay() {
    mNewDay->Enable();
    mTimerText->Disable();
    mTimerVal->Disable();
    mStartedText->Disable();
    mStartedVal->Disable();
    mStartTimer->Disable();
    mStopTimer->Disable();
    mResetTimer->Disable();
    mChoices->Disable();
    mEnterTime->Disable();
}

void DashBoard::ShowWithoutCurrentDay() {
    mNewDay->Disable();
    mTimerText->Enable();
    mTimerVal->Enable();
    mStartedText->Enable();
    mStartedVal->Enable();
    mStartTimer->Enable();
    mStopTimer->Enable();
    mResetTimer->Enable();
    mChoices->Enable();
    mEnterTime->Enable();
}

void DashBoard::GUILogic() {
    if (c_api->DB()->IsEmpty() == true) return;
    auto db = *c_api->DB()->GetDataBase();

    // New Day check
    auto today = wxDateTime::Now();
    Date lastDayInDB = (*db._entries)[db._entries->size() - 1]._date;
    Date today_comp;
    today_comp.set(today.GetDay(), today.GetMonth() + 1, today.GetYear());

    if (lastDayInDB == today_comp)
        // Last created Day was today enable timer controls
        ShowWithoutCurrentDay();
    else
        ShowWithCurrentDay();

    // Enter Time Check
    if (mTimerStarted) {  // prevent disabling choices when stop is entered (for
                          // precision)
        mChoices->Enable();
        if (mChoices->GetString(mChoices->GetSelection()) != "")
            mEnterTime->Enable();
    } else {
        mEnterTime->Disable();
        mChoices->Disable();
    }
    SetTodayEntry();
}

wxBEGIN_EVENT_TABLE(DashBoard, wxFrame)

    EVT_BUTTON(ID_DASHBOARD_SAVE_BTN,
               DashBoard::OnSaveBtn) EVT_BUTTON(ID_DASHBOARD_SAVE_BTN,
                                                DashBoard::OnEnterCommmand)

        EVT_BUTTON(ID_DASHBOARD_START_TIMER, DashBoard::OnStartTimer)
            EVT_BUTTON(ID_DASHBOARD_STOP_TIMER, DashBoard::OnStopTimer)
                EVT_BUTTON(ID_DASHBOARD_RESET_TIMER, DashBoard::OnResetTimer)

                    EVT_BUTTON(ID_DASHBOARD_ENTER_TIME, DashBoard::OnEndTimer)

                        EVT_BUTTON(ID_DASHBOARD_NEW_DAY, DashBoard::OnNewDay)

                            EVT_CLOSE(DashBoard::OnQuit)

                                EVT_TIMER(ID_DASHBOARD_TIMER,
                                          DashBoard::OnProgressTimer)

                                    EVT_IDLE(DashBoard::OnIDLE)

                                        wxEND_EVENT_TABLE()
