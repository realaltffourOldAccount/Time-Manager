#ifndef _H_LOG_H_
#define _H_LOG_H_

#pragma once
#include <vector>
#include <string>
#include <wx/wx.h>
#include "../time/Timer.h"
#include "../files/File_Manager.h"
#include "../misc/random_rework.h"

struct Log {

	std::vector<std::string> *_queue = nullptr;
	Timer *_timer = nullptr;

	wxListBox *_list = nullptr;

	Log(wxListBox *list = nullptr) {
		_list = list;
		_queue = new std::vector<std::string>();
		_timer = new Timer;
		_timer->Start();
	}

	void operator<<(const std::string str) {
		append(str);
	}

	void append(std::string str) {
		str += ", At ";
		str += to_string(_timer->get());
		str += "ms";
		_queue->push_back(str);

		if (_list != nullptr)
			_list->AppendString(str);
	}

	std::string get() {
		if (_queue->size() != 0)
			return (*_queue)[_queue->size() - 1];
		return "[LOG] Log Is Empty";
	}

	void clear(bool _flush = false) {
		_queue->clear();
		if (_flush)
			flush(false);
	}

	void flush(bool _clear = true) {
		File_Manager file;

		std::string str = "LogFile_";
		str.append(to_string(random(0, INT_MAX)));
		str.append(".txt");

		file.Write(str, *_queue);

		if (_clear)
			clear();
	}
};

#endif // !_H_LOG_H_
