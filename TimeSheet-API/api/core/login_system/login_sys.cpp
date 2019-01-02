#include "login_sys.h"

void LoginSys::Init(Log* log, std::string user, std::string pass)
{
	this->_givenUser = user;
	this->_givenPass = pass;
	mLoggedIn = false;

	_Log = log;
	Login();
}

bool LoginSys::IsLogged()
{
	return mLoggedIn;
}

void LoginSys::ChangeCred(std::string oldUser, std::string oldPass, std::string newUser, std::string newPass)
{
	if (mLoggedIn &&
		(oldUser == _givenUser && oldPass == _givenPass)) {

		std::vector<std::string> data;
		int key = createKey();

		std::string user = crypt(newUser, key);
		std::string pass = crypt(newPass, key);

		data.push_back(user);
		data.push_back(pass);
		data.push_back(std::to_string(key));

		File_Manager files;
		files.Write(std::string(DATA_PATH) + "cred.info", data);
	}
	else {
		(*_Log) << "[LOGIN_SYS] UnRecognized Change of Credentials";
	}
}

void LoginSys::Login()
{
	File_Manager files;
	std::vector<std::string> read;
	files.Read(std::string(DATA_PATH) + "cred.info", &read);

	if (!read.empty()) {
		// creds avlble
		std::string user = decrypt(read[0], atoi(read[2].c_str()));
		std::string pass = decrypt(read[1], atoi(read[2].c_str()));

		if (_givenUser == user)
			if (_givenPass == user) {
				mLoggedIn = true;
				(*_Log) << "[LOGIN_SYS] Logged In";
				return;
			}

		(*_Log) << std::string("[LOGIN_SYS] User: ").append(_givenUser);
		(*_Log) << std::string("[LOGIN_SYS] Pass: ").append(_givenPass);
		(*_Log) << "[LOGIN_SYS] Loggin Failed!";
		(*_Log).flush(false);
		mLoggedIn = false;

	}
	else {
		// create creds
		createFile(std::string(DATA_PATH) + "cred.info");
		std::vector<std::string> data;
		int key = createKey();
		string User = crypt(_givenUser, key);
		string Pass = crypt(_givenPass, key);

		data.push_back(User);
		data.push_back(Pass);
		data.push_back(to_string(key));

		files.Write(std::string(DATA_PATH) + "cred.info", data);
		Login();
	}
}
