#ifndef _H_FILE_UTIL_H_
#define _H_FILE_UTIL_H_
#pragma once
#include "../misc/string_conv.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

static int fileExists(std::string  file) {
	std::ifstream ffs(file);
	return ffs.is_open();
}

static bool dirExists(const std::string& dirName_in) {
	struct stat info;
	if (stat(dirName_in.c_str(), &info) != 0) // might be a file
		return false;
	else if (info.st_mode & S_IFDIR) // it is a dir
		return true;
	else return false; // it is neither
}

static bool createFile(std::string str) {
	FILE *fp = fopen(str.c_str(), "w");
	return fp;
}

static bool createDir(std::string str) {
#ifdef _WINDOWS_
	mkdir(str);
#else
	mkdir(str.c_str(), 0755);
#endif
}

static bool deleteDir(std::string str) {
	return false;
}

static bool deleteFile(std::string str) {
	return remove(str.c_str());
}


#endif // !_H_FILE_UTIL_H_
