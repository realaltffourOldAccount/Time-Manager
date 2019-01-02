#pragma once
#include "config.h"
#include "../../defines.h"

class LoginSys
{
public:
	void Init(Log* log, std::string user = "", std::string pass = "");
	
	bool IsLogged();

	void ChangeCred(std::string oldUser, std::string oldPass, std::string newUser, std::string newPass);

private:
	void Login();

	bool mLoggedIn = false;

	std::string _givenUser = ""; // true if mLoggedIn = true
	std::string _givenPass = ""; // true if mLoggedIn = true

	Log *_Log = nullptr;

	int createKey() {
		return random(0, 26);
	}
	std::string crypt (std::string str, int key) {
		for (int i = 0; i < str.size(); i++)
			str[i] += key;
		return str;
	};
	std::string decrypt(std::string str, int key) {
		for (int i = 0; i < str.size(); i++)
			str[i] -= key;
		return str;
	}
};

/*
	Structure of login file:

	Name: cred.info
	Ex. Data:
	admin		// user
	admin123	// pass
	14			// key

*/