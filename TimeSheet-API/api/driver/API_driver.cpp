#include "API_driver.h"

void API_driver::Init(wxListBox *list) {
    _log = new Log(list);
    sys = new DB_sys();
    sys->Init(_log);

    ranking = new Ranking_sys();
    ranking->Init(_log, sys);

    *_log << "[API] Init Success";
}
void API_driver::DeInit() {
    *_log << "[API] DeInitializing . . . ";
    delete _log;
    delete sys;
}

bool API_driver::VerifyDB() { return true; }
bool API_driver::VerifyLoadedDB() { return true; }

bool API_driver::LoadDB(string user, string pass) {
    if ((sys->IsThere() == false))  // first time start
        sys->CreateEmpty(user, pass);

    if (sys->IsEmpty() == false)
        if (sys->Load(user, pass)) {  // load the data, it is sure that it will
                                      // be present to load
            // calculations
            ranking->calc();
            sys->ReCalc();
        } else {
            sys->GetDataBase()->_entries = new vector<Entry>();
            return false;
        }
}
bool API_driver::CreateDB(string user, string pass) {
    return sys->CreateEmpty(user, pass);
}