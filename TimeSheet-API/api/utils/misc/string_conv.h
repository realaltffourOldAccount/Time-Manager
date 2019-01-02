#ifndef _H_STRING_CONV_H_
#define _H_STRING_CONV_H_

#pragma once
#include <string>
#include <vector>

static std::wstring s2ws(const std::string &s) {
	std::wstring wsTmp(s.begin(), s.end());

	return wsTmp;
}

static std::string ws2s(const std::wstring &ws) {
	std::string sTmp(ws.begin(), ws.end());
	return sTmp;
}

static std::string v2s(const std::vector<std::vector<std::string> > &data) {
	std::string str;
	for (unsigned int i = 0; i < data.size(); i++)
		for (unsigned int j = 0; j < data[i].size(); j++)
			str.append(data[i][j]);

	return str;
}

#endif // !_H_STRING_CONV_H_
