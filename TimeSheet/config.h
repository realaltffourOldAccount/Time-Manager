#ifndef _H_CONFIG_H_
#define _H_CONFIG_H_

#pragma once

#include <wx/aui/aui.h>
#include <wx/wx.h>

#include "api/defines.h"

#define LOGIN_DLG_W 300
#define LOGIN_DLG_H 134
#define LOGIN_DLG_T "Login"

// 978, 573
#define DASHBOARD_DLG_W 978
#define DASHBOARD_DLG_H 573
#define DASHBOARD_DLG_T std::string("DashBoard | TimeSheet")

// 359, 203
#define NEW_DAY_DLG_W 359
#define NEW_DAY_DLG_H 203
#define NEW_DAY_DLG_T std::string("New Day | TimeSheet")

enum {  // IDS
        /////////////////////////////
        //
        //	Login IDs
        //
        /////////////////////////////

    ID_LOGIN_DLG_MAIN,
    ID_LOGIN_DLG_PANEL,
    ID_LOGIN_DLG_USER_BOX,
    ID_LOGIN_DLG_PASS_BOX,
    ID_LOGIN_DLG_LOGIN_BTN,

    /////////////////////////////
    //
    //	DashBoard IDs
    //
    /////////////////////////////

    ID_DASHBOARD_MAIN,
    ID_DASHBOARD_PANEL,
    ID_DASHBOARD_TAB_CONTROL,
    ID_DASHBOARD_LISTBOX,
    ID_DASHBOARD_PROGRESS_BAR,
    ID_DASHBOARD_SAVE_BTN,
    ID_DASHBOARD_COMMAND_BTN,
    ID_DASHBOARD_START_TIMER,
    ID_DASHBOARD_STOP_TIMER,
    ID_DASHBOARD_RESET_TIMER,
    ID_DASHBOARD_ENTER_TIME,
    ID_DASHBOARD_NEW_DAY,
    ID_DASHBOARD_TIMER,

    /////////////////////////////
    //
    //	NewDay IDs
    //
    /////////////////////////////

    ID_NEW_DAY_DLG_MAIN,
    ID_NEW_DAY_DLG_PANEL,
    ID_NEW_DAY_DLG_ID,
    ID_NEW_DAY_DLG_DATE,
    ID_NEW_DAY_DLG_START_TIME,
    ID_NEW_DAY_DLG_EXIT_TIME,
    ID_NEW_DAY_DLG_SCHOOL_DAY,
    ID_NEW_DAY_DLG_CANCEL_BTN,
    ID_NEW_DAY_DLG_CREATE_BTN,

};
#endif  // !_H_CONFIG_H_
