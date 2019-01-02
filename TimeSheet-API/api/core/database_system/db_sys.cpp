#include "db_sys.h"

void DB_sys::Init(Log* _log) {
    _db = new DataBase();
    _db->_entries = new vector<Entry>();
    _login = new LoginSys();
    _Log = _log;
}

void DB_sys::DeInit() {
    delete _db;
    delete _login;
}

bool DB_sys::Load(std::string oldUser, std::string oldPass) {
    //////// CHECK IF THERE
    if (!IsThere()) return false;

    //////// AUTHENTICATION
    _login->Init(_Log, oldUser, oldPass);

    if (_login->IsLogged() != true) {
        _isLoaded = false;
        return false;
    }

    //////// SETTINGS LOAD
    vector<string> raw_settings;
    file.Read(DATA_SETTINGS_PATH, &raw_settings);

    if (!raw_settings.empty()) {  // if not new
        _db->_TotalDays = atoi(raw_settings[0].c_str());
        _db->_SchoolDays = atoi(raw_settings[1].c_str());
        _db->_NonSchoolDays = atoi(raw_settings[2].c_str());
        _db->_TotalTime.set(raw_settings[3]);
        _db->_TotalTimeWaisted.set(raw_settings[4]);
        _db->_TotalTimenotWaisted.set(raw_settings[5]);
        _db->_StudiedTime.set(raw_settings[6]);
        _db->_CPTime.set(raw_settings[7]);
        _db->_SideProjTime.set(raw_settings[8]);
        _db->_GamesTime.set(raw_settings[9]);
        _db->_ExerciseTime.set(raw_settings[10]);
    }

    ////// ENTRIES LOAD
    csv_loaders csv;
    auto raw_entries = csv.Load(DATA_ENTRIES_PATH);

    if (!raw_entries.empty()) {  // if not new
        _db->_entries = new vector<Entry>();

        for (int i = 0; i < raw_entries.size(); i++) {
            auto entry_data = raw_entries[i];
            Entry entry;

            entry._ID = atoi(entry_data[0].c_str());
            entry._date.set(entry_data[1]);
            entry._EnterTime.set(entry_data[2]);
            entry._StudiedTime.set(entry_data[3]);
            entry._CPTime.set(entry_data[4]);
            entry._SideProjTime.set(entry_data[5]);
            entry._ExerciseTime.set(entry_data[6]);
            entry._GamesTime.set(entry_data[7]);
            entry._isSchool = (entry_data[8] == "1") ? true : false;
            entry._ExitTime.set(entry_data[9]);
            entry._AvlbleTime.set(entry_data[10]);
            entry._WaistedTime.set(entry_data[11]);
            entry._NWaistedTime.set(entry_data[12]);

            _db->_entries->push_back(entry);
        }
        (*_Log) << "[DB_SYS] Loaded " + to_string(_db->_entries->size()) +
                       " Entries successfully!";
    }

    _isLoaded = true;
    return true;
}
bool DB_sys::CreateEmpty(std::string newUser, std::string newPass) {
    createDir(DATA_PATH);
    createFile(DATA_CRED_PATH);
    createFile(DATA_SETTINGS_PATH);
    createFile(DATA_ENTRIES_PATH);

    _login->Init(_Log, newUser, newPass);

    vector<string> _settings_data;

    for (int i = 0; i < 11; i++) _settings_data.push_back("NULL");

    file.Write(DATA_SETTINGS_PATH, _settings_data);

    vector<string> _entries_data;
    _entries_data.push_back("NULL");

    file.Write(DATA_ENTRIES_PATH, _entries_data);

    if (!IsThere()) {
        (*_Log) << "[DB_SYS] Could Not Create Database!";
        return false;
    } else {
        (*_Log) << "[DB_SYS] Created Database!";
        return true;
    }
}

void DB_sys::AddEntry(Entry entry) {
    _db->_entries->push_back(entry);
    ReCalc();
}

