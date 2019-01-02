#pragma once
#include <vector>
#include <string>
#include <wx/wx.h>

#include "../defines.h"
#include "../core/login_system/login_sys.h"
#include "../core/database_system/db_sys.h"
#include "../core/ranking_system/ranking_sys.h"

class API_driver
{
public:
	void Init(wxListBox *list = nullptr); // creates log, and db system, locks db
	void DeInit(); // deletes log,and db system, unlocks db


	bool VerifyDB(); // verify db files and syntax
	bool VerifyLoadedDB(); // verify loaded db values

	bool LoadDB(string user, string pass);	// login and loads and locks
	bool CreateDB(string user, string pass); // creates logins and doesnt load or lock

	string getLog() {
		return _log->get();
	}
	auto getLogSys() { return _log; }
	vector<string> getLogQueue() {
		return *_log->_queue;
	}
	auto getRank() { return ranking; }
	
	auto DB() {
		return sys;
	}

private:
	Log *_log = nullptr;
	DB_sys *sys = nullptr;
	Ranking_sys *ranking = nullptr;
};

