#pragma once

#include "../config.h"

#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/wx.h>
#include <thread>
#include "api/driver/API_driver.h"

#include "../panels/timesheet_view.h"
#include "newDay_dlg.h"

class DashBoard : public wxFrame {
   public:
    DashBoard(wxWindow *pID, string user, string pass);
    void CreateControls();
    void SizeControls();
    void ShowData();

   private:
    void OnSaveBtn(wxCommandEvent &event);
    void OnEnterCommmand(wxCommandEvent &event);
    void OnQuit(wxCloseEvent &event);
    void OnIDLE(wxIdleEvent &event);
    void OnResize(wxSizeEvent &event);

    void OnNewDay(wxCommandEvent &event);
    void OnStartTimer(wxCommandEvent &event);
    void OnStopTimer(wxCommandEvent &event);
    void OnResetTimer(wxCommandEvent &event);
    void OnProgressTimer(wxTimerEvent &event);
    void OnEndTimer(wxCommandEvent &event);

    void OnDraw(wxPaintEvent &event);
    wxDECLARE_EVENT_TABLE();

    void ShowWithCurrentDay();
    void ShowWithoutCurrentDay();
    void GUILogic();

    void SetTodayEntry() {
        auto db = c_api->DB()->GetDataBase();
        if (c_api->DB()->IsEmpty() == true)
            mTodayEntry = nullptr;
        else
            mTodayEntry = &(*db->_entries)[db->_entries->size() - 1];
    }

    wxPanel *mPanel = nullptr;

    wxNotebook *mTabs = nullptr;
    TimeSheetView *mTimeSheetView = nullptr;

    wxStaticText *mHours = nullptr;
    wxStaticText *mLevel = nullptr;
    wxStaticText *mFunnyText = nullptr;

    wxStaticText *mTotalDays = nullptr;
    wxStaticText *mSchoolDays = nullptr;
    wxStaticText *mNonSchoolDays = nullptr;
    wxStaticText *mTotalTime = nullptr;
    wxStaticText *mTimeWaisted = nullptr;
    wxStaticText *mTimeNWaisted = nullptr;
    wxStaticText *mTotalTimeWaisted = nullptr;
    wxStaticText *mStudiesTime = nullptr;
    wxStaticText *mCPTime = nullptr;
    wxStaticText *mSideProjTime = nullptr;
    wxStaticText *mGamesTime = nullptr;
    wxStaticText *mExcerciseTime = nullptr;

    wxTextCtrl *mTotalDaysVal = nullptr;
    wxTextCtrl *mSchoolDaysVal = nullptr;
    wxTextCtrl *mNonSchoolDaysVal = nullptr;
    wxTextCtrl *mTotalTimeVal = nullptr;
    wxTextCtrl *mTotalTimeNWaistedVal = nullptr;
    wxTextCtrl *mTotalTimeWaistedVal = nullptr;
    wxTextCtrl *mStudiesTimeVal = nullptr;
    wxTextCtrl *mCPTimeVal = nullptr;
    wxTextCtrl *mSideProjVal = nullptr;
    wxTextCtrl *mGamesTimeVal = nullptr;
    wxTextCtrl *mExcerciseVal = nullptr;

    wxButton *mSaveBtn = nullptr;

    wxListBox *mLogList = nullptr;
    wxButton *mEnterLog = nullptr;
    wxTextCtrl *mCommand = nullptr;

    wxStaticText *mTimerText = nullptr;
    wxTextCtrl *mTimerVal = nullptr;
    wxStaticText *mStartedText = nullptr;
    wxTextCtrl *mStartedVal = nullptr;
    wxComboBox *mChoices = nullptr;
    wxButton *mStartTimer = nullptr;
    wxButton *mStopTimer = nullptr;
    wxButton *mResetTimer = nullptr;
    wxButton *mEnterTime = nullptr;
    wxTimer *mTimer;
    Time time;
    Timer timer;

    wxButton *mNewDay = nullptr;

    bool mTimerStarted = false;

    wxStaticText *mProgressText = nullptr;
    wxGauge *mProgressBar = nullptr;

    API_driver *c_api = nullptr;
    Entry *mTodayEntry = nullptr;

    wxBoxSizer *mMainSizer = nullptr;
    wxBoxSizer *mLeftPane = nullptr;
    wxBoxSizer *mRightPane = nullptr;
    wxBoxSizer *mRightTopPane = nullptr;
    wxBoxSizer *mRightBotPane = nullptr;
};