void DB_sys::ReCalc() {
    if (IsEmpty() == true && IsDataEmpty() == true)
        return;  // db empty nothing to calc

    //_db = new DataBase;
    _db->_TotalDays = _db->_entries->size();

    _db->_SchoolDays = 0;
    _db->_NonSchoolDays = 0;
    for (int i = 0; i < _db->_TotalDays; i++) {
        if ((*_db->_entries)[i]._isSchool)
            _db->_SchoolDays++;
        else
            _db->_NonSchoolDays++;
    }

    _db->_TotalTime.reset();
    _db->_TotalTimeWaisted.reset();
    _db->_TotalTimenotWaisted.reset();
    for (int i = 0; i < _db->_TotalDays; i++) {
        _db->_TotalTime.add((*_db->_entries)[i]._AvlbleTime._hr,
                            (*_db->_entries)[i]._AvlbleTime._min,
                            (*_db->_entries)[i]._AvlbleTime._sec, 0);
        _db->_TotalTimeWaisted.add((*_db->_entries)[i]._WaistedTime._hr,
                                   (*_db->_entries)[i]._WaistedTime._min,
                                   (*_db->_entries)[i]._WaistedTime._sec, 0);
        _db->_TotalTimenotWaisted.add((*_db->_entries)[i]._NWaistedTime._hr,
                                      (*_db->_entries)[i]._NWaistedTime._min,
                                      (*_db->_entries)[i]._NWaistedTime._sec,
                                      0);
    }

    _db->_StudiedTime.reset();
    _db->_CPTime.reset();
    _db->_SideProjTime.reset();
    _db->_GamesTime.reset();
    _db->_ExerciseTime.reset();
    for (int i = 0; i < _db->_TotalDays; i++) {
        _db->_StudiedTime =
            _db->_StudiedTime + (*_db->_entries)[i]._StudiedTime;
        _db->_CPTime = _db->_CPTime + (*_db->_entries)[i]._CPTime;
        _db->_SideProjTime =
            _db->_SideProjTime + (*_db->_entries)[i]._SideProjTime;
        _db->_GamesTime = _db->_GamesTime + (*_db->_entries)[i]._GamesTime;
        _db->_ExerciseTime =
            _db->_ExerciseTime + (*_db->_entries)[i]._ExerciseTime;
    }

    if (IsDataEmpty() == false) {
        _db->_AvgWaistTime = _db->_TotalTimeWaisted / _db->_TotalDays;
        _db->_AvgStudiedTime = _db->_StudiedTime / _db->_TotalDays;
        _db->_AvgCPTime = _db->_CPTime / _db->_TotalDays;
        _db->_AvgSideProjTime = _db->_SideProjTime / _db->_TotalDays;
        _db->_AvgGamesTime = _db->_GamesTime / _db->_TotalDays;
        _db->_AvgExerciseTime = _db->_ExerciseTime / _db->_TotalDays;
    }
}

bool DB_sys::Save() {
    /////// SETTINGS FILE
    vector<string> _settings_data;

    _settings_data.push_back(to_string(_db->_TotalDays));
    _settings_data.push_back(to_string(_db->_SchoolDays));
    _settings_data.push_back(to_string(_db->_NonSchoolDays));
    _settings_data.push_back(_db->_TotalTime.get());
    _settings_data.push_back(_db->_TotalTimeWaisted.get());
    _settings_data.push_back(_db->_TotalTimenotWaisted.get());
    _settings_data.push_back(_db->_StudiedTime.get());
    _settings_data.push_back(_db->_CPTime.get());
    _settings_data.push_back(_db->_SideProjTime.get());
    _settings_data.push_back(_db->_GamesTime.get());
    _settings_data.push_back(_db->_ExerciseTime.get());

    file.Write(DATA_SETTINGS_PATH, _settings_data);

    /////// ENTRIES FILE
    vector<string> _entries_data;

    auto entries = *_db->_entries;

    for (int i = 0; i < _db->_entries->size(); i++) {
        string entry_data = "";

        entry_data.append(to_string(entries[i]._ID));
        entry_data.append(",");
        entry_data.append(entries[i]._date.get());
        entry_data.append(",");
        entry_data.append(entries[i]._EnterTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._StudiedTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._CPTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._SideProjTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._ExerciseTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._GamesTime.get());
        entry_data.append(",");
        entry_data.append((entries[i]._isSchool) ? "1" : "0");
        entry_data.append(",");
        entry_data.append(entries[i]._ExitTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._AvlbleTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._WaistedTime.get());
        entry_data.append(",");
        entry_data.append(entries[i]._NWaistedTime.get());

        _entries_data.push_back(entry_data);
    }

    file.Write(DATA_ENTRIES_PATH, _entries_data);

    return IsThere();
}

bool DB_sys::IsThere() {
    if (!dirExists(DATA_PATH)) {
        (*_Log) << "[DB_SYS] Could not find Database!";
        return false;
    }
    if (!fileExists(DATA_CRED_PATH)) {
        (*_Log) << "[DB_SYS] Could not find Database!";
        return false;
    }
    if (!fileExists(DATA_SETTINGS_PATH)) {
        (*_Log) << "[DB_SYS] Could not find Database!";
        return false;
    }
    if (!fileExists(DATA_ENTRIES_PATH)) {
        (*_Log) << "[DB_SYS] Could not find Database!";
        return false;
    }

    (*_Log) << "[DB_SYS] Found Database!";
    return true;
}

bool DB_sys::IsEmpty() {
    File_Manager file;
    vector<string> entries_data;
    file.Read(DATA_ENTRIES_PATH, &entries_data);
    if (entries_data[0] == "NULL")
        return true;
    else
        return false;
}

bool DB_sys::IsDataEmpty() {
    if (_db->_entries->size() == 0) return true;
    return false;
}