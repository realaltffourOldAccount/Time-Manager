#pragma once
#include "../../defines.h"
#include "../login_system/login_sys.h"

class DB_sys {
   public:
    void Init(Log *_log);
    void DeInit();

    bool Load(std::string oldUser, std::string oldPass);
    bool CreateEmpty(std::string newUser,
                     std::string newPass);  // deletes if already exists

    void AddEntry(Entry entry);
    void ReCalc();

    bool Save();

    DataBase *GetDataBase() { return _db; }
    bool Loaded() { return _isLoaded; }

    bool IsThere();
    bool IsEmpty();      // checks file
    bool IsDataEmpty();  // checks loaded data
   private:
    DataBase *_db = nullptr;
    Log *_Log = nullptr;
    LoginSys *_login = nullptr;

    File_Manager file;

    bool _isLoaded = false;
};

/*
        Database Structure

        -data/
                -cred.info
                -settings.conf
                -entries.dat

        -cred.info
                [USER]
                [PASS]
                [KEY]

        -settings.conf					DEFAULTS:
                -[TOTAL_DAYS]				NULL
                -[SCHOOL_DAYS]				NULL
                -[NONSCHOOL_DAYS]			NULL
                -[TOTAL_TIME]				NULL
                -[TOTAL_TIME_WAISTED]		NULL
                -[TOTAL_TIME_NOT_WAISTED]	NULL
                -[STUDIED_TIME]				NULL
                -[CP_TIME]					NULL
                -[SIDE_PROJ_TIME]			NULL
                -[GAMES_TIME]				NULL
                -[EXERCISE_TIME]			NULL

        -entries.dat					Default: empty file
                -[ID],[DATE],[ENTER_TIME],[STUDIED_TIME],[CP_TIME],[SIDE_PROJ_TIME],[EXERCISE_TIME],[GAMES_TIME],[IS_SCHOOL_DAY],[EXIT_TIME],[AVLBLE_TIME],[WAISTED_TIME],[NOT_WAISTED_TIME]
                -[ID],[DATE],[ENTER_TIME],[STUDIED_TIME],[CP_TIME],[SIDE_PROJ_TIME],[EXERCISE_TIME],[GAMES_TIME],[IS_SCHOOL_DAY],[EXIT_TIME],[AVLBLE_TIME],[WAISTED_TIME],[NOT_WAISTED_TIME]
                -[ID],[DATE],[ENTER_TIME],[STUDIED_TIME],[CP_TIME],[SIDE_PROJ_TIME],[EXERCISE_TIME],[GAMES_TIME],[IS_SCHOOL_DAY],[EXIT_TIME],[AVLBLE_TIME],[WAISTED_TIME],[NOT_WAISTED_TIME]
                -[ID],[DATE],[ENTER_TIME],[STUDIED_TIME],[CP_TIME],[SIDE_PROJ_TIME],[EXERCISE_TIME],[GAMES_TIME],[IS_SCHOOL_DAY],[EXIT_TIME],[AVLBLE_TIME],[WAISTED_TIME],[NOT_WAISTED_TIME]
                -[ID],[DATE],[ENTER_TIME],[STUDIED_TIME],[CP_TIME],[SIDE_PROJ_TIME],[EXERCISE_TIME],[GAMES_TIME],[IS_SCHOOL_DAY],[EXIT_TIME],[AVLBLE_TIME],[WAISTED_TIME],[NOT_WAISTED_TIME]

*/