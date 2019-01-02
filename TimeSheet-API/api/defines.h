#pragma once
#include <map>
#include <string>
#include <vector>

#include "utils/files/File_Manager.h"
#include "utils/files/csv/csv_loaders.h"
#include "utils/files/csv/csv_saver.h"

#include "utils/log/Log.h"
#include "utils/misc/basic_str_parser.h"
#include "utils/misc/finder.h"
#include "utils/misc/random_rework.h"
#include "utils/misc/string_conv.h"
#include "utils/time/Date.h"
#include "utils/time/Time.h"
#include "utils/time/Timer.h"

#define DATA_CRED_NAME std::string("cred.info")
#define DATA_SETTINGS_NAME std::string("settings.conf")
#define DATA_ENTRIES_NAME std::string("entries.dat")

#define DATA_PATH std::string("data/")
#define DATA_CRED_PATH (DATA_PATH + DATA_CRED_NAME)
#define DATA_SETTINGS_PATH (DATA_PATH + DATA_SETTINGS_NAME)
#define DATA_ENTRIES_PATH (DATA_PATH + DATA_ENTRIES_NAME)

using namespace std;

struct Entry {
    int _ID = -1;  // invalid default
    Date _date;
    Time_PAM _EnterTime;
    Time _StudiedTime;
    Time _CPTime;
    Time _SideProjTime;
    Time _ExerciseTime;
    Time _GamesTime;
    Time_PAM _ExitTime;

    bool _isSchool = false;

    Time _AvlbleTime;
    Time _WaistedTime;
    Time _NWaistedTime;
};

struct DataBase {
    vector<Entry> *_entries = nullptr;

    int _TotalDays = -1;
    int _SchoolDays = -1;
    int _NonSchoolDays = -1;

    Time _TotalTime;
    Time _TotalTimeWaisted;
    Time _TotalTimenotWaisted;

    Time _StudiedTime;
    Time _CPTime;
    Time _SideProjTime;
    Time _GamesTime;
    Time _ExerciseTime;

    Time _AvgStudiedTime;
    Time _AvgCPTime;
    Time _AvgSideProjTime;
    Time _AvgGamesTime;
    Time _AvgExerciseTime;
    Time _AvgWaistTime;
};

static Entry CalcEntry(const Entry &entry) {
    Entry _entry = entry;
    _entry._AvlbleTime =
        Time_PAM(_entry._ExitTime - _entry._EnterTime).convertTo24HrFormat();
    _entry._WaistedTime =
        _entry._AvlbleTime -
        (_entry._StudiedTime + _entry._CPTime + _entry._SideProjTime +
         _entry._GamesTime + _entry._ExerciseTime);
    _entry._NWaistedTime = _entry._AvlbleTime - _entry._WaistedTime;
    return _entry;
}